#include "stdafx.h"
#include "Display.h"

void display_vec(vector<double>& vec)
{
	cout << setiosflags(ios::fixed) << setprecision(4);
	int nrow = 10, ncol = 6;    // our vector is a 1*60, we change into 10*6
	for (int i = 0; i <= nrow - 1; i++)
	{
		for (int j = 0; j <= ncol - 1; j++)
			cout << setw(8) << vec[6 * i + j] * 100.0 << "%" << "\t";
		cout << endl;
	}
	cout << endl;
}

void display_vec2(vector<double>& vec)
{
	//    output double
	cout << setiosflags(ios::fixed) << setprecision(4);
	int nrow = 10, ncol = 6;    // our vector is a 1*60, we change into 10*6
	cout << setiosflags(ios::fixed) << setprecision(4);
	for (int i = 0; i <= nrow - 1; i++)
	{
		for (int j = 0; j <= ncol - 1; j++)
			cout << setw(8) << vec[6 * i + j] << "\t";
		cout << endl;
	}
	cout << endl;
}

void display_in_file(ofstream& fout, vector<double>& vec)
{
	//    int N = vec.size();
	int nrow = 6, ncol = 10;    // our vector is a 1*60, we change into 5*12
	fout << setiosflags(ios::fixed) << setprecision(4);
	for (int i = 0; i <= nrow - 1; i++)
	{
		for (int j = 0; j <= ncol - 1; j++)
			fout << setw(8) << vec[10 * i + j] * 100.0 << "%";
		fout << endl;
	}

	fout << endl;
}

void ShowMenu()
{
	cout << "Menu: " << endl;
	cout << "Please enter 1, 2, 3, 4, 0 to select your option:" << endl;
	cout << "1.Retrieve historical price data for all stocks." << endl;
	cout << "2.Pull information for one stock." << endl;
	cout << "3.Show AAR,AAR SD,CAAR or CAAR SD for one group." << endl;
	cout << "4.Show the graph with CAAR for 3 groups." << endl;
	cout << "0.Exit the program." << endl;
	cout << endl;
}