#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main () {
    Ket a = states::z0;
    Ket b = states::z0;
    Ket b00 = states::b00;

    Ket* A = &a;
    Ket* B = &b;

    Matrix H = gates::H;
    Matrix CX = gates::CX;

    circuit::Circuit bell;

    bell.setQubits({A, B});

    bell.setCircuit({
        {
            {H, {A}}
        },
        {
            {CX, {A, B}}
        }
    });


    Matrix fc = bell.getFinalCircuit();

    fc.print();

    Ket c = a * b;

    c *= fc;

    cout << "Our result is:\n";
    c.print();

    cout << "The true result is:\n";
    b00.print();


}
