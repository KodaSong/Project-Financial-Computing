#pragma once
#ifndef ReadFile_h
#define ReadFile_h

/*
 * @Author: Koda Song
 * @Date: 2019-12-01 03:33:04
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-02 10:23:52
 * @Description: 
 */

#include <vector>
#include <string>
#include "stock.h"
#include "RetrieveData.h"

// Get ticker list, announcement date, eps information from file (Bloomberg)
vector<stock> Get_EPS(string filename);

// Read data in txt file alreadyed downloaded from Yahoo Finance
void GetPriceData_txt(vector<stock> &stockList, string filename, stock& spy);

// Split line and push date and every price into vector
//void split_string(string& line, vector<string>& vec_date, vector<double>& vec_vol, vector<double>& vec_adj,
//	vector<double>& vec_close, vector<double>& vec_low, vector<double>& vec_high, vector<double>& vec_open);

// Push information of these vectors into itr, from index1 to index2 + 1
//void price_push(stock* itr, int index1, int index2, vector<string>& vec_date, 
//	vector<double>& vec_vol, vector<double>& vec_adj, vector<double>& vec_close, 
//	vector<double>& vec_low, vector<double>& vec_high, vector<double>& vec_open)

#endif // !ReadFile_h



