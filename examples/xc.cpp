#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    Ket k0 = states::z0;
    Ket k1 = states::z0;

    Ket* q0 = &k0;
    Ket* q1 = &k1;

    Matrix CX = gates::CX;
    Matrix H = gates::H;

    circuit::Circuit XC;

    XC.setQubits({q0, q1});

    XC.setCircuit({
                    {
                        {H, {q0}}, {H, {q1}}
                    },
                    {
                        {CX, {q0, q1}}
          
                    },
                    {
                        {H, {q0}}, {H, {q1}}
                    }
    });

    Matrix fc = XC.getFinalCircuit();

    fc.print();
};
