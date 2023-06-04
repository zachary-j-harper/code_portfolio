import time
import random
import pygame

pygame.init()
dwidth = 400
dheight = 400

acell = [10, 10, 110, 110]
bcell = [150, 10, 250, 110]
ccell = [290, 10, 390, 110]
dcell = [10, 150, 110, 250]
ecell = [150, 150, 250, 250]
fcell = [290, 150, 390, 250]
gcell = [10, 290, 110, 390]
hcell = [150, 290, 250, 390]
icell = [290, 290, 390, 390]

nnc = pygame.display.set_mode((dwidth, dheight))
pygame.display.set_caption("Neural Nets and Naughts 'N' Crosses")
clock = pygame.time.Clock()

black = (0,0,0)
white = (255,255,255)
background = white

grid = pygame.image.load('grid.png')
cross = pygame.image.load('cross.png')
naught = pygame.image.load('naught.png')

nnc.fill((background))
nnc.blit(grid, (0,0))
pygame.display.update()
cells = [3, 3, 3, 3, 3, 3, 3, 3, 3]
lastcells = list(cells)
turns = 0
lastturns = 0
win = 'False'
turn = 'player'
train = 'no'
loops = 0
wins = 0
currentwins = 0
losses = 0
currentlosses = 0
currentpercentage = 0
previouspercentage = 0
printloops = 'no'

boardstatelist = {}
weights = []
weightsplace = 0
a = 1
b = 1
c = 1
d = 1
e = 1
f = 1
g = 1
h = 1
i = 1
j = 0
storedstates = []
storedstatestwo = []
storedmoves = []
storedmovestwo = []
storedreset = []

#General setup above, such as creating variable to be used

while i <= 3:
    move = a + (b * 10) + (c * 100) + (d * 1000) + (e * 10000) + (f * 100000) + (g * 1000000) + (h * 10000000) + (i * 100000000)
    boardstatelist[move] = (9 * weightsplace)
    weightsplace += 1
    a += 1
    if a == 4:
        a = 1
        b += 1
    if b == 4:
        b = 1
        c += 1
    if c == 4:
        c = 1
        d += 1
    if d == 4:
        d = 1
        e += 1    
    if e == 4:
        e = 1
        f += 1
    if f == 4:
        f = 1
        g += 1
    if g == 4:
        g = 1
        h += 1
    if h == 4:
        h = 1
        i += 1
while j < (9 * weightsplace):
    #WEIGHTS!
    weights.append(30)
    j += 1

#Above is setting up the list of all possible board states, and the weighting list.
#It is a dictionary function, so it refers to a specific place in the weighting list for a specific board state

def checkwin(cells): #Checks if anyone has won a game
    if cells[0] == cells[1] and cells[0] == cells[2] and cells[0] != 3:
        return cells[0]
    if cells[3] == cells[4] and cells[3] == cells[5] and cells[3] != 3:
        return cells[3]
    if cells[6] == cells[7] and cells[6] == cells[8] and cells[6] != 3:
        return cells[6]
    if cells[0] == cells[3] and cells[0] == cells[6] and cells[0] != 3:
        return cells[0]
    if cells[1] == cells[4] and cells[1] == cells[7] and cells[1] != 3:
        return cells[1]
    if cells[2] == cells[5] and cells[2] == cells[8] and cells[2] != 3:
        return cells[2]
    if cells[0] == cells[4] and cells[0] == cells[8] and cells[0] != 3:
        return cells[0]
    if cells[2] == cells[4] and cells[2] == cells[6] and cells[2] != 3:
        return cells[2]
    else:
        return 'False'

def getmouseplace(x, y): #locates the mouse and returns the cell it is in
    place = []
    if x >= 10 and x <= 110:
        place.append(1)
    elif x >= 150 and x <= 250:
        place.append(2)
    elif x >= 290 and x <= 390:
        place.append(3)
    else:
        place.append('error')
    if y >= 10 and y <= 110:
        place.append(1)
    elif y >= 150 and y <= 250:
        place.append(2)
    elif y >= 290 and y <= 390:
        place.append(3)
    else:
        place.append('error')
    if place[0] == 0 or place[1] == 0:
        return 0
    else:  
        return place

def draw(shape, x, y): #draws the given shape at the given coordinates
    coords = [x, y]
    if shape == cross:
        number = 1
    else:
        number = 2
    if coords == [1,1]:
        nnc.blit(shape, (10,10))
        cells[0] = number
    elif coords == [2,1]:
        nnc.blit(shape, (150,10))
        cells[1] = number
    elif coords == [3,1]:
        nnc.blit(shape, (290,10))
        cells[2] = number
    elif coords == [1,2]:
        nnc.blit(shape, (10,150))
        cells[3] = number
    elif coords == [2,2]:
        nnc.blit(shape, (150,150))
        cells[4] = number
    elif coords == [3,2]:
        nnc.blit(shape, (290,150))
        cells[5] = number
    elif coords == [1,3]:
        nnc.blit(shape, (10,290))
        cells[6] = number
    elif coords == [2,3]:
        nnc.blit(shape, (150,290))
        cells[7] = number
    elif coords == [3,3]:
        nnc.blit(shape, (290,290))
        cells[8] = number
    pygame.display.update()

def getstate(cells): #finds the numerical code for the current state of the naughts and crosses board
    state = (cells[0]) + (10 * cells[1]) + (100 * cells[2]) + (1000 * cells[3]) + (10000 * cells[4]) + (100000 * cells[5]) + (1000000 * cells[6]) + (10000000 * cells[7]) + (100000000 * cells[8])
    return state

def weightlist(cells, weights): #Returns list of cell weightings to pick from
    state = getstate(cells)
    storedstates.append(state)
    place = boardstatelist[state]
    placeend = place + 8
    appnum = 1
    cellweights =[]
    while place <= placeend:
        iterations = weights[place]
        iteration = 0
        while iteration < iterations:
            cellweights.append(appnum)
            iteration += 1
        appnum += 1
        place += 1
    return cellweights

def weightlistagainst(cells, weights): #Returns list of cell weightings to pick from
    state = getstate(cells)
    storedstatestwo.append(state)
    place = boardstatelist[state]
    placeend = place + 8
    appnum = 1
    cellweights =[]
    while place <= placeend:
        iterations = weights[place]
        iteration = 0
        while iteration < iterations:
            cellweights.append(appnum)
            iteration += 1
        appnum += 1
        place += 1
    return cellweights

def pickcell(cells, weights): #selects a cell for the net to play in
    weightlisting = weightlist(cells, weights)
    end = len(weightlisting) - 1
    if end >=  1:
        placing = random.randint(0, end)
        return weightlisting[placing]
    else:
        return 'fail'
    
def pickcellagainst(cells, weights): #selects a cell for the net to play in
    weightlisting = weightlistagainst(cells, weights)
    end = len(weightlisting) - 1
    if end >=  1:
        placing = random.randint(0, end)
        return weightlisting[placing]
    else:
        return 'fail'

def cellconvert(cell): #recalls a place for 
    if cell == 1:
        place = [1, 1]
    elif cell == 2:
        place = [2, 1]
    elif cell == 3:
        place = [3, 1]
    elif cell == 4:
        place = [1, 2]
    elif cell == 5:
        place = [2, 2]
    elif cell == 6:
        place = [3, 2]
    elif cell == 7:
        place = [1, 3]
    elif cell == 8:
        place = [2, 3]
    elif cell == 9:
        place = [3, 3]
    return place

def placeconvert(place):
    if place == [1,1]:
        cell = 1
    if place == [2,1]:
        cell = 2
    if place == [3,1]:
        cell = 3
    if place == [1,2]:
        cell = 4
    if place == [2,2]:
        cell = 5
    if place == [3,2]:
        cell = 6
    if place == [1,3]:
        cell = 7
    if place == [2,3]:
        cell = 8
    if place == [3,3]:
        cell = 9
    return cell    

def weightchange(cells, weights, state, weight, change):
    if weight >= 1:
        weight = weight - 1
        place = boardstatelist[state] + weight
        changeweight = weights.pop(place) + change
        weights.insert(place, changeweight)
    
def weightremove(cells, weights, weight):
    state = getstate(cells)
    weight = weight - 1
    place = boardstatelist[state] + weight
    changeweight = weights.pop(place)
    weights.insert(place, 0)
        
    
def taketurn(cells, weights):
    cell = pickcell(cells, weights)
    if cell == 'fail':
        return 'True'
    elif cells[cell-1] != 3:
        weightremove(cells, weights, cell)
        return 'again'
    else:
        storedmoves.append(cell)
        return cell

def taketurnagainst(cells, weights):
    cell = pickcellagainst(cells, weights)
    if cell == 'fail':
        return 'True'
    elif cells[cell-1] != 3:
        weightremove(cells, weights, cell)
        return 'again'
    else:
        storedmovestwo.append(cell)
        return cell

def learn(win, storedstates, storedmoves):
    it = 0
    adjust = len(storedmoves)
    if win == 'True':
        for item in storedmoves:
            weightchange(cells, weights, storedstates[it], storedmoves[it], 3+round(adjust/9, 0)) #WIN BONUS
            it += 1
    else:
        for item in storedmoves:
            weightchange(cells, weights, storedstates[it], storedmoves[it], -(it+1)) #LOSS PENALTY
            it += 1
            
             
closed = False

while not closed:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            closed = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_t:
                train = 'yes'
                printloops = 'yes'
                loops += 1
                currentwins = 0
                currentlosses = 0
                previouspercentage = currentpercentage
            if event.key == pygame.K_w:
                print('I have won ' + str(wins) + ' times and lost ' + str(losses) + ' times')
                percentage = (wins / (wins + losses)) * 100
                print("That's a " + str(percentage) + '% winrate!')
                currentpercentage = (currentwins / (currentwins + currentlosses)) * 100
                print("And a " + str(currentpercentage) + "% winrate over the last training cycle, a " + str(currentpercentage - previouspercentage) + "% improvement!")
            if event.key == pygame.K_o:
                turn = 'net'
    if loops % 50000 == 0:
        train = 'no'
        if printloops == 'yes':
            print(str(loops) + ' loops')
            printloops = 'no'
    click = pygame.mouse.get_pressed()
    place = pygame.mouse.get_pos()
    if click[0] == 1 and turn == 'player' and train == 'no':
        placetwo = getmouseplace(place[0], place[1])
        if 'error' not in placetwo:
            repeat = placeconvert(placetwo)
            if cells[repeat-1] == 3:
                draw(cross, placetwo[0], placetwo[1])
                time.sleep(0.2)
                win = checkwin(cells)
                if win != 'False':
                    print(str(win) + ' wins')
                    winner = win
                    if winner == 2:
                        learn('True', storedstates, storedmoves)
                        wins += 1
                    if winner == 1:
                        learn('False', storedstates, storedmoves)
                        losses += 1
                    storedstates = list(storedreset)
                    storedmoves = list(storedreset)
                    cells = [3, 3, 3, 3, 3, 3, 3, 3, 3]
                    win = 'False'
                    turn = 'player'
                    nnc.blit(grid, (0,0))
                    pygame.display.update()
                else:
                    turn = 'net'
    elif train == 'yes' and turn == 'player':
        concede = taketurnagainst(cells, weights)
        if concede != 'True' and concede != 'again':
            position = cellconvert(concede)
            draw(cross, position[0], position[1])
            turn = 'net'
            win = checkwin(cells)
        elif concede == 'True':
            print('I concede 2')
            win = 2
        if win != 'False':
            winner = win
            if winner == 2:
                learn('False', storedstatestwo, storedmovestwo)
                learn('True', storedstates, storedmoves)
                wins += 1
                currentwins += 1
            if winner == 1:
                learn('True', storedstatestwo, storedmovestwo)
                learn('False', storedstates, storedmoves)
                losses += 1
                currentlosses += 1
            storedstates = list(storedreset)
            storedmoves = list(storedreset)
            storedstatestwo = list(storedreset)
            storedmovestwo = list(storedreset)
            cells = [3, 3, 3, 3, 3, 3, 3, 3, 3]
            if train == 'yes':
                loops += 1
            else:
                print(str(win) + ' wins')
            win = 'False'
            turn = 'net'
            nnc.blit(grid, (0,0))
            pygame.display.update()
    elif turn == 'net':
        concede = taketurn(cells, weights)
        if concede != 'True' and concede != 'again':
            position = cellconvert(concede)
            draw(naught, position[0], position[1])
            turn = 'player'
            win = checkwin(cells)
            if train == 'no':
                time.sleep(0.1)
        elif concede == 'True':
            print('I concede')
            win = 1
        if win != 'False':
            winner = win
            if winner == 2:
                learn('True', storedstates, storedmoves)
                if train == 'yes':
                    learn('False', storedstatestwo, storedmovestwo)
                wins += 1
                currentwins += 1
            if winner == 1:
                learn('False', storedstates, storedmoves)
                if train == 'yes':
                    learn('True', storedstatestwo, storedmovestwo)
                losses += 1
                currentlosses += 1
            storedstates = list(storedreset)
            storedmoves = list(storedreset)
            cells = [3, 3, 3, 3, 3, 3, 3, 3, 3]
            if train == 'yes':
                loops += 1
            else:
                print(str(win) + ' wins')
            win = 'False'
            turn = 'player'
            nnc.blit(grid, (0,0))
            pygame.display.update()
    if 3 not in cells:
        if train != 'yes':
            print('draw')
        if train == 'yes':
            loops += 1
        storedstates = list(storedreset)
        storedstatestwo = list(storedreset)
        storedmoves = list(storedreset)
        storedmovestwo = list(storedreset)
        cells = [3, 3, 3, 3, 3, 3, 3, 3, 3]
        win = 'False'
        turn = 'player'
        nnc.blit(grid, (0,0))
        pygame.display.update()
pygame.quit()
quit()
