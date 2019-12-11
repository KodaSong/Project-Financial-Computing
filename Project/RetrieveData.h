/*
 * @Author: Koda Song
 * @Date: 2019-11-28 23:03:15
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:53:05
 * @Description: 
 */
#pragma once
#ifndef RetrieveData_h
#define RetrieveData_h

#include"stdafx.h"
#include <string> 
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <iomanip>
#include <vector>
#include <locale>
#include <locale>
#include <locale.h>
#include <algorithm>
#include <thread>
#include <numeric>

#include "curl.h"
#include "stock.h"
#include "RetrieveData.h"

using namespace std;
using std::locale;

// Get Price data from Yahoo Finance
int GetData(vector<stock>& stocklist, stock& spy, vector<stock>::iterator start, vector<stock>::iterator end);

// Get SPY's Price data from Yahoo Finance
int GetSPYData(stock& spy);

// Use multi thread to run "GetData"
void multi_thread(vector<stock>& stockList, stock& spy);

// Only download data from Yahoo Finance and store it in file without any calculation!
int Download_Data(vector<stock>& stockList);

time_t convert_string_to_time_t(const std::string& time_string);

static int convert_time_t_to_string(std::string& strDateStr, const time_t& timeData)
{
	char chTmp[40];
	memset(chTmp, 0, sizeof(chTmp));

	struct tm* p;
	p = localtime(&timeData);
	p->tm_year = p->tm_year + 1900;
	p->tm_mon = p->tm_mon + 1;
	snprintf(chTmp, sizeof(chTmp), "%04d-%02d-%02d-%02d:%02d:%02d",
		p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

	strDateStr = chTmp;
	return 0;
};

// Split line and push date and every price into vector
void split_string(string& line, vector<string>& vec_date, vector<double>& vec_vol, vector<double>& vec_adj,
	vector<double>& vec_close, vector<double>& vec_low, vector<double>& vec_high, vector<double>& vec_open);


#endif // !RetrieveData_h