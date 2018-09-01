#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main() {
    Ket k0 = states::z0;
    Ket k1 = states::z0;
    Ket k2 = states::z0;
    
    Ket* q0 = &k0;
    Ket* q1 = &k1;
    Ket* q2 = &k2;

    Matrix H = gates::H;
    Matrix S = gates::S;
    Matrix X = gates::X;

    Matrix CS = S.controlled();
    Matrix CX = X.controlled();

    circuit::Circuit toffoli;

    toffoli.setQubits({q0, q1, q2});

    toffoli.setCircuit({
        {
            {H, {q2}}
        },
        {
            {CS, {q1, q2}}
        },
        {
            {CX, {q0, q1}}
        },
        {
            {CS, {q1, q2}}
        },
        {
            {CS, {q1, q2}}
        },
        {
            {CS, {q1, q2}}
        },
        {
            {CX, {q0, q1}}
        },
        {
            {CS, {q0, q2}}
        },
        {
            {H, {q2}}
        }
    });

    Matrix fc = toffoli.getFinalCircuit();

    cout << "\nToffoli gate matrix:\n";
    fc.print();


};

