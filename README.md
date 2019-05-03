# Sampling-Profiler-C-implementation
A sampling profiler probes the target program's call stack at regular intervals using operating system interrupts.
## Getting Started
### Prerequisites
Please first install "libunwind" library from "www.nongnu.org/libunwind/download.html".
### Installing
```
gcc -o main main.c hotspots_sampling.c -lunwind -lunwind-x86_64
```
## Running the tests
sample at 500Hz
```
./main 500
```
## Output
sample frequency: 500 Hz

running time：1323.70 ms

rtime(%)	 rtime(ms)	 name

  0.50  	    666.86    	 func_c  
  0.30  	    398.51    	 func_b  
  0.10  	    132.17    	 main  
  0.10  	    126.16  	   func_a
  ## Authors

* **Chou Kuan Yu** - *Initial work* - [zhougy18](https://github.com/zhougy18)
