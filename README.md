# fft_simd
A simple demo shows how to use the SIMD,*Single Instruction Multiple Data*, to optimize and accelerate the FFT algorithm.

- [x] **Task 1.** Implement standard DFT algorithm with C++. See [task1_solution]()

- [x] **Task 2.** Rewrite the DFT with Cooley–Tukey FFT algorithm. See [task2_solution]()

- [ ] **Task 3.** Ues SIMD to accelerate the FFT alogrithm.

- [ ] **Task 4.** Make a time consuming contrast among these algorithms.See the table as blews:

  | Algorithm     | Time consum                                     |
  | ------------- | ----------------------------------------------- |
  | Standard dft  | 606 ms                                          |
  | FFT           | 74 ms (out-off-place algorithm) ,7ms (in-place) |
  | FFT with SIMD | 1.2 ms                                          |


To be Completed :D...
