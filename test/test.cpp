#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    Matrix I = gates::I;
    Matrix X = gates::X;
    Matrix CX = control(X);

    Matrix finalm = control(tensorProduct(I, tensorProduct(X, I)));
    Matrix finaln = tensorProduct(control(tensorProduct(I, X)), I);


    finalm.print();
    finaln.print();

};


