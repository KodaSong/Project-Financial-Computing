/*
 * @Author: Koda Song
 * @Date: 2019-11-29 16:25:45
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-02 10:24:09
 * @Description: 
 */
#include "stdafx.h"
#include "Repeat.h"
#include <cmath>

void Repeat30::Mean()
{
	int days = 60;
	vector<double> vec1(days), vec2(days), vec3(days);
	for (int i = 0; i < 30; i++)	// Repeat 30 times
	{
		Group samplegroup = SampleStocks(group, i);	// generate sample groups 30*3
		Cal_C_AAR(samplegroup);		// generate CAAR(value)

		// Calculate Expected Value of CAAR first
		Beat_Expected_CAAR = (i / (i + 1.0)) * Beat_Expected_CAAR + samplegroup.Beat_CAAR / (i + 1.0);
		Meet_Expected_CAAR = (i / (i + 1.0)) * Meet_Expected_CAAR + samplegroup.Meet_CAAR / (i + 1.0);
		Miss_Expected_CAAR = (i / (i + 1.0)) * Miss_Expected_CAAR + samplegroup.Miss_CAAR / (i + 1.0);

		// Calculate sum of AAR at each day
		for (int j = 0; j < days; j++)
		{
			vec1[j] += samplegroup.Beat_AAR[j];
			vec2[j] += samplegroup.Meet_AAR[j];
			vec3[j] += samplegroup.Miss_AAR[j];
		}
	}

	for (int d = 0; d < days; d++)
	{	// Average Value for each day
		Beat_Expected_AAR.push_back(vec1[d]/30);	
		Meet_Expected_AAR.push_back(vec2[d] / 30);
		Miss_Expected_AAR.push_back(vec3[d] / 30);
	}		

}

void Repeat30::Std()
{
	int days = 60;
	double val1 = 0.0, val2 = 0.0, val3 = 0.0;
	vector<double> vec1(days), vec2(days), vec3(days);
	for (int i = 0; i < 30; i++)	// Repeat 30 times
	{
		Group samplegroup = SampleStocks(group, i);	// The seed is the same as Mean(), so the series should be totally same
		Cal_C_AAR(samplegroup);		// generate AAR(vector) and CAAR(value)

		// Calculate std of CAAR first
		val1 = (i / (i + 1.0)) * val1 + pow( samplegroup.Beat_CAAR - Beat_Expected_CAAR, 2.0 ) / (i + 1.0);
		val2 = (i / (i + 1.0)) * val2 + pow( samplegroup.Meet_CAAR - Meet_Expected_CAAR, 2.0 ) / (i + 1.0);
		val3 = (i / (i + 1.0)) * val3 + pow( samplegroup.Miss_CAAR - Miss_Expected_CAAR, 2.0 ) / (i + 1.0);

		// Calculate std of AAR
		for (int j = 0; j < days; j++)
		{
			vec1[j] += pow( samplegroup.Beat_AAR[j] - Beat_Expected_AAR[j], 2.0 );
			vec2[j] += pow( samplegroup.Meet_AAR[j] - Meet_Expected_AAR[j], 2.0 );
			vec3[j] += pow( samplegroup.Miss_AAR[j] - Miss_Expected_AAR[j], 2.0 );
		}
	}

	Beat_std_CAAR = sqrt(val1);		Meet_std_CAAR = sqrt(val2);	Miss_std_CAAR = sqrt(val3);

	for (int d = 0; d < days; d++)
	{
		Beat_std_AAR.push_back(sqrt(vec1[d] / 30.0));
		Meet_std_AAR.push_back(sqrt(vec2[d] / 30.0));
		Miss_std_AAR.push_back(sqrt(vec3[d] / 30.0));
	}
}