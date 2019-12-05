/*
 * @Author: Koda Song
 * @Date: 2019-12-01 03:33:30
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-02 10:23:40
 * @Description: 
 */
#include "stdafx.h"
#include "ReadFile.h"
#include <iostream>
#include <sstream> 
#include <fstream>


vector<stock> Get_EPS(string filename)
{
	// read csv
	ifstream inFile(filename, ios::in);
	string line;

	vector<stock> stockList;

	getline(inFile, line);	// This is the head of the chart, "Ticker"  "Date"  "Period"  "Actual"  "Estimate"
	//cout << line << endl;
	while (getline(inFile, line))	// getline is from <sstream>
	{
		//cout << line << endl;

		stock mystock;	// new an object to store the information of this stock

		mystock.name = line.substr(0, line.find_first_of(','));
		mystock.EPS_Estimate = stod(line.substr(line.find_last_of(',') + 1));
		line.erase(line.find_last_of(','));
		mystock.EPS_Actual = stod(line.substr(line.find_last_of(',') + 1));
		line.erase(line.find_last_of(','));

		mystock.surprise = (mystock.EPS_Actual - mystock.EPS_Estimate) / mystock.EPS_Estimate;

		line.erase(line.find_last_of(','));		// We don't need "Period", delete

		mystock.announcement_day = line.substr(line.find_last_of(',') + 1);
		line.erase(line.find_last_of(','));

		stockList.push_back(mystock);	// push "mystock" into our stock list
	}

	return stockList;
}

void GetPriceData_txt(vector<stock>& stockList, string filename, stock &spy)
{
	// transit "filename" into inFile
	ifstream inFile(filename, ios::in);
	string line;

	vector<stock>::iterator itr = stockList.begin(); 
	getline(inFile, line);	// This is the head of the chart, "Ticker"  "Date"  "Period"  "Actual"  "Estimate"
	while (itr != stockList.end())
	{	
		cout << "Read " << itr->name << endl;
		
		vector<string> vec_date;
		vector<double> vec_vol, vec_adj, vec_close, vec_low, vec_high, vec_open;
		while (getline(inFile, line))
		{
			if (line.substr(line.find_last_of(',') + 1) != "Volume")
			{
				//cout << line << endl;
				split_string(line, vec_date, vec_vol, vec_adj, vec_close, vec_low, vec_high, vec_open);
			}
			else
				break;
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

	}

}

