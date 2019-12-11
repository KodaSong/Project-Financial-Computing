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

using namespace std;

class Repeat30
{
public:
	Repeat30(Group group_) : group(group_) {}	// Parameter Constructor
	void Calculation();	// Calculate each group's Mean and std of AAR and CAAR
	void PrintGroupInfo(int& groupname, int& valuename);	// print information of choosen group and value

	Group group;	// This should be our total companies with 3 groups

	Vector_ Beat_Expected_AAR;
	Vector_ Beat_std_AAR;
	Vector_ Meet_Expected_AAR;
	Vector_ Meet_std_AAR;
	Vector_ Miss_Expected_AAR;
	Vector_ Miss_std_AAR;

	Vector_ Beat_Expected_CAAR;
	Vector_ Beat_std_CAAR;
	Vector_ Meet_Expected_CAAR;
	Vector_ Meet_std_CAAR;
	Vector_ Miss_Expected_CAAR;
	Vector_ Miss_std_CAAR;

	// We use a matrix to store 30 AAR vectors -> used for Mean and SD of AAR
	Matrix_ M_Beat_AAR;	
	Matrix_ M_Beat_std_AAR;
	Matrix_ M_Meet_AAR;
	Matrix_ M_Meet_std_AAR;
	Matrix_ M_Miss_AAR;
	Matrix_ M_Miss_std_AAR;

	Matrix_ M_Beat_CAAR;
	Matrix_ M_Beat_std_CAAR;
	Matrix_ M_Meet_CAAR;
	Matrix_ M_Meet_std_CAAR;
	Matrix_ M_Miss_CAAR;
	Matrix_ M_Miss_std_CAAR;

	
};


#endif // !Repeat_h
