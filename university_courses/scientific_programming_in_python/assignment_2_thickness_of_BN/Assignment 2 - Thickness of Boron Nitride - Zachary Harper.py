'''
Zachary Harper
18/11/2019
This is a piece of code that reads in data from a specified .csv file, fits an equation to it
using minimised chi squared, and prints a plot of the data points and fit line.
'''
import csv
import os
import warnings as w
import numpy as np
import matplotlib.pyplot as plt
#import time as t                       #Uncomment for time taken to find d with reduce function
                                        #See also lines 136, 159, 160

w.filterwarnings('ignore')              #Prevents ugly warnings for trying to root negative numbers.

def makeFloat(data):                    #This functions turns all entries in an array into floats
    dimensions = data.shape
    newData = np.zeros((dimensions))
    x = 0
    while x < dimensions[0]:
        y = 0
        while y < dimensions[1]:
            newData[x,y] = float(data[x,y])
            y += 1
        x += 1
    return newData

def chi(observed, expected, error):     #This function calculates a value of chi
    chiSquared = sum(((observed - expected)**2)/(error**2))
    return chiSquared

def clean(data, column):                #This function removes anomalous data values
    loop = False
    row = 0
    removed = False
    checked = data[:,column]
    stdDev = np.std(checked)
    mean = np.mean(checked)
    upperLimit = mean + 3*stdDev        #Data values outside of mean +/- 3 standard deviations are
    lowerLimit = mean - 3*stdDev        #treated as anomalies, and removed
    
    if (lowerLimit < 0) and (column == 0):  #These assumptions are not valid outside of the
        lowerLimit = 0                      #context of transmission coefficients 
        
    if (upperLimit > 1) and (column == 0):
        upperLimit = 1
           
    for item in checked:
        item = float(item)
        if (item >= lowerLimit) and (item <= upperLimit):
            if loop:
                newData = np.vstack((newData, data[row,:]))
                
            elif not loop:
                newData = np.array(data[row,:])
                loop = True
                
        else:
            removed = True
            
        row += 1
        
    return newData, removed

def getData():                          #This function acquires data from a csv file specified by the user.
    i = 0
    fileList = os.listdir('.')          #Lists files in the same folder as the program
    possFiles = []
    
    for item in fileList:
        if '.csv' in item:
            possFiles.append(item)
            
    fileNum = len(possFiles)
    
    print('Please select the file you would like to analyse from the following:') 
    validAnswer = []                    #Presents user with choice of files to analyse
    while i < fileNum:
        print('Enter', i+1, 'for', possFiles[i])
        i += 1
        validAnswer.append(str(i))

    answer = input()
    while answer not in validAnswer:    #Validates user input
        answer = input("That's not a valid file. Please enter the number corresponding to the data file you would like to analyse\n")
        
    fileSelect = possFiles[int(answer)-1]
    file = open(fileSelect, 'r')
    looped = False
    
    for r in csv.reader(file):
        a = np.array(r)
        valid = True
        for x in a:
            try:                        #This removes 'data points' that are not values
                float(x)
            except:
                valid = False
        if valid and (not looped):      #Condenses values into an array for later use
            data = np.array(a)          #Creates array on first valid data line
            looped = True
        elif valid and looped:
            data = np.vstack((data, a)) #Appends new valid data lines onto array

    data = makeFloat(data)          
    dirty = True    
    while dirty:                        #Loops catch edge cases where removal of outer anomalies
        data, dirty = clean(data, 0)    #cause new values to become anomalous

    dirty = True
    while dirty:
        data, dirty = clean(data, 1)
        
    file.close()
    return data

def createExpectedValues(E, d):         #Function creates expected values of transmission coefficients
    e = 1                               #based on an input of energy values and thickness, d
    Er = 4
    E0 = 0.00553
    V0 = 3
    mass_h_bar = 0.512327
    Lambda = ((e**2)*np.log(2))/(8*np.pi*Er*E0*d)
    V = V0*(1-((2.3*Lambda)/(V0-2.4*Lambda))*np.log((V0-1.2*Lambda)/(1.2*Lambda)))
    T = np.exp(-2*d*(1-(2.4*Lambda)/V0)*mass_h_bar*np.sqrt(V-E))
    return T

def reduce(xValues, observed, errors):  #Function finds d by reducing chi squared value
    d = 15
    step = 10                           #These values have been found to be most efficient, but
    stepDecrease = 3/5                  #can be altered
    accuracy = 0.0001
    previousChange = 'nothing'
    change = 'nothing'
    #start = t.time()                   #Uncomment for time taken to find d with reduce function
    while True:                         #See also lines 12, 159, 160
        Chi = chi(observed, createExpectedValues(xValues, d), errors)
        chiUp = chi(observed, createExpectedValues(xValues, d+step), errors)
        chiDown = chi(observed, createExpectedValues(xValues, d-step), errors)
        if chiUp < Chi:
            d += step
            change = 'increase'
        elif chiDown < Chi:
            d -= step
            change = 'decrease'
            
        if step < accuracy:             #stops once desired level of accuracy is reached
            break
        
        if previousChange != change:    #If statements reduce step size if chiDown is invalid,
            step = stepDecrease*step    #real d value is passed, or neither chi limit is smaller
        if (Chi < chiUp) and (Chi < chiDown):
            step = stepDecrease*step
        if np.isnan(chiDown):
            step = stepDecrease*step

        previousChange = change
    #finish = t.time()                                      #Uncomment for time taken to find d with reduce function
    #print('It took ', finish - start, 'seconds to find d') #See also lines 12, 136
    return d, Chi
    

#Main Program

data = getData()                                    #Gets data
d, Chi = reduce(data[:,1], data[:,0], data[:,2])    #Gets d and chi
reducedChi = Chi/(len(data[:,1])-1)
print('The thickness of the Boron Nitride sample is {:.3f} Angstrom. This is approximately {:.0f} layer(s). \nThe Reduced Chi Squared of the fit to this data set is {:.2f}'.format(d, d/3, reducedChi))

x = np.linspace(np.amin(data[:,1]), np.amax(data[:,1]), 101) #Sets up accurate plot for 
y = createExpectedValues(x, d)                               #line of best fit
xObs = data[:,1]                        #Sets up values for real data
yObs = data[:,0]
yerr = data[:,2]
fig, axes = plt.subplots()

axes.errorbar(xObs, yObs, yerr, 0, 'r.')    #Plots errors as red bars
axes.plot(xObs, yObs, 'kx')                 #Plots values as black crossed
axes.plot(x, y, 'b')                        #Plots LoBF as blue line
plt.show() 







