/*
 * @Author: Suki
 * @Date: 2019-12-08 10:06:48
 * @LastEditors: Suki
 * @LastEditTime: 2019-12-11 12:47:49
 * @Description: Operator Overloading
 */

#pragma once
#ifndef Operator_h
#define Operator_h

#include <iostream>
#include <vector>
using namespace std;

// Since Vector and Matrix are already used in "ExcelDriver"
// We use "Vector_" and "Matrix_" to rename vector<double> and vector< vector<double> >
typedef vector<double> Vector_;
typedef vector<Vector_> Matrix_;

Vector_ operator-(const Vector_& V, const Vector_& W);

Vector_ operator/(const Vector_& V, const double n);

Vector_ operator+=(Vector_& V, const Vector_& W);

Vector_ operator/=(Vector_& V, const double n);

Vector_ sqrt(const Vector_& V);  //calculate square root of a vector

Vector_ sqrr(const Vector_& V);  //calculate square of a vector


#endif // !Operator_h

