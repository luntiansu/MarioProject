/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
//#include "SDL_Plotter.h"


//using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int JUMPSTEPS = 2;
const int JUMPHEIGHT = 80;
const int JUMPWIDTH = 40;
const int JUMPDELAY = 100;
//Current animation frame
int frame = 0;

bool doneflipping = false;

SDL_Texture* bannerTexture;
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gbannerSurface = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;


//Walking animation
const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
SDL_Rect gBannerClips[ 9 ];



class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loads image at specified path
    bool loadFromFile( std::string path );
    
    #ifdef _SDL_TTF_H
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif
    
//Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

//The dot that will move around on the screen
class Mario
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 24;
    static const int DOT_HEIGHT = 32;
    
    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;
    
    //Initializes the variables
    Mario();
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the dot and checks collision
    void move(); // SDL_Rect& wall );
    void jump(int j); // SDL_Rect& wall );

//    //Shows the dot on the screen
//    void render(SDL_Rect* passClip);
    //Renders texture at given point
    void render(SDL_Rect* passClip, LTexture &mRenderTexture);
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    
    //The velocity of the dot
    int mVelX, mVelY;
    
    //Dot's collision box
    SDL_Rect mCollider;
    
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    bool xdir = 1;
    
//    int j;

};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void loadmario();

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) ); //0, 0xFF, 0xFF ) );
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //Return success
    mTexture = newTexture;
//    bannerTexture = newTexture;
    return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    
    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

Mario::Mario()
{
    //Initialize the offsets
    mPosX = 80;
    mPosY = 400;
    
    //Set collision box dimension
    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    flipType = SDL_FLIP_NONE;
}

void Mario::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; xdir = 0; flipType = SDL_FLIP_NONE; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; xdir = 1; flipType = SDL_FLIP_HORIZONTAL; break;
        }
        //Go to next frame
        ++frame;
        
        //Cycle animation
        if( frame  >= WALKING_ANIMATION_FRAMES - 1)
        {
            frame = 0;
        }
        
        
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
        frame = 0;
        
    }
}

void Mario::move( ) //SDL_Rect& wall )
{
    //Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) ) //|| checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the dot up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) ) //|| checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
    
    
}

void Mario::jump(int j)
{
    
    if (xdir == 1 && (mPosX + DOT_WIDTH < SCREEN_WIDTH))
    {
        mPosX += DOT_VEL / JUMPSTEPS;
    }
    if (xdir == 0 && (mPosX - DOT_WIDTH > 0))
    {
        mPosX -= DOT_VEL / JUMPSTEPS;
        
    }
    
    
    if (j < JUMPSTEPS / 2 )
    {
        mPosY -= JUMPHEIGHT;
        
    }
    if (j>=JUMPSTEPS / 2)
    {
        mPosY += JUMPHEIGHT;
        
    }
    
    
}

void Mario::render(SDL_Rect* passClip, LTexture &mRenderTexture)
{
    //Show the dot
    //    gDotTexture.render( mPosX, mPosY );
    mRenderTexture.render( mPosX, mPosY, passClip, NULL, NULL, flipType);

}

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "MARIO BROS.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 ); //0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia(LTexture& gLoadSheetTexture)
{
    //Loading success flag
    bool success = true;
//    int index;
    
    //Load sprite sheet texture
    if( !gLoadSheetTexture.loadFromFile( "/Users/luisc/Xcode Projects/Game3/mb_spritesheet.png" ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        
        //Set sprite No1: Mario_Stand
        gSpriteClips[ 0 ].x =  3;
        gSpriteClips[ 0 ].y = 602;
        gSpriteClips[ 0 ].w = 16;
        gSpriteClips[ 0 ].h = 21;
        
        //SSet sprite No2: Mario_Walk_1
        gSpriteClips[ 1 ].x = 22;
        gSpriteClips[ 1 ].y = 602;
        gSpriteClips[ 1 ].w = 13;  //26
        gSpriteClips[ 1 ].h = 21;
        
        //Set sprite No3: Mario_Walk_2
        gSpriteClips[ 2 ].x =  36;
        gSpriteClips[ 2 ].y = 602;
        gSpriteClips[ 2 ].w = 14;
        gSpriteClips[ 2 ].h = 21;
        
        //Set sprite No4:Mario_Walk_3
        gSpriteClips[ 3 ].x = 54;
        gSpriteClips[ 3 ].y = 602;
        gSpriteClips[ 3 ].w = 14;
        gSpriteClips[ 3 ].h = 21;
        
        //Set sprite No5:Mario_Jump
        gSpriteClips[ 4 ].x = 93;
        gSpriteClips[ 4 ].y = 602;
        gSpriteClips[ 4 ].w = 15;
        gSpriteClips[ 4 ].h = 21;
        
        //Set sprite No5:Mario_Jump
        gSpriteClips[ 5 ].x = 0;
        gSpriteClips[ 5 ].y = 0;
        gSpriteClips[ 5 ].w = 208;
        gSpriteClips[ 5 ].h = 87;
        

        
    }
    
    return success;
}

void close(LTexture gCloseSheetTexture)
{
    //Free loaded images
    gCloseSheetTexture.free();
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

void loadmario( ) //int argc, char* args[] )
{
    
    //Scene textures
    LTexture gBannerTexture;
    LTexture gSpriteSheetTexture;
    

    //Start up SDL and create window
    //    if( !init() )
    //    {
    //        printf( "Failed to initialize!\n" );
    //    }
    //    else
    //    {
    //Load media
    if( !loadMedia(gSpriteSheetTexture) )
    {
        printf( "Failed to load media!\n" );
    }
    else
    {
        //Main loop flag
        bool quit = false;
        
        //The dot that will be moving around on the screen
//        Mario mario;
        
        //            //Event handler
        //            SDL_Event e;
        //
        //            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
        //            SDL_RenderClear( gRenderer );
        //
        //            //Render to screen
//                    SDL_Rect* bannerClip = &gSpriteClips[ 5 ];
//                    SDL_Rect wall;
//                    wall.x = 216;
//                    wall.y = - 220;
//                    wall.w = 208;
//                    wall.h = 87;
////                    int bannerstep = 0;
//                    gbannerSurface = IMG_Load( "/Users/luisc/Xcode Projects/Game3/banner.png" );
//                    bannerTexture = SDL_CreateTextureFromSurface(gRenderer, gbannerSurface);
//                    SDL_FreeSurface(gbannerSurface); /* we got the texture now -> free surface */
//                    wall.x = 216;
//                    wall.y = 200;
//                    SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_NONE );
                    //                    SDL_RenderDrawRect( gRenderer, &wall );
        //
        //            //                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
        //            //                    SDL_RenderDrawRect( gRenderer, &wall );
        //
        //
        //
        //            //While application is running
        //            while( !quit )
        //            {
        //                //Handle events on queue
        //                while( SDL_PollEvent( &e ) != 0 )
        //                {
        //                    //User requests quit
        //                    if( e.type == SDL_QUIT )
        //                    {
        //                        quit = true;
        //                    }
        //
        //                    //Handle input for the dot
        //                    mario.handleEvent( e );
        //
        //
        //                }
        //
        //                SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
        //                SDL_RenderClear( gRenderer );
        //                //Render current frame
        //                SDL_Rect* currentClip = &gSpriteClips[ frame / 3 ];
        //                mario.render(currentClip, gSpriteSheetTexture);
        //
        //
        //
        //                if (e.key.keysym.sym == SDLK_SPACE)
        //                {
        //                    int i;
        //                    for(i = 0;i < JUMPSTEPS ;i++)
        //                    {
        //                        mario.jump(i);
        //                        if (i == JUMPSTEPS -1)
        //                        {
        //                            frame = 0;
        //                        }
        //                        else
        //                        {
        //                            frame = 4;
        //                        }
        //                        SDL_Rect* currentClip = &gSpriteClips[ frame ];
        //                        mario.render(currentClip, gSpriteSheetTexture);
        //                        SDL_RenderPresent( gRenderer );
        //                        SDL_Delay( JUMPDELAY );
        //                        //Clear screen
        //                        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
        //                        SDL_RenderClear( gRenderer );
        //
        //                    }
        //                    e.key.keysym.sym = NULL;
        //
        //                }
        //                else
        //                {
        //                    mario.move();
        //
        //
        //                    if (bannerstep < 400)
        //                    {
        //                        wall.y = -200+bannerstep;
        //                        //Clear screen
        //
        //                        SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_VERTICAL );
        //                        //Update screen
        ////                        SDL_RenderPresent( gRenderer );
        //                        bannerstep += 10;
        //                        SDL_Delay(50);
        //
        //                    }
        //                    else if (!doneflipping)
        //                    {
        //                        wall.x = 216;
        //                        wall.y = 200;
        //                        SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_VERTICAL );
        //                    }
        //                    else
        //                    {
        //                        wall.x = 216;
        //                        wall.y = 200;
        //                        SDL_RenderCopyEx( gRenderer, bannerTexture, bannerClip, &wall, NULL, NULL, SDL_FLIP_NONE );
        //
        //                    }
        //
                           //Render current frame
//                            SDL_Rect* currentClip = &gSpriteClips[ frame / 3 ];
//                            mario.render(currentClip, gSpriteSheetTexture);
//        //
        //                    //Update screen
        //                    SDL_RenderPresent( gRenderer );
        //
        //                }
        //            }
        //        }
    }
    
    //Free resources and close SDL
//    close(gSpriteSheetTexture);
    
    return; // 0;
}

//void plotmario()
//{
//    int x, int y, int r, int g, int b;
//    int xd;
//    int yd;
//    int i;
//    
//    for (i = 1; i < (24); i++)
//    {
//        for (j = 1; j < 34; j++)
//        {
//            g.plotPixel(x + xd, y + yd, R, G, B);
//        }
//gSpriteClips[ 5 ]
//}

