#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main() {
    Ket k1 = states::z1;
    Ket k2 = states::z1;
    Ket k3 = states::z0;
    Ket k4 = states::z0;

    Matrix H = gates::H;
    Matrix CX = gates::X.controlled();
    Matrix CCX = CX.controlled();
    Matrix T = gates::T;
    Matrix Td = T.adjoint();
    Matrix S = gates::S;
    Matrix X = gates::X;
    Matrix I = gates::I;
    Matrix Z = gates::Z;
    Matrix SWAP = gates::SWAP;

    Ket* q1 = &k1;
    Ket* q2 = &k2;
    Ket* q3 = &k3;
    Ket* q4 = &k4;

    int b;


    circuit::Circuit balls;

    balls.setQubits({q1, q2});

    //balls.setCircuit({ { H, {q3}},
    //                   {CX, {q2, q3}},
    //                   {Td, {q3}},
    //                   {CX, {q1, q3}},
    //                   { T, {q3}},
    //                   {CX, {q2, q3}},
    //                   {Td, {q3}},
    //                   {CX, {q1, q3}},
    //                   {Td, {q2}},
    //                   { T, {q3}},
    //                   {CX, {q1, q2}},
    //                   { H, {q3}},
    //                   {Td, {q2}},
    //                   {CX, {q1, q2}},
    //                   { T, {q1}},
    //                   { S, {q2}} });

    balls.setCircuit({{
                        {X, {q1}},
                        {X, {q2}}
                        }});

    Matrix fc = balls.getFinalCircuit();

    fc.print();

    //Ket qubs = k1 * k2 * k3;

    //qubs.print();

    //qubs *= fc;

    //qubs.print();

}


