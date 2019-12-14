/*
 * @Author: Koda Song
 * @Date: 2019-11-28 23:03:15
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:53:34
 * @Description: Create a class stock to store SP500 companies information
 */
#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>
#include "Operator.h"

using namespace std;

class stock {
public:
	string name;
	string announcement_day;
	double EPS_Estimate; // Estimate Earning per share
	double EPS_Actual; // Actual Earning per share
	double surprise;	// Calculate surprise for EPS

	vector<string> datetime;
	Vector_ open;
	Vector_ high;
	Vector_ low;
	Vector_ close;
	Vector_ adj_close;
	Vector_ volumn;
	Vector_ daily_return;
	Vector_ spy_adj;		// Date matched SPY's adjust close price
	Vector_ spy_return;	// Market Daily Return based on SPY
	Vector_ AR;		// Abnormal Daily Return -> daily_return - spy_return 

	map<string, double> my_map;		// Only used for stock SPY

	void GetSPYADJ(stock& spy);		// transit SPY's adjust close price into this stock
	void Calulate_AR();		// Stock's Daily Return - SPY's Daily Return 
	void PrintAllInfo(); // print all information for one stock
};

// Calculate Daily Return -> return a double vector
Vector_ Calculate_Return(vector<double> &price);	


// Create a stockmap -> Use tickers as the key to search its information
map<string, stock> stock_map(vector<stock>& stockList);