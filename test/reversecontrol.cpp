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

Matrix controllerAgain(Matrix U, int ctrl, int targ, int size) {
    Matrix Z = gates::Z;
    if (ctrl < targ) {
        if (targ - ctrl - 2 < 0) {
            // figure out adding one, three, and five
            Matrix two = U - In(2);
            Matrix four = In(1) - Z;
            return In(size) + tensorProduct(four, two) / 2;
        } else {
            Matrix one = In(size - targ);
            Matrix two = U - In(2);
            Matrix three = In(targ - ctrl - 2);
            Matrix four = In(1) - Z;
            Matrix five = In(ctrl - 1);

            return In(size) + tensorProduct(five, tensorProduct(four, tensorProduct (three, tensorProduct(two, one)))) / 2;
        }
    } else {
        if (ctrl - targ - 2 < 0){
            // figure out adding one, three, and five
            Matrix two = In(1) - Z;
            Matrix four = U - In(2);
            return In(size) + tensorProduct(four, two) / 2;
        } else {
            Matrix one = In(size - targ);
            Matrix two = In(1) - Z;
            Matrix three = In(ctrl - 2 - targ);
            Matrix four = U - In(2);
            Matrix five = In(targ - 1);

            return In(size) + tensorProduct(five, tensorProduct(four, tensorProduct(three, tensorProduct(two, one)))) / 2;
        }

   };
};


int main() {
    Matrix X = gates::X;
    Matrix Z = gates::Z;
    Matrix I = gates::I;

    //cout << "one\n";
    Matrix one = controller(X, 1, 2, 2);
    //one.print();
//
    //cout << "two\n";
    Matrix two = controller(X, 2, 1, 2);
    //two.print();
//
    //cout << "3\n";
    //Matrix three = controller(X, 2, 3, 3);
    //three.print();
//
    //cout << "4\n";
    //Matrix four = controller(X, 2, 1, 3);
    //four.print();
//
    //cout << "5\n";
    //Matrix five = controller(X, 3, 1, 3);
    //five.print();
//
    //cout << "6\n";
    //Matrix six = controller(X, 1, 2, 3);
    //six.print();
//
    //cout << "7\n";
    //Matrix seven = controller(X, 3, 2, 3);
    //seven.print();
//
    //cout << "8\n";
    Matrix eight = controller(X, 1, 3, 3);
    //eight.print();
//
    //cout << "9\n";
    //Matrix nine = controllerAgain(one, 1, 3, 3);
    //nine.print();
//
    //cout << "10\n";
    //Matrix ten = controllerAgain(two, 3, 1, 3);
    //ten.print();
//
    cout << "11\n";
    Matrix eleven = controllerAgain(two, 1, 2, 4);
    eleven.print();
//

    cout << "11.5\n";
    Matrix elevenfive = controllerAgain(one, 3, 2, 3);
    elevenfive.print();


    //cout << "12\n";
    //Matrix twelve = controllerAgain(two, 2, 4, 4);
    //twelve.print();
//
    //cout << "13\n";
    //Matrix thirteen = controllerAgain(one, 1, 3, 4);
    //thirteen.print();
//
    //cout << "14\n";
    //Matrix fourteen =  controllerAgain(one, 1, 4, 4);
    //fourteen.print();
//
    //cout << "15\n";
    //Matrix fifteen = controllerAgain(eight, 1, 4, 4);
    //fifteen.print();
//
    //cout << "16\n";
    //Matrix sixteen = controllerAgain(one, 1, 4, 4);
    //sixteen.print();
//
    //cout << "17\n";
    ////Matrix seventeen = controllerAgain(five, 4, 1, 4);
    ////seventeen.print();
//
    //cout << "18\n";
    //Matrix eighteen = controllerAgain(two, 4, 1, 4);
    //eighteen.print();
//
    //cout << "19\n";
    //Matrix nineteen = controllerAgain(two, 3, 1, 4);
    //nineteen.print();
//
    //cout << "20\n";
    //Matrix twenty = controller(X, 2, 3, 4);
    //twenty.print();
//
//
    //cout << "21\n";
    //Matrix twentyone = controller(X, 3, 2, 4);
    //twentyone.print();

}