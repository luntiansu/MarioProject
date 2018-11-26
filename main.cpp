/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "functions.h"
#include "SDL_Plotter.h"

//using namespace std;
//Scene textures
LTexture gBannerTexture;
LTexture gSpriteSheetTexture;

SDL_Plotter g(500, 500); 


int main( int argc, char* args[] )
{
    
    
	//Start up SDL and create window
    if( !init() ) //g.init()
	{
        std::cout << "Failed to initialize!\n";
	}
	else
	{
		//Load media
        if( !loadMedia(gSpriteSheetTexture) ) //g.update()
		{
            std::cout << "Failed to load media!\n";
		}
		else
		{	
			//Main loop flag
			bool quit = false;

            //The dot that will be moving around on the screen
            Mario mario;
            
			//Event handler
			SDL_Event e;

            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
            SDL_RenderClear( gRenderer );

            //Render to screen
            SDL_Rect* bannerClip = &gSpriteClips[ 5 ];
            SDL_Rect wall;
            wall.x = 216;
            wall.y = - 220;
            wall.w = 208;
            wall.h = 87;
            int bannerstep = 0;
            gbannerSurface = IMG_Load( "/Users/Calypso/Dropbox/Shared/Game2/banner.png" );
            bannerTexture = SDL_CreateTextureFromSurface(gRenderer, gbannerSurface);
            SDL_FreeSurface(gbannerSurface); /* we got the texture now -> free surface */
            //                    SDL_RenderDrawRect( gRenderer, &wall );

            //                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
            //                    SDL_RenderDrawRect( gRenderer, &wall );
            
            

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    
                
                    
                    //Handle input for the dot
                    mario.handleEvent( e );
				}

                SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                SDL_RenderClear( gRenderer );
                //Render current frame
                SDL_Rect* currentClip = &gSpriteClips[ frame / 3 ];
                mario.render(currentClip, gSpriteSheetTexture);
                
                
                
                if (g.getKey() == ' ')
                {
                    int i;
                    for(i = 0;i < JUMPSTEPS ;i++)
                    {
                        mario.jump(i);
                        if (i == JUMPSTEPS -1)
                        {
                            frame = 0;
                        }
                        else
                        {
                            frame = 1;
                            //SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                            SDL_RenderClear( gRenderer );
                            g.clear();
                        }
                        SDL_Rect* currentClip = &gSpriteClips[ frame ];
                        mario.render(currentClip, gSpriteSheetTexture);
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay( JUMPDELAY );
                        //Clear screen
//                        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
//                        SDL_RenderClear( gRenderer );
//                        g.clear();
                        
                    }
                    e.key.keysym.sym = NULL;

                }
                else
                {
                    mario.move();
                    

                    if (bannerstep < 400)
                    {
                        wall.y = -200+bannerstep;
                        //Clear screen
                        
                        SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_VERTICAL );
                        //Update screen
//                        SDL_RenderPresent( gRenderer );
                        bannerstep += 10;
                        SDL_Delay(50);
                        
                    }
                    else if (!doneflipping)
                    {
                        wall.x = 216;
                        wall.y = 200;
                        SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_VERTICAL );
                    }
                    else
                    {
                        wall.x = 216;
                        wall.y = 200;
                        SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_NONE );

                    }
                    
                   //Render current frame
                    SDL_Rect* currentClip = &gSpriteClips[ frame / 3 ];
                    mario.render(currentClip, gSpriteSheetTexture);
                    
                    //To clear the Mario after moving him
                    g.clear();

                    //Update screen
                    SDL_RenderPresent( gRenderer );
                    
                }
			}
		}
	}

	//Free resources and close SDL
	close(gSpriteSheetTexture);
    //potential sdl transfer
    g.~SDL_Plotter();

	return 0;
}

/***************/

//background code starts here
//#include <iostream>
//
//#include "SDL_Plotter.h"
//
//using namespace std;
//
//int main(int argc, char ** argv)
//{
//
//    SDL_Plotter g(1000,1000);
//    bool stopped = false;
//    bool colored = false;
//    int x,y, xd, yd;
//    int R,G,B;
//
//    //RGB values for red (Can change to what ever color though)
//    // Pink
//    R = 239;
//    G = 13;
//    B = 246;
//
//
//
//    while (!g.getQuit())
//    {
//        if(!stopped){
//
//            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
//            x = 1;
//            y = 1;
//
//
//
//            for(xd = 0; xd < 1000 && x + xd < g.getCol(); xd++ ){
//                for(yd = 0; yd < 1000 && y + yd < g.getRow(); yd++ ){
//                    if(colored){
//                        g.plotPixel(x + xd, y + yd, R, G, B);
//                    }
//                    else{
//                        g.plotPixel(x + xd, y + yd, R, G, B);
//                    }
//
//                }
//            }
//        }
//
//        if(g.kbhit()){
//            g.getKey();
//        }
//
//        if(g.getMouseClick(x,y)){
//            stopped = !stopped;
//        }
//
//        //RGB values for red (Can change to what ever color though)
//        // bottom yellow
//        R = 240;
//        G = 255;
//        B = 0;
//
//
//
//        while (!g.getQuit())
//        {
//            if(!stopped){
//
//                //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
//                x = 175 ;
//                y = 500 ;
//
//
//
//                for(xd = 0; xd < 600 && x + xd < g.getCol(); xd++ ){
//                    for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
//                        if(colored){
//                            g.plotPixel(x + xd, y + yd, R, G, B);
//                        }
//                        else{
//                            g.plotPixel(x + xd, y + yd, R, G, B);
//                        }
//
//                    }
//                }
//            }
//
//            if(g.kbhit()){
//                g.getKey();
//            }
//
//            if(g.getMouseClick(x,y)){
//                stopped = !stopped;
//            }
//
//
//            //RGB values for red (Can change to what ever color though)
//            // Bottom Blue.
//            R = 26;
//            G = 18;
//            B = 107;
//
//
//
//            while (!g.getQuit())
//            {
//                if(!stopped){
//
//                    //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
//                    x = 1 ;
//                    y = 700 ;
//
//
//
//                    for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
//                        for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
//                            if(colored){
//                                g.plotPixel(x + xd, y + yd, R, G, B);
//                            }
//                            else{
//                                g.plotPixel(x + xd, y + yd, R, G, B);
//                            }
//
//                        }
//                    }
//                }
//
//                if(g.kbhit()){
//                    g.getKey();
//                }
//
//                if(g.getMouseClick(x,y)){
//                    stopped = !stopped;
//                }
//
//                //RGB values for red (Can change to what ever color though)
//                // green
//                R = 18;
//                G = 107;
//                B = 18;
//
//
//
//                while (!g.getQuit())
//                {
//                    if(!stopped){
//
//                        //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
//                        x = 600 ;
//                        y = 700 ;
//
//
//
//                        for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
//                            for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
//                                if(colored){
//                                    g.plotPixel(x + xd, y + yd, R, G, B);
//                                }
//                                else{
//                                    g.plotPixel(x + xd, y + yd, R, G, B);
//                                }
//
//                            }
//                        }
//                    }
//
//                    if(g.kbhit()){
//                        g.getKey();
//                    }
//
//                    if(g.getMouseClick(x,y)){
//                        stopped = !stopped;
//                    }
//
//                    // green
//
//                    R = 18;
//                    G = 107;
//                    B = 18;
//
//
//
//                    while (!g.getQuit())
//                    {
//                        if(!stopped){
//
//                            //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
//                            x = 600 ;
//                            y = 300 ;
//
//
//
//                            for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
//                                for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
//                                    if(colored){
//                                        g.plotPixel(x + xd, y + yd, R, G, B);
//                                    }
//                                    else{
//                                        g.plotPixel(x + xd, y + yd, R, G, B);
//                                    }
//
//                                }
//                            }
//                        }
//
//                        if(g.kbhit()){
//                            g.getKey();
//                        }
//
//                        if(g.getMouseClick(x,y)){
//                            stopped = !stopped;
//                        }
//                        //// Top Blue
//                        R = 26;
//                        G = 18;
//                        B = 107;
//
//
//                        while (!g.getQuit())
//                        {
//                            if(!stopped){
//
//                                //Sets position of the square (If you go below 110 or over 830 the square is off the sdl screen at least on my computer)
//                                x = 1 ;
//                                y = 300 ;
//
//
//
//                                for(xd = 0; xd < 400 && x + xd < g.getCol(); xd++ ){
//                                    for(yd = 0; yd < 50 && y + yd < g.getRow(); yd++ ){
//                                        if(colored){
//                                            g.plotPixel(x + xd, y + yd, R, G, B);
//                                        }
//                                        else{
//                                            g.plotPixel(x + xd, y + yd, R, G, B);
//                                        }
//
//                                    }
//                                }
//                            }
//
//                            if(g.kbhit()){
//                                g.getKey();
//                            }
//
//                            if(g.getMouseClick(x,y)){
//                                stopped = !stopped;
//                            }
//
//
//
//                            g.update();
//
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//}

/**********/
//background code ends here
