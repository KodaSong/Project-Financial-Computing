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

/*  Get ticker list, announcement date, eps information from file (Bloomberg)
	filename could be file in current working space -> "Input_SP500.txt"
	filename could be file in relative or absolute working space -> ".\\Data\\Input_SP500.txt" */
vector<stock> Get_EPS(string filename);

//	Read data in txt file already downloaded from Yahoo Finance
void GetPriceData_txt(vector<stock> &stockList, string filename, stock& spy);



#endif // !ReadFile_h



