import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Circle
from matplotlib.collections import PatchCollection

# initialise some values
NCOLS = 6 # columns of output per particle
BULK = 50

with open("data/planets.dat") as planets:
    line = planets.readline()
    line = line.split()
    NITER = int(line[2].strip())

    lines = planets.readlines()
    lines = [line.split() for line in lines]
    masses = [int(float(line[0].strip()))**(1/10)*10 for line in lines if len(line) == 1]

# read the tab separated file
infile = open("data/output.dat")
lines = infile.readlines()
# split all the lines, ignore the '#' ones and transpose
cols = list(zip(*(line.strip().split('\t') for line in lines if not line.startswith('#'))))
cols = [[float(item.strip()) for item in col] for col in cols]


# start plotting yay
fig, ax = plt.subplots(figsize=(8,6))

lines = []
circles = []
patches = []

for i in range(0, len(cols), NCOLS):
    print(i)
    # print(cols[i])
    # print(cols[i+1])
    line, = ax.plot(cols[i], cols[i+1])
    lines.append(line)

    circle = Circle((cols[i][0], cols[i+1][0]), radius=masses[int(i/NCOLS)])
    patch = ax.add_patch(circle)
    circles.append(circle)
    patches.append(patch)


# x1, x2 = -5, 5
# y1, y2 = -120, 120
# ax.set_xlim(x1, x2)
# ax.set_ylim(y1, y2)
ax.set_aspect('equal', 'datalim')
# x1, x2 = ax.get_xlim()
# y1, y2 = ax.get_ylim()
# ax.xaxis.set_ticks(np.arange(x1, x2, (x2-x1)/10))
# ax.yaxis.set_ticks(np.arange(y1, y2, (y2-y1)/10))

def animate(i):
    global lines, cols, patches, circles

    for j, line in enumerate(lines):
        line.set_data(cols[NCOLS*j][0:i*BULK], cols[NCOLS*j+1][0:i*BULK])
        circles[j].center = cols[NCOLS*j][i*BULK], cols[NCOLS*j+1][i*BULK]
        patches[j] = ax.add_patch(circles[j])

    return lines + patches

anim = animation.FuncAnimation(fig, animate, frames=int(NITER/BULK), interval=0.2, repeat=True, blit=True)

# # Set up formatting for the movie files
# plt.rcParams['animation.ffmpeg_path'] ='D:\\Movies\\ffmpeg-20171120-8f4702a-win64-static\\bin\\ffmpeg.exe'
# FFwriter = animation.FFMpegWriter(fps=50)

# anim.save('planet.mp4', writer=FFwriter)

plt.show()
