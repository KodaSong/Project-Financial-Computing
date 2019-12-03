// TestChartStructure.cpp
//
// Test output of a chart structure in Excel.
//
// (C) Datasim Education BV 2006
//
#include "stdafx.h"
#include "ChartStructure.hpp"
#include "ExcelDriver.hpp"
#include "VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "BitsAndPieces\StringConversions.hpp"

#include <string>
using namespace std;

int main()
{

	long N = 20; long M = 30;
	NumericMatrix<double, long> matrix(N+1, M+1);

	Vector<double, long> xarr(N+1);
	Vector<double, long> yarr(M+1);

	double h1 = 0.1;
	xarr[xarr.MinIndex()] = 0.0;
	for (long i = xarr.MinIndex()+1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i-1] + h1;
	}

	double h2 = 0.2;
	yarr[yarr.MinIndex()] = 0.0;
	for (long j = yarr.MinIndex()+1; j <= yarr.MaxIndex(); j++)
	{
		yarr[j] = yarr[j-1] + h2;
	}

	list<std::string> rowlabels = convertToString(xarr);
	list<std::string> columnlabels = convertToString(yarr);

	std::string sheetName("First");

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!

	excel.AddMatrix(sheetName, matrix, rowlabels, columnlabels);


	return 0;
}
