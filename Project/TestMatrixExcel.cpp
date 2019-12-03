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
	//stock spy;
	//cout << "Retrieve historical price data for SPY from Yahoo Finance" << endl;
	//GetSPYData(spy);

	//// Read Bloomberg file and store tickers, annoucement day, eps information into stockList
	//cout << "Read data from file downloaded on Bloomberg:" << endl;
	//vector<stock> stockList = Get_EPS("SP6_bbg.csv");
	//cout << endl;

	////// Retrieve historical price data for SP500 from Yahoo Finance
	////cout << "Retrieve historical price data for all stocks." << endl;
	////GetData(stockList, spy);
	////cout << endl;

	//// Risk Management: directly read stock price data from txt
	//cout << "Read stock price data from txt file:" << endl;
	//string filename = "Input6_SP500.txt";
	//GetPriceData_txt(stockList, filename, spy);
	//cout << endl << endl;

	//// Divide stocks into 3 groups
	//Group stock_group;
	//group_stocks(stockList, stock_group);

	//// Calculation indicators (30 times)
	//Repeat30 my_repeat(stock_group);
	//my_repeat.Mean();
	//my_repeat.Std();

	//// Show
	//string split_line = "------------------------------------------";
	//split_line += split_line;
	//split_line += split_line;
	//split_line += "---";
	//cout << setiosflags(ios::fixed) << setprecision(3);
	//cout << split_line << endl
	//	 << "Beat Group:" << endl
	//	 << "Group Size = " << stock_group.Beat.size() << endl
	//	 << "Expected Value of CAAR = " << my_repeat.Beat_Expected_CAAR * 100 << "%" << endl
	//	 << "Standard Deviation of CAAR = " << my_repeat.Beat_std_CAAR * 100 << "%" << endl << endl;

	//cout << "Expected Value of AAR: " << endl;
	//display_vec(my_repeat.Beat_Expected_AAR);
	//cout << "Standard Deviation of AAR: " << endl;
	//display_vec(my_repeat.Beat_std_AAR);

	//cout << split_line << endl
	//	 << "Meet Group:" << endl 
	//	 << "Group Meet = " << stock_group.Meet.size() << endl
	//	 << "Expected Value of CAAR = " << my_repeat.Meet_Expected_CAAR * 100 << "%" << endl
	//	 << "Standard Deviation of CAAR = " << my_repeat.Meet_std_CAAR * 100 << "%" << endl << endl;

	//cout << "Expected Value of AAR: " << endl;
	//display_vec(my_repeat.Meet_Expected_AAR);
	//cout << "Standard Deviation of AAR = " << endl;
	//display_vec(my_repeat.Meet_std_AAR);

	//cout << split_line << endl
	//	 << "Miss Group:" << endl 
	//	 << "Group Size = " << stock_group.Miss.size() << endl
	//	 << "Expected Value of CAAR = " << my_repeat.Miss_Expected_CAAR * 100 << "%" << endl
	//	 << "Standard Deviation of CAAR = " << my_repeat.Miss_std_CAAR * 100 << "%" << endl << endl;

	//cout << "Expected Value of AAR: " << endl;
	//display_vec(my_repeat.Miss_Expected_AAR);
	//cout << "Standard Deviation of AAR: " << endl;
	//display_vec(my_repeat.Miss_std_AAR);
	//cout << split_line << endl;


	//cout << endl;

	//// Show in file
	//ofstream fout;
	//fout.open("Tables.csv");

	//fout << setiosflags(ios::fixed) << setprecision(3);
	//fout << "Beat Group:" << endl
	//	<< "Group Size = " << stock_group.Beat.size() << endl
	//	<< "Expected Value of CAAR = " << my_repeat.Beat_Expected_CAAR * 100 << "%" << endl
	//	<< "Standard Deviation of CAAR = " << my_repeat.Beat_std_CAAR * 100 << "%" << endl << endl;

	//fout << "Expected Value of AAR: " << endl;
	//display_in_file(fout, my_repeat.Beat_Expected_AAR);
	//fout << "Standard Deviation of AAR: " << endl;
	//display_in_file(fout, my_repeat.Beat_std_AAR);

	//fout << "Meet Group:" << endl
	//	<< "Group Meet = " << stock_group.Meet.size() << endl
	//	<< "Expected Value of CAAR = " << my_repeat.Meet_Expected_CAAR * 100 << "%" << endl
	//	<< "Standard Deviation of CAAR = " << my_repeat.Meet_std_CAAR * 100 << "%" << endl << endl;

	//fout << "Expected Value of AAR: " << endl;
	//display_in_file(fout, my_repeat.Meet_Expected_AAR);
	//fout << "Standard Deviation of AAR = " << endl;
	//display_in_file(fout, my_repeat.Meet_std_AAR);

	//fout << "Miss Group:" << endl
	//	<< "Group Size = " << stock_group.Miss.size() << endl
	//	<< "Expected Value of CAAR = " << my_repeat.Miss_Expected_CAAR * 100 << "%" << endl
	//	<< "Standard Deviation of CAAR = " << my_repeat.Miss_std_CAAR * 100 << "%" << endl << endl;

	//fout << "Expected Value of AAR: " << endl;
	//display_in_file(fout, my_repeat.Miss_Expected_AAR);
	//fout << "Standard Deviation of AAR: " << endl;
	//display_in_file(fout, my_repeat.Miss_std_AAR);

	long N = 20; long M = 30;
	NumericMatrix<double, long> matrix(N+1, M+1);

	Vector<double, long> xarr(N+1);
	Vector<double, long> yarr(N+1);
	Vector<double, long> yarr2(N+1);

	double h1 = 0.1;
	xarr[xarr.MinIndex()] = 0.0;
	for (long i = xarr.MinIndex()+1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i - 1] + h1;
	}

	double h2 = 0.2;
	yarr[yarr.MinIndex()] = 0.0;
	for (long j = yarr.MinIndex()+1; j <= yarr.MaxIndex(); j++)
	{
		yarr[j] = yarr[j - 1] + h2;
		yarr2[j] = yarr[j] + yarr2[j - 1];
	}

	list<std::string> rowlabels = convertToString(xarr);
	list<std::string> columnlabels = convertToString(yarr);

	std::string sheetName("First");

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!

	excel.AddMatrix(sheetName, matrix, rowlabels, columnlabels);

	try
	{
		// Difference of vectors
		printDifferenceInExcel(xarr, yarr2, yarr);
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
