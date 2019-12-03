// TestMatrixExcel.cpp
//
// Test output of a matrix in Excel. Here we 
// use the Excel Driver object directly.
//
// (C) Datasim Education BV 2006
//
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
	stock spy;
	cout << "Retrieve historical price data for SPY from Yahoo Finance" << endl;
	GetSPYData(spy);

	// Read Bloomberg file and store tickers, annoucement day, eps information into stockList
	cout << "Read data from file downloaded on Bloomberg:" << endl;
	vector<stock> stockList = Get_EPS("SP_bbg.csv");
	cout << endl;

	//// Retrieve historical price data for SP500 from Yahoo Finance
	//cout << "Retrieve historical price data for all stocks." << endl;
	//GetData(stockList, spy);
	//cout << endl;

	// Risk Management: directly read stock price data from txt
	cout << "Read stock price data from txt file:" << endl;
	string filename = "Input_SP500.txt";
	GetPriceData_txt(stockList, filename, spy);
	cout << endl << endl;

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
	fout.open("Tables.txt");

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
