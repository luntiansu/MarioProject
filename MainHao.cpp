//
//  main.cpp
//  MarioProject
//
//  Created by hao sheng wu on 11/11/18.
//  Copyright © 2018 Hao Sheng. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "SDL_Plotter.h"

using namespace std;

int main(int argc, char ** argv)
{
    const int windowHeight = 600;
    const int windowWidth = 1000;
    SDL_Plotter g(windowHeight,windowWidth);   // makes width and height of play window
    
    bool stopped = false;
    
    int width = 20;
    int height = 20;
    int posX = 300;
    int posY = 300;
    
    while (!g.getQuit())
    {
        //input
        if(g.getKey() == DOWN_ARROW)    // allows you to move
        {
            posY = min(posY + 4, windowHeight - height);    // ensures you do not go off screen
        }
        else if (g.getKey() == UP_ARROW)
        {
            posY = max(posY - 2,0);
            
        }
        else if (g.getKey() == RIGHT_ARROW)
        {
            posX = min(posX + 4, windowWidth - width);
        }
        else if (g.getKey() == LEFT_ARROW)
        {
            posX = max(posX - 4, 0);
        }
        
        // draw background
        for (int col = 0; col < windowWidth; col++)
        {
            for (int row = 0; row < windowHeight; row++)
            {
                g.plotPixel(col,row, 300,225,225);
            }
        }
        // draw loop
        for (int col = posX; col < width + posX; col++)   // goes through all columns
        {
            for (int row = posY; row < height + posY; ++row)
            {
                g.plotPixel(col,row, 23,10,204);
            }
        }
        
        if(g.kbhit()){
            g.getKey();
        }
        
        
        
        g.update();
    }
}



