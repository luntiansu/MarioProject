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

    //RGB values for red
    R = 255;
	G = 0;
    B = 0;



    while (!g.getQuit())
    {
		if(!stopped){

            //Set position of the square (If you go below 110 or over
            x = 830;
			y = 110;



			for(xd = 0; xd < 10 && x + xd < g.getCol(); xd++ ){
				for(yd = 0; yd < 10 && y + yd < g.getRow(); yd++ ){
					if(colored){
						g.plotPixel(x + xd, y + yd, R, G, B);
					}
					else{
					    g.plotPixel(x + xd, y + yd, R, 0, 0);
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



