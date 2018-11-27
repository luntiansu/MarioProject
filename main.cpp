//
//  main.cpp
//  MarioProject
//
//  Created by Amanda Cervantes on 11/13/18.
//  Copyright © 2018 SDL_tutorial. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"
#include "Point.h"
#include "functions.h"
#include "opensprite.h"



using namespace std;


//Scene textures
//LTexture gBannerTexture;
//LTexture gSpriteSheetTexture;


int main(int argc, char ** argv)
{
    //This sets the background to be 480 x 640 pixels
    SDL_Plotter g(480,640);
    
    //initialization of variables to be later used with the functions
    bool stopped = false;
    bool colored = false;
    bool moved = false;
    int x,y, xd, yd;
    int R,G,B;
    int startx = 80;
    int starty = 400;
    char keyname = '\0';
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    
    //The velocity of the dot
    int mVelX = 80, mVelY = 400;
    //static const int DOT_WIDTH = 24;
    //static const int DOT_HEIGHT = 32;
    
    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;
    
    
    //RGB values for red (Can change to what ever color though)
    // Pink
    //    R = 239;
    //    G = 13;
    //    B = 246;
    
    //    //The window we'll be rendering to
    //    gWindow = g.getwindow();
    //    //The window renderer
    //    gRenderer = g.getrenderer();
    //
    //    gTexture = g.gettexture();
    //    loadmario();
    
    ifstream infile;
    ofstream outfile;
    Picture pics[PICS];
    
    infile.open("/Users/Calypso/Dropbox/Shared/Game2/sprite.txt");
    if (!infile)
    {
        cout << "Error: Picture not found!" << endl;
        return 1;
    }
    
    // outfile.open("foo.testing.txt");
    // if (!outfile){
    //     return 1;
    // }
    
    int upics = 0;
    //read in used number of pictures
    infile >> upics;
    char readbuffer[COLS+1];
    cout << "DEBUG|upics:" <<upics << endl;
    
    for (int i = 0; i<upics; i++)
    {
        readImageFromBoothGIF(infile, pics, i);
        //        pics[i].print(cout);
    }
    
    infile.close();
    
    Mario mario;
    
    
    
    while (!g.getQuit())
    {
        
        R = 0;
        G = 0;
        B = 0;
        if(!stopped){
            
            g.clear();
            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 0;
            y = 0;
            
            
            
            for(xd = 0; xd < 640 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 480 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    
                }
            }
            //            g.update();
        }
        
        
        //        if(g.kbhit()){
        //            g.getKey();
        //        }
        //
        //        if(g.getMouseClick(x,y)){
        //            stopped = !stopped;
        //        }
        
        //RGB values for red (Can change to what ever color though)
        // bottom yellow
        //        R = 240;
        //        G = 255;
        //        B = 0;
        //
        
        //        while (!g.getQuit())
        //        {
        R = 239;
        G = 13;
        B = 246;
        
        
        if(!stopped){
            
            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 112; //175 ;
            y = 240; //500 ;
            
            //was 600x50
            
            for(xd = 0; xd < 386 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 24 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    
                }
            }
            //                g.update();
        }
        
        //            if(g.kbhit()){
        //                g.getKey();
        //            }
        //
        //            if(g.getMouseClick(x,y)){
        //                stopped = !stopped;
        //            }
        
        
        //RGB values for red (Can change to what ever color though)
        // Bottom Blue.
        //            R = 26;
        //            G = 18;
        //            B = 107;
        R = 240;
        G = 255;
        B = 0;
        
        
        
        
        //            while (!g.getQuit())
        //            {
        if(!stopped){
            
            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 0 ;
            y = 336; //700 ;
            
            
            // was 400x50
            for(xd = 0; xd < 256 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 24 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    
                }
            }
            //                    g.update();
        }
        
        //                if(g.kbhit()){
        //                    g.getKey();
        //                }
        //
        //                if(g.getMouseClick(x,y)){
        //                    stopped = !stopped;
        //                }
        
        //RGB values for red (Can change to what ever color though)
        // green
        R = 18;
        G = 107;
        B = 18;
        
        
        
        //                while (!g.getQuit())
        //                {
        if(!stopped){
            
            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 384;  //600 ;
            y = 336;  //700 ;
            
            // was 400x50
            
            for(xd = 0; xd < 256 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 24 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    
                }
            }
            //                        g.update();
        }
        
        //                    if(g.kbhit()){
        //                        g.getKey();
        //                    }
        //
        //                    if(g.getMouseClick(x,y)){
        //                        stopped = !stopped;
        //                    }
        
        // green
        
        R = 18;
        G = 107;
        B = 18;
        
        
        
        //                    while (!g.getQuit())
        //                    {
        
        
        if(!stopped){
            
            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 384; //600 ;
            y = 144;  //300 ;
            
            
            //was400x50
            for(xd = 0; xd < 256 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 24 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    
                }
            }
            //                            g.update();
        }
        
        //                        if(g.kbhit()){
        //                            g.getKey();
        //                        }
        //
        //                        if(g.getMouseClick(x,y)){
        //                            stopped = !stopped;
        //                        }
        //// Top Blue
        //                        R = 26;
        //                        G = 18;
        //                        B = 107;
        R = 240;
        G = 255;
        B = 0;
        
        
        
        //                        while (!g.getQuit())
        //                        {
        if(!stopped){
            
            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 0 ;
            y = 144;  //300 ;
            
            
            // was 400x50
            for(xd = 0; xd < 256 && x + xd < g.getCol(); xd++ ){
                for(yd = 0; yd < 24 && y + yd < g.getRow(); yd++ ){
                    if(colored){
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    else{
                        g.plotPixel(x + xd, y + yd, R, G, B);
                    }
                    
                }
            }
            //                                g.update();
        }
        
        if(g.kbhit()){
            keyname = g.getKey();
            moved = true;
        }
        
        if(g.getMouseClick(x,y) || keyname == 'Q'){
            stopped = !stopped;
            g.getQuit();
        }
        
        if (!g.getQuit()) {
            
            //                            plotmario();
            
            if(!moved)
            {
                pics[1].setRowsCols(24, 20);
                
            }
            else if (keyname == LEFT_ARROW)
            {
                
                pics[1].setRowsCols(24, 20);
                mVelX -= DOT_VEL;
                
            }
            else if (keyname == RIGHT_ARROW)
            {
                
                pics[1].setRowsCols(24, 20);
                mVelX += DOT_VEL;
                
            }
//            else if (keyname == UP_ARROW)
//            {
//
//                pics[1].setRowsCols(24, 20);
//                mVelY -= DOT_VEL;
//
//            }
//            else if (keyname == DOWN_ARROW)
//            {
//
//                pics[1].setRowsCols(24, 20);
//                mVelY += DOT_VEL;
//
//            }
        
//            else if (keyname == UP_ARROW)
//            {
//                pics[1].setRowsCols(24, 20);
//                mVelY = -1 * pow(mVelX, 2);
//
//            }
            pics[1].drawPicture(g, mVelY, mVelX);

            
            g.update();
            SDL_Delay(50);
        }
        //            }
    }
}



