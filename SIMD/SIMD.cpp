// SIMD.cpp: 定义控制台应用程序的入口点。
// Target: Be familiar with the SIMD command.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <intrin.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <string>
#include <complex>
using namespace std;
#define PI 3.141592653589793238462643383279502884
int standard_fft( vector<double>fft_in, vector<complex<double>> &fft_out );
int main()
{
	/*----------------------------------------------------------------
	*	SIMD test.
	* -Task 1. Implement standard DFT algorithm with C++.
	* Task 2. Rewrite the DFT with Cooley–Tukey FFT algorithm.
	* Task 3. Ues SIMD to accelerate the FFT alogrithm.
	* Task 4. Make a time consuming contrast among these algorithms.
	----------------------------------------------------------------*/
	//const double  PI = acos(-1.0);

	// read the testing data.
	ifstream fi("fft_1024.txt");
	vector<double> data;
	string temp;
	while (fi.good())
	{
		getline(fi,temp);
		data.push_back( stod(temp));
	}
	vector<complex<double>> result;
	standard_fft(data, result);

	// output the result
	ofstream fo("fft_out_exp.txt", ios::ate);
	for (auto per_data : result) {
		fo << per_data.real() <<" + "<< per_data.imag()<<"j"<< "\n";
	}

	fi.close();
	fo.close();
	

    return 0;
}

int standard_fft(vector<double> fft_in, vector<complex<double>> &fft_out)
{
	// Standard fft algorithm without any optimization.
	// Ref:https://en.wikipedia.org/wiki/DFT

	int N = fft_in.size();
	for (size_t k = 0; k != N; ++k) {
		//complex<double> x_n(0, 0);
		double re = 0;												// the real part
		double im = 0;												// the imag part
		for (size_t n = 0; n != N; ++n) {
			re += fft_in[n] * cos(-double(k * 2 * PI * n / N));		// Euler's formula： exp( i*x ) = cos_x + i*sin_x
			im += fft_in[n] * sin(-double(k * 2 * PI * n / N));
			//x_n += data[n] * exp( (double)k *-1i * 2.0*PI* (double)( n )/double( N) );	 // 注意整数除法与浮点除法
		}

		fft_out.push_back(complex<double>(re, im));
	}
	return 0;
}
