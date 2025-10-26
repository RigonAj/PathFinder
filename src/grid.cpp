#include <raylib.h>
#include "grid.hpp"
#include <raymath.h>
#include <array>
#include <iostream>

void Grid::Draw()
{
    Color c[5]={WHITE,BLACK,VIOLET,RED,BLUE};
    int bord=2;
    for(int row=0;row<rows;row++)
    {
            for(int column=0;column<columns;column++)
            {
                DrawRectangle(cellSize*column+bord,cellSize*row+bord,cellSize-bord,cellSize-bord,c[cells[row][column]]);
            }
    }
}

void Grid::SetCell(Vector2 MousePos,int value)
{
    
    int row= MousePos.y/cellSize;
    int column= MousePos.x/cellSize;
    if(value==3){cells[srow][scolumn]=0;cells[row][column]=value;srow=row;scolumn=column;}
    else if(value==4){cells[erow][ecolumn]=0;cells[row][column]=value;erow=row;ecolumn=column;}
    else{
    cells[row][column]=value;}
}

bool Grid::IsInGrid(int row, int column)
{
    return ((row<rows && row>0) && (column<columns && column>0)); 
}

bool Grid::IsColliding(Vector2 P, int value)
{   
    int row=(int)(P.y)/cellSize;
    int column=(int)(P.x)/cellSize;
    return cells[row][column]==value;
}

void Grid::Reset()
{
    for(int row=0;row<rows;row++)
    {
            for(int column=0;column<columns;column++)
            {
                cells[row][column]=0;
            }
    }
}
    

void Grid::astar(){
    bool pathFound = false;
    int min = 0, max = 0;
    
    for(int h = 0; h < rows * columns; h++){
        node &k = at(h % columns, h / columns);
        k.parent = {-1, -1};
        k.local = INT_MAX;
        k.heuristic = INT_MAX;
        k.priority = INT_MAX;
        k.visited = false;
    }

    Vectors start = {scolumn, srow};
    Vectors end = {ecolumn, erow};

    node& startNode = at(start.x, start.y);
    startNode.parent = start;
    startNode.local = 0;
    startNode.heuristic = abs(ecolumn - scolumn) + abs(erow - srow);
    startNode.priority = startNode.heuristic;
    std::array<std::vector<Vectors>, 20000> m;
    
    int sizem = 0; 

    m[startNode.priority].emplace_back(start);
    sizem++;
    min = startNode.priority;
    max = startNode.priority;

    int v[4] = {0, 0, -1, 1};
    Vectors pos;

    while (sizem > 0) 
    {
        


        for(int g = min; g <= max; g++) 
        {
            if(!m[g].empty())
            {
                pos = m[g].back();
                m[g].pop_back();
                sizem--;
                min = g;
                break;
            }
        }


        at(pos.x, pos.y).visited = true;

        if (pos.x == end.x && pos.y == end.y)
        {
            pathFound = true;
            break;
        }

        int clocal = at(pos.x, pos.y).local;

        for(int i = 0; i < 4; i++)
        {
            int cx = pos.x + v[i];
            int cy = pos.y + v[3-i];

            if(IsInGrid(cy, cx))
            {
                node &Case = at(cx, cy);

                if(!Case.visited && cells[cy][cx] != 1)
                {
                    
                    int rlocal = clocal + 1;
                    if(rlocal < Case.local)
                    {
                        Case.parent = pos;
                        Case.local = rlocal;
                        Case.heuristic = abs(ecolumn - cx) + abs(erow - cy);
                        Case.priority = Case.local + Case.heuristic;
                        int priority = Case.priority;
                        m[priority].emplace_back(Vectors{cx, cy});
                        sizem++;
                        if(priority < min) min = priority;
                        if(priority > max) max = priority;
                    }
                }  
            }
        }
    }

    for (auto& p : path) {
        cells[p.y][p.x] = 0;
    }
    path.clear();

    if (pathFound) {
        Vectors current = end;
        while (true) {
            current = at(current.x, current.y).parent;
            if (current.x == start.x && current.y == start.y) break;
            if (current.x == -1 || current.y == -1) break;
            
            cells[current.y][current.x] = 2;
            path.emplace_back(current);
        }
    }
}