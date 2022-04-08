#include <cekeikon.h>
int main()
{
    Mat_<GRY> a;
    le(a, "mickey.bmp");
    for (int l = 1; l < a.rows - 1; l++)
        for(int c = 1; c < a.cols - 1; c++){
            if((a(l, c) == 255) && (a(l - 1, c) == 0) && (a(l + 1, c) == 0) && (a(l, c - 1) == 0) && (a(l, c + 1) == 0))
                a(l, c) = 0;
            //if(a(l, c) == 255) a(l, c) = 0;
               
        }
    imp(a,"mickeysemruido.bmp");
}