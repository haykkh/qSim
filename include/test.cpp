#include "qSim.h"
#include <vector>


using namespace qsim;
using namespace math;

int main() {
    //math::Ket a = states::z00;
    //math::Ket b = states::z01;
    //math::Ket c = states::z10;
    //math::Ket d = states::z11;
    //math::Ket e = states::z0;
    //math::Ket g = states::b00;
//
//
    //a.print();
    //b.print();
    //c.print();
    //d.print();
//
    //math::Ket f = a + b;
    //f.print();
//
    //g.print();
//
    //f += a;
    //f *= 2;
    //f /= 4;
//
    //f.print();

    //math::Matrix X = gates::X;
    //math::Matrix Y = gates::Y;
    //math::Matrix Z = gates::Z;
    //math::Matrix S = gates::S;
    //math::Matrix T = gates::T;
    //math::Matrix H = gates::H;
//
    //math::Matrix SWAP = gates::SWAP;
    //math::Matrix CX = gates::CX;
    //math::Matrix CZ = gates::CZ;
    //math::Matrix CS = gates::CS;
    //math::Matrix CCNOT = gates::CCNOT;
    //math::Matrix CSWAP = gates::CSWAP;
//
    //X.print();
    //Y.print();
    //Z.print();
    //S.print();
    //T.print();
    //H.print();
//
    //SWAP.print();
    //CX.print();
    //CZ.print();
    //CS.print();
    //CCNOT.print();
    //CSWAP.print();

    //math::Ket z0 = states::z0;
    //math::Ket z1 = states::z1;
//
    //math::Ket z00 = z0 * z0;
    //math::Ket z01 = z0 * z1;
    //math::Ket z10 = z1 * z0;
    //math::Ket z11 = z1 * z1;
//
    //z00.print();
    //z01.print();
    //z10.print();
    //z11.print();
//
    //math::Ket random = z11 * z0;
//
    //random.print();


    //math::Ket z0 = states::z0;
    //math::Matrix X = gates::X;
    //math::Matrix H = gates::H;
    //math::Matrix Y = gates::Y;
//
    //z0.print();
    //X.print();
//
    //X *= Y;
    //z0.print();
    //X.print();

    Ket z0 = states::z0;
    Matrix X = gates::X;
    Matrix H = gates::H;

    z0 *= X;
    z0 *= H;
    z0.print();
}