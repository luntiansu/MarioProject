/*
#include <iostream>

#include "SDL_Plotter.h"

using namespace std;

int main(int argc, char ** argv)
{

    SDL_Plotter g(1000,1000);
    bool stopped = false;
    bool colored = false;
    int x,y, xd, yd;
    int R,G,B;

    //RGB values for red (Can change to what ever color though)
    // Black BAckground.
    R = 0;
	G = 0;
    B = 0;



    while (!g.getQuit())
    {
		if(!stopped){

//Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 0.001;
			y = 0.001;



			for(xd = 0; xd < 1000 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 1000 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, G, B);
					}

				}
			}
		}

		if(g.kbhit()){
			g.getKey();
		}

		if(g.getMouseClick(x,y)){
			stopped = !stopped;
		}

		    //RGB values for red (Can change to what ever color though)
		    // Medium level yellow floor.
    R = 240;
	G = 255;
    B = 100;



    while (!g.getQuit())
    {
		if(!stopped){

//Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 175 ;
			y = 500 ;



			for(xd = 0; xd < 600 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, G, B);
					}

				}
			}
		}

		if(g.kbhit()){
			g.getKey();
		}

		if(g.getMouseClick(x,y)){
			stopped = !stopped;
		}


				    //RGB values for red (Can change to what ever color though)
				    // Bottom Blue level for .
    R = 95;
	G = 65;
    B = 245;



    while (!g.getQuit())
    {
		if(!stopped){

//Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 1 ;
			y = 700 ;



			for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, G, B);
					}

				}
			}
		}

		if(g.kbhit()){
			g.getKey();
		}

		if(g.getMouseClick(x,y)){
			stopped = !stopped;
		}

						    //RGB values for red (Can change to what ever color though)
						    // green
    R = 340;
	G = 77;
    B = 145;



    while (!g.getQuit())
    {
		if(!stopped){

//Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 600 ;
			y = 700 ;



			for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, G, B);
					}

				}
			}
		}

		if(g.kbhit()){
			g.getKey();
		}

		if(g.getMouseClick(x,y)){
			stopped = !stopped;
		}

		// green

		    R = 134;
	G = 13;
    B = 23;



    while (!g.getQuit())
    {
		if(!stopped){

//Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 600 ;
			y = 300 ;



			for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, G, B);
					}

				}
			}
		}

		if(g.kbhit()){
			g.getKey();
		}

		if(g.getMouseClick(x,y)){
			stopped = !stopped;
		}
//// Top Blue
		 R = 234;
	G = 14;
    B = 65;


		while (!g.getQuit())
    {
		if(!stopped){

//Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
            x = 1 ;
			y = 300 ;



			for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, G, B);
					}

				}
			}
		}

		if(g.kbhit()){
			g.getKey();
		}

		if(g.getMouseClick(x,y)){
			stopped = !stopped;
		}



		g.update();

    }
}
}
    }
}
}

}
*/
