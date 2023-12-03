// 01 Tukar Nilai
#include <iostream>
using namespace std;

int main() {
    int x, y;
    int *p1 = &x, *p2 = &y;
    cin     >> x >> y;

    int a   = *p1;
        *p1 = *p2;
        *p2 = a;
    cout    << "x = " << x << endl 
            << "y = " << y << endl;

}


