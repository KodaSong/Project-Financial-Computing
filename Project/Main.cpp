/*
 * @Author: Koda Song
 * @Date: 2019-11-29 10:20:52
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:50:33
 * @Description: 
 */

#include "stdafx.h"
#include "BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExceptionClasses\DatasimException.hpp"

#include <stdio.h>
#include <vector>
#include <list>
#include <locale>
#include <iomanip>
#include <locale>
#include <locale.h>
//#include "ExcelDriver\ExcelDriver.hpp"
#include <algorithm>
#include <thread>
#include <numeric>
#include <iomanip>
#include <cstdio>
#include <time.h>

#include "curl.h"
#include "stock.h"
#include "RetrieveData.h"
#include "Repeat.h"
#include "ReadFile.h"
#include "Display.h"

#include <string>
using namespace std;


int main()
{
	/*// Delete files downloaded last time 
	remove(".\\in_out\\Output_PricesSPY.txt");
	remove(".\\in_out\\Output_PricesSP500.txt");*/

	stock spy;
	cout << "Start to retrieve historical price data for SPY from Yahoo Finance:" << endl;
	GetSPYData(spy);
	cout << "SPY data retrieved successfully!" << endl << endl;

	// Read Bloomberg file and store tickers, annoucement day, eps information into stockList
	cout << "Read data from file downloaded on Bloomberg:" << endl;
	//vector<stock> stockList = Get_EPS(".\\in_out\\SP_bbg.csv");
	vector<stock> stockList = Get_EPS(".\\in_out\\SP_bbg.csv");
	cout << "EPS File read successfully!" << endl << endl;

	/*// retrieve historical price data for sp500 from yahoo finance and do calculations in the meantime
	cout << "Start to retrieve historical price data for all stocks:" << endl;
	clock_t start = clock();
	GetData(stockList, spy);
	clock_t ends = clock();
	cout << "SP500 data retrieved successfully!" << endl;
	double secs = (double)(ends - start) / CLOCKS_PER_SEC;
	cout << "Running Time : " << secs / 60.0 << " minutes" << endl << endl;*/

	/*// Only download data and store in file without any calculation -> Save time!
	clock_t start = clock();
	Download_Data(stockList);
	clock_t ends = clock();
	double secs = (double)(ends - start) / CLOCKS_PER_SEC;
	cout << "Running Time : " << secs/60.0 << " minutes" << endl;

	//	Read file and store stock's price information into "stockList"
	string filename = ".\\in_out\\Output_PricesSP500.txt";
	GetPriceData_txt(stockList, filename, spy);*/

	// Risk Management: directly read stock price data from txt
	cout << "Read stock price data from txt file:" << endl;
	string filename = ".\\in_out\\Input_SP500.txt";
	GetPriceData_txt(stockList, filename, spy);
	cout << endl << endl;

	map<string, stock> StockMap = stock_map(stockList);
	

	// Divide stocks into 3 groups
	Group stock_group;
	group_stocks(stockList, stock_group);

	// Calculation indicators (30 times)
	Repeat30 my_repeat(stock_group);
	my_repeat.Mean();
	my_repeat.Std();

	/* // Show
	string split_line = "------------------------------------------";
	split_line += split_line;
	split_line += split_line;
	split_line += "---";
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << split_line << endl
		 << "Beat Group:" << endl
		 << "Group Size = " << stock_group.Beat.size() << endl
		 << "Expected Value of CAAR = " << my_repeat.Beat_Expected_CAAR * 100 << "%" << endl
		 << "Standard Deviation of CAAR = " << my_repeat.Beat_std_CAAR * 100 << "%" << endl << endl;

	cout << "Expected Value of AAR: " << endl;
	display_vec(my_repeat.Beat_Expected_AAR);
	cout << "Standard Deviation of AAR: " << endl;
	display_vec(my_repeat.Beat_std_AAR);

	cout << split_line << endl
		 << "Meet Group:" << endl 
		 << "Group Meet = " << stock_group.Meet.size() << endl
		 << "Expected Value of CAAR = " << my_repeat.Meet_Expected_CAAR * 100 << "%" << endl
		 << "Standard Deviation of CAAR = " << my_repeat.Meet_std_CAAR * 100 << "%" << endl << endl;

	cout << "Expected Value of AAR: " << endl;
	display_vec(my_repeat.Meet_Expected_AAR);
	cout << "Standard Deviation of AAR = " << endl;
	display_vec(my_repeat.Meet_std_AAR);

	cout << split_line << endl
		 << "Miss Group:" << endl 
		 << "Group Size = " << stock_group.Miss.size() << endl
		 << "Expected Value of CAAR = " << my_repeat.Miss_Expected_CAAR * 100 << "%" << endl
		 << "Standard Deviation of CAAR = " << my_repeat.Miss_std_CAAR * 100 << "%" << endl << endl;

	cout << "Expected Value of AAR: " << endl;
	display_vec(my_repeat.Miss_Expected_AAR);
	cout << "Standard Deviation of AAR: " << endl;
	display_vec(my_repeat.Miss_std_AAR);
	cout << split_line << endl;*/


	cout << endl;

	// Show in file
	ofstream fout;
	fout.open(".\\in_out\\Tables.txt");

	fout << setiosflags(ios::fixed) << setprecision(3);
	fout << "Beat Group:" << endl
		<< "Group Size = " << stock_group.Beat.size() << endl
		<< "Expected Value of CAAR = " << my_repeat.Beat_Expected_CAAR * 100 << "%" << endl
		<< "Standard Deviation of CAAR = " << my_repeat.Beat_std_CAAR * 100 << "%" << endl << endl;

	fout << "Expected Value of AAR: " << endl;
	display_in_file(fout, my_repeat.Beat_Expected_AAR);
	fout << "Standard Deviation of AAR: " << endl;
	display_in_file(fout, my_repeat.Beat_std_AAR);

	fout << "Meet Group:" << endl
		<< "Group Meet = " << stock_group.Meet.size() << endl
		<< "Expected Value of CAAR = " << my_repeat.Meet_Expected_CAAR * 100 << "%" << endl
		<< "Standard Deviation of CAAR = " << my_repeat.Meet_std_CAAR * 100 << "%" << endl << endl;

	fout << "Expected Value of AAR: " << endl;
	display_in_file(fout, my_repeat.Meet_Expected_AAR);
	fout << "Standard Deviation of AAR = " << endl;
	display_in_file(fout, my_repeat.Meet_std_AAR);

	fout << "Miss Group:" << endl
		<< "Group Size = " << stock_group.Miss.size() << endl
		<< "Expected Value of CAAR = " << my_repeat.Miss_Expected_CAAR * 100 << "%" << endl
		<< "Standard Deviation of CAAR = " << my_repeat.Miss_std_CAAR * 100 << "%" << endl << endl;

	fout << "Expected Value of AAR: " << endl;
	display_in_file(fout, my_repeat.Miss_Expected_AAR);
	fout << "Standard Deviation of AAR: " << endl;
	display_in_file(fout, my_repeat.Miss_std_AAR);


	Vector<double, long> xarr(60);
	Vector<double, long> yarr1(60);
	Vector<double, long> yarr2(60);
	Vector<double, long> yarr3(60);

	double h1 = 1.0;
	xarr[xarr.MinIndex()] = -29.0;
	for (long i = xarr.MinIndex()+1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i - 1] + h1;
	}

	for (long j = yarr1.MinIndex(); j <= yarr1.MaxIndex(); j++)
	{
		yarr1[j] = my_repeat.Beat_Expected_AAR[j - 1];
		yarr2[j] = my_repeat.Meet_Expected_AAR[j - 1];
		yarr3[j] = my_repeat.Miss_Expected_AAR[j - 1];
	}

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!	-> open excel, creat empty sheet "Chart Data"

 	try
	{
		list<string> labels;	// labels for 3 groups
		list<Vector<double, long> > functionResult;
		string title = "AAR Plot for 3 Groups";
		string ylabel = "Average Abnormal Return";	
		string xlabel = "Days";

		labels.push_back("Beat");	labels.push_back("Meet");	labels.push_back("Miss");
		functionResult.push_back(yarr1);	functionResult.push_back(yarr2);	functionResult.push_back(yarr3);

		printInExcel(xarr, labels, functionResult, title, ylabel, xlabel);
	}
	catch(DatasimException& e)
	{
		e.print();
	}
	catch (...)
	{
		// Catches everything else
	}

	return 0;
}
