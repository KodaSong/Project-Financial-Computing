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

	cout << "Waiting for next command:" << endl;
	getchar();	// To wait for the next command
	
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

	cout << "Waiting for next command:" << endl;
	getchar();	// To wait for the next command

	// Risk Management: directly read stock price data from txt
	cout << "Start to read stock price data from txt file:" << endl;
	string filename = ".\\in_out\\Input_SP500.txt";
	GetPriceData_txt(stockList, filename, spy);
	cout << "SP500's Price information read successfully!" << endl << endl;

	cout << "Waiting for next command:" << endl;
	getchar();	// To wait for the next command

	map<string, stock> StockMap = stock_map(stockList);
	
	// Divide stocks into 3 groups
	cout << "Start to divide stocks in 3 groups:" << endl;
	Group stock_group;
	group_stocks(stockList, stock_group);
	cout << "Grouping Finished!" << endl << endl;

	cout << "Waiting for next command:" << endl;
	getchar();

	// Calculation indicators (30 times)
	cout << "Start to repeat 30 times and do calculations:" << endl;
	Repeat30 my_repeat(stock_group);
	my_repeat.Mean();
	my_repeat.Std();
	cout << "Calculations Finished!" << endl << endl;

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
	Vector<double, long> yarr1(60);	Vector<double, long> yarr1_(60);
	Vector<double, long> yarr2(60);	Vector<double, long> yarr2_(60);
	Vector<double, long> yarr3(60);	Vector<double, long> yarr3_(60);
	NumericMatrix<double, long> matrix1(3, 60), matrix2(3,60);	// One for mean, another for std

	// Input data into matrix
	for (long j = matrix1.MinColumnIndex(); j <= matrix1.MaxColumnIndex(); j++)
	{
		matrix1(1, j) = my_repeat.Beat_Expected_AAR[j - 1] * 100.0;	// let data appear as percentage
		matrix2(1, j) = my_repeat.Beat_std_AAR[j - 1] * 100.0;
	}
		

	for (long j = matrix1.MinColumnIndex(); j <= matrix1.MaxColumnIndex(); j++)
	{
		matrix1(2, j) = my_repeat.Meet_Expected_AAR[j - 1] * 100.0;
		matrix2(2, j) = my_repeat.Meet_std_AAR[j - 1] * 100.0;
	}
		

	for (long j = matrix1.MinColumnIndex(); j <= matrix1.MaxColumnIndex(); j++)
	{
		matrix1(3, j) = my_repeat.Miss_Expected_AAR[j - 1] * 100.0;
		matrix2(3, j) = my_repeat.Miss_std_AAR[j - 1] * 100.0;
	}
	
	double h1 = 1.0;
	xarr[xarr.MinIndex()] = -29.0;
	for (long i = xarr.MinIndex() + 1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i - 1] + h1;
	}

	// labels for 3 groups
	list<string> rowlabels;
	rowlabels.push_back("Beat");	rowlabels.push_back("Meet");	rowlabels.push_back("Miss");

	// Names for different sheets
	string name1 = "Expected AAR";	string name2 = "AAR-SD";

	list<std::string> columnlabels = convertToString(xarr);	// From day-29 to day30

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!	-> open excel, creat empty sheet "Chart Data"
	excel.AddMatrix(name1, matrix1, rowlabels, columnlabels);	// Sheet for Expected AAR
	excel.AddMatrix(name2, matrix2, rowlabels, columnlabels);	// Sheet for AAR-SD


	for (long j = yarr1.MinIndex(); j <= yarr1.MaxIndex(); j++)
	{
		yarr1[j] = my_repeat.Beat_Expected_AAR[j - 1] * 100.0;	// let data appear as percentage
		yarr2[j] = my_repeat.Meet_Expected_AAR[j - 1] * 100.0;
		yarr3[j] = my_repeat.Miss_Expected_AAR[j - 1] * 100.0;
		yarr1_[j] = my_repeat.Beat_std_AAR[j - 1] * 100.0;	// let data appear as percentage
		yarr2_[j] = my_repeat.Meet_std_AAR[j - 1] * 100.0;
		yarr3_[j] = my_repeat.Miss_std_AAR[j - 1] * 100.0;
	}
	
 	try
	{
		string title = "Expected AAR Plot for 3 Groups";		// Chart title
		string ylabel = "Average Abnormal Return";
		string xlabel = "Days";
			
		list<Vector<double, long> > functionResult;		// Data

		functionResult.push_back(yarr1);	functionResult.push_back(yarr2);	functionResult.push_back(yarr3);
		printInExcel(xarr, rowlabels, functionResult, title, xlabel, ylabel);
	}
	catch(DatasimException& e)
	{
		e.print();
	}
	catch (...)
	{
		// Catches everything else
	}

	try
	{
		string title = "AAR-SD Plot for 3 Groups";		// Chart title
		string ylabel = "SD of Average Abnormal Return";
		string xlabel = "Days";
		list<Vector<double, long> > functionResult;		// Data

		functionResult.push_back(yarr1_);	functionResult.push_back(yarr2_);	functionResult.push_back(yarr3_);
		printInExcel(xarr, rowlabels, functionResult, title, xlabel, ylabel);
	}
	catch (DatasimException& e)
	{
		e.print();
	}
	catch (...)
	{
		// Catches everything else
	}

	return 0;
}
