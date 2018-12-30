## Mira Mastoras
## November 25, 2016
##
## prog67.py

def count_live(row, column, grid):
    "argument is row #, column # of cell and the whole grid"
    "counts number of neighboring live cells"
    offsets = [[-1,-1],[-1,0],[-1,1],[0,-1],[0,1],[1,-1],[1,0],[1,1]]
    num_live_cells = 0 
    for x in offsets:
        y = grid[row + x[0]][column + x[1]]
        if y == 1:
            num_live_cells = num_live_cells + 1
        else:
            pass
    return num_live_cells
    
def does_cell_die(row, column, grid):
    "argument is row #, column # of cell and the whole grid"
    "A live cell surrounded by < 2 live cells dies in the next cycle"
    "A live cell surrounded by >3 live cells dies in the next cycle" 
    "returns true if cell dies, false if not"
    num_live_cells = count_live(row,column,grid)
    if num_live_cells < 2:
        return True
    elif num_live_cells > 3:
        return True
    else:
        return False
               
def does_cell_live(row, column, grid):
    "argument is row #, column # of cell and the whole grid"
    "A live cell surrounded by 2 or 3 live cells continues to live"
    "returns true if cell lives, false if not"
    num_live_cells = count_live(row,column,grid)
    if num_live_cells == 2 or num_live_cells == 3:
        return True
    else:
        return False
    
def is_cell_born(row, column, grid):
    "argument is row #, column # of cell and the whole grid"
    "A dead cell/ empty cell surrounded by exactly 3 live cells comes to life"
    "returns true if cell is born, false if not"
    num_live_cells = count_live(row,column,grid)
    if num_live_cells == 3:
        return True
    else:
        return False
    
def create_matrix(rows, columns):
    'creates a new matrix with desired columns and rows of zeroes'
    newmatrix = []
    value = 0
    for r in range(0, rows):
        newrow = []
        for c in range(0, columns):
            newrow.append(value)
        newmatrix.append(newrow)    
    return newmatrix
    
def embedmatrix(matrix):
    "embed imputed matrix into larger one that deals with edge cases"
    r = len(matrix) + 2
    c = len(matrix[0]) + 2
    newmatrix = create_matrix(r,c)
    
    row = 0
    column = 0
    while row < len(matrix):
        while column < len(matrix[row]):
            newmatrix[row+1][column+1] = matrix[row][column]
            column = column + 1
        column = 0 
        row = row + 1
    return newmatrix

def is_on_edge(row, column, grid):
    "checks if position in grid is on the edge"
    "argument is row #, column # of cell and the whole grid"
    if row == 0 or column == 0:
        return True
    elif row == len(grid) - 1 or column == len(grid[0]) - 1:
        return True
    else:
        return False
    
def nextGen(grid):
    largergrid = embedmatrix(grid)
    ## Now loop through large grid checking if we change small grid values
    row = 0
    column = 0
    while row < len(largergrid):
        while column < len(largergrid[row]):
            if is_on_edge(row,column,largergrid) == True:
                pass
            else:
                if largergrid[row][column] == 1:
                    if does_cell_live(row, column, largergrid) == False or does_cell_die(row, column, largergrid) == True:
                        grid[row - 1][column - 1] = 0
                    else:
                        pass
                else:
                    if is_cell_born(row, column, largergrid) == True:
                        grid[row - 1][column - 1] = 1
                    else:
                        pass
            column = column + 1
        column = 0 
        row = row + 1
   
    return grid

def read_to_file(filename):
    "reads to a file, converts into a matrix"
    "argument is desired filename"
    grid = []
    row = []
    somefile = open(filename, "r")
    for line in somefile:
        for x in line.strip():
            row.append(int(x))
        grid.append(row)
        row = []
    somefile.close()
    return grid
    
def write_to_file(grid, filename):
    "writes a matrix out to a file"
    "argument is matrix and desired file name"
    outFile = open(filename, "w")
    for x in grid:
        for i in x:
            outFile.write(str(i))
        outFile.write("\n")
    outFile.close()

def print_grid(matrix):
    "takes a matrix of 0's and 1's and prints it as . and *'s"
    for x in matrix:
        for i in x:
            if i == 0:
                print(". ",end='')
            else:
                print("* ",end='')
        print("\n")

def run_nextGen(numGens, matrix):
    most_recent = []
    print("Generation 0:")
    print_grid(matrix)
    for x in range(0, numGens):
        most_recent = nextGen(matrix)
        print("Generation:", x + 1)
        print_grid(most_recent)
        matrix = most_recent
    return most_recent
    
def life():
    while True:
        filename = input("Enter input file name: ")
        try:
            infile = open(filename, "r")
            break
        except:
            print("No such file. Try again")
    while True:
        numGens = input("How many generations would you like to print? ")
        try:
            numGens = int(numGens)
            break 
        except:
            print("Not a valid number.")

    file_matrix = read_to_file(filename)
    most_recent = run_nextGen(numGens, file_matrix)
    yesorno = input("Would you like to save the latest generation? ('y' to save): ")
    if yesorno == 'y' :
        while True:
            destination = input("Enter destination file name: ")
            try:
                filedestination = open(destination, "r")
                question = input("Do you want to overwrite that file? ('y' to continue): ")
                if question == 'y':
                    break
                else:
                    pass
            except:
                break
        print("Saving data to" , destination)
        write_to_file(most_recent, destination)
    print("End of program.")


life()    


