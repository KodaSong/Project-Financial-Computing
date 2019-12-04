/*
 * @Author: Koda Song
 * @Date: 2019-11-28 23:03:15
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:53:34
 * @Description: 
 */
#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>

using namespace std;


class stock {
public:
	string name;
	string announcement_day;
	double EPS_Estimate; // Estimate Earning per share
	double EPS_Actual; // Actual Earning per share
	double surprise;	// Calculate surprise for EPS

	vector<string> datetime;
	vector<double> open;
	vector<double> high;
	vector<double> low;
	vector<double> close;
	vector<double> adj_close;
	vector<double> volumn;
	vector<double> daily_return;
	vector<double> spy_adj;		// SPY's adjust close price
	vector<double> spy_return;	// Market Daily Return based on SPY
	vector<double> AR;		// Abnormal Daily Return -> daily_return - spy_return 

	map<string, double> my_map;		// Only used for stock SPY

	void GetSPYADJ(stock& spy);		// transit SPY's adjust close price into this stock
	void Calulate_AR();		// Stock's Daily Return - SPY's Daily Return 
};

vector<double> Calculate_Return(vector<double> &price);	// Calculate Daily Return -> return a double vector

//vector<double> Calculate_AAR(vector<stock>& stockList);	// return a vector to store AARt
//double Calculate_CAAR(vector<stock>& stockList);	// return a Value -> Cumulative AAR

// Create a stockmap -> Use tickers to search its information
map<string, stock> stock_map(vector<stock>& stockList);	// used to retrieving stock's information based on its name