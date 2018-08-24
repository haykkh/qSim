#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {

    Matrix ii = gates::I;
    shared_ptr<Matrix> I = make_shared<Matrix>(ii);
    
    Matrix xx = gates::X;

    shared_ptr<Matrix> X = make_shared<Matrix>(xx);

    vector<shared_ptr<Matrix>> range(3, I);

    Matrix zz = gates::Z;

    shared_ptr<Matrix> Z = make_shared<Matrix>(zz);

    Matrix cc = (In(1) - zz) / 2;
    shared_ptr<Matrix> C = make_shared<Matrix>(cc);

    range = {C, X, I};

    for (auto i : range) {
        i -> print();
    };

    Matrix fin = tensorProduct(In(2) + tensorProduct(*C, *X - In(1)), In(1));

    fin.print();

    Matrix bin = In(3) + tensorProduct(*C, tensorProduct(In(1), *X - In(1)));
    bin.print();

    /*
     *  basically need to use our for loop iterating through range
     *  and use the *C listed above for control gates 
     * 
     *  simple for a moment that contains only one gate being controlled
     *  but need to implemenet if there is a gate being controlled + another gate 
     *  eg:
     *  
     *  ---|X|---
     *   
     *  ----●----
     *      │   
     *  ---|X|---
     * 
     * 
     *  maybe introduce another vector to range
     *  eg for example above:
     *  range = {{X}, {C, X}}
     * 
     * 
     */
}