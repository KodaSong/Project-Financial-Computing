#pragma once
#ifndef Display1_h
#define Display1_h

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

void display_vec(vector<double>& vec)
{
	cout << setiosflags(ios::fixed) << setprecision(4);
	vector<double>::iterator itr;
	for (itr = vec.begin(); itr != vec.end(); itr++)
		cout << setw(8) << (*itr) * 100.0 << "%";        // Shown as Percentage
	cout << endl << endl;
}

//void display_in_file(ofstream& fout, vector<double>& vec)
//{
////    int N = vec.size();
//    int nrow = 5, ncol = 12;    // our vector is a 1*60, we change into 5*12
//    fout << setiosflags(ios::fixed) << setprecision(4);
//    for (int i = 0; i <= nrow - 1; i++)
//    {
//        for (int j = 0; j <= ncol - 1; j++)
//            fout << setw(8) << vec[12*i+j] * 100.0 << "%";
//        fout << endl;
//    }
//
//    fout << endl;
//}

#endif /* Display1_h */
