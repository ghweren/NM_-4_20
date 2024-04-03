#pragma once
#include <iostream>
#include <vector>
using namespace std;

class GaussMethod
{
public:
	vector<double> Calculation(vector<vector<double>> matrix, vector<double> f)
	{
		int n = matrix.size();

		for (int i = 0; i < n; i++) {
			double norm = matrix[i][i];
			for (int j = 1; j < n; j++)
				matrix[i][j] /= norm;
			f[i] /= norm;
			matrix[i][i] = 1;
			for (int j = i + 1; j < n; j++) {
				double factor = matrix[j][i];
				for (int k = i + 1; k < n; k++)
					matrix[j][k] -= factor * matrix[i][k];
				f[j] -= factor * f[i];
				matrix[j][i] = 0;
			}
		}

		vector<double> result(n);
		for (int i = n - 1; i >= 0; i--) {
			double sum = 0;
			for (int j = i + 1; j < n; j++)
				sum += matrix[i][j] * result[j];
			result[i] = (f[i] - sum);
		}

		return result;
	}

};