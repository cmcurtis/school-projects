using namespace std;
#include <iostream>
#include "zDepthList.cpp"
int main() {
    int l[30];
    for (int i=0;i<30;i++) l[i]=i;
    zDepthList z(l,30);
    z.out('f');
    z.move(10,2,'f');
    z.out();
    z.move(14,3,'r');
    z.out('r');
    z.movefront(4);
    z.moveback(13);
    z.out();
    cout << endl << endl;
    for (int i=0;i<30;i+=2) l[i]=28
-i; 
    zDepthList x(l,30), x1;
    x.out('f');
    x.move(27,2,'f');
    x.out();
    x.move(3,8,'r');
    x.out('r');
    x.movefront(4);
    x.moveback(13);
    x.out();
    x.del(3);
    x.out();
    x.addback();
    x.out();
    x.split(12,x1);
    x.out();
    x1.out();
    x1.combine(x);
    x1.out();
#define bigsize 1000000
    int big[bigsize];
    for (int i=0;i<bigsize;i++) big[i]=i;
    zDepthList y(big,bigsize);
