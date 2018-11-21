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
    
    SDL_Plotter g(1000,1000);
    bool stopped = false;
    bool colored = false;
    int x = 0,y = 0, xd, yd;
    int R,G,B;
    R = 100;
    G = 20;
    B = 50;
    
    while (!g.getQuit())
    {
        // INPUT
        if(g.kbhit()){
            char key = g.getKey();
            if(key == RIGHT_ARROW) {
                x += 10;
            }
            else if(key == LEFT_ARROW) {
                x -= 30;
                
            }
            else if(key == DOWN_ARROW){
                y-= 10;
            }
            else if(key ==UP_ARROW){
                y+= 10;
            }
        }
        
        // DRAW
        //x = rand()%g.getCol();
        //y = rand()%g.getRow();
        
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                g.plotPixel(j + x, i + y, 255, 255, 255);
                
            }
        }
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                g.plotPixel(j + x, i + y, R, G, B);
                
            }
        }
        
        g.update();
    }
    
}







