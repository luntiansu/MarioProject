//
//  Point.h
//  MarioProject
//
//  Created by Amanda Cervantes on 11/16/18.
//  Copyright © 2018 SDL_tutorial. All rights reserved.
//

#ifndef Point_h
#define Point_h

#include "SDL_Plotter.h"
struct Point
{
    int x,y;
    int speed;
    int direction; 
    Point()
    {
        x = y = 0;
        speed = 0;
        direction = 0;
    }
    
    Point(int a, int b)
    {
        x = a;
        y = b;
        speed = 1;
    }
    void move()
    {
        x += direction;
        y += direction;
    }
    
    void draw(SDL_Plotter& g)
    {
        for(int r = -1; r <=1; r++)
        {
            for(int c = -1; c <= 1; c++)
            {
                g.plotPixel(c+x,r+y,0,0,0);
            }
        }
    }
    
    void erase(SDL_Plotter& g)
    {
        for(int r = -1; r <=1; r++)
        {
            for(int c = -1; c <= 1; c++)
            {
                g.plotPixel(c+x,r+y,255,255,255);
            }
        }
    }
};
#endif /* Point_h */
