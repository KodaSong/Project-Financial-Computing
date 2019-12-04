/*
 * @Author: Koda Song
 * @Date: 2019-11-28 23:03:15
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:53:22
 * @Description: 
 */

#include "stdafx.h"
#include "stock.h"

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
	int days = daily_return.size();
	for (int i = 0; i < days; i++)
		AR.push_back(daily_return[i] - spy_return[i]);
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

vector<double> Calculate_AAR(vector<stock>& stockList)
{
	int stock_nums = stockList.size();
	int days = stockList[0].daily_return.size();
	vector<double> AAR(days);
	for (int i = 0; i < days; i++)
	{
		double res = 0.0;
		for (int j = 0; j < stock_nums; j++)
		{
			res += stockList[j].daily_return[i];		// the ith daily return of the jth stock
		}
		AAR[i] = res / stock_nums;	// Average Value for the ith day
	}
	return AAR;
}

double Calculate_CAAR(vector<stock>& stockList)
{
	vector<double> AAR = Calculate_AAR(stockList);
	int days = AAR.size();
	double result = 0.0;
	for (int i = 0; i < days; i++)
		result += AAR[i];
	return result;
}

map<string, stock> stock_map(vector<stock>& stockList)
{
	map<string, stock> my_map;
	vector<stock>::iterator itr;
	for (itr = stockList.begin(); itr != stockList.end(); itr++)
		my_map[itr->name] = *itr;
	
	return my_map;
}