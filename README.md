# fft_simd
A simple demo shows how to use the SIMD,*Single Instruction Multiple Data*, to optimize and accelerate the FFT algorithm.

- [x] **Task 1.** Implement standard DFT algorithm with C++. See [task1_solution]()

- [x] **Task 2.** Rewrite the DFT with Cooley–Tukey FFT algorithm. See [task2_solution]()

- [x] **Task 3.** Ues SIMD to accelerate the FFT alogrithm. See blews in this page.

- [x] **Task 4.** Make a time consuming contrast among these algorithms.See the table as blews:

  | Algorithm     | Time consum                                     |
  | ------------- | ----------------------------------------------- |
  | Standard dft  | 606 ms                                          |
  | FFT           | 74 ms (out-off-place algorithm) ,7ms (in-place) |
  | FFT with SIMD | 1.011 ms                                        |

To be Completed :D...

----------

### **Introduction to SIMD** 

Referecnr [the wiki of SIMD](https://en.wikipedia.org/wiki/SIMD).

### **SIMD instructions chosen**

We use SSE2 in this project. SSE2 (Streaming SIMD Extensions 2) is one of the Intel SIMD, it supports two double-precision-floate  operations as its MMX rigister are extended from 64 to 128 bits.



### **SIMD instructions exercise**

To be familiar with SSE2 instructions,  we use SSE2 to compute the complex multiplication as an exercise.

Complex multiplication can be described as  follows:
$$
if A = a+b*j,B=c+d*j,then,A*B=(ac-bd)+(bc+ad)*j
$$
We use a figure to summary and described the complex multiplication using SSE2:

*Missing a figure  :D...*

You can find the code in the **complex_mul(double * A, double * B)** function in the project.



### **Using SIMD to accelerate the FFT**

The FFT algorithm was introduced in [task2_solution](), reviewing the codes,  we can find that the combing part consum most time. So we can use SIMD to rewrite this part. Blew  is the  orginal code:

```c++
			...
            // combine the odd and even parts
			complex<double> e = X[k];			// even
			complex<double> o = X[k + N / 2];   // odd
												// w is the "twiddle-factor"
			complex<double> w = exp(complex<double>(0, -2.*PI*k / N));
			X[k] = e + w * o;
			X[k + N / 2] = e - w * o;
			...
```

Well, parameters e,o and w are complex type, and our goal becomes using SIMD to process a complex addition, a complex subtraction and a complex  multiplication. 

- First, using a struct type ,***comp***,to replace the C++ built-in complex type.

```c++
struct comp {
	double real =0;
	double imag = 0;
};
```

The comp struct pack two double-type value, real part and imag part. So we can use a *comp-pointer* to access a complex number. In fact, a *comp*  takes up 8 bytes,128 bit, and it can be loaded into a SSE2's MMX rigister.

- Rewrite the original codes with SSE2 instructions. 

```c++
			__m128d o = _mm_load_pd( (double *)&X[k + N/2 ] );   // odd
			double cc = cos(-2.*PI*k / N);
			double ss = sin(-2.*PI*k / N);
			__m128d wr =  _mm_set_pd( cc,cc );		// cc 
			__m128d wi =  _mm_set_pd( ss, ss );		// dd 
			// compute the w*o
			wr = _mm_mul_pd(o,wr);					// ac|bc
			__m128d n1 = _mm_shuffle_pd(o,o,_MM_SHUFFLE2(0,1) ); // invert
			wi = _mm_mul_pd(n1, wi);				// bd|ad
			n1 = _mm_sub_pd(wr, wi);				// ac-bd|x
			wr = _mm_add_pd(wr, wi);				// x|bc+ad
			n1 = _mm_shuffle_pd(n1,wr,_MM_SHUFFLE2(1,0));// select ac-bd|bc+ad

			o = _mm_load_pd((double *)&X[k]);		// load even part
			wr = _mm_add_pd(o, n1);					// compute even part, X_e + w * X_o;
			wi = _mm_sub_pd(o, n1);					// compute odd part,  X_e - w * X_o;
			_mm_store_pd((double *)&X[k],wr);
			_mm_store_pd((double *)&X[k + N/2],wi);
```

We use 4 MMX rigisters, and cost 4 load/store , 2 set ,6 ops( +-*/) , 2 reorder operations. It's obvious that the time consuming of 1024-point FFT was decreased from 7ms to 1.01ms !



----------------------

### Some useful link:.

**FFT:**

https://en.wikipedia.org/wiki/Fast_Fourier_transform		Introduction to FFT

https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm Cooley–Tukey FFT algorithm

**SIMD:**

SIMD and sse2 introduction:

​	https://www.intel.com/content/www/us/en/support/articles/000005779/processors.html

**Intel(R) C++ Compiler Intrinsics Reference - Intel® Software:**

​	https://software.intel.com/sites/default/files/ee/11/6373   

**Streaming SIMD Extensions 2 Instructions:**

​	https://msdn.microsoft.com/zh-cn/library/kcwz153a%28v=vs.110%29.aspx?f=255&MSPPError=-2147217396

Intrinsics Guide:

​	https://software.intel.com/sites/landingpage/IntrinsicsGuide/#cats=Load&expand=3296