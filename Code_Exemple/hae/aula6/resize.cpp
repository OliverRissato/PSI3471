//cvvizinho.cpp pos2018 - usa funcao resize do OpenCV
#include <cekeikon.h>
int main() {
    Mat_<GRY> a; le(a,"lennag.jpg");
    Mat_<GRY> b;
    resize(a, b, Size(0,0), 3.6, 3.6, INTER_NEAREST);
    imp(b,"lennag_vizinho.png");
    resize(a, b, Size(0,0), 3.6, 3.6, INTER_LINEAR);
    imp(b,"lennag_bilinear.png");
    resize(a, b, Size(0,0), 3.6, 3.6, INTER_CUBIC);
    imp(b,"lennag_bicubico.png");
    resize(a, b, Size(0,0), 3.6, 3.6, INTER_LANCZOS4);
    imp(b,"lennag_lanczos.png");
}