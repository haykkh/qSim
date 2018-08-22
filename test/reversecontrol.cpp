#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

Matrix controller(Matrix U, int ctrl, int targ, int size) {
    Matrix Z = gates::Z;
    if (ctrl < targ) {
        return In(size) + tensorProduct(In(ctrl-1), tensorProduct(In(1) - Z, tensorProduct(In(targ - 1 - ctrl), tensorProduct(U - In(1), In(size-targ))))) / 2;
    } else {
        return In(size) + tensorProduct(In(targ - 1), tensorProduct(U - In(1), tensorProduct(In(ctrl - 1 - targ), tensorProduct(In(1)- Z, In(size - ctrl))))) / 2;
    };
};


int main() {
    Ket k0 = states::z0;
    Ket k1 = states::z1;

    Ket* q0 = &k0;
    Ket* q1 = &k1;

    Matrix X = gates::X;
    Matrix Z = gates::Z;
    Matrix I = gates::I;

    Matrix i2 = tensorProduct(I, I);

    Matrix uid = X - I;
    Matrix idz = I - Z;

    Matrix uz = tensorProduct(idz, uid)/2;

    Matrix fc = i2 + uz;

    i2.print();
    uid.print();
    idz.print();
    uz.print();

    fc.print();


    Matrix gg = In(0);

    gg.print();

    Matrix CX = controller(X, 1, 2, 2);
    Matrix XC = controller(X, 2, 1, 2);

    Matrix nCX = controller(X, 3, 1, 3); 

    CX.print();
    XC.print();

    nCX.print();

}