#!/usr/bin/env python
from mpi4py import MPI
import os

global jack
jack = "All work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play makes Jack a dull boy/nAll work and no play ma"

def main():
    print("RUNNING PYTHON SCRIPT")
    make_file()
    print("SUCESS")

def make_file():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    name = 'file_' + str(rank) + '.txt'
    print(name)
    os.system('echo ' + jack + ' > ' + name)


if __name__ == "__main__":
    main()
