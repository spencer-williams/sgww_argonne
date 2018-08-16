from matplotlib import pyplot as pl
from matplotlib import ticker as ticker
import numpy as np
import math
from matplotlib.ticker import AutoMinorLocator

global x, xaxis, onetwonode, twofivenode, fiveonenode, onesigma, twosigma, threesigma
x = np.linspace(0, 524288, 20)
xaxis = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288]
onetwonode = []
twofivenode = []
fiveonenode = []
onesigma = []
twosigma = []
threesigma = []

def main():
    read_file()
    graph()

def read_file():
    file = open("/Users/spenc/OneDrive/Documents/Python Projects/gathersigma.txt", "r") 
    for line in file:
        ans = line.split("\t")
        ans[4] = ans[4].rstrip()
        if(ans[0].isdigit() == True):
            onetwonode.append(float(ans[1])), twofivenode.append(float(ans[3])), onesigma.append(float(ans[2])), twosigma.append(float(ans[4]))
        print(ans)

def graph():
    pl.xticks(np.linspace(0, 524288, 20), xaxis)
    pl.grid()
    pl.plot(x, onetwonode, color="blue")
    pl.plot(x, twofivenode, color="red")
    firstdown = [None] * 20
    firstup = [None] * 20
    secondown = [None] * 20
    secondup = [None] * 20
    for i in range(len(onetwonode)):
        firstdown[i] = onetwonode[i] - onesigma[i]
        firstup[i] = onetwonode[i] + onesigma[i]
        secondown[i] = twofivenode[i] - twosigma[i]
        secondup[i] = twofivenode[i] + twosigma[i]

    pl.fill_between(x, firstdown, firstup, alpha=0.5, edgecolor='#1B2ACC', facecolor='#089FFF',
        linewidth=0, linestyle='dashdot', antialiased=True, label='128')
    pl.fill_between(x, secondown, secondup, alpha=0.5, edgecolor='#CC4F1B', facecolor='#FF9848',
        linewidth=0, antialiased=True, label='256')
    pl.legend(loc='upper left', fontsize=13)
    pl.xlabel('Message Size', fontdict=None, labelpad=False, fontsize = 13)
    ax = pl.gca()
    ax.xaxis.set_label_coords(1.0, -0.06)
    pl.ylabel('Relative Latency [(in-out)/out]', fontdict=None, labelpad=False, fontsize = 13)
    pl.title('Gather', fontsize=14)
    pl.show()

if __name__ == "__main__":
    main()
