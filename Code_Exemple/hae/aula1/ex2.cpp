#include <cekeikon.h>
#include <queue>

Mat_<COR> pintaVermelho(Mat_<COR> a, int ls, int cs, int t){
    Mat_<COR> b=a.clone();
    queue<int> q;
    COR cormatriz = b(ls, cs);
    q.push(ls); q.push(cs);
    while(!q.empty()) {
        int l = q.front(); q.pop();
        int c = q.front(); q.pop();
        if (distancia(cormatriz, b(l, c)) < t){
            b(l, c) = COR(0, 0, 255);
            q.push(l-1); q.push(c);
            q.push(l+1); q.push(c);
            q.push(l); q.push(c+1);
            q.push(l); q.push(c-1);
        }
    }
    return b;    
}

int main() {
    int l, c, t;
    Mat_<COR> a; le(a, "elefante.jpg");
    cout << "Insira l: ";
    cin >> l;
    cout << "Insira c: ";
    cin >> c;
    cout << "Insira t: ";
    cin >> t;
    Mat_<COR> b = pintaVermelho(a, l, c, t);
    imp(b, "ex2.jpg");
}