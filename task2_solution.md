# Task2 solution

- Task 2. Rewrite the DFT with Cooley–Tukey FFT algorithm.

 Cooley–Tukey FFT algorithm  is the most common [fast Fourier transform](https://en.wikipedia.org/wiki/Fast_Fourier_transform) (FFT) algorithm. Our goals is to replace the standard DFT algorithm with FFT. In general, the DFT algoritm can be described as follows formula:
$$
{\displaystyle {\begin{matrix}X_{k}=\underbrace {\sum \limits _{m=0}^{N/2-1}x_{2m}e^{-{\frac {2\pi i}{N/2}}mk}} _{\mathrm {DFT\;of\;even-indexed\;part\;of\;} x_{n}}{}+e^{-{\frac {2\pi i}{N}}k}\underbrace {\sum \limits _{m=0}^{N/2-1}x_{2m+1}e^{-{\frac {2\pi i}{N/2}}mk}} _{\mathrm {DFT\;of\;odd-indexed\;part\;of\;} x_{n}}=E_{k}+e^{-{\frac {2\pi i}{N}}k}O_{k}.\end{matrix}}}
$$
The input sequeue's DFT, $ X_{k} $ , can be separed into two parts , the even part and oven part, and compute the  two parts' DFT respectively .Then finally,combine them you will get the orginal sequeue's DFT.  The process continues until the length of sequeue as small as possible ,at that moment subsequeue's DFT can be computed easily. We can reference the code blows and learn how the FFT  is going:

```c++
void fft2(complex<double>* X, int N) {
	if (N < 2) {
		// bottom of recursion.
		// Do nothing here, because already X[0] = x[0]
	}
	else {
		separate(X, N);						// all evens to lower half, all odds to upper half
		fft2(X, N / 2);						// recurse even items
		fft2(X + N / 2, N / 2);				// recurse odd  items
											// combine results of two half recursions
		for (int k = 0; k<N / 2; k++) {

			complex<double> e = X[k];			// even
			complex<double> o = X[k + N / 2];   // odd
												// w is the "twiddle-factor"
			complex<double> w = exp(complex<double>(0, -2.*PI*k / N));
			X[k] = e + w * o;
			X[k + N / 2] = e - w * o;
			/*
			comp e = X[k];						// even
			comp o = X[k + N / 2];				// odd
			complex<double> ww = exp(complex<double>(0, -2.*PI*k / N));
			comp w;
			w.real = ww.real();
			w.imag = ww.imag();
			comp wo = complex_mul_c(w, o);
			X[k].real = e.real + wo.real;
			X[k].imag = e.imag + wo.imag;
			X[k + N / 2].real = e.real - wo.real;
			X[k + N / 2].imag = e.imag - wo.imag;
			*/
		}
	}
}
```

With this FFT algorithm,it cost 7ms to compute a 1024 points DFT .Our processor is Intel(R) Core I5-3470. And it is faster than the standard DFT algorithm at the same condition, almost 600ms.

In the next section we will use SIMD to accelerate the FFT alogrithm above.

See [Task3: Accelerate the FFT alogrithm](https://github.com/jagger2048/fft_simd/blob/master/README.md).



_______

Ps:  At the begining I writed a FFT algorithm myself, which is a out-off-place algorithm and it cost 70ms to compute a 1024-point DFT. For learning SIMD operate , I chosed a faster and easy to understand FFT algorithm from the wiki .

Ref:  https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
