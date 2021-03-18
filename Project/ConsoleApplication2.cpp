#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <chrono>


using namespace std;
using namespace chrono;


int FindSize(std::string path)
{
	ifstream in(path);
	string s;
	int i = 0;
	while (in.peek() != EOF) {
		getline(in, s);
		i++;
	}
	in.close();
	return i;
}


void Read(int* arrayNumb, std::string path)
{
	int i = 0;
	string line;
	ifstream in(path);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			int number = stoi(line);
			arrayNumb[i] = number;
			i++;
		}
	}
	in.close();
}


void quickSort(int* mas, int first, int last, int& counts)
{
	int mid, count;
	int f = first, l = last;
	mid = mas[(f + l) / 2];
	while (f < l)
	{
		while (mas[f] < mid)
		{
			f++;
			counts++;
		}
		while (mas[l] > mid)
		{
			l--;
			counts++;
		}
		if (f <= l)
		{
			count = mas[f];
			mas[f] = mas[l];
			mas[l] = count;
			f++;
			l--;
			counts++;
		}
		counts++;
	} 
	if (first < l) quickSort(mas, first, l,counts);
	if (f < last) quickSort(mas, f, last,counts);
}


int main()
{
	int iteration = 0;
	for (int i = 0; i < 100; i++)
	{		
		string path = "C:\\Users\\scum\\Desktop\\semestr\\Kit" + to_string(i) + ".txt";
		int size = FindSize(path);
		int *array = new int[size];

		Read(array, path);

		system_clock::time_point start = system_clock::now();
		quickSort(array, 0, size - 1, iteration);
		system_clock::time_point end = system_clock::now();
		duration<double> sec = end - start;

		cout << to_string(i + 1) + " " + "Time sort(microsec) " << duration_cast<microseconds>(end - start).count() << " Array size: "<<size<<" Iteration: " << iteration << endl;
		iteration = 0;		
		delete[] array;
	}
}
