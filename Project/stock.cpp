/*
 * @Author: Koda Song
 * @Date: 2019-11-28 23:03:15
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:53:22
 * @Description: 
 */

#include "stdafx.h"
#include "Stock.h"
#include "Display.h"


void stock::GetSPYADJ(stock& spy)
{
	int days = datetime.size();
	for (int i = 0; i < days; i++)
	{
		string date = datetime[i];
		spy_adj.push_back(spy.my_map[date]);
	}
}

void stock::Calulate_AR()
{
	AR = daily_return - spy_return;
}

void stock::PrintAllInfo()
{
	cout << "name: " << name << endl;
	cout << endl;
	cout << "Announcement Date: " << announcement_day << endl;
	cout << endl;
	cout << "Estimated EPS: " << EPS_Estimate << endl;
	cout << endl;
	cout << "Actual EPS: " << EPS_Actual << endl;
	cout << endl;
	cout << "surprise: " << surprise << endl;
	cout << endl;

	cout << "adj_close prices: " << endl;
	display_vec2(adj_close);

	cout << "daily returns: " << endl;
	display_vec(daily_return);
}

vector<double> Calculate_Return(vector<double>& price)
{
	double a, b, r = 0.0;
	vector<double> vec;
	vector<double>::iterator itr;
	for (itr = price.begin(); itr != price.end()-1; itr++)
	{
		a = *(itr + 1);	// next day's price
		b = *itr;	// this day's price
		r = (a - b) / b;	// daily return
		vec.push_back(r);
	}
	return vec;
}

map<string, stock> stock_map(vector<stock>& stockList)
{
	map<string, stock> my_map;
	vector<stock>::iterator itr;
	for (itr = stockList.begin(); itr != stockList.end(); itr++)
		my_map[itr->name] = *itr;
	
	return my_map;
}