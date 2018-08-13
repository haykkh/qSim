#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    Matrix CX = gates::CX;
    Matrix CZ = gates::CZ;
    Matrix CS = gates::CS;
    Matrix CCNOT = gates::CCNOT;
    Matrix CSWAP = gates::CSWAP;
    Matrix X = gates::X;
    vector<Matrix> b = {CX, CZ, CS, CCNOT, CSWAP};

    for (auto i : b){
        i.print();
        if (i.isControlled()) {
            cout << "Banana" << endl;
        };
    };

    if (X.isControlled()) {
        cout << "Yesnana" << endl;
    } else {
        cout << "Nonana" << endl;
    }

}
