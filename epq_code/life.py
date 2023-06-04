#<- Comment (non-functional code for descriptive purposes)
import time
import math
import random
#Setup Pygame, used here to create a display for the 'game' of life
import pygame
pygame.init()
#Defined height/width of display
dwidth = 1100
dheight = 1100
#Defined size of cells, and other handy parameters
ncellx = 100
ncelly = 100
ncells = ncellx * ncelly
cwidth = dwidth / ncellx
cheight = dheight / ncelly

#Some Generic variables to hold information
i = 0
n = 0
p = 1
#Some lists to store cell states
cells = []
cellsnew = []
cellsreset = []
stateweights = [0] * 13 + [1] * 7


#Setup for list for cell coordinates
while i < ncells:
    cellsreset.append(0)
    i += 1

cells = list(cellsreset)
cellsnew = list(cellsreset)
    
#Defined display
life = pygame.display.set_mode((dwidth, dheight))
pygame.display.set_caption("The Game of Life")

#Defined clock for crude frames per second (FPS)
clock = pygame.time.Clock()

#Defined colours for later use
black = (0,0,0)
white = (255,255,255)
red = (255,0,0)
green = (0,255,0)
blue = (0,0,255)
yellow = (255,255,0)
magenta = (255,0,255)
cyan = (0,255,255)
#Colours currently used for roles
background = black
dead = black
alive = yellow
debug = white

#Finds the state of a cell with given coordingates
def findstate(x, y):  
    cellplace = ((y - 1) * ncellx) + (x - 1)
    return cells[cellplace]

#Finds all neighbouring cells
def adjacent(x, y):
    #Handles edge cases
    if y == ncelly:
        yup = ncelly - 1
        ydown = 1
    elif y == 1:
        yup = ncelly
        ydown = 2
    else:
        yup = y - 1
        ydown = y + 1
    if x == ncellx:
        xleft = ncellx - 1
        xright = 1
    elif x == 1:
        xleft = 2
        xright = ncellx
    else:
        xleft = x - 1
        xright = x + 1
    
    neighbours = []   
    neighbours.append(findstate(xleft, yup))
    neighbours.append(findstate(xleft, y))
    neighbours.append(findstate(xleft, ydown))
    neighbours.append(findstate(x, yup))
    neighbours.append(findstate(x, ydown))
    neighbours.append(findstate(xright, yup))
    neighbours.append(findstate(xright, y))
    neighbours.append(findstate(xright, ydown))
    adjacents = neighbours.count(1) + neighbours.count(2)
    return adjacents

#Changes the state of a cell the that desired
def editstate(x, y, state):
    cellplace = ((y - 1) * ncellx) + (x - 1)
    cells[cellplace] = state

#Edits the state of a cell given that of its neighbours
def iteratestate(x, y):
    
    cellplace = ((y - 1) * ncellx) + (x - 1)
    nlive = adjacent(x, y)
    #In the new cell lists so as to not interfere with the next adjacent function
    if nlive == 3:
        cellsnew[cellplace] = 1        
    elif nlive >= 4:
        cellsnew[cellplace] = 0
    elif nlive <= 1:
        cellsnew[cellplace] = 0
    elif nlive == 2:
        cellsnew[cellplace] = findstate(x, y)
    else:
        cellsnew[cellplace] = 63
        
#Draws a cell at given coordinates
def cell(x, y):
    
    state = findstate(x, y)
    if state == 0:  
        colour = dead   
    elif state == 1:        
        colour = alive
    else:
        colour = debug
    pygame.draw.rect(life, colour, [(x - 1) * cwidth, (y - 1) * cheight, cwidth, cheight])


#Creates the new cell list, then sets it to the first list
def simIterate():
    j = 0
    x = 1
    y = 1
    while j < ncells:
        iteratestate(x, y)
        x += 1
        if x > ncellx:
            x = 1
            y += 1
        j += 1
        
#Updates the displsy to draw the new cells
def disIterate():
    j = 0
    x = 1
    y = 1
    while j < ncells:
        cell(x, y)
        x += 1
        if x > ncellx:
            x = 1
            y += 1
        j += 1

#Places a cell at the coordinates of a mouse click
def draw():
    click = pygame.mouse.get_pressed()
    place = pygame.mouse.get_pos()
    if click[0] == 1:
        xcoord = math.floor(place[0] / cwidth)
        ycoord = math.floor(place[1] / cheight)
        cell(xcoord, ycoord)
        editstate(xcoord, ycoord, 1)

def randomize():
    j = 0
    x = 1
    y = 1
    while j < ncells:
        editstate(x, y, random.choice(stateweights))
        cell(x, y)
        x += 1
        if x > ncellx:
            x = 1
            y += 1
        j += 1

#Loop Setup, executes code until loop is broken, allows display to function iteritively 
closed = False

while not closed:

    for event in pygame.event.get():        
        #Prints events in display to the shell for debug purposes     
        #Closes game of life when close button clicked     
        if event.type == pygame.QUIT:            
            #Breaks loop
            closed = True
        #Looks for a button press
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_p:
                p = 1 #Pauses on the press of p
            elif event.key == pygame.K_o:
                p = 0 #Unpauses on the press of o
            elif event.key == pygame.K_c:
                cells = list(cellsreset)
                cellsnew = list(cellsreset) #Clears on the press of c
                life.fill(background)
                n = 0
            elif event.key == pygame.K_r:
                randomize()
            elif event.key == pygame.K_n:
                print(n)

    if p == 1:
        draw()
    if p == 0:
        #Sets display to default to draw over
        life.fill(background)
        #Performs one iteration of the simulation
        simIterate()
        cells = list(cellsnew)
        cellsnew = list(cellsreset)
        disIterate()
        n += 1
    if n == 2000:
        p = 1
        #Updates display so it actually changes
    pygame.display.update()
    clock.tick(60)
    
#Once loop is broken, exits program
pygame.quit()
quit()
