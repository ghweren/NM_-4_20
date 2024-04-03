#include "GL\glew.h"
#include "GL\glut.h"
#include "GLFW\glfw3.h" 
#include <iostream>
#include <vector>
#include "LeastSquareMethod.h"
#define PI 3.14159265 


using namespace std;

void drawXY();
void drawGraph(vector<vector<double>> table, vector<vector<double>> result, float sx, float sy, float dx, float dy);
int Visualisation(vector<vector<double>> table, vector<vector<double>> result);
double function(double x);
void print_table(vector<vector<double>> table)
{
	cout << '\n';
	for (int i = 0; i < table.size() - 1; i++)
	{
		cout << table[i][0] << ' ';
	}
	cout << '\n'<<1;
	for (int i = 0; i < table.size() - 1; i++)
	{
		cout << table[i][1] << ' ';
	}
}

int main() {

		int n;
		cout << "Enter the n: ";
		cin >> n;
		cout << "\nEnter the start: ";
		double start;
		cin >> start;
		double step;
		cout << "\nEnter the step: ";
		cin >> step;
		vector<vector<double>> table;
		for (int i = 0; i < n; i++)
		{
			vector<double> temp;
			temp.push_back(start);
			temp.push_back(function(start));
			table.push_back(temp);
			start += step;
		}

		vector<vector<double>> result = (new LeastSquareMethod)->Calculation(table, 1);
	
	return Visualisation(table,result);
}

void drawXY()
{
	glBegin(GL_LINES); 
	glColor3f(0.0f, 0.0f, 0.0f); 
	glVertex2f(0, 1); 
	glVertex2f(0, -1); 
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
}

void drawGraph(vector<vector<double>> table, vector<vector<double>> result, float sx, float sy, float dx, float dy) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glScalef(sx, sy, 1);
	glTranslatef(-dx, -dy, 0);
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i = 0; i < table.size(); i++)
		glVertex2d(table[i][0], table[i][1]);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < result.size(); i++)
		glVertex2d(result[i][0], result[i][1]);
	glEnd();
	glPopMatrix();
}

double function(double x)
{
	return sin(x)+x;
}

int Visualisation(vector <vector<double>> table, vector<vector<double>> result)
{
	GLFWwindow* window1;
	GLFWwindow* window2;

	if (!glfwInit()) {
		return -1;
	}

	// Создаем первое окно
	window1 = glfwCreateWindow(800, 600, "Window 1", NULL, NULL);
	if (!window1) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window1);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glViewport(0, 0, 800, 600);

	float sx = 2.0 / (table[table.size() - 1][0] - table[0][0]);
	float dx = (table[table.size() - 1][0] + table[0][0])*0.5;
	float min = table[0][1];
	float max = table[0][1];
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i][1] < min)
			min = table[i][1];
		if (table[i][1] > max)
			max = table[i][1];
	}
	float sy = 2.0 / (max - min);
	float dy = (max + min)*0.5;

	while (!glfwWindowShouldClose(window1)) {
			glfwMakeContextCurrent(window1);
			glClear(GL_COLOR_BUFFER_BIT);
			drawXY();
			drawGraph(table,result,sx,sy,dx,dy);
			glfwSwapBuffers(window1);
			glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}