#pragma once
#include <iostream>
#include <vector>
#include "GaussMethod.h"
using namespace std;

class LeastSquareMethod
{
public:
	vector<vector<double>> Calculation(vector<vector<double>> table, int degree);
private:
	double generate_c(vector<vector<double>> table, int k);
	double generate_b(vector<vector<double>> table, int k);
	double generate_y(vector<double> a, double x);
};