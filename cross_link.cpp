#include "head.h"

int main()
{
    Triple t1[5] = {
        {1,1,12},
        {1,4,-1},
        {2,2,3},
        {3,3,2},
        {4,3,10},
    };

    Triple t2[5] = {
        {1,2,7},
        {2,2,3},
        {3,3,-2},
        {4,1,9},
        {4,4,8},
    };

    Crosslist A, B;
    CreateMatrix(A, 4, 4, 5, t1);
    CreateMatrix(B, 4, 4, 5, t2);
    cout << "矩阵A：" << endl;
    PrintMatrix(A);
    cout << endl<< "矩阵B：" << endl;
    PrintMatrix(B);

    AddMatrix(A, B);
    cout << endl << "A+B：" << endl;
    PrintMatrix(A);

    DestroyMatrix(A);
    DestroyMatrix(B);
    return 0;
}