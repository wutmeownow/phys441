#!/usr/local/bin/python3

import random
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

#abirdiebogeyratio = 1.9
#bbirdiebogeyratio = 1.9
#arisk = 0.55
#brisk = 0.55
abirdiebogeyratio = 2.5
bbirdiebogeyratio = 1.2
arisk = 0.80
brisk = 0.55

apar = 1/(1+arisk)
abirdielimit = (1 - apar)/(1 + 1/abirdiebogeyratio)
abogeylimit = abirdielimit/abirdiebogeyratio
print (abirdielimit,apar,abogeylimit)

bpar = 1/(1+brisk)
bbirdielimit = (1 - bpar)/(1 + 1/bbirdiebogeyratio)
bbogeylimit = bbirdielimit/bbirdiebogeyratio
print (bbirdielimit,bpar,bbogeylimit)

nholes = 18
holearray = [0 for i in range(0,nholes)]
numsim = 28000
nummatch = int(numsim/28)
ateamscore = 0
bteamscore = 0
ateamscorelist = [0 for i in range(0,nummatch)]
bteamscorelist = [0 for i in range(0,nummatch)]
matchindex = 0

for numsim in range(0,numsim):
    ascore = 0
    bscore = 0

    if numsim%28 == 0 and numsim > 0:
        #print ("A Team = ",ateamscore," B Team = ",bteamscore)
        ateamscorelist[matchindex]=ateamscore
        bteamscorelist[matchindex]=bteamscore
        matchindex = matchindex + 1
        ateamscore = 0
        bteamscore = 0

    for hole in range(1,nholes+1):

        arand = np.random.random_sample()
        brand = np.random.random_sample()

        if arand < abirdielimit:
            a = 3
        else:
            if arand > 1 - abogeylimit:
                a = 5
            else:
                a = 4

        if brand < bbirdielimit:
            b = 3
        else:
            if brand > 1 - bbogeylimit:
                b = 5
            else:
                b = 4

        if a < b:
            ascore = ascore + 1
        if a > b:
            bscore = bscore + 1

        diff = abs(ascore-bscore)

        #print ("Hole = ",hole," Score = ",diff," A = ",ascore," B = ",bscore)

        remain = nholes - hole

        if diff > remain:
            #print ("Win! Final Hole = ",hole," A Score = ",ascore," B Score = ",bscore)
            finalhole = hole
            if ascore > bscore:
                ateamscore = ateamscore + 1.0
            if ascore == bscore:
                ateamscore = ateamscaore + 0.5
            if ascore < bscore:
                bteamscore = bteamscore + 1.0
            break

        if hole == nholes:
            finalhole = hole
            ateamscore = ateamscore + 0.5
            bteamscore = bteamscore + 0.5
            #print ("Tie? Final Hole = ",hole," A Score = ",ascore," B Score = ",bscore)

    #print ("Done! Final Hole = ",finalhole)
    holearray[finalhole-1]=holearray[finalhole-1]+1

for i in range(0,nholes):
    holearray[i]=holearray[i]/numsim

#print (holearray)

ryderdata = [.0, .0, .214,.074,.308,.240,.250]
rydererror = [.08, .08, .077,.049,.087,.081,.082]

starthole = 12
simhole = [0 for i in range(0,nholes-starthole+1)]
simdata = [0 for i in range(0,nholes-starthole+1)]
chi2 = 0.0
for i in range(starthole,nholes+1):
    simhole[i-starthole]=i
    simdata[i-starthole]=holearray[i-1]
    chi2 = chi2 + pow((simdata[i-starthole]-ryderdata[i-starthole])/rydererror[i-starthole],2)

print("Chi^2 / DOF = ",chi2/(nholes-starthole))

fig = plt.figure(1)
ax1 = fig.add_subplot(111)

ax1.set_title("Ryder Cup 2018 - Data vs. Simulation")
ax1.set_xlabel('Finishing Hole of Match')
ax1.set_ylabel('Fraction of Matches')
ax1.set_yscale("linear",nonposy='clip')
ax1.grid(True)
ax1.plot(simhole,simdata)
ax1.errorbar(simhole,ryderdata,yerr=rydererror,fmt='o')

fig = plt.figure(2)

ax2 = fig.add_subplot(211)
ax2.set_title("Winning Team Final Score")
ax2.set_xlabel('Final Score')
ax2.set_ylabel('N')
ax2.set_yscale("linear",nonposy='clip')
ax2.grid(True)
ax2.hist(ateamscorelist,55,(0,28))

ax3 = fig.add_subplot(212)
ax3.set_title("Losing Team Final Score")
ax3.set_xlabel('Final Score')
ax3.set_ylabel('N')
ax3.set_yscale("linear",nonposy='clip')
ax3.grid(True)
ax3.hist(bteamscorelist,55,(0,28))

plt.show()
