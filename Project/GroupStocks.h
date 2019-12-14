/*
 * @Author: Koda Song
 * @Date: 2019-11-29 10:03:13
 * @LastEditors: Suki
 * @LastEditTime: 2019-12-11 12:46:55
 * @Description: Divide SP500 companies into 3 groups based on EPS surprise
 */
#pragma once
#ifndef GroupStocks_h
#define GroupStocks_h

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Stock.h"

// Each Group object has 3 child groups, Beat, Meet, Miss
class Group
{
public:
	vector<stock> Beat;		// Group's Beat is the total Beat companies in SP500; samplegroup's Beat is just 30 stocks;
	vector<stock> Meet;
	vector<stock> Miss;

	Vector_ Beat_AAR;		// Store Group Beat's AAR from day-30 to day30
	Vector_ Meet_AAR;	// Store Group Meet's AAR from day-30 to day30
	Vector_ Miss_AAR;		// Store Group Miss's AAR from day-30 to day30

	Vector_ Beat_CAAR;
	Vector_ Meet_CAAR;
	Vector_ Miss_CAAR;

};

// Compare Function; Overload '>', so sort the map in a descending order
double cmp(const pair<string, double>& x, const pair<string, double>& y);	

// Sort Map By Value; tVector is used to store the already sorted elements in tMap
void sortMapByValue(map<string, double>& tMap, vector<pair<string, double> >& tVector);

// Group our stocklist into 3 -> Beat, Meet, Miss -> return a Group object with 3 vector<stock>
void group_stocks(vector<stock>& stockList, Group &stockgroup);

// Return an object with 3 groups -> Each randomly select 30 stocks
Group SampleStocks(Group& group);

// Calculate each group's AAR from day-30 to day30
void Cal_AAR(Group& samplegroup);

// Calculate each group's CAAR from day-30 to day30
void Cal_CAAR(Group& samplegroup);

#endif // !GroupStocks_h