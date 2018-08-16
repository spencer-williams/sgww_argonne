# Singularity files exists test
To run this test I first created a python script, named 'create_files.py', which uses mpi4py to create and name a 1 kilobyte file for every mpi rank you run the python script on. Then I created another python script, named 'time_test.py', which uses os and timit to time how long it takes to loop through the created files and perform os.path.exists() functions until 100k of them have been performed. The second python script also loops the number of times os.path.exists() is performed so that it starts with 100k times, then it goes through 200k times, then 400k times and so on.

I built a singularity container which has python3 installed which runs create_files.py when it is being built so that the files are created inside  itself. Then I used aprun on theta to run time_test.py from within the container. On theta I used miniconda to run create_files.py and an aprun to run time_test.py.

# Project goal
The goal of this project was to determine if accessing a large number of files on theta is faster if you use a singularity container. Since singularity caches its own files, it should be faster to access many files using a singularity container as opposed to accessing them without.

### The result
The results of the three tests I performed show that it is in fact faster to use a singularity container when accessing large numbers of files. The relative runtimes of the tests show that speed can be increased by factors of 7 and up when using a singularity container to access a large number of files. Also the speed of accessing files is much more consistent when using a singularity container as the relative error is much higher in tests which do not use containers compared to those which do.

[A spreadsheet of the results and graphs can be found at this link](https://docs.google.com/spreadsheets/d/1KicxNRm4tWdLVbVyrzV-rZebFYGGa000D3JopjkynYQ/edit?usp=sharing)

[The built singularity container on shub can be found here](https://www.singularity-hub.org/containers/3777)
