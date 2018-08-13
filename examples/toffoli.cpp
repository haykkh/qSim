#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main() {
    Matrix H = gates::H;
    Matrix CX = gates::CX;
    Matrix T = gates::T;
    Matrix Td = T.adjoint();
    Matrix S = gates::S;
    Matrix X = gates::X;

    Ket q1 = states::z1;
    Ket q2 = states::z1;
    Ket q3 = states::z0;

    Matrix I = {{1,0},{0,1}};


    Matrix g1 = tensorProduct(I, tensorProduct(I, H));
    Matrix g2 = tensorProduct(I, CX);
    Matrix g3 = tensorProduct(I, tensorProduct(I, Td));
    Matrix g4 = tensorProduct(I, X).controlled();
    Matrix g5 = tensorProduct(I, tensorProduct(I, T));
    Matrix g6 = g2;
    Matrix g7 = g3;
    Matrix g8 = g4;
    Matrix g9 = tensorProduct(I, tensorProduct(Td, T));
    Matrix g10 = tensorProduct(X.controlled(), H);
    Matrix g11 = tensorProduct(I, tensorProduct(Td, I));
    Matrix g12 = tensorProduct(X.controlled(), I);
    Matrix g13 = tensorProduct(T, tensorProduct(S, I));

    Matrix final = g13 * (g12 * (g11 * (g10 * (g9 * (g8 * (g7 * (g6 * (g5 * (g4 * (g3 * (g2 * g1)))))))))));

    final.print();

    Ket qT = q1 * (q2 * q3);

    qT.print();

    Ket fina = final * qT;

    fina.print();



};