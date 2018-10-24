# fft_simd
A simple demo shows how to use the SIMD,*Single Instruction Multiple Data*, to optimize and accelerate the FFT algorithm.

- [x] **Task 1.** Implement standard DFT algorithm with C++. See [task1_solution]()

- [x] **Task 2.** Rewrite the DFT with Cooley–Tukey FFT algorithm. See [task2_solution]()

- [x] **Task 3.** Ues SIMD to accelerate the FFT alogrithm. See blews.

- [x] **Task 4.** Make a time consuming contrast among these algorithms.See the table as blews:

  | Algorithm     | Time consum                                     |
  | ------------- | ----------------------------------------------- |
  | Standard dft  | 606 ms                                          |
  | FFT           | 74 ms (out-off-place algorithm) ,7ms (in-place) |
  | FFT with SIMD | 1.011 ms                                        |

To be Completed :D...

----------

SIMD 介绍

指令介绍 （列出参考链接和文档）

指令练习：复数计算，配图

使用 SIMD 加速 FFT，列公式

