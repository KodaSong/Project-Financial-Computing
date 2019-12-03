#pragma once
#ifndef GroupStocks_h
#define GroupStocks_h

/*
 * @Author: Koda Song
 * @Date: 2019-11-29 10:03:13
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-02 10:22:45
 * @Description: 
 */

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "stock.h"

/*
	Map cannot directly sort by value. 
	So We first put map's elements (pair) into vector, and then sort it.
*/

// Each Group object has 3 child groups, Beat, Meet, Miss
class Group
{
public:
	vector<stock> Beat;		// Group's Beat is the total Beat companies in SP500; samplegroup's Beat is just 30 stocks;
	vector<stock> Meet;
	vector<stock> Miss;

	vector<double> Beat_AAR;		// Store Group Beat's AAR from day-30 to day30
	vector<double> Meet_AAR;	// Store Group Meet's AAR from day-30 to day30
	vector<double> Miss_AAR;		// Store Group Miss's AAR from day-30 to day30

	double Beat_CAAR = 0.0;
	double Meet_CAAR = 0.0;
	double Miss_CAAR = 0.0;

	//Group *samplegroup;		// This is sample stock group -> to store the selected 30*3 stocks
	//Group * SampleStocks(int n);	// Randomly select 30 stocks for each group
	//void Cal_C_AAR(Group* samplegroup);		// Calculate each group's AAR from day-30 to day30 and CAAR
};

// Compare Function; Overload '>', so sort the map in a descending order
double cmp(const pair<string, double>& x, const pair<string, double>& y);	

// Sort Map By Value; tVector is used to store the already sorted elements in tMap
void sortMapByValue(map<string, double>& tMap, vector<pair<string, double> >& tVector);

// Group our stocklist into 3 -> Beat, Meet, Miss -> return a Group object with 3 vector<stock>
void group_stocks(vector<stock>& stockList, Group &stockgroup);

// Return an object with 3 groups -> Each randomly select 30 stocks
Group SampleStocks(Group& group, int n);

// Calculate each group's AAR from day-30 to day30 and CAAR
void Cal_C_AAR(Group& samplegroup);


#endif // !GroupStocks_h