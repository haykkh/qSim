#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    Ket k0 = states::z0;
    Ket k1 = states::z0;
    Ket k2 = states::z0;
    Ket k3 = states::z0;

    Ket two = k0 * k1;
    Ket three = k0 * k1 * k2;
    Ket four = k0 * k1 * k2 * k3;

    cout << "2 qubit QFT matrix:\n\n";
    Matrix twoQFT = gates::QFT(4);
    twoQFT.print();
    
    cout << "\nSystem starting state:\n";
    two.print();

    two *= twoQFT;

    cout << "\nSystem state after circuit:\n";
    two.print();

    two.measure();

    cout << "\nSystem state after measurement:\n";
    two.print();


    cout << "\n3 qubit QFT matrix:\n\n";
    Matrix threeQFT = gates::QFT(8);
    threeQFT.print();

    cout << "\nSystem starting state:\n";
    three.print();

    three *= threeQFT;

    cout << "\nSystem state after circuit:\n";
    three.print();

    three.measure();

    cout << "\nSystem state after measurement:\n";
    three.print();


    cout << "\n4 qubit QFT matrix:\n\n";
    Matrix fourQFT = gates::QFT(16);
    fourQFT.print();

    cout << "\nSystem starting state:\n";
    four.print();

    four *= fourQFT;

    cout << "\nSystem state after circuit:\n";
    four.print();

    four.measure();

    cout << "\nSystem state after measurement:\n";
    four.print();

}