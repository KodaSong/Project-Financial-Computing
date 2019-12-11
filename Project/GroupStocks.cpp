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

using namespace std;

/*
	Map sort by key (Default) -> but cannot directly sort by value.
	So We first put map's elements (pair) into vector, and then sort it.
*/

// '>' overloading
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

	// Begin to group
	int size = surprise_vec.size();
	int size_beat = size / 3;	// Size of Group "Beat"; index = size - 1;
	int size_meet = size * 2 / 3;
	
	vector<stock>::iterator itr_;	
	for (itr_ = stockList.begin(); itr_ != stockList.end(); itr_++)
	{
		if (itr_->surprise >= surprise_vec[size_beat - 1].second)	// Highest surprise
			stockgroup.Beat.push_back(*itr_);			
		else if (itr_->surprise >= surprise_vec[size_meet - 1].second)	// Mid surprise
			stockgroup.Meet.push_back(*itr_);			
		else
			stockgroup.Miss.push_back(*itr_);
			
	}

}

Group SampleStocks(Group &group, int n)
{
	Group samplegroup;		// Initialization

	// group beat
	int size_beat = group.Beat.size();
	srand(time(NULL)+n);	// "+n" -> Since calculation is fast, sometimes time(NULL) are almost same in Bootstrapping
	for (int i = 0; i < 30; i++)
	{
		int rand_num = rand() % size_beat;	// '%' -> generate a random number between 0 and size-1
		samplegroup.Beat.push_back(group.Beat[rand_num]);
	}

	// group match
	int size_meet = group.Meet.size();
	srand(time(NULL)+n);		// set a seed
	for (int i = 0; i < 30; i++)
	{
		int rand_num = rand() % size_meet;	// generate a random number between 0 and size-1
		samplegroup.Meet.push_back(group.Meet[rand_num]);
	}

	// group miss
	int size_miss = group.Miss.size();
	srand(time(NULL)+n);		// set a seed
	for (int i = 0; i < 30; i++)
	{
		int rand_num = rand() % size_miss;	// generate a random number between 0 and size-1
		samplegroup.Miss.push_back(group.Miss[rand_num]);
	}
	return samplegroup;
}


void Cal_AAR(Group& samplegroup)
{
	int stock_nums = 30;
	int days = 60;
	Vector_ res1(60), res2(60), res3(60);
	for (int i = 0; i < stock_nums; i++) //the jth stock
	{
		res1 += samplegroup.Beat[i].AR;  // 60 days daily return of ith stock
		res2 += samplegroup.Meet[i].AR;  //60 days daily return of ith stock
		res3 += samplegroup.Miss[i].AR;  //60 days daily return of ith stock
	}
	res1 /= stock_nums; //Average Value for each group
	res2 /= stock_nums;
	res3 /= stock_nums;

	samplegroup.Beat_AAR = res1; // AAR of Beat Group
	samplegroup.Meet_AAR = res2;
	samplegroup.Miss_AAR = res3;
}

void Cal_CAAR(Group& samplegroup)
{
	Vector_ res1(60), res2(60), res3(60);
	int days = 60;

	res1[0] = samplegroup.Beat_AAR[0];
	res2[0] = samplegroup.Meet_AAR[0];
	res3[0] = samplegroup.Miss_AAR[0];
	for (int i = 1; i < days; i++)
	{
		res1[i] = samplegroup.Beat_AAR[i] + res1[i - 1];
		res2[i] = samplegroup.Meet_AAR[i] + res2[i - 1];
		res3[i] = samplegroup.Miss_AAR[i] + res3[i - 1];
	}
	samplegroup.Beat_CAAR = res1;
	samplegroup.Meet_CAAR = res2;
	samplegroup.Miss_CAAR = res3;
}