/*
 * @Author: Koda Song
 * @Date: 2019-11-29 14:58:51
 * @LastEditors: Koda Song
 * @LastEditTime: 2019-12-04 00:51:30
 * @Description: 
 */

#include "stdafx.h"
#include <ctime>
#include "GroupStocks.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

double cmp(const pair<string, double>& x, const pair<string, double>& y)
{
	return x.second > y.second;		// Descending Order
}

void sortMapByValue(map<string, double>& tMap, vector<pair<string, double> >& tVector)
{
	for (map<string, double>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));

	sort(tVector.begin(), tVector.end(), cmp);
}

void group_stocks(vector<stock>& stockList, Group &stockgroup)
{
	map<string, double> surprise_map;	// key -> stock's name, value -> stock's surprise
	vector<stock>::iterator itr;
	for (itr = stockList.begin(); itr != stockList.end(); itr++)
		surprise_map[itr->name] = itr->surprise;

	vector<pair<string, double> > surprise_vec;
	sortMapByValue(surprise_map, surprise_vec);	// surprise is in descending order

	/*for (auto itr__ = surprise_vec.begin(); itr__ != surprise_vec.end(); itr__++)
		cout << itr__->first << itr__->second << endl;*/

	// Begin to group
	int size = surprise_vec.size();
	int size_beat = size / 3;	// Size of Group "Beat"; index = size - 1;
	int size_meet = size * 2 / 3;
	

	vector<stock>::iterator itr_;	
	for (itr_ = stockList.begin(); itr_ != stockList.end(); itr_++)
	{
		if (itr_->surprise >= surprise_vec[size_beat - 1].second)
			stockgroup.Beat.push_back(*itr_);			
		else if (itr_->surprise >= surprise_vec[size_meet - 1].second)
			stockgroup.Meet.push_back(*itr_);			
		else
			stockgroup.Miss.push_back(*itr_);
			
	}

}

Group SampleStocks(Group &group, int n)
{
	//srand(n);		// set a seed
	Group samplegroup;		// Initialization

	// group beat
	int size_beat = group.Beat.size();

	srand(time(NULL));
	for (int i = 0; i < 30; i++)
	{
		int rand_num = rand() % size_beat;	// generate a random number between 0 and size-1
		samplegroup.Beat.push_back(group.Beat[rand_num]);
	}

	// group match
	int size_meet = group.Meet.size();
	srand(time(NULL));		// set a seed
	for (int i = 0; i < 30; i++)
	{
		int rand_num = rand() % size_meet;	// generate a random number between 0 and size-1
		samplegroup.Meet.push_back(group.Meet[rand_num]);
	}

	// group miss
	int size_miss = group.Miss.size();
	srand(time(NULL));		// set a seed
	for (int i = 0; i < 30; i++)
	{
		int rand_num = rand() % size_miss;	// generate a random number between 0 and size-1
		samplegroup.Miss.push_back(group.Miss[rand_num]);
	}
	return samplegroup;
}

void Cal_C_AAR(Group& samplegroup)
{
	int stock_nums = 30;
	int days = 60;
	samplegroup.Beat_CAAR = 0.0; samplegroup.Meet_CAAR = 0.0; samplegroup.Miss_CAAR = 0.0;
	
	for (int i = 0; i < days; i++)	// The ith day
	{
		// First, get each group's AAR vector
		double res1 = 0.0, res2 = 0.0, res3 = 0.0;
		for (int j = 0; j < stock_nums; j++)	// The jth stock
		{	
			res1 += samplegroup.Beat[j].AR[i];		// the ith daily return of the jth stock
			res2 += samplegroup.Meet[j].AR[i];	// the ith daily return of the jth stock
			res3 += samplegroup.Miss[j].AR[i];		// the ith daily return of the jth stock
		}
		res1 /= stock_nums;	// Average Value for each group
		res2 /= stock_nums;
		res3 /= stock_nums;

		samplegroup.Beat_AAR.push_back(res1);	// ith days' AAR of Beat Group
		samplegroup.Meet_AAR.push_back(res2);
		samplegroup.Miss_AAR.push_back(res3);

		// Second, get each group's CAAR
		samplegroup.Beat_CAAR += samplegroup.Beat_AAR[i];
		samplegroup.Meet_CAAR += samplegroup.Meet_AAR[i];
		samplegroup.Miss_CAAR += samplegroup.Miss_AAR[i];
	}
	
}