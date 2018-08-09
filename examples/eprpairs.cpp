#include "../include/qSim.h"

using namespace qsim;
using namespace math;
using namespace std;

int main () {
    Ket a = states::z0;
    Ket b = states::z0;
    Ket b00 = states::b00;

    Matrix H = gates::H;
    Matrix CX = gates::CX;

    a *= H;

    Ket c = a * b;

    c *= CX;

    cout << "Our result is:\n";
    c.print();

    cout << "The true result is:\n";
    b00.print();


}
