'''
Zachary Harper
7/12/2019
This is a piece of code that reads in as many data files as asked, sanitizes and validates
that data, fits an equation to that data, outputting the values calculated from that fit
along with their uncertainties, and produces two graphs of that data, which is then also
saved as a .png file.
'''

import os
import numpy as np
from matplotlib import pyplot as plt
from scipy import optimize as op

#=====Calculation Functions=====#

def chi(observed, expected, error):     #This function calculates a value of chi. Data types are all arrays (float).
    chiSquared = sum(((observed - expected)**2)/(error**2))
    return chiSquared

def activityRb(decays, t): #This function calculates the activity of Rubidium-79. Data types are a tuple (floats and then singular value or array (float)
    decaySr = decays[0]
    decayRb = decays[1]
    activity = (6.0221409*(10**23))*(10**(-6)) * ((decaySr * decayRb) / (decayRb - decaySr)) * (np.exp(-decaySr * t) - np.exp(-decayRb * t))
    return activity

def halfLife(decayCons): #Calculates halflives. Data type is a float
    T = np.log(2)/decayCons
    return T

def fitFunction(decays, data): #Is a re-format of the chi function to work with fmin's data inputting format. Data types are tuple, array, (both floats)
    chiSquared = chi(data[:,1], activityRb(decays, data[:,0]), data[:,2])
    return chiSquared

def reduce(function, data): #Minimises function value for given data. Data types are function name (string) and array (float)
    fit = op.fmin(function, (0.005, 0.0005), args = data, xtol = (10**-6), ftol = (10**-6), maxfun = (10**6), full_output = True, disp = False)
    return fit

#=====Data Validation Functions=====#

def cleanNans(data): #Removes all 'nan' values from array. Data type is an array
    nans = np.isnan(data)
    row = 0
    column = nans[:,0]
    looped = False
    removed = False
    for item in column:
        rowNans = nans[row,:]
        if (True in rowNans):
            removed = True
                
        else:
            if looped:
                newData = np.vstack((newData, data[row,:]))
                
            elif not looped:
                newData = np.array(data[row,:])
                looped = True
            
        row += 1
        
    return newData, removed
        
def cleanGeneral(data, column): #This function removes awkward data values from the array that may cause issue for the code, and does some anomoly removal too.
    looped = False              #Data types are array (float) and a float
    row = 0
    removed = False
    checked = data[:,column]
    stdDev = np.std(checked)
    mean = np.mean(checked)
    upperLimit = mean + 3*stdDev        #Data values outside of mean +/- 3 standard deviations are
    lowerLimit = mean - 3*stdDev        #treated as anom0lies, and removed
    
    if (lowerLimit < 0) and (column == 1):
        lowerLimit = 0                      
        
           
    for item in checked:
        if (item >= lowerLimit) and (item <= upperLimit):
            if looped:
                newData = np.vstack((newData, data[row,:]))
                
            elif not looped:
                newData = np.array(data[row,:])
                looped = True
                
        else:
            removed = True
        row += 1

    return newData, removed

def cleanTrend(data, decays): #This function removes values that are anomolous, which is checked using chi-squared. Allows removal of anomolies within general range of the data.
    looped = False            #Data types are array (float), tuple (float)
    removed = False
    row = 0
    expected = activityRb(decays, data[:,0])
    
    for value in expected:
        chiSquared = ((data[row,1] - expected[row])**2) / (data[row,2]**2)

        if chiSquared < 10: #Value can be altered depending on desired level of accuracy. 10 Seems a good standard, the given data points have are generally < 10 or > 300 in chisquareds here.
            
            if looped:
                newData = np.vstack((newData, data[row,:]))
                
            elif not looped:
                newData = np.array(data[row,:])
                looped = True
        else:
            removed = True
            
        row += 1

    return newData, removed

def sanitize(data): #Calls previous functions to make data parseable by rest of code. Data type is array (float)
    x = 0
    y = 0
    dimension = data.shape
    dirty = True
    
    while dirty:                        #Loops catch edge cases where removal of outer anomalies
        data, dirty = cleanNans(data)    #cause new values to become anomalous
        
    while x < dimension[1]:    
        dirty = True
        while dirty:
             data, dirty = cleanGeneral(data, x)
        x += 1

    return data

#=====User Interface Functions=====#

def fileSelect(alreadySelected): #Gets a data file selection from user. Data type is list (string)
    i = 0
    add = True
    sure = False
    fileList = os.listdir('.')          #Lists files in the same folder as the program
    possFiles = []
    picked = []
    
    for item in fileList:
        if '.csv' in item:
            possFiles.append(item)
            
    fileNum = len(possFiles)
    print('Please select the file you would like to analyse from the following:') 
    validAnswer = []                    #Presents user with choice of files to analyse
    
    while i < fileNum:
        print('Enter', i+1, 'for', possFiles[i])
        if possFiles[i] in alreadySelected:
            picked.append(str(i+1))
        i += 1
        validAnswer.append(str(i))

    answer = input()
    while (answer not in validAnswer) or ((answer in picked) and (not sure)):   #Validates user input
        
        if (answer not in validAnswer):
            answer = input("That's not a valid file. Please enter the number corresponding to the data file you would like to analyse\n")
            
        elif (answer in picked):
            addAgain = input("You've already selected that file. Are you sure you want to add it again?\n").lower()
            
            if (addAgain == 'y') or (addAgain == 'yes'):
                sure = True
            else:
                sure = True
                add = False
                
    if add:
        fileSelected = possFiles[int(answer)-1]
        return fileSelected
    else:
        return None

def getData(): #Acquires a full set of fully sanitized user requested data.
    files = []
    files.append(fileSelect(files))


    moreFiles = input('Would you like to analyse any more data files?\n').lower()
    while (moreFiles != 'n') and (moreFiles != 'no'):
        
        if moreFiles == 'y' or moreFiles == 'yes':
            files.append(fileSelect(files))
            moreFiles = input('Would you like to analyse any more data files?\n').lower()
            
        else:
            moreFiles = input("Sorry, I'm nore sure what you mean.\nWould you like to analyse any more data files?\n").lower()
            
    looped = False
    for file in files:
        if file != None:
            dataTemp = np.genfromtxt(file, delimiter = ',', dtype = 'float_', skip_header = 1)
            reset = open(file) #getfromtxt only extracts floats from data files, also skips title line.
            reset.seek(0) #Resets pointer in file to first line in case user wants to use a file's data set multiple times
            reset.close()
            dataTemp = sanitize(dataTemp)
            if looped == False:
                data = dataTemp
                looped = True
            elif looped == True:
                data = np.vstack((data, dataTemp))
       
    timeSeconds = data[:,0] * 60 * 60 #Unit conversions
    activityBecquerels = data[:,1] * (10**12)
    uncertainties = data[:,2] * (10**12)
    data = np.column_stack((timeSeconds, activityBecquerels, uncertainties))
    
    return data

#~~~~~~~~~~~~~~~~~~~~~~#
#=====Main Program=====#
#~~~~~~~~~~~~~~~~~~~~~~#

data = getData() #Data Acquisition

dirty = True
while dirty: #Fits data, and removes anomolies
    fminValues = reduce(fitFunction, (data,))
    data, dirty = cleanTrend(data, fminValues[0])

decaySr = fminValues[0][0] #Better, more readable formatting of results
decayRb = fminValues[0][1]
chiSquared = fminValues[1]

#=====Graphing=====#

fig, axes = plt.subplots(nrows = 2, figsize = (10, 10), tight_layout = True )
#fig.suptitle = ('Graphing of Strontium-79 to Krypton-79 decay via Rubidium-79')
#Above line does not work when adjusting figure size, can only have one or the other.

#==Graph 1===#

x = np.linspace(np.amin(data[:,0]), np.amax(data[:,0]), 101) 
y = activityRb((fminValues[0][0], fminValues[0][1]), x)
xObs = data[:,0]
yObs = data[:,1]
yErr = data[:,2]

axes[0].errorbar(xObs, yObs, yErr, 0, 'r.')
axes[0].plot(xObs, yObs, 'kx')
axes[0].plot(x, y, 'b')

axes[0].set_xlabel('Time (s)')
axes[0].set_ylabel('Received Gamma Radiation (Bq)')
axes[0].set_title('Gamma Radiation emitted over time')

#===Graph 2===#

SrAdjustment = decaySr/5 #Currently produce useful graph that hopefully goes for other data sets
RbAdjustment = decayRb/10 #Otherwise factors are easy to change
SrDecayValues = np.linspace(decaySr-SrAdjustment, decaySr+SrAdjustment, 201) 
RbDecayValues = np.linspace(decayRb-RbAdjustment, decayRb+RbAdjustment, 201)
xContour, yContour = np.meshgrid(SrDecayValues,RbDecayValues)
chiContour = np.zeros(xContour.shape)

for a in range(len(SrDecayValues)):
    for b in range(len(RbDecayValues)):
        chiContour[a,b] = fitFunction((xContour[a,b], yContour[a,b]), data)

contourValues = np.stack((xContour, yContour, chiContour))
#Above lines create array for contour

#Contour Plot
axes[1].contourf(contourValues[0,:,:], contourValues[1,:,:], contourValues[2,:,:], 10)
axes[1].plot(decaySr, decayRb, 'bx')
confidenceLine = axes[1].contour(contourValues[0,:,:], contourValues[1,:,:], contourValues[2,:,:], [chiSquared + 1] , colors = 'b' )
labelLines = axes[1].contour(contourValues[0,:,:], contourValues[1,:,:], contourValues[2,:,:], 10)
axes[1].clabel(labelLines, colors = 'w')
axes[1].clabel(confidenceLine, colors = 'w')

axes[1].set_xlabel('Strontium Decay Constant (/s)')
axes[1].set_ylabel('Rubidium Decay Constant (/s)')
axes[1].set_title('Distribution of Chi-Squared Values')


#Uncertainty Calculation from graph. Uses points on contour at chi-squared + 1
lineValues = confidenceLine.collections[0].get_paths()[0].vertices
decaySrUncertainty = np.absolute(np.amax(lineValues[:,0]) - decaySr)
decayRbUncertainty = np.absolute(np.amax(lineValues[:,1]) - decayRb)
halfLifeSrUncertainty = (decaySrUncertainty * ((halfLifeSr*60)/decaySr)) /60
halfLifeRbUncertainty = (decayRbUncertainty * ((halfLifeRb*60)/decayRb)) /60

#=====Output=====#

#Value output
print('The value of the decay constant of Strontium-79 is ({:.3} +/- {:.2})/s'.format(decaySr, decaySrUncertainty))
print('The value of the decay constant of Rubidium-79 is ({:.3} +/- {:.2})/s'.format(decayRb, decayRbUncertainty))
print('Strontium-79 has a half-life of ({:.3} +/- {:.2})minutes, and Rubidium has a half-life of ({:.3} +/- {:.2})minutes'.format(halfLifeSr, halfLifeSrUncertainty, halfLifeRb, halfLifeRbUncertainty))
print('The reduced chi-squared of the fit is {:.2f}'.format(reducedChi))

#Graph/visual output
plt.savefig('Graphing of Rb-79 Decay.png', dpi = 500)
plt.show()


