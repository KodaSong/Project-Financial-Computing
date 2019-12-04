/*
 * @Author: Koda Song
 * @Date: 2019-11-29 15:40:02
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:52:44
 * @Description: 
 */
#pragma once
#ifndef Repeat_h
#define Repeat_h

#include "GroupStocks.h"
#include <list>
using namespace std;

class Repeat30
{
public:
	Group group;	// This should be our total companies with 3 groups
	double Beat_Expected_CAAR = 0.0;
	double Beat_std_CAAR = 0.0;
	double Meet_Expected_CAAR = 0.0;
	double Meet_std_CAAR = 0.0;
	double Miss_Expected_CAAR = 0.0;
	double Miss_std_CAAR = 0.0;

	vector<double> Beat_Expected_AAR;
	vector<double> Beat_std_AAR;
	vector<double> Meet_Expected_AAR;
	vector<double> Meet_std_AAR;
	vector<double> Miss_Expected_AAR;
	vector<double> Miss_std_AAR;

	Repeat30(Group group_) : group(group_) {}	// Constructor
	void Mean();	// Calculate expected value of AAR and CAAR
	void Std();		// Calculate standard deviation of AAR and CAAR;	Std() must be implemented after Mean()
};


#endif // !Repeat_h
