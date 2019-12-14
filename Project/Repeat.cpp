/*
 * @Author: Koda Song
 * @Date: 2019-11-29 16:25:45
 * @LastEditors: Suki
 * @LastEditTime: 2019-12-11 12:48:41
 * @Description: 
 */
#include "stdafx.h"
#include <cmath>
#include "Repeat.h"
#include "Display.h"

void Repeat30::Calculation()
{
	// Repeat 30 times
	for (int i = 0; i < 30; i++) {
		Group samplegroup = SampleStocks(group);	// Generate sample groups 30*3
		Cal_AAR(samplegroup);		// Calculate AAR
		Cal_CAAR(samplegroup);		// Calculate CAAR

		M_Beat_AAR.push_back(samplegroup.Beat_AAR);	// Use Matrix ( 30*60 ) to store each time's AAR
		M_Meet_AAR.push_back(samplegroup.Meet_AAR);
		M_Miss_AAR.push_back(samplegroup.Miss_AAR);
		M_Beat_CAAR.push_back(samplegroup.Beat_CAAR);
		M_Meet_CAAR.push_back(samplegroup.Meet_CAAR);
		M_Miss_CAAR.push_back(samplegroup.Miss_CAAR);
	}

	int days = 60;
	Vector_ vec1(days), vec2(days), vec3(days), vec4(days), vec5(days), vec6(days);	// For AAR
	Vector_ vec1_(days), vec2_(days), vec3_(days), vec4_(days), vec5_(days), vec6_(days);	// For CAAR
	
	// Calculate Mean -> Sum the rows of Matrix (30*60) -> Vector (1*60)
	for (int i = 0; i < 30; i++) {
		vec1 += M_Beat_AAR[i];	vec2 += M_Meet_AAR[i];	 vec3 += M_Miss_AAR[i];
		vec1_ += M_Beat_CAAR[i];	vec2_ += M_Meet_CAAR[i];	 vec3_ += M_Miss_CAAR[i];
	}
	// Average these vectors to get mean vector
	Beat_Expected_AAR = vec1/30.0;	Meet_Expected_AAR = vec2/30.0;	Miss_Expected_AAR = vec3/30.0;
	Beat_Expected_CAAR = vec1_/30.0;	Meet_Expected_CAAR = vec2_/30.0;	Miss_Expected_CAAR = vec3_/30.0;

	// Calculate Std -> Sum of (Each row of Matrix - Expected Vector)^2
	for (int i = 0; i < 30; i++) {
		vec4 += sqrr(M_Beat_AAR[i] - Beat_Expected_AAR);	vec5 += sqrr(M_Meet_AAR[i] - Meet_Expected_AAR);	vec6 += sqrr(M_Miss_AAR[i] - Miss_Expected_AAR);
		vec4_ += sqrr(M_Beat_CAAR[i] - Beat_Expected_CAAR);	vec5_ += sqrr(M_Meet_CAAR[i] - Meet_Expected_CAAR);	vec6_ += sqrr(M_Miss_CAAR[i] - Miss_Expected_CAAR);
	}
	// Average these vectors to get SAMPLE standard deviation ( should divided by (n-1) )
	Beat_std_AAR = sqrt(vec4 / 29.0);	Meet_std_AAR = sqrt(vec5 / 29.0);	Miss_std_AAR = sqrt(vec6 / 29.0);
	Beat_std_CAAR = sqrt(vec4_ / 29.0);	Meet_std_CAAR = sqrt(vec5_ / 29.0);	Miss_std_CAAR = sqrt(vec6_ / 29.0);
}

void Repeat30::PrintGroupInfo(int& groupname, int& valuename)
{
	if (groupname == 1)
	{
		switch (valuename)
		{
		case 1:
		{
			cout << "Expected AAR for Beat Group is:" << endl;
			display_vec(Beat_Expected_AAR);
			break;
		}
		case 2:
		{
			cout << "Standard deviation of AAR for Beat Group is:" << endl;
			display_vec(Beat_std_AAR);
			break;
		}
		case 3:
		{
			cout << "Expected CAAR for Beat Group is:" << endl;
			display_vec(Beat_Expected_CAAR);
			break;
		}
		case 4:
		{
			cout << "Standard deviation of CAAR for Beat Group is:" << endl;
			display_vec(Beat_std_CAAR);
			break;
		}
		default:
		{
			cout << "Invalid input. Please input again." << endl;
		}
		}
	}
	else if (groupname == 2)
	{
		switch (valuename)
		{
		case 1:
		{
			cout << "Expected AAR for Meet Group is:" << endl;
			display_vec(Meet_Expected_AAR);
			break;
		}
		case 2:
		{
			cout << "Standard deviation of AAR for Meet Group is:" << endl;
			display_vec(Meet_std_AAR);
			break;
		}
		case 3:
		{
			cout << "Expected CAAR for Meet Group is:" << endl;
			display_vec(Meet_Expected_CAAR);
			break;
		}
		case 4:
		{
			cout << "Standard deviation of CAAR for Meet Group is:" << endl;
			display_vec(Meet_std_CAAR);
			break;
		}
		default:
		{
			cout << "Invalid input. Please input again." << endl;
		}
		}
	}
	else if (groupname == 3)
	{
		switch (valuename)
		{
		case 1:
		{
			cout << "Expected AAR for Miss Group is:" << endl;
			display_vec(Miss_Expected_AAR);
			break;
		}
		case 2:
		{
			cout << "Standard deviation of AAR for Miss Group is:" << endl;
			display_vec(Miss_std_AAR);
			break;
		}
		case 3:
		{
			cout << "Expected CAAR for Miss Group is:" << endl;
			display_vec(Miss_Expected_CAAR);
			break;
		}
		case 4:
		{
			cout << "Standard deviation of CAAR for Miss Group is:" << endl;
			display_vec(Miss_std_CAAR);
			break;
		}
		default:
		{
			cout << "Invalid input. Please input again." << endl;
		}
		}
	}
	else
	{
		cout << "Invalid input. Please input again." << endl;
	}
}

