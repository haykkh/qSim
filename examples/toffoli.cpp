#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

//Ket toffoli(Ket q1, Ket q2, Ket q3) {
//    Matrix H = gates::H;
//    Matrix CX = gates::CX;
//    Matrix T = gates::T;
//    Matrix Td = T.adjoint();
//    Matrix S = gates::S;
//    
//
//    q3 *= H;
//
//    Ket q23 = q2 * q3;
//
//    q23 *= CX;
//
//};


int main() {
    Matrix H = gates::H;
    Matrix CX = gates::CX;
    Matrix T = gates::T;
    Matrix Td = T.adjoint();
    Matrix S = gates::S;

    Ket q1 = states::z1;
    Ket q2 = states::z1;
    Ket q3 = states::z0;

    q3 *= H;

    Ket q23 = q2 * q3;
    q23.print();
    q23 *= CX;

    q23.print();

    Matrix I = {{1,0},{0,1}};
    Matrix X = gates::X;

    I.print();

    Matrix B = tensorProduct(I,tensorProduct(X, I));

    B.print();
};