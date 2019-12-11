/*
 * @Author: Koda Song
 * @Date: 2019-11-29 10:20:52
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:50:33
 * @Description: 
 */

#include "stdafx.h"

#include <iomanip>
#include <time.h>

#include "Stock.h"
#include "Repeat.h"
#include "Display.h"
#include "gnuplot.h"
#include "ReadFile.h"
#include "RetrieveData.h"

#include "BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExceptionClasses\DatasimException.hpp"

using namespace std;

int main()
{
	/*// Delete files downloaded last time 
	remove(".\\in_out\\Output_PricesSPY.txt");
	remove(".\\in_out\\Output_PricesSP500.txt");*/

	cout << "Data retrieving...Please wait." << endl;

	// First, download SPY from Yahoo Finance, only once!
	stock spy;
	GetSPYData(spy);
	
	// Read Bloomberg file and store tickers, annoucement day, eps information into stockList
	vector<stock> stockList = Get_EPS(".\\in_out\\SP_bbg.csv");

	// Use multithreading to retrieve data from Yahoo Finance
	clock_t start = clock();
	multi_thread(stockList, spy);
	clock_t ends = clock();
	double secs = (double)(ends - start) / CLOCKS_PER_SEC;	// Count time
	cout << "Running Time : " << secs / 60.0 << " minutes" << endl << endl;
	
	/*// Risk Management: directly read stock price data from txt
	string filename = ".\\in_out\\Input_SP500.txt";
	GetPriceData_txt(stockList, filename, spy);*/

	// Create a stockmap, for menu!
	map<string, stock> StockMap = stock_map(stockList);
	
	// Divide stocks into 3 groups
	Group stock_group;
	group_stocks(stockList, stock_group);

	// Calculation indicators (30 times)
	Repeat30 my_repeat(stock_group);
	my_repeat.Calculation();

	// All things done, now is for menu!
	ShowMenu();
	cout << "Please input: ";
	int input;
	cin >> input;
	cout << endl;

	while (input != 0)
	{
		switch (input)
		{
		case 1://retrieve historical price data for all stocks and store data in txt
		{
			cout << "Retrieving data and calculation completed!" << endl;
			cout << "Store data in the 'SP500Price.txt'." << endl;
			cout << endl;

			ofstream fout;
			fout.open(".\\in_out\\SP500Price.txt");

			//print data in txt file,with 6*10 matrix for each stock
			map<string, stock>::iterator itr;
			for (itr = StockMap.begin(); itr != StockMap.end(); itr++)
			{
				fout << itr->first << endl;
				display_in_file(fout, itr->second.adj_close);
				fout << endl;
			}
			break;
		}
		case 2://pull information for one stock.
		{
			cout << "Please enter the stock name: ";
			string stockname;
			cin >> stockname;
			cout << endl;
			map<string, stock>::iterator iter;
			iter = StockMap.find(stockname);
			cout << "Please enter 1, 2, 0 to select your option:" << endl;
			cout << "1.Get all infomation of stock." << endl;
			cout << "2.Get specific infomation of stock." << endl;
			cout << "0.Return to the last menu." << endl << endl;
			cout << "Please input: ";
			int input2;
			cin >> input2;
			cout << endl;

			while (input2 != 0)
			{
				switch (input2)
				{
				case 1:
				{
					if (iter != StockMap.end())
					{
						iter->second.PrintAllInfo();
					}
					else
					{
						cout << "No such stock. " << endl << endl;
					}
					break;
				}
				case 2:
				{
					cout << "Please enter 1, 2, 3, 4, 5, 6 to select the data type:" << endl;
					cout << "1.Annocement date" << endl;
					cout << "2.estimated EPS" << endl;
					cout << "3.actual EPS" << endl;
					cout << "4.surprise" << endl;
					cout << "5.adj_close" << endl;
					cout << "6.daily returns" << endl << endl;
					cout << "Please input: ";
					int value;
					cin >> value;
					cout << endl;

					while (value != 0)
					{
						switch (value)
						{
						case 1:
						{
							if (iter != StockMap.end())
							{
								cout << "Announcement date:" << iter->second.announcement_day << endl;
								cout << endl;
							}
							else
							{
								cout << "No such stock." << endl;
							}
							break;
						}
						case 2:
						{
							if (iter != StockMap.end())
							{
								cout << "estimated EPS:" << iter->second.EPS_Estimate << endl;
								cout << endl;
							}
							else
							{
								cout << "No such stock." << endl;
							}
							break;
						}
						case 3:
						{
							if (iter != StockMap.end())
							{
								cout << "actual EPS:" << iter->second.EPS_Actual << endl;
								cout << endl;
							}
							else
							{
								cout << "No such stock." << endl;
							}
							break;
						}
						case 4:
						{
							if (iter != StockMap.end())
							{
								cout << "surprise:" << iter->second.surprise << endl;
								cout << endl;
							}
							else
							{
								cout << "No such stock. " << endl;
							}
							break;
						}
						case 5:
						{
							if (iter != StockMap.end())
							{
								cout << "adj_close:" << endl;
								display_vec2(iter->second.adj_close);
							}
							else
							{
								cout << "No such stock." << endl;
							}
							break;
						}
						case 6:
						{
							if (iter != StockMap.end())
							{
								cout << "daily return:" << endl;
								display_vec(iter->second.daily_return);
							}
							else
							{
								cout << "No such stock. " << endl;
							}
							break;
						}
						default:
						{
							cout << "Invalid input. Please input again." << endl;
							cout << endl;
						}
						}
						cout << "Please enter 1, 2, 3, 4, 5, 6, 0 to select the data type:" << endl;
						cout << "1.Annocement date" << endl;
						cout << "2.estimated EPS" << endl;
						cout << "3.actual EPS" << endl;
						cout << "4.surprise" << endl;
						cout << "5.adj_close" << endl;
						cout << "6.daily returns" << endl;
						cout << "0.Return to the last menu." << endl << endl;
						cout << "Please input: ";
						cin >> value;
						cout << endl;
					}
					break;
				}
				default:
				{
					cout << "Invalid input. Please input again." << endl;
				}
				}
				cout << "Please enter 1, 2, 0 to select your option:" << endl;
				cout << "1.Get all infomation of stock." << endl;
				cout << "2.Get specific infomation of stock." << endl;
				cout << "0.Return to the last menu." << endl << endl;
				cout << "Please input: ";
				cin >> input2;
				cout << endl;
			}
			break;
		}
		case 3://show AAR,AAR SD,CAAR or CAAR SD for one group.
		{
			cout << "Please enter 1, 2, 3, 0 to select the group:" << endl;
			cout << "1.Beat" << endl;
			cout << "2.Meet" << endl;
			cout << "3.Miss" << endl;
			cout << "Other values.Return to the menu." << endl << endl;
			cout << "Please input: ";
			int group;
			cin >> group;
			cout << endl;

			while (group == 1 || group == 2 || group == 3)
			{
				cout << "Please enter 1, 2, 3, 4 to select the value:" << endl;
				cout << "1.AAR" << endl;
				cout << "2.AAR SD" << endl;
				cout << "3.CAAR" << endl;
				cout << "4.CAAR SD" << endl;
				cout << "Other values.Return to the menu." << endl << endl;
				cout << "Please input: ";
				int value;
				cin >> value;
				cout << endl;

				while ((group == 1 || group == 2 || group == 3) && ((value == 1) || value == 2 || value == 3 || value == 4))
				{
					my_repeat.PrintGroupInfo(group, value);
					cout << "Stay or change another group? Please select option:" << endl;
					cout << "1.Stay" << endl;
					cout << "2.Change" << endl;
					cout << "Other values.Return to the menu." << endl << endl;
					cout << "Please input: ";
					int value2;
					cin >> value2;
					cout << endl;

					switch (value2)
					{
					case 1:
					{
						cout << "Please enter 1, 2, 3, 4 to select the value:" << endl;
						cout << "1.AAR" << endl;
						cout << "2.AAR SD" << endl;
						cout << "3.CAAR" << endl;
						cout << "4.CAAR SD" << endl << endl;
						cout << "Please input: ";
						cin >> value;
						cout << endl;
						break;
					}
					case 2:
					{
						cout << "Please enter 1, 2, 3, 0 to select the group:" << endl;
						cout << "1.Beat" << endl;
						cout << "2.Meet" << endl;
						cout << "3.Miss" << endl;
						cout << "Other values.Return to the menu." << endl << endl;
						cout << "Please input: ";
						cin >> group;
						cout << endl;

						cout << "Please enter 1, 2, 3, 4 to select the value:" << endl;
						cout << "1.AAR" << endl;
						cout << "2.AAR SD" << endl;
						cout << "3.CAAR" << endl;
						cout << "4.CAAR SD" << endl;
						cout << "Other values.Return to the menu." << endl << endl;
						cout << "Please input: ";
						cin >> value;
						cout << endl;

						break;
					}
					default:
					{
						group = 0;
					}
					}
				}
				group = 0;
			}
			cout << endl;
			break;
		}
		case 4://show the graph with CAAR for 3 groups.
		{
			int nIntervals = 60;
			double* xData = (double*)malloc((nIntervals + 1) * sizeof(double));
			double* yData1 = (double*)malloc((nIntervals + 1) * sizeof(double));
			double* yData2 = (double*)malloc((nIntervals + 1) * sizeof(double));
			double* yData3 = (double*)malloc((nIntervals + 1) * sizeof(double));

			xData[0] = -30.0;
			for (int i = 0; i <= nIntervals - 1; i++) {
				xData[i + 1] = xData[i] + 1.0;
			}

			yData1[0] = 0.0;	yData2[0] = 0.0;	yData3[0] = 0.0;
			for (int i = 1; i <= nIntervals; i++) {
				yData1[i] = my_repeat.Beat_Expected_CAAR[i - 1] * 100.0;	// Percentage
				yData2[i] = my_repeat.Meet_Expected_CAAR[i - 1] * 100.0;
				yData3[i] = my_repeat.Miss_Expected_CAAR[i - 1] * 100.0;
			}

			cout << "Graph shown!" << endl;
			plotResults(xData, yData1, yData2, yData3, nIntervals);
			cout << endl;
			break; 
		}
		default:
		{
			cout << "Invalid input. Please input again." << endl;
			cout << endl;
		}
		}
		ShowMenu();
		cout << "Please input: ";
		cin >> input;
		cout << endl;
	}
	cout << "Exit program." << endl << endl;//0 exit program.

	int aaaaaaa;
	cout << "Do you want to use ExcelDriver to see plot?" << endl;
	cout << "Enter 1 means Yes" << endl;
	cout << "Please input: ";
	cin >> aaaaaaa;
	if (aaaaaaa == 1) {
		Vector<double, long> xarr(61);
		Vector<double, long> yarr1(61);    //Vector<double, long> yarr1_(61);
		Vector<double, long> yarr2(61);    //Vector<double, long> yarr2_(61);
		Vector<double, long> yarr3(61);    //Vector<double, long> yarr3_(61);
		NumericMatrix<double, long> matrix1(3, 61);// matrix2(3, 61);    // One for mean, another for std
		// Input data into matrix
		matrix1(1, 1) = 0.0;    matrix1(2, 1) = 0.0;    matrix1(3, 1) = 0.0;
		for (long j = matrix1.MinColumnIndex() + 1; j <= matrix1.MaxColumnIndex(); j++)
		{
			matrix1(1, j) = my_repeat.Beat_Expected_CAAR[j - 2] * 100.0;    // let data appear as percentage
			matrix1(2, j) = my_repeat.Meet_Expected_CAAR[j - 2] * 100.0;
			matrix1(3, j) = my_repeat.Miss_Expected_CAAR[j - 2] * 100.0;
		}

		double h1 = 1.0;
		xarr[xarr.MinIndex()] = -30.0;
		for (long i = xarr.MinIndex() + 1; i <= xarr.MaxIndex(); i++)
		{
			xarr[i] = xarr[i - 1] + h1;
		}

		// labels for 3 groups
		list<string> rowlabels;
		rowlabels.push_back("Beat");    rowlabels.push_back("Meet");    rowlabels.push_back("Miss");

		// Names for different sheets
		string name1 = "Expected CAAR";

		list<std::string> columnlabels = convertToString(xarr);    // From day-30 to day30

		ExcelDriver& excel = ExcelDriver::Instance();
		excel.MakeVisible(true);        // Default is INVISIBLE!    -> open excel, creat empty sheet "Chart Data"
		excel.AddMatrix(name1, matrix1, rowlabels, columnlabels);    // Sheet for Expected AAR

		yarr1[1] = 0.0;        yarr2[1] = 0.0;        yarr3[1] = 0.0;
		for (long j = yarr1.MinIndex() + 1; j <= yarr1.MaxIndex(); j++)
		{
			yarr1[j] = my_repeat.Beat_Expected_CAAR[j - 2] * 100.0;    // let data appear as percentage
			yarr2[j] = my_repeat.Meet_Expected_CAAR[j - 2] * 100.0;
			yarr3[j] = my_repeat.Miss_Expected_CAAR[j - 2] * 100.0;
		}

		try
		{
			string title = "Expected CAAR Plot for 3 Groups";        // Chart title
			string ylabel = "Cumulative Average Abnormal Return";
			string xlabel = "Days";

			list<Vector<double, long> > functionResult;        // Data

			functionResult.push_back(yarr1);    functionResult.push_back(yarr2);    functionResult.push_back(yarr3);
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
	}

	cout << endl;
	cout << "***************************************************************" << endl;
	cout << "After you finished the program, please close the Excel Sheet!" << endl;
	cout << "Thank you for using our software!~~~" << endl;
	cout << "***************************************************************" << endl;

	return 0;
}
