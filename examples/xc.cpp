#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    Ket k0 = states::z0;
    Ket k1 = states::z0;

    Ket_ptr q0 = make_shared<Ket>(k0);
    Ket_ptr q1 = make_shared<Ket>(k1);

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

    cout << "\nXC gate (second qubit controlled CX):\n";
    fc.print();
};