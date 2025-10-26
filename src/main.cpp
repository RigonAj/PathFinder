#include <raylib.h>
#include <iostream>
#include <raymath.h>
#include "grid.hpp"

using namespace std;
const int CellSize=12;


int ff=0;
Color green = { 173 , 204 , 96, 255};

int main(){

    InitWindow(100,100,"PathFinder");
    int monitor=GetCurrentMonitor();
    const int sw=GetMonitorWidth(monitor),sh=GetMonitorHeight(monitor);
    SetWindowSize(sw, sh);
    SetWindowPosition(0,0);


    Grid grid{sw,sh,CellSize};
    cout<<grid.IsInGrid(23,10);
    while(!WindowShouldClose()){
        if (IsKeyDown(KEY_LEFT_SHIFT)){
            grid.astar();
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){grid.SetCell(GetMousePosition(),1);}
            if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){grid.SetCell(GetMousePosition(),0);}
        }else{
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !grid.IsColliding(GetMousePosition(),1)){grid.SetCell(GetMousePosition(),3); grid.astar();}
            if( IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !grid.IsColliding(GetMousePosition(),1)){grid.SetCell(GetMousePosition(),4);grid.astar();}
        }
        if(IsKeyPressed(KEY_R))grid.Reset();

        BeginDrawing();
        ClearBackground(BLACK);

        grid.Draw();
        DrawRectangle(9*CellSize,9*CellSize,7*CellSize,3*CellSize,BLACK);
        DrawFPS(10*CellSize,10*CellSize);
        DrawText(TextFormat("%d", grid.IsColliding(GetMousePosition(),2)), 25*CellSize, 10*CellSize, 35, BLACK);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
