'''
Zachary Harper
03/10/2019
A piece of code that examines the energy loss of a bouncy ball by looking at how long it takes
to fall below a minimum height value, and how many bounces occur in this time. 
'''

import math

def get_n():     #Function to collect user input for n (Coefficient of Restitution)
    while True:  #While loop causes function to repeat until a valid value for n is obtained form the user.
        try:     #Try-Except checks the input was a number as opposed to a string.
            n = float(input('Please enter a number between 1 and 0, not including 1 or 0, for the fractional amount of energy retained on each bounce.\n'))
            if (n > 1) or (n < 0):      #If-Elif-Else checks to ensure the value for the Coefficient of Restitution is valid, and returns it if so.
                print('Sorry,', n, 'is not between 1 and 0.')
            elif n == 1 or n == 0:
                print('The number cannot be 1 or 0.')
            else:
                return n
        except ValueError:      
            print("That's not a number.")

def getDropHeight():    #Function to collectd user input for drop height
    while True:         #Very similar in structure to get_n() function, simply with different checks.
        try:        
            height = float(input('Please enter a number (in meters) for the height the ball is dropped from. \n'))
            if height < 0:
                print('Sorry, the height cannot be less than 0.')
            else:
                return height
        except ValueError:
            print("That's not a number.")

def getMinHeight(maxHeight):    #Function to collect user input for minimum height a bounce has to reach to be counted.
    while True:                 #Very similar in structure to get_n() function, simply with different checks.
        try:                    #Takes the input of max hight, so that it can be checked it is not over the previously obtained drop hight.
            minHeight = float(input('Please enter a number (in meters) for the height below which bounces are not counted. \n'))
            if minHeight < 0:
                print('Sorry, the minimum height reached cannot be less than 0.')
            elif minHeight > maxHeight:
                print('Sorry, the minimum height reached cannot be greater than the drop height.')
            else:
                return minHeight
        except ValueError:
            print("That's not a number.")
            
def getGravity():       #Function to check whether the user would like to input their own value of gravity, and if so, what value they would like.
    while True: #First while loop checks for if the user would like to use 9.81, or something different.
        standardGravity = str(input("Would you like this program to default to 9.81m/s as the value for gravity? \nIf no, you can set your own value. \n"))
        standardGravity = standardGravity.lower() #Sets string answer to lowercase to reduce the number of checks needed for valid yes/no answer.
        if standardGravity == 'yes' or standardGravity == 'y':
            return 9.81
        elif standardGravity == 'no' or standardGravity == 'n':
            while True: #Second while loop ensures a valid input for a user defined value for gravity.
                try:
                    gravity = float(input('Please enter a number for the value of gravity to be used.\n'))
                    if gravity > 0:         #Answer validity checks are similar to those used for previous getX() style functions.
                        return gravity
                    elif gravity == 0:
                        print('Gravity must be higher than 0, or the ball will not bounce.')
                    else:
                        print('Gravity cannot be negative.')
                except ValueError:
                    print("That's not a number.")
        else:
            print('Please provide a Yes or No answer.')

def again(): #Short function to check if the user would like to enter another set of values or close the program
    while True:
        repeat = str(input('Would you like to repeat this for another set of values?\n'))
        repeat = repeat.lower() #Structure is similar to validity checks for getGravity function's first loop.
        if repeat == 'yes' or repeat == 'y':
            return True
        elif repeat == 'no' or repeat == 'n':
            return False
        else:
            print('Please provide a yes or no answer.')

    
def getBounces(n, h, hmin): #Function to calculate number of bounces iteratively.
    hnew = h                #A logarithmic solution may have been better in this case, but the iterative method can be applied to all similar problems,
    bounce = 0              #while the log function may not work.
    while hnew > hmin:  #While loop iterates until new bounce height is below minimum value
        hnew = hnew * n
        if hnew < hmin:     #Break clause combined with conditional while loop deals with edge cases like h = hmin, hnew=hmin, 
            break           #and prevents final bounce below hmin counting for the bounces.
        bounce += 1
    return bounce

def listHeights(bounces, n, h): #Function to calculate the heights reached on each bounce and add to a list,
    j = 0   #Iteration Variable                    
    heights = []
    while j <= bounces:
        heights.append(h*(n**j)) #Adds the height times a power of n for each bounce, starting from n^0 for the drop height.
        j += 1
    return heights
                       
def getTime(heights, gravity): #Function to calculate time using the gravity and list of heights reached.
    timeTotal = 0
    drop = heights.pop(0) #Also removes the inital drop height from the list so that it doesn't interfere with the for loop.
    dropTime = math.sqrt((2*drop)/gravity)
    timeTotal += dropTime
    for height in heights:
        time = math.sqrt((8*height)/gravity)    #Calculates the time taken for the ball to travel along a single bounce path.
        timeTotal += time
    return timeTotal


while True: 
    n = get_n()                             #Collects variable values from user
    dropHeight = getDropHeight()
    minHeight = getMinHeight(dropHeight)
    gravity = getGravity()
    bounceAmount = getBounces(n, dropHeight, minHeight) #Feeds values into calculation functions
    heightsReached = listHeights(bounceAmount, n, dropHeight)
    timeTaken = getTime(heightsReached, gravity)    # \/ Outputs values.
    print('The ball took {0:1.2f} bounces and {1:1.2f}s to drop below the minimum bounce height of {2:1.2f}m from a height of {3:1.2f}m, with a value for gravity of {4:1.2f}m/s, and all values rounded to 2 decimal places.'.format(bounceAmount, timeTaken, minHeight, dropHeight, gravity))
    runAgain = again()      #Checks if the user wants to enter more values or not
    if runAgain == False: #If not ends while loop
        break

exit() #Exits program once while loop is ended.


    



    
    


