//M[x][y] = x coneix y

int x, y, ytemp;
x = 0;
y = M.size() - 1;

while (x < y){
    if (M[x][y] == 0) ytemp = y - 1;
    if (M[y][x] == 0) ++x;
    y = ytemp;
}

bool cel = False;
if (x == y) {
    cel = True;
    for (int it = 0; cel and it < M.size(); ++it) {
        if(x != it and M[x][it] == 1) cel = False;
        if(x != it and M[it][x] == 0) cel = False;
    }
}

return cel;
