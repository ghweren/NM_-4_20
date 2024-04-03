#include "GL\glew.h"
#include "GL\glut.h"
#include "GLFW\glfw3.h" 
#include <iostream>
#include <vector>
#include "LeastSquareMethod.h"
#define PI 3.14159265 


using namespace std;

void drawXY();
void drawGraph(vector<vector<double>> table, vector<vector<double>> result , double rangeX, double rangeY, float sx, float sy, float dx, float dy);
int Visualisation(vector<vector<double>> table, vector<vector<double>> result);
vector<vector<double>> normalize(vector<vector<double>> points);
double function(double x);
void print_table(vector<vector<double>> table)
{
	cout << '\n';
	for (int i = 0; i < table.size(); i++)
	{
		cout << table[i][0] << ' ';
	}
	cout << '\n';
	for (int i = 0; i < table.size(); i++)
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

		table = normalize(table);
		result = normalize(result);

		print_table(table);
	
	return Visualisation(table,result);
}

vector<vector<double>> normalize(vector<vector<double>> points) {
	
	double maxX = abs(points[0][0]), maxY = abs(points[0][1]);
	for (int i = 0; i < points.size(); i++)
	{
		if (abs(points[i][0])>maxX)
			maxX = abs(points[i][0]);
		if (abs(points[i][1])>maxY)
			maxY = abs(points[i][1]);
	}
	double scaleX = 1 / maxX;
	double scaleY = 1 / maxY;

	for (int i = 0; i < points.size(); i++)
	{
		points[i][0] *= scaleX;
		points[i][1] *= scaleY;
	}

	return points;
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

void drawGraph(vector<vector<double>> table, vector<vector<double>> result) {

	
	glColor3f(1.0f, 0.0f, 0.0f);
	//glPushMatrix();
	//glScalef(sx, sy, 1);
	//glTranslatef(-dx, -dy, 0);
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i = 0; i < table.size(); i++)
		glVertex2f(table[i][0], table[i][1]);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < result.size(); i++)
		glVertex2f(result[i][0], result[i][1]);
	glEnd();
	//glPopMatrix();
}

double function(double x)
{
	return sin(x);
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
	glViewport(0, 0, 1366, 768);

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
			drawGraph(table, result);
			glfwSwapBuffers(window1);
			glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}