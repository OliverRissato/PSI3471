#include <cekeikon.h>
int main() {
    Mat_<COR> a;
    le(a, "lenna.jpg");
    for (int l=0; l<a.rows; l++)
        for(int c=0; c<a.cols; c++){
            a(l,c)[0] = 255-a(l,c)[0];
            a(l,c)[1] = 255-a(l,c)[1];
            a(l,c)[2] = 255-a(l,c)[2];
        }
    imp(a,"aza.jpg");
}