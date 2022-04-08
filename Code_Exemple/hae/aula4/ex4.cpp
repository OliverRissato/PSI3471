#include <cekeikon.h>
int main(){
    Mat_<FLT> a; le(a,"quadrado.png");
    Mat_<FLT> sx, sy, ox, oy;
    Sobel(a,sx,-1,1,0,3); ox=sx/4.0+0.5; imp(ox,"ox.png");
    Sobel(a,sy,-1,0,1,3); oy=sy/4.0+0.5; imp(oy,"oy.png");

    oy = sy; imp(oy,"hor_sup.png");
    oy =-sy; imp(oy,"hor_inf.png");
    oy = elev2(sy); imp(oy,"todo_hor.png");
    
    ox = sx; imp(ox,"ver_esq.png");
    ox =-sx; imp(ox,"ver_dir.png");
    ox = elev2(sx); imp(ox,"todo_ver.png");
}