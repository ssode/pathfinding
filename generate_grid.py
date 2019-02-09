import random as rand

def obstacles(chance):
    if rand.random() <= chance:
        return 1
    else:
        return 0

with open("grid.txt", "w") as f:
    rows = rand.randint(30, 60)
    cols = rand.randint(30, 60)
    grid = [[obstacles(0.25)  for j in range(cols)] for i in range(rows)]
    ghost_row = rand.randint(0, len(grid) - 1)
    ghost_col = rand.randint(0, len(grid[ghost_row]))
    targ_row = rand.randint(0, len(grid) - 1)
    targ_col = rand.randint(0, len(grid[targ_row]))
    dist = abs(targ_row - ghost_row) + abs(targ_col - ghost_col)
    while dist < 30:
        ghost_row = rand.randint(0, len(grid) - 1)
        ghost_col = rand.randint(0, len(grid[ghost_row]))
        targ_row = rand.randint(0, len(grid) - 1)
        targ_col = rand.randint(0, len(grid[targ_row]))
        dist = abs(targ_row - ghost_row) + abs(targ_col - ghost_col)
    grid[ghost_row][ghost_col] = 2
    grid[targ_row][targ_col] = 3

    for row in grid:
        line = ""
        for num in row:
            line += str(num)
        line += "\n"
        f.write(line)
