#include "stdafx.h"
#include "Operator.h"

using namespace std;

Vector_ operator-(const Vector_& V, const Vector_& W)
{
	int size = V.size();
	Vector_ U(size);
	for (int i = 0; i < size; i++)
	{
		U[i] = V[i] - W[i];
	}
	return U;
}

Vector_ operator/(const Vector_& V, const double n)
{
	int size = V.size();
	Vector_ U(size);
	for (int i = 0; i < size; i++)
	{
		U[i] = V[i] / n;
	}
	return U;
}

Vector_ sqrt(const Vector_& V)
{
	int d = V.size();
	Vector_ U(d);
	for (int j = 0; j < d; j++) U[j] = sqrt(V[j]);
	return U;
}

Vector_ sqrr(const Vector_& V)
{
	int d = V.size();
	Vector_ U(d);
	for (int j = 0; j < d; j++)
		U[j] = V[j] * V[j];
	return U;
}

Vector_ operator+=(Vector_& V, const Vector_& W)
{
	int size = V.size();
	for (int i = 0; i < size; i++)
	{
		V[i] += W[i];
	}
	return V;
}

Vector_ operator/=(Vector_& V, const double n)
{
	int size = V.size();
	for (int i = 0; i < size; i++)
	{
		V[i] /= n;
	}
	return V;
}