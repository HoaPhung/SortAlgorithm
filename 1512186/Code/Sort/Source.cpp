#include "Sort.h"

int main() {
	RunSort run;
	int*a;
	int n;
	int temp[5] = { 1000,3000,10000,30000,100000 };
	string state[4] = { "Random","Sorted","Reverse","NearSorted" };
	ofstream result;
	result.open("Result.csv");
	result << "Input State" << "," 
		<< "Input Size" << "," 
		<< "Selection" << "," 
		<< "Bubble" << "," 
		<< "Insertion" << "," 
		<< "Merge" << "," 
		<< "Quick" << "," 
		<< "Heap" << "," 
		<< "Radix" << endl;
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 5; i++) {
			float time;
			n = temp[i];
			a = new int[n];
			result << state[k] << "," << temp[i] << ",";
			for (int j = 1; j < 8; j++) {
				time = getTime(run, a, n, j, k+1);
				result << time << ",";
			}
			delete[]a;
			result << endl;
		}
	}
	result.close();
	system("pause");
	return 0;
}