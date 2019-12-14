/*
 * @Author: Koda Song
 * @Date: 2019-11-29 14:58:51
 * @LastEditors: Laureline
 * @LastEditTime: 2019-12-11 12:44:45
 * @Description: Display vector beautifully into console
 */

#pragma once
#ifndef Display_h
#define Display_h

#include <iostream>
#include <sstream> 
#include <fstream>
#include <string> 
#include <iomanip>
#include <vector>
using namespace std;

// cout a vector(60) like 10*6 matrix, with every element * 100% -> percentage
void display_vec(vector<double>& vec);

// No percentage
void display_vec2(vector<double>& vec);

// fout vector in files
void display_in_file(ofstream& fout, vector<double>& vec);

// Our Main Menu
void ShowMenu();

#endif // !Display_h