#include <cekeikon.h>

Mat_<FLT> fazmoldura(Mat_<FLT> x, int i, int j, float k){
    Mat_<FLT> y(i, j);
    int xl = (i-x.rows)/2; //50
    int xc = (j-x.cols)/2; //150
    //printf("xl: %i, xc: %i, x.rows: %i, x.cols: %i\n", xl, xc, x.rows, x.cols);
    for (int l = 0; l < y.rows; l++)
        for (int c = 0; c < y.cols; c++){
                if((l >= xl && c >xc) && (l >= xl && c < (xc+x.cols)) && (l < (xl+x.rows) && c > xc)) y(l,c) = x(l-xl,c-xc);
                else y(l, c) = k;
        }
    return y;
}


Mat_<FLT> mudaescala(Mat_<FLT> x, float i){
    int nl=cvRound(x.rows*i);
    int nc=cvRound(x.cols*i);
    Mat_<FLT> y(nl,nc); //q2m com escala mudada
    for (int l=0; l<y.rows; l++)
        for (int c=0; c<y.cols; c++)
            y(l,c) = x(cvRound(l/i),cvRound(c/i));
    return y;
}

Mat_<FLT> rotacionamatriz(Mat_<FLT> x, double i){
    double co, se, radianos;
    radianos = deg2rad(i);
    co = cos(radianos);
    se = sin(radianos);
    ImgXyb<FLT> matrizrotacionada;
    matrizrotacionada = x;
    matrizrotacionada.centro(matrizrotacionada.rows/2, matrizrotacionada.cols/2); matrizrotacionada.backg = 1;
    ImgXyb<FLT> matrizrotacionada2(matrizrotacionada.rows, matrizrotacionada.cols);
    matrizrotacionada2.centro(matrizrotacionada2.rows/2, matrizrotacionada2.cols/2); matrizrotacionada2.backg = 1;
    for (int xb=matrizrotacionada2.minx; xb<=matrizrotacionada2.maxx; xb++)
        for (int yb=matrizrotacionada2.miny; yb<=matrizrotacionada2.maxy; yb++) {
            int xa=cvRound(xb*co+yb*se);
            int ya=cvRound(-xb*se+yb*co);
            matrizrotacionada2(xb,yb)=matrizrotacionada(xa,ya);
    }
    matrizrotacionada2 = Mat_<FLT>(matrizrotacionada2);
    return matrizrotacionada2;
}

Mat_<FLT> deslocamatriz(Mat_<FLT> x, int i, int j){
    Mat_<FLT> y(x.rows, x.cols);
    for(int m = 0; m < y.rows; m++){
        for(int n = 0; n < y.cols; n++){
            if(m+i<0 || m+i >= y.rows || n+j < 0 || n+j >= y.cols){

            }
            else{
                y(m+i, n+j) = x(m, n);
            }
            if(m+i < 0){
                y(m+i+y.rows, n) = 128.0/255.0;
            }
            if(m+i >= y.rows){
                y(m+i-y.rows, n) = 128.0/255.0;
            }
            if(n+j < 0){
                y(m, n+j+y.cols) = 128.0/255.0;
            }
            if(n+j >= y.cols){
                y(m, n+j-y.cols) = 128.0/255.0;
            }
        }
    }
    return y;
}

int main(int argc, char** argv){
    if(argc != 3){
        printf("Erro: Numero de argumentos invalido");
    }
    else{
    TimePoint t1=timePoint();

    Mat_<FLT> m2; le(m2, "m2.pgm");
    Mat_<FLT> m3; le(m3, "m3.pgm");
    Mat_<FLT> m4; le(m4, "m4.pgm");
    Mat_<FLT> can; le(can, argv[1]);
    //imp(can, "m2_001_peb.jpg");
    
    //transforma o canhota em 750 colunas 
    float fator750 = 750.0/can.cols;
    int nl = cvRound(can.rows*fator750);
    Mat_<FLT> can2(nl, 750);
    for (int l = 0; l < can2.rows; l++)
        for (int c = 0; c < can2.cols; c++)
            can2(l, c) = can(cvRound(l/fator750),cvRound(c/fator750));
    //imp(can2, argv[2]);
    
    
    //mediacinza da iamgem de entrada
    float mediacinza = 0;
    for(int i = 0; i < can2.rows; i++)
        for(int j = 0; j < can2.cols; j++)
            mediacinza += can2(i, j);
    mediacinza /= (can2.rows)*(can2.cols);

    //faz a moldura nas iamgens
    Mat_<FLT> can2m = fazmoldura(can2, 310, 1150, mediacinza);
    Mat_<FLT> q2 = fazmoldura(m2, 210, 1050, 128.0/255.0);
    Mat_<FLT> q3 = fazmoldura(m3, 210, 1050, 128.0/255.0);
    Mat_<FLT> q4 = fazmoldura(m4, 210, 1050, 128.0/255.0);
    //imp(can2m, "m2_001_peb_moldura.jpg");
    //imp(q2, "m2_moldura.jpg");
    //variaveis
    Mat_<FLT> qm;
    Mat_<FLT> p1, p2;
    float resultado2 = 0;
    float resultado3 = 0;
    float resultado4 = 0;
    float resultadoescala2, resultadoescala3, resultadoescala4;
    double resultadorot2, resultadorot3, resultadorot4;
    int resultadom2, resultadom3, resultadom4, resultadon2, resultadon3, resultadon4;
    
    
    //loop para o matchtempalte mudando a escala e a rotação
    for(int modelo = 2; modelo < 5; modelo++){
        for(float escala = 0.88; escala < 1.10; escala = escala + 0.22/21){
            for(double rot = -3; rot <= 3; rot = rot + 0.375){     
                        if(modelo == 2)
                            qm = q2.clone();
                        else if(modelo == 3)
                            qm = q3.clone();
                        else
                            qm = q4.clone();

                        //muda a escala de q2m
                        qm = mudaescala(qm, escala);

                        //rotaciona a imagem
                        qm = rotacionamatriz(qm, rot);
                        
                        qm=somaAbsDois(dcReject(qm, 128.0/255.0));
                        p1=matchTemplateSame(can2m, qm, CV_TM_CCORR);
                        
                        
                            for(int i = 0; i < p1.rows; i++)
                            for(int j = 0; j<p1.cols; j++){
                                if(modelo == 2)    
                                    if(p1(i, j) > resultado2){ 
                                        resultado2 = p1(i, j);
                                        p2 = p1;
                                        resultadoescala2 = escala;
                                        resultadorot2 = rot;
                                        resultadom2 = i;
                                        resultadon2 = j;
                                    }
                                if(modelo == 3)    
                                    if(p1(i, j) > resultado3){ 
                                        resultado3 = p1(i, j);
                                        p2 = p1;
                                        resultadoescala3 = escala;
                                        resultadorot3 = rot;
                                        resultadom3 = i;
                                        resultadon3 = j;
                                    }
                                if(modelo == 4)    
                                    if(p1(i, j) > resultado4){ 
                                        resultado4 = p1(i, j);
                                        p2 = p1;
                                        resultadoescala4 = escala;
                                        resultadorot4 = rot;
                                        resultadom4 = i;
                                        resultadon4 = j;
                                    }
                            }
                        //printf("%f %lf %i\n", escala, rot, modelo);
                    }
        }
    }

    //imprime na tela as correlacoes
    printf("Maior correlacao entre %s e m2.pgm: %f\n", argv[1], resultado2);
    printf("Maior correlacao entre %s e m3.pgm: %f\n", argv[1], resultado3);
    printf("Maior correlacao entre %s e m4.pgm: %f\n", argv[1], resultado4);
    
    //imprime na tela os dados
    if((resultado2 > resultado3) && (resultado2 > resultado4))
        printf("melhorModelo=2 corr= %f graus= %lf fator= %f desloc(x,y)=[ %i, %i]\n", resultado2, resultadorot2, resultadoescala2, resultadom2-155, resultadon2-575);
    if((resultado3 > resultado2) && (resultado3 > resultado4))
        printf("melhorModelo=3 corr= %f graus= %lf fator= %f desloc(x,y)=[ %i, %i]\n", resultado3, resultadorot3, resultadoescala3, resultadom3-155, resultadon3-575);
    if((resultado4 > resultado2) && (resultado4 > resultado3))
        printf("melhorModelo=4 corr= %f graus= %lf fator= %f desloc(x,y)=[ %i, %i]\n", resultado4, resultadorot4, resultadoescala4, resultadom4-155, resultadon4-575);
    impTempo(t1);


    Mat_<COR> fotofinal; converte(can2m, fotofinal);
    Mat_<FLT> qfinal;

    if((resultado2 > resultado3) && (resultado2 > resultado4)){
        qfinal = q2.clone();
        //muda a escala
        qfinal = mudaescala(qfinal, resultadoescala2);
        //rotaciona a imagem
        qfinal = rotacionamatriz(qfinal, resultadorot2);
        //desloca a imagem em relacao ao centro
        qfinal = deslocamatriz(qfinal, resultadom2-155, resultadon2-575);
    }
    if((resultado3 > resultado2) && (resultado3 > resultado4)){
        qfinal = q3.clone();
        //muda a escala
        qfinal = mudaescala(qfinal, resultadoescala3);
        //rotaciona a imagem
        qfinal = rotacionamatriz(qfinal, resultadorot3);
        //desloca a imagem em relacao ao centro
        qfinal = deslocamatriz(qfinal, resultadom3-155, resultadon3-575);
    }
    if((resultado4 > resultado2) && (resultado4 > resultado3)){
        qfinal = q4.clone();
        //muda a escala
        qfinal = mudaescala(qfinal, resultadoescala4);
        //rotaciona a imagem
        qfinal = rotacionamatriz(qfinal, resultadorot4);
        //desloca a imagem em relacao ao centro
        qfinal = deslocamatriz(qfinal, resultadom4-155, resultadon4-575);
    }


    Mat_<FLT> qfinal2 = fazmoldura(qfinal, 310, 1150, 128.0/255.0);
    for(int i = 0; i < qfinal2.rows; i++)
        for(int j = 0; j < qfinal2.cols; j++){
            if(qfinal2(i, j) == 0){
                fotofinal(i,j)[2] = 255;
                fotofinal(i,j)[1] = max(fotofinal(i,j)[1] - 100,0);
                fotofinal(i,j)[0] = max(fotofinal(i,j)[0] - 100,0);
            }
            if(qfinal2(i, j) > 0.4 && qfinal2(i, j) < 0.6){
                fotofinal(i,j)[0] = 255;
                fotofinal(i,j)[1] = max(fotofinal(i,j)[1] - 100, 0);
                fotofinal(i,j)[2] = max(fotofinal(i,j)[2] -100, 0);
            }
        }


    imp(fotofinal, argv[2]);
    }
}