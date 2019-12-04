/*
 * @Author: Koda Song
 * @Date: 2019-11-28 23:03:15
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:52:27
 * @Description: 
 */
#pragma once
#include"stdafx.h"
#include <iostream>
#include <sstream> 
#include <fstream>
 //#include "ExcelDriver\ExcelDriver.hpp"

#include "RetrieveData.h"

using namespace std;

int write_data(void *ptr, int size, int nmemb, FILE *stream)
{	// ptr -- the address of the element written; size -- size of every element; nmemb -- number of elements
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}
struct MemoryStruct {
	char *memory;
	size_t size;
};
void *myrealloc(void *ptr, size_t size)
{	if (ptr)
		return realloc(ptr, size);	// reallocate the size of the pointer
	else
		return malloc(size);
}
int write_data2(void *ptr, size_t size, size_t nmemb, void *data)
{	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;
	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

string getTimeinSeconds(string Time)
{
	std::tm t = {0};
    std::istringstream ssTime(Time);	// let ssTime stores the "information" in Time
	char time[100];
	memset(time, 0, 100);	// memory set, void *memset(void *s, int ch, size_t n);
    if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))	// use t to store ssTime
    {
        //cout << std::put_time(&t, "%c %Z") << "\n"	// %c -- date and time; %Z -- name of time zone
        //          << std::mktime(&t) << "\n";	// transfer t into seconds from 1970
		sprintf (time, "%lld", mktime(&t));
		return string(time);
    }
    else
    {
        cout << "Parse failed\n";
		return "";
    }
}

string getStartinSeconds(string Time)	// Time is the announcement date. Use it to get Start time
{
	std::tm t = { 0 };
	std::istringstream ssTime(Time);	// let ssTime stores the "information" in Time
	char time[100];
	memset(time, 0, 100);	// memory set, void *memset(void *s, int ch, size_t n);
	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))	// use t to store ssTime
	{
		sprintf(time, "%lld", mktime(&t)-50*24*60*60);	// mktime(&t) -> transfer t into seconds from 1970
		return string(time);	// 30days * 24hrs * 3600scs
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}

string getEndinSeconds(string Time)	// Time is the announcement date. Use it to get End time
{
	std::tm t = { 0 };
	std::istringstream ssTime(Time);	// let ssTime stores the "information" in Time
	char time[100];
	memset(time, 0, 100);	// memory set, void *memset(void *s, int ch, size_t n);
	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))	// use t to store ssTime
	{
		sprintf(time, "%lld", mktime(&t) + 50 * 24 * 60 * 60);	// mktime(&t) -> transfer t into seconds from 1970
		return string(time);	// 30days * 24hrs * 3600scs
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}

time_t convert_string_to_time_t(const std::string& time_string)
{
	struct tm tm1;
	time_t time1;
	int i = sscanf_s(time_string.c_str(), "%d/%d/%d %d:%d:%d",
		&(tm1.tm_year),
		&(tm1.tm_mon),
		&(tm1.tm_mday),
		&(tm1.tm_hour),
		&(tm1.tm_min),
		&(tm1.tm_sec),
		&(tm1.tm_wday),
		&(tm1.tm_yday));

	tm1.tm_year -= 1900;
	tm1.tm_mon--;
	tm1.tm_isdst = -1;
	time1 = mktime(&tm1);

	return time1;
}

void split_string(string& line, vector<string>& vec_date, vector<double>& vec_vol, vector<double>& vec_adj,
	vector<double>& vec_close, vector<double>& vec_low, vector<double>& vec_high, vector<double>& vec_open)
{
	vec_date.push_back(line.substr(0, line.find_first_of(',')));
	vec_vol.push_back(stod(line.substr(line.find_last_of(',') + 1)));
	line.erase(line.find_last_of(','));
	vec_adj.push_back(stod(line.substr(line.find_last_of(',') + 1)));
	line.erase(line.find_last_of(','));
	vec_close.push_back(stod(line.substr(line.find_last_of(',') + 1)));
	line.erase(line.find_last_of(','));
	vec_low.push_back(stod(line.substr(line.find_last_of(',') + 1)));
	line.erase(line.find_last_of(','));
	vec_high.push_back(stod(line.substr(line.find_last_of(',') + 1)));
	line.erase(line.find_last_of(','));
	vec_open.push_back(stod(line.substr(line.find_last_of(',') + 1)));
	line.erase(line.find_last_of(','));
}

int GetData(vector<stock> & stockList, stock &spy)
{
	vector<stock>::iterator itr = stockList.begin();

	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	// file pointer to create file that store the data  
	FILE *fp;

	// name of files  
	const char outfilename[FILENAME_MAX] = "Output.txt";
	const char resultfilename[FILENAME_MAX] = ".\\in_out\\Output_PricesSP500.txt";

    // declaration of an object CURL 
    CURL *handle;                   

    CURLcode result;              

    // set up the program environment that libcurl needs 
    curl_global_init(CURL_GLOBAL_ALL);
    
	// curl_easy_init() returns a CURL easy handle 
    handle = curl_easy_init();

    // if everything's all right with the easy handle... 
	if (handle)
	{
		while (true)
		{
			string sCookies, sCrumb;	// crumb is what we don't need
			if (sCookies.length() == 0 || sCrumb.length() == 0)
			{
				fp = fopen(outfilename, "w");
				//curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history?p=AMZN");
				curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");

				curl_easy_setopt(handle, CURLOPT_ENCODING, "");
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
				result = curl_easy_perform(handle);
				fclose(fp);

				if (result != CURLE_OK)
				{
					// if errors have occurred, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);

				// perform, then store the expected code in result
				result = curl_easy_perform(handle);

				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				char cKey[] = "CrumbStore\":{\"crumb\":\"";
				char *ptr1 = strstr(data.memory, cKey);
				char *ptr2 = ptr1 + strlen(cKey);
				char *ptr3 = strstr(ptr2, "\"}");
				if ( ptr3 != NULL )
					*ptr3 = NULL;

				sCrumb = ptr2;

				fp = fopen("cookies.txt", "r");
				char cCookies[100];
				if (fp) {
					while (fscanf(fp, "%s", cCookies) != EOF);
					fclose(fp);
				}
				else
					cerr << "cookies.txt does not exists" << endl;

				sCookies = cCookies;
				free(data.memory);
				data.memory = NULL;
				data.size= 0;
			}
			
			if (itr == stockList.end())
				break;

			cout << "Retrieve " << itr->name << endl;

			string day0 = itr->announcement_day + "T16:00:00";
			string startTime = getStartinSeconds(day0);
			string endTime = getEndinSeconds(day0);

			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string symbol = itr->name;
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";
			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char * cURL = url.c_str();
			const char * cookies = sCookies.c_str();
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
			curl_easy_setopt(handle, CURLOPT_URL, cURL);
			fp = fopen(resultfilename, "ab");
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			result = curl_easy_perform(handle);
			fclose(fp);
			
			// Check for errors */
			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with 'result'
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			stringstream sData;
			sData.str(data.memory);
			string sDate, line;
			getline(sData, line);

			vector<string> vec_date;
			vector<double> vec_vol, vec_adj, vec_close, vec_low, vec_high, vec_open;
			while ( getline(sData, line) ) {	// let the string in "sData" transit to "line"
				//cout << line << endl;	// cout is for test; formal projects will delete
				sDate = line.substr(0, line.find_first_of(','));
				vec_date.push_back(sDate);	

				/*str.find_last_of(',') -> return the biggest index of ','
				str.substr(index) -> return the substr from the index to the last
				stod -> transfer the string into double*/ 
				vec_vol.push_back(stod(line.substr(line.find_last_of(',') + 1)));
				line.erase(line.find_last_of(','));		// line.erase(index) -> erase the substr from the index
				vec_adj.push_back(stod(line.substr(line.find_last_of(',') + 1)));
				line.erase(line.find_last_of(','));
				vec_close.push_back(stod(line.substr(line.find_last_of(',') + 1)));
				line.erase(line.find_last_of(','));
				vec_low.push_back(stod(line.substr(line.find_last_of(',') + 1)));
				line.erase(line.find_last_of(','));
				vec_high.push_back(stod(line.substr(line.find_last_of(',') + 1)));
				line.erase(line.find_last_of(','));
				vec_open.push_back(stod(line.substr(line.find_last_of(',') + 1)));
				line.erase(line.find_last_of(','));
			}

			// Find the index of announcement date in vec_date
			vector<string>::iterator itr_date;
			itr_date = find(vec_date.begin(), vec_date.end(), itr->announcement_day);
			int nindex = distance(vec_date.begin(), itr_date);	// The index of day0
			int start_index = nindex - 30;	// The index of day-30
			int end_index = nindex + 30;	// The index of day30

			// Push the data of day-30 to day30 into object
			for (int i = start_index; i < end_index + 1; i++)
			{
				itr->datetime.push_back(vec_date[i]);
				itr->volumn.push_back(vec_vol[i]);
				itr->adj_close.push_back(vec_adj[i]);
				itr->close.push_back(vec_close[i]);
				itr->low.push_back(vec_low[i]);
				itr->high.push_back(vec_high[i]);
				itr->open.push_back(vec_open[i]);
			}

			// Directly use adjust close price to get "daily return" vector
			itr->daily_return = Calculate_Return(itr->adj_close);

			itr->GetSPYADJ(spy);	// Transfer SPY's adj_close into vector "spy_adj"
			itr->spy_return = Calculate_Return(itr->spy_adj);	// Calculate SPY Daily Return

			itr->Calulate_AR();		// daily_return - spy_return

			itr++;
			//cout << "-------------------------------------------------------------------------------" << endl;
		}
		free(data.memory);
		data.size= 0;
	}
    else 
    {
            fprintf(stderr, "Curl init failed!\n");
            return 1;
    }

    // cleanup since you've used curl_easy_init  
    curl_easy_cleanup(handle);

    // release resources acquired by curl_global_init() 
    curl_global_cleanup();
	
    return 0;
}

int GetSPYData(stock& spy)
{
	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	// file pointer to create file that store the data  
	FILE* fp;

	// name of files  
	const char outfilename[FILENAME_MAX] = "OutputSPY.txt";
	//const char resultfilename[FILENAME_MAX] = "Results.txt";
	const char resultfilename[FILENAME_MAX] = ".\\in_out\\Output_PricesSPY.txt";

	// declaration of an object CURL 
	CURL* handle;

	CURLcode result;

	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();

	// if everything's all right with the easy handle... 
	if (handle)
	{
		string sCookies, sCrumb;	// crumb is what we don't need
		if (sCookies.length() == 0 || sCrumb.length() == 0)
		{
			fp = fopen(outfilename, "w");
			//curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/SPY/history?p=AMZN");
			curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/SPY/history");
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
			curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
			curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");

			curl_easy_setopt(handle, CURLOPT_ENCODING, "");
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			result = curl_easy_perform(handle);
			fclose(fp);

			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)& data);

			// perform, then store the expected code in result
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				// if errors have occured, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			char cKey[] = "CrumbStore\":{\"crumb\":\"";
			char* ptr1 = strstr(data.memory, cKey);
			char* ptr2 = ptr1 + strlen(cKey);
			char* ptr3 = strstr(ptr2, "\"}");
			if (ptr3 != NULL)
				* ptr3 = NULL;

			sCrumb = ptr2;

			fp = fopen("cookies.txt", "r");
			char cCookies[100];
			if (fp) {
				while (fscanf(fp, "%s", cCookies) != EOF);
				fclose(fp);
			}
			else
				cerr << "cookies.txt does not exists" << endl;

			sCookies = cCookies;
			free(data.memory);
			data.memory = NULL;
			data.size = 0;
		}

		string startTime = getTimeinSeconds("2019-02-01T16:00:00");		// The earliest announcement date is 2019-04-02
		string endTime = getTimeinSeconds("2019-08-30T16:00:00");		// The latest announcement date is 2019-06-27
		string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
		string symbol = "SPY";
		string urlB = "?period1=";
		string urlC = "&period2=";
		string urlD = "&interval=1d&events=history&crumb=";
		string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
		const char* cURL = url.c_str();
		const char* cookies = sCookies.c_str();
		curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
		curl_easy_setopt(handle, CURLOPT_URL, cURL);
		fp = fopen(resultfilename, "ab");
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
		result = curl_easy_perform(handle);
		fclose(fp);

		// Check for errors */
		if (result != CURLE_OK)
		{
			// if errors have occurred, tell us what is wrong with 'result'
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}
		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)& data);
		result = curl_easy_perform(handle);

		if (result != CURLE_OK)
		{
			// if errors have occurred, tell us what is wrong with result
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}

		stringstream sData;
		sData.str(data.memory);
		string sDate;
		double adj;
		string line;
		getline(sData, line);
		while (getline(sData, line)) {	// let the string in "sData" transit to "line"
			//cout << line << endl;
			sDate = line.substr(0, line.find_first_of(','));
			spy.datetime.push_back(sDate);

			/*str.find_last_of(',') -> return the biggest index of ','
			str.substr(index) -> return the substr from the index to the last
			stod -> transfer the string into double*/
			spy.volumn.push_back(stod(line.substr(line.find_last_of(',') + 1)));
			line.erase(line.find_last_of(','));		// line.erase(index) -> erase the substr from the index
			adj = stod(line.substr(line.find_last_of(',') + 1));
			spy.adj_close.push_back(adj);
			line.erase(line.find_last_of(','));
			spy.close.push_back(stod(line.substr(line.find_last_of(',') + 1)));
			line.erase(line.find_last_of(','));
			spy.low.push_back(stod(line.substr(line.find_last_of(',') + 1)));
			line.erase(line.find_last_of(','));
			spy.high.push_back(stod(line.substr(line.find_last_of(',') + 1)));
			line.erase(line.find_last_of(','));
			spy.open.push_back(stod(line.substr(line.find_last_of(',') + 1)));
			line.erase(line.find_last_of(','));

			spy.my_map[sDate] = adj;
		}
		//cout << "-------------------------------------------------------------------------------" << endl;

		free(data.memory);
		data.size = 0;
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	// cleanup since you've used curl_easy_init  
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init() 
	curl_global_cleanup();

	return 0;
}


// Only download data from Yahoo Finance and store it in file without any calculation!
int Download_Data(vector<stock>& stockList)
{
	vector<stock>::iterator itr = stockList.begin();

	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	// file pointer to create file that store the data  
	FILE* fp;

	// name of files  
	const char outfilename[FILENAME_MAX] = "Output.txt";
	const char resultfilename[FILENAME_MAX] = ".\\in_out\\Output_PricesSP500.txt";

	// declaration of an object CURL 
	CURL* handle;

	CURLcode result;

	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();

	// if everything's all right with the easy handle... 
	if (handle)
	{
		while (true)
		{
			string sCookies, sCrumb;	// crumb is what we don't need
			if (sCookies.length() == 0 || sCrumb.length() == 0)
			{
				fp = fopen(outfilename, "w");
				//curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history?p=AMZN");
				curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");

				curl_easy_setopt(handle, CURLOPT_ENCODING, "");
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
				result = curl_easy_perform(handle);
				fclose(fp);

				if (result != CURLE_OK)
				{
					// if errors have occurred, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)& data);

				// perform, then store the expected code in result
				result = curl_easy_perform(handle);

				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				char cKey[] = "CrumbStore\":{\"crumb\":\"";
				char* ptr1 = strstr(data.memory, cKey);
				char* ptr2 = ptr1 + strlen(cKey);
				char* ptr3 = strstr(ptr2, "\"}");
				if (ptr3 != NULL)
					* ptr3 = NULL;

				sCrumb = ptr2;

				fp = fopen("cookies.txt", "r");
				char cCookies[100];
				if (fp) {
					while (fscanf(fp, "%s", cCookies) != EOF);
					fclose(fp);
				}
				else
					cerr << "cookies.txt does not exists" << endl;

				sCookies = cCookies;
				free(data.memory);
				data.memory = NULL;
				data.size = 0;
			}

			if (itr == stockList.end())
				break;

			cout << "Retrieve " << itr->name << endl;

			string day0 = itr->announcement_day + "T16:00:00";
			string startTime = getStartinSeconds(day0);
			string endTime = getEndinSeconds(day0);
			
			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string symbol = itr->name;
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";
			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char* cURL = url.c_str();
			const char* cookies = sCookies.c_str();
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);   // Only needed for 1st stock
			curl_easy_setopt(handle, CURLOPT_URL, cURL);
			fp = fopen(resultfilename, "ab");
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
			result = curl_easy_perform(handle);
			fclose(fp);

			// Check for errors */
			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with 'result'
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}
			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)& data);
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with result
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			stringstream sData;
			sData.str(data.memory);
			string sDate, line;
			getline(sData, line);

			while (getline(sData, line));

			itr++;
			//cout << "-------------------------------------------------------------------------------" << endl;
		}
		free(data.memory);
		data.size = 0;
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	// cleanup since you've used curl_easy_init  
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init() 
	curl_global_cleanup();

	return 0;
}