//mediana.cpp - pos2018
#include <cekeikon.h>

Mat_<GRY> mediana(Mat_<GRY> a) {
    Mat_<GRY> b(a.rows,a.cols);
    medianBlur(a, b, 5);    
    return b;
}
int main() {
    Mat_<GRY> a;
    le(a,"fever-2.pgm");
    Mat_<GRY> b=mediana(a);
    for(int i = 0; i < 10; i++)
        b=mediana(b);
    
    imp(b,"ex35.png");
}