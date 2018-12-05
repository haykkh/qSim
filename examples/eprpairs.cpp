/*
 *  An example of entangled EPR pairs in a shared Bell state
 */ 

#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main () {
    Ket a = states::z0;
    Ket b = states::z0;
    Ket b00 = states::b00;

    Ket_ptr A = make_shared<Ket>(a);
    Ket_ptr B = make_shared<Ket>(b);

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

    cout << "\nCircuit Matrix:\n";
    fc.print();

    Ket c = a * b;

    cout << "\nSystem starting state:\n";
    c.print();

    c *= fc;

    cout << "\nResult from circuit:\n";
    c.print();

    cout << "\nRecalled variable result:\n";
    b00.print();

    c.measure();
    cout << "\nState after measurement:\n";

    c.print();


}
