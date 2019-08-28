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

chi2min = 10000000.0
abr = 0.0
bbr = 0.0
ar = 0.0
br = 0.9

abins = 13
bbins = 11

for j in range(0,abins):
    abirdiebogeyratio=1.7+j*0.1
    for k in range(0,abins):
        bbirdiebogeyratio=0.5+k*0.1
        for l in range (0,bbins):
            arisk=0.30+l*0.05
            for m in range(0,bbins):
                brisk=0.30+m*0.05

                apar = 1/(1+arisk)
                abirdielimit = (1 - apar)/(1 + 1/abirdiebogeyratio)
                abogeylimit = abirdielimit/abirdiebogeyratio
                #print (abirdielimit,apar,abogeylimit)

                bpar = 1/(1+brisk)
                bbirdielimit = (1 - bpar)/(1 + 1/bbirdiebogeyratio)
                bbogeylimit = bbirdielimit/bbirdiebogeyratio
                #print (bbirdielimit,bpar,bbogeylimit)

                nholes = 18
                holearray = [0 for i in range(0,nholes)]
                numsim = 1000

                for numsim in range(0,numsim):
                    ascore = 0
                    bscore = 0
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

                        if a > b:
                            ascore = ascore + 1
                        if a < b:
                            bscore = bscore + 1

                        diff = abs(ascore-bscore)

                        #print ("Hole = ",hole," Score = ",diff," A = ",ascore," B = ",bscore)

                        remain = nholes - hole

                        if diff > remain:
                            #print ("Win! Final Hole = ",hole)
                            finalhole = hole
                            break

                        if hole == nholes:
                            finalhole = hole

                    #print ("Done! Final Hole = ",finalhole)
                    holearray[finalhole-1]=holearray[finalhole-1]+1

                for i in range(0,nholes):
                    holearray[i]=holearray[i]/numsim

                #print (holearray)
                print (j,k,l,m)

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

                #print("Chi^2 / DOF = ",chi2/(nholes-starthole))
                if chi2 < chi2min:
                    chi2min = chi2
                    ar = arisk
                    br = brisk
                    abr = abirdiebogeyratio
                    bbr = bbirdiebogeyratio

print ("Chi^2 Min = ",chi2min," A Birdie Ratio = ",abr," A Risk = ",ar," B Birdie Ratio = ",bbr," B Risk = ",br)

fig = plt.figure()
ax1 = fig.add_subplot(111)

ax1.set_title("Ryder Cup 2018 - Data vs. Simulation")
ax1.set_xlabel('Finishing Hole of Match')
ax1.set_ylabel('Fraction of Matches')
ax1.set_yscale("linear",nonposy='clip')
ax1.grid(True)

ax1.plot(simhole,simdata)
ax1.errorbar(simhole,ryderdata,yerr=rydererror,fmt='o')

leg = ax1.legend()
plt.show()
