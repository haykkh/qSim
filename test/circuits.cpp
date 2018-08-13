#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main() {
    Ket q1 = states::z1;
    Ket q2 = states::z1;
    Ket q3 = states::z0;

    Matrix H = gates::H;
    Matrix CX = gates::CX;
    Matrix T = gates::T;
    Matrix Td = T.adjoint();
    Matrix S = gates::S;
    Matrix X = gates::X;
    Matrix I = gates::I;


    circuit::Circuit balls;

    balls.setQubits({&q1, &q2, &q3});

    balls.setCircuit({ { H, {&q3}},
                       {CX, {&q2, &q3}},
                       {Td, {&q3}},
                       {CX, {&q1, &q3}},
                       { T, {&q3}},
                       {CX, {&q2, &q3}},
                       {Td, {&q3}},
                       {CX, {&q1, &q3}},
                       {Td, {&q2}},
                       { T, {&q3}},
                       {CX, {&q1, &q2}},
                       { H, {&q3}},
                       {Td, {&q2}},
                       {CX, {&q1, &q2}},
                       { T, {&q1}},
                       { S, {&q2}} });

}