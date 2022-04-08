//pers.cpp grad-2018
#include <cekeikon.h>

int main() {
    Mat_<FLT> src = (Mat_<FLT>(4,2) <<
        165,58,
        189,57,
        163,78,
        188,77);
    Mat_<FLT> dst = (Mat_<FLT>(4,2) <<
        165,58,
        189,58,
        165,78,
        189,78);
    Mat_<double> m=getPerspectiveTransform(src,dst);
    cout << m << endl;

    //Verifica se a transformacao esta fazendo o que queremos
    Mat_<double> v=(Mat_<double>(3,1) << 163,78,1);
    Mat_<double> w=m*v;
    cout << w << endl;
    cout << w(0)/w(2) << " " << w(1)/w(2) << endl;

    //Corrige a perspectiva
    Mat_<COR> a; le(a,"calib_result.jpg");
    Mat_<COR> b;
    warpPerspective(a,b,m,a.size());
    imp(b,"calib_result_1.jpg");

    //Refaz a perspectiva
    m=m.inv();
    warpPerspective(b,a,m,a.size());
    imp(a,"calib_result_2.jpg");
}