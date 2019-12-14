/*
 * @Author: Laureline
 * @Date: 2019-12-05 16:49:52
 * @LastEditors: Laureline
 * @LastEditTime: 2019-12-11 12:46:18
 * @Description: Use gnuplot to visualize time series
 */

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void plotResults(double* xData, double* yData, double* yData2, double* yData3, int dataSize) {
	FILE* gnuplotPipe, * tempDataFile;
	const char* tempDataFileName1 = "Beat";
	const char* tempDataFileName2 = "Meet";
	const char* tempDataFileName3 = "Miss";
	double x, y, x2, y2, x3, y3;
	int i;
	gnuplotPipe = _popen("D:\\gnuplot\\bin\\gnuplot", "w");
	if (gnuplotPipe) {
		fprintf(gnuplotPipe, "plot \"%s\" using 1:2 title 'Beat' with lines linetype 4 smooth csplines, \"%s\" using 1:2 title 'Meet' with lines linetype 6 smooth csplines, \"%s\" using 1:2 title 'Miss' with lines linetype 8 smooth csplines\n", tempDataFileName1, tempDataFileName2, tempDataFileName3);
		fflush(gnuplotPipe);
		/*tempDataFile = fopen(tempDataFileName1, "w");*/
		tempDataFile = fopen("Beat", "w");
		for (i = 0; i <= dataSize; i++) {
			x = xData[i];
			y = yData[i];
			fprintf(tempDataFile, "%lf %lf\n", x, y);
		}
		fclose(tempDataFile);

		//tempDataFile = fopen(tempDataFileName2, "w");
		tempDataFile = fopen("Meet", "w");
		for (i = 0; i <= dataSize; i++) {
			x2 = xData[i];
			y2 = yData2[i];
			fprintf(tempDataFile, "%lf %lf\n", x2, y2);
		}
		fclose(tempDataFile);

		//tempDataFile = fopen(tempDataFileName3, "w");
		tempDataFile = fopen("Miss", "w");
		for (i = 0; i <= dataSize; i++) {
			x3 = xData[i];
			y3 = yData3[i];
			fprintf(tempDataFile, "%lf %lf\n", x3, y3);
		}
		fclose(tempDataFile);
		//printf("press enter to continue...");
		//getchar();
		//remove(tempDataFileName1);
		//remove(tempDataFileName2);
		//remove(tempDataFileName3);
		fprintf(gnuplotPipe, "exit \n");
	}
	else {
		printf("gnuplot not found...");
	}
}

