# MVAPICH OSU Micro-Benchmarks on theta
During my time at Argonne, I used several tests from Ohio State Universities OSU Micro-Benchmark software. I edited the code in the tests I used so that the tests would run 1000 tests instead of just one for each message size, and so that they would print out the average and sigma of the 1000 runs performed. This was implemented to smooth out the final result thus making our data less susceptible to erratic outputs from individual tests. [If you want to read more on OSU Micro-Benchmarks follow this link.](http://mvapich.cse.ohio-state.edu/benchmarks/)

Within this directory I have included the files osu_util.c and osu_util.h. These files are imported by all the benchmark programs and contain variables and methods. I edited these two files to add a method which properly prints out the tests results as I specified above. Also within this directory I have included a singularity recipe file which builds the container I used to perform tests from a container. [Here is a link to the singularity hub page where it is already built.](https://www.singularity-hub.org/collections/1252)



### How the tests were run
Each different benchmark used a python script to create a directory tree and a COBALT submit script for a test inside and outside of a singularity container. These python scripts can be found within their appropriate benchmark directories, and are named as "second_auto.py". The structure of the COBALT submit scripts is explained in these pictures:
![128 and 256 node test](https://i.imgur.com/8POGbRN.png)
![512 node test](https://i.imgur.com/dPr7PFL.png)
The blue area represents the COBALT script itself which runs bash scripts which are represented by the orange areas. The bash scripts are in the same location that the python script mentioned before is and they should be placed together when running the tests. The gray areas inside the orange areas represent apruns within the bash scripts which run the benchmarks either from a container or from outside a container.

# Project goal
The goal of this project was to compare the efficiency mpi functions within a container vs outside of a container on Theta.
