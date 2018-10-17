# Task1 solution

- Task 1. Implement standard DFT algorithm with C++.

As we all know, The DFT, *discrete Fourier transform* transforms, can be defined by follow formula:

$$
{\begin{aligned}X_{k}&=\sum _{n=0}^{N-1}x_{n}\cdot e^{-{\frac {2\pi i}{N}}kn}=\sum _{n=0}^{N-1}x_{n}\cdot [\cos(2\pi kn/N)-i\cdot \sin(2\pi kn/N)]\end{aligned}}
$$
The last expression follows from the previous one by Euler's formula, which can caculate the exponent using cosine operates. We can implement the DFT formula with C++ as belows:

```c++
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
			//x_n += fft_in[n] * exp( (double)k *-1i * 2.0*PI* (double)( n )/double( N) );	 
            // be careful for the division in C++
		}

		fft_out.push_back(complex<double>(re, im));
	}
	return 0;
}
```

Ps. The number of dft is the fft_i's size.

 The standard DFT algorithm takes more time to compute the retult and it's inefficient in real application.So we should consider the other faster algorithm , Cooley–Tukey FFT algorithm.

See [Task2: Cooley–Tukey FFT algorithm]().