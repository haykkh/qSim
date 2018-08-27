#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

Matrix controller(vector<circuit::Gate> range, shared_ptr<Matrix> C, shared_ptr<Matrix> I) {
     Matrix res = {{1}};

    for (auto i : range) {
        Matrix midres = {{1}};
        if (i.containsControl()) {
            for (auto gate : i.getGate()) {
                if(gate == I || gate == C) {
                    midres = tensorProduct(midres, *gate);
                } else {
                    midres = tensorProduct(midres, *gate - In(log(gate -> getXSize()) / log(2)));
                };
            };

            midres = In(log(midres.getXSize()) / log(2)) + midres;

        } else {
            for (auto gate : i.getGate()) {
                midres = tensorProduct(midres, *gate);
            };
        };
        res = tensorProduct(res, midres);

    };

    return res;

};


int main() {

    Matrix ii = gates::I;
    shared_ptr<Matrix> I = make_shared<Matrix>(ii);
    
    Matrix xx = gates::X;

    shared_ptr<Matrix> X = make_shared<Matrix>(xx);

    Matrix zz = gates::Z;

    shared_ptr<Matrix> Z = make_shared<Matrix>(zz);

    Matrix cc = (In(1) - zz) / 2;
    cc.setControlGate(true);
    shared_ptr<Matrix> C = make_shared<Matrix>(cc);

    vector<vector<circuit::Gate>> range = {
        {{C, X}},
        {{X, C}},
        
        {{I}, {C, X}},
        {{X, C}, {I}},
        
        {{C, X}, {I}},
        {{I}, {X, C}},

        {{C, I, X}},
        {{X, I, C}},

        {{I}, {C, X}, {I}},
        {{I}, {X, C}, {I}},

        {{C, C, X}},
        {{X, C, C}},

        {{C, C, X}, {I}},
        {{X, C, C}, {I}},

        {{C, I, C, X}},
        {{X, C, I, C}},

        {{C, X, C}},
        {{I}, {C, X, C}},
        {{C, X, C}, {I}},

        {{X, I, C, C}},
        {{C, C, I, X}}
    };

    int j = 1;
    for (auto i : range) {
        cout << j << endl;
        Matrix mat = controller(i, C, I);
        mat.arrayPrint();
        j++;
    };
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