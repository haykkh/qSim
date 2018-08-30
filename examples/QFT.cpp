#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    cout << "2 qubit QFT matrix:\n\n";
    gates::QFT(4).print();

    cout << "\n3 qubit QFT matrix:\n\n";
    gates::QFT(8).print();

    cout << "\n4 qubit QFT matrix:\n\n";
    gates::QFT(16).print();

}