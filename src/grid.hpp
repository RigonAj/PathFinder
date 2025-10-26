
#pragma once
#include <vector>
#include <unordered_set>

class Grid
{
    public:
    Grid(const int sw,const int sh,const int CellSize):
        rows(sh/CellSize),columns(sw/CellSize),cellSize(CellSize),cells(rows,std::vector<int>(columns,0)){Node.resize(rows * columns);};
        
        
    struct Vectors {
        int x, y;
    };
    std::vector<Vectors> path;
    
    int srow=0,scolumn=0,erow=0,ecolumn=0;

    struct node{
            Vectors parent;
            int local=900;
            int heuristic=900;
            int priority=900;
            bool visited=false;
                };
        std::vector<node> Node;

    

        void Draw();
        int GetRows() const{return rows;}
        int GetColumns() const{return columns;}
        void SetCell(Vector2 MousePos,int value);
        bool IsInGrid(int row,int column);
        bool IsColliding(Vector2 P,int value);
        void Reset();
        node& at(int r,int c){return Node[r*rows + c];}; 
        void astar();

    private:
        int rows;
        int columns;
        int cellSize;
        std::vector<std::vector<int>> cells;
        



};