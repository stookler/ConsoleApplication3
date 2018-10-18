#include "pch.h"
#include<iostream>
#include<iomanip>  
#include<cmath>
#include<fstream>
using namespace std;

int main() {

	const int NUM_ROWS = 10;
	const int NUM_COLUMNS = 10;
	const int SET_PRECISION = 3;
	const int SET_WIDTH = 9;
	double temperature[NUM_ROWS][NUM_COLUMNS];
	double newTemperature[NUM_ROWS][NUM_COLUMNS];
	bool isStable = false;
	double difference = 0.0;
	double maxDifference = 0.0;
	double oldTemperature = 0.0;
	ofstream outputFile;

	cout << "Hotplate simulator" << endl << endl;
	cout << "Printing initial plate..." << endl;

	//initialize array
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			temperature[i][j] = 0.0;
			if ((i == 0) || (i == NUM_ROWS - 1)) {
				temperature[i][j] = 100.0;
			}
			if ((j == 0) || (j == NUM_COLUMNS - 1)) {
				temperature[i][j] = 0.0;
			}
		}
	}
	cout << fixed << setprecision(SET_PRECISION);

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			cout << fixed << setw(SET_WIDTH);
			if (j < NUM_COLUMNS - 1) {
				cout << temperature[i][j] << ",";
			}
			else {
				cout << temperature[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;


	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			newTemperature[i][j] = temperature[i][j];
		}
	}

	for (int i = 1; i < NUM_ROWS - 1; i++) {
		for (int j = 1; j < NUM_COLUMNS - 1; j++) {
			newTemperature[i][j] = (temperature[i - 1][j] + temperature[i][j - 1] + temperature[i][j + 1] + temperature[i + 1][j]) / 4.0;
		}
	}

	cout << "Printing plate after one iteration..." << endl;
	cout << fixed << setprecision(SET_PRECISION);

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			cout << fixed << setw(SET_WIDTH);
			if (j < NUM_COLUMNS - 1) {
				cout << newTemperature[i][j] << ",";
			}
			else {
				cout << newTemperature[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;

	while (!isStable) {
		for (int i = 0; i < NUM_ROWS; i++) {
			for (int j = 0; j < NUM_COLUMNS; j++) {
				temperature[i][j] = newTemperature[i][j];
			}
		}
		maxDifference = 0.0;
		for (int i = 1; i < NUM_ROWS - 1; i++) {
			for (int j = 1; j < NUM_COLUMNS - 1; j++) {
				oldTemperature = newTemperature[i][j];
				newTemperature[i][j] = (temperature[i - 1][j] + temperature[i][j - 1] + temperature[i][j + 1] + temperature[i + 1][j]) / 4.0;
				difference = newTemperature[i][j] - oldTemperature;
				if (pow(0.5, (difference * difference)) > maxDifference) {
					maxDifference = difference;
				}
			}
		}  if (maxDifference <= 0.1) {
			isStable = true;
		}
	}
	cout << "Printing final plate..." << endl;
	cout << fixed << setprecision(SET_PRECISION);

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLUMNS; j++) {
			cout << fixed << setw(SET_WIDTH);
			if (j < NUM_COLUMNS - 1) {
				cout << newTemperature[i][j] << ",";
			}
			else {
				cout << newTemperature[i][j];
			}
		}
		cout << endl;
	}


	cout << "Outputting final plate to file Hotplate.csv...";
	cout << endl;

	ofstream outputFile;
	outputFile.open("Hotplate.txt");
		outputFile << fixed << setprecision(SET_PRECISION);
		for (int i = 0; i < NUM_ROWS; i++) {
			for (int j = 0; j < NUM_COLUMNS; j++) {
				outputFile << fixed << setw(SET_WIDTH);
				if (j < NUM_COLUMNS - 1) {
					outputFile << newTemperature[i][j] << ",";
				}
				else {
					outputFile << newTemperature[i][j];
				}
			}

			outputFile.close();
		}
	return 0;
}
