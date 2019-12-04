/*
 * @Author: Koda Song
 * @Date: 2019-11-29 14:58:51
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:51:56
 * @Description: 
 */
#pragma once
#ifndef ReadFile_h
#define ReadFile_h

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



