#include <iostream>
#include <iomanip>
#include <fstream>
#include "SDL_Plotter.h"
using namespace std;

const int ROWS = 50;
const int COLS = 500;
const int PICS = 5;
struct pixel {int r;int g;int b;};
ostream &printPixel(ostream &out, pixel p)
{out <<setfill('0')<<setw(3)<<p.r<<"|"<<setfill('0')<<setw(3)<<p.g<<"|"<<setfill('0')<<setw(3)<<p.b;return out;}
class Picture
{protected:
    //Used rows and columns
    int urows;int ucolumns;
    pixel pic[ROWS][COLS];
    public:Picture(){this->urows=0;this->ucolumns=0;}
    void setRowsCols(int rows, int columns)
    {this->urows = rows;this->ucolumns = columns;}
    pixel getPixel(int r, int c) {return pic[r][c];}
    void setPixel(pixel p, int r, int c) {pic[r][c] = p;}
    ostream &print(ostream &out){out << "CLASS: Picture";out << "   rows:" << this->urows << "\t\tcols:" << this->ucolumns << endl;
    for (int i=0; i<this->urows; i++)
        {for (int j=0; j<this->ucolumns; j++)
        {printPixel(out, this->pic[i][j]) << " ";}out << endl;
}return out;}
void drawPicture(SDL_Plotter &canvas, int x, int y)
{for(int xd = 0; xd < this->urows ; xd++ )
{for (int yd = 0; yd < this->ucolumns; yd++) {pixel p = this->getPixel(xd, yd);
canvas.plotPixel(y + yd, x + xd, p.r, p.g, p.b);}}}};
void readImageFromBoothGIF(ifstream &in, Picture pics[], int index){int urows;int ucols;pixel pix;
//read used rows and columns from
 in >> urows >> ucols;
 pics[index].setRowsCols(urows, ucols);
 for (int i=0; i<urows; i++){for (int j=0; j<ucols; j++){in >>pix.r >>pix.g >>pix.b;pics[index].setPixel(pix, i, j);}}}
 int main(int argc, char ** argv) {SDL_Plotter g(600,600);
 ifstream infile;ofstream outfile;
 Picture pics[PICS];
 infile.open("sprite.txt");
 if (!infile){return 1;}
 // outfile.open("foo.testing.txt");
 // if (!outfile){
 //     return 1;// }
 int upics = 0;
 //read in used number of pictures
 infile >> upics;
 char readbuffer[COLS+1];cout << "DEBUG|upics:" <<upics << endl;
for (int i = 0; i<upics; i++) {readImageFromBoothGIF(infile, pics, i);
pics[i].print(cout);}
while (!g.getQuit()) {for (int i = 0; i<upics; i++) {pics[i].drawPicture(g, i*100, 0);}
if( g.kbhit() ){g.getKey();}g.update();}infile.close();outfile.close();}


//#include <iostream>
//#include <fstream>
//#include "SDL_Plotter.h"
//using namespace std;
//const int ROW = 90;
//const int COL = 14;
//struct pixel {int r;int g;int b;};
//int main(int argc, char ** argv)
//{SDL_Plotter g(500,500);int x = 200,y = 200, xd, yd;
//int R = 0,G = 200,B = 0;
//ifstream infile;
//infile.open("sprite.txt");
//if (!infile){return 1;}
//pixel pic[ROW][COL];
//for( int i = 0; i < ROW; i++)
//    {for(int k = 0; k < COL; k++ )
//    {infile >> pic[i][k].r;
//infile >> pic[i][k].g;
//infile >> pic[i][k].b;}}
//while (!g.getQuit())
//    {for(xd = 0; xd < ROW ; xd++ )
//    {for (yd = 0; yd < COL; yd++)
//    {g.plotPixel(y + yd, x + xd, pic[xd][yd].r, pic[xd][yd].g, pic[xd][yd].b);}}
//if( g.kbhit() ){g.getKey();}g.update();}}
