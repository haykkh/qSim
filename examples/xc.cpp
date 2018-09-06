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

    circuit::Circuit XC1;

    XC1.setQubits({q0, q1});

    XC1.setCircuit({
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

    Matrix fc1 = XC1.getFinalCircuit();

    circuit::Circuit XC2;

    XC2.setQubits({q0, q1});

    XC2.setCircuit({
        {
            {CX, {q1, q0}}
        }
    });

    Matrix fc2 = XC2.getFinalCircuit();

    cout << "\nXC1 gate (second qubit controlled CX):\n";
    fc1.print();

    cout << "\nXC2 gate (second qubit controlled CX):\n";
    fc2.print();
};
