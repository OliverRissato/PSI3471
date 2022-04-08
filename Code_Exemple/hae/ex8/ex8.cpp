#include <cekeikon.h>

Mat_<GRY> mediana(Mat_<GRY> a) {
    Mat_<GRY> b(a.rows,a.cols);
    for (int l=0; l<b.rows; l++)
        for (int c=0; c<b.cols; c++) {
            vector<int> v;
            //mediana 14x14
            for (int l2=-7; l2<=7; l2++)
                for (int c2=-7; c2<=7; c2++)
                    if (0<=l+l2 && l+l2<a.rows && 0<=c+c2 && c+c2<a.cols) {
                        v.push_back(a(l+l2,c+c2));
                    }
            //vector<int>::iterator meio=v.begin()+v.size()/2;
            auto meio=v.begin()+v.size()/2;
            nth_element(v.begin(), meio, v.end());
            b(l,c) = *meio;
        }
    return b;
}


int main() {
    Mat_<GRY> ax; le(ax,"janei.pgm");
    Mat_<GRY> ay; le(ay,"janei-1.pgm");
    Mat_<GRY> qx; le(qx,"julho.pgm");
    if (ax.size()!=ay.size()) erro("Erro dimensao");
    Mat_<GRY> qp(qx.rows,qx.cols);

    //Cria as estruturas de dados para alimentar OpenCV
    Mat_<FLT> features(ax.rows*ax.cols,9);
    Mat_<FLT> saidas(ax.rows*ax.cols,1);
    int i=0;

    for (int l=1; l<ax.rows-1; l++)
        for (int c=1; c<ax.cols-1; c++) {
            int count = 0;
            for (int l2=-1; l2<=1; l2++)
                for (int c2=-1; c2<=1; c2++) {
                    count++;
                    features(i,count)=ax(l+l2,c+c2)/255.0;
                }
            saidas(i)=ay(l,c)/255.0;
            i=i+1;
        }

    //Boosting
    CvBoost ind(features,CV_ROW_SAMPLE,saidas);
    Mat_<FLT> query(1,9);
    for (int l=1; l<qp.rows-1; l++)
        for (int c=1; c<qp.cols-1; c++) {
            int count = 0;
            for (int l2=-1; l2<=1; l2++)
                for (int c2=-1; c2<=1; c2++) {
                    query(0,count)=qx(l+l2,c+c2)/255.0;
                    count++;
                }
            int pred=saturate_cast<GRY>(255.0*ind.predict(query));
            qp(l,c)=pred;
        }
    imp(qp,"julho-p1.png");
    Mat_<GRY> b = mediana(qp);
    imp(b,"julho-p1(mediana).png");
    Mat_<COR> qp_cor; le(qp_cor,"julho.pgm");
    for (int l=0; l<qp_cor.rows; l++)
        for (int c=0; c<qp_cor.cols; c++) {
            if (b(l,c) == 0){
                qp_cor(l,c)[0] = 0;
                qp_cor(l,c)[1] = 0;
                qp_cor(l,c)[2] = 255;
            }
        }
    imp(qp_cor, "julho-c1.png");
}
