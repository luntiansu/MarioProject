class Enemy
{
    private:

        int x,y,speed,tempy,tempx,enemyFloor,color,timer,score,type,direction;

        bool stuck;
    public:
        Enemy(int startx,int starty,int startspeed,int variety)
        {
            type=variety;
            score=0;
            timer=0;
            if(type==1)
            {

            direction=1;
            color=80;
            }
            if(type==2)
            {


            direction=-1;
            color=100;
            }
            stuck=false;
            x=startx;
            y=starty;
            tempx=x;
            tempy=y;
            speed=startspeed;
        }

        struct Color {
            int R;
            int G;
            int B;
        };

        int getScore()
        {
            return score;
        }
        bool collision(int playerX, int playerY,bool jumped)
        {

            if(stuck)
            {
                timer++;

                if(timer == 1000)
                {
                    stuck=false;
                    timer=0;
                    color =80;
                }


            }

            bool ans=true;
            int left1=x;
            int right1=x+19;
            int top1=y;
            int bottom1=y+19;
            int left2=playerX;
            int right2=playerX+19;
            int top2=playerY;
            int bottom2=playerY+19;

            if(left1>right2)
            ans=false;

            if(right1<left2)
            ans=false;

            if(top1>bottom2)
            ans=false;

            if(bottom1<top2)
            ans=false;

            if(ans&&stuck)
            {
                respawn();
                return true;

            }
            else if(ans)
                cout << "game over";
                /////////////////////////////////////////////////////////////



            if(jumped)
            if((playerX-x<=40)&&(playerX-x>=-40))
                if(playerY-y<25&&playerY-y>5)
                    stop();

            return false;



        }

        int getY()
        {
            return y;
        }
        int getX()
        {
            return x;
        }
        void stop()
        {
            stuck=true;
            /////////////////////////////

            color = 160;
        }
        void respawn()
        {
            timer =0;
            if(type==1)
            {


            x=20;
            y=20;
            tempx=20;
            tempy=20;
            stuck=false;
            color=80;
            }
            if(type==2)
            {
            x=600;
            y=20;
            tempx=600;
            tempy=20;
            stuck=false;
            color=100;

            }
            score++;
            cout << score;
        }
/////
        void drawEnemy(SDL_Plotter &g)
        {
            tempx=x-10;
            tempy=y-10;
            Color character1[16][16];
            fstream input;

            if(stuck)
            input.open("GhostDown.txt");
            else if(direction==1)
            input.open("GhostRight.txt");
            else
            input.open("GhostLeft.txt");

            if(!input)
            {
                cout << "Color File Not Found" << endl;
            }
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++)
                {

                    input >> character1[j][i].R >>character1[j][i].G >> character1[j][i].B;
                }
            }
            for(int a = 0;a<27;a++)
                {
                    for(int b =0;b<21 ;b++)
                        {
                            g.plotPixel( tempx+a,tempy+b, 255, 255, 255);
                        }
                }
           for(int a = 0;a<16;a++)
                {
                    for(int b =0;b<16;b++)
                        {
                            g.plotPixel( x+a,y+b, character1[a][b].R, character1[a][b].G, character1[a][b].B);
                        }
                }
                input.close();
        }

        void moveEnemy(int bot)
        {
            if(type==2&&x==320)
            {
                direction*=-1;
            }
            if(type==2&&x==950)
            {
                direction*=-1;
            }
            if(!stuck)
            {


            if(y<bot-20)
                y+=2;
            else
            {

                x+=direction;
            }
            if(x==1000)
            {
              x=0;
            }
            }

            /*
            if(y<179&&x<400)
            {
                y++;

            }
            if(y==179&&x<400)
            {
                x++;
            }
            if(x>=400&&y<499)
            {
                y++;
            }
            if(y==499)
            {
                x++;
            }
            if(x==1000)
            {
              x=0;
            }
*/





        }


};
