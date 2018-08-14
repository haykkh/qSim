#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main() {
    Ket k1 = states::z0;
    Ket k2 = states::z0;
    Ket k3 = states::z0;

    Matrix H = gates::H;
    Matrix CX = gates::X.controlled();
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


    circuit::Circuit balls;

    //balls.setQubits({q1, q2, q3});

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

    //balls.setCircuit({{X, {q1}}, {CX, {q2, q3}}});

    //Matrix fc = balls.getFinalCircuit();

    //Matrix* c = CX.getControlGate();

    //c->print();

    Matrix g = gates::S;

    H.setControlGate(&gates::S);

    Matrix n = CX.getControlGate();

    n.print();
    CX.print();


}


