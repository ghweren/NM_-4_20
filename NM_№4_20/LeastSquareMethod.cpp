#include "LeastSquareMethod.h"

vector<vector<double>>LeastSquareMethod::Calculation(vector<vector<double>> table, int degree)
{
	vector<vector<double>> matrix(degree+1);
	vector<double> b;
	for (int i = 0; i <= degree; i++)
	{
		for (int j = 0; j <= degree; j++)
		{
			matrix[i].push_back(generate_c(table, i + j));
		}
		b.push_back(generate_b(table, i));
	}
	vector<double> a = (new GaussMethod)->Calculation(matrix, b);
	vector<vector<double>> result;
	for (int i = 0; i < table.size(); i++)
	{
		vector<double> temp;
		temp.push_back(table[i][0]);
		temp.push_back(generate_y(a, table[i][0]));
		result.push_back(temp);
	}
	return result;
}

double LeastSquareMethod::generate_c(vector<vector<double>> table, int k)
{
	double c=0;
	for (int i = 0; i < table.size(); i++)
	{
		double x = 1;
		double x_temp=table[i][0];
		for (int j = 0; j < k; j++)
			x *= x_temp;
		c += x;
	}
	return c;
}
double LeastSquareMethod::generate_b(vector<vector<double>> table, int k)
{
	double b = 0;
	for (int i = 0; i < table.size(); i++)
	{
		double x = 1;
		double x_temp = table[i][0];
		for (int j = 0; j < k; j++)
			x *= x_temp;
		b += (x*table[i][1]);
	}
	return b;
}

double LeastSquareMethod::generate_y(vector<double> a, double x)
{
	double y = a[0];
	cout << a[0] << ' ';
	for (int i = 1; i < a.size(); i++)
	{
		double x_temp = x;
		for (int j = 1; j < i; j++)
			x_temp *= x;
		y += a[i] * x_temp;
		cout << a[i] << ' ';
	}
	return y;
}