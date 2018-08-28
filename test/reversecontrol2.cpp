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

    Matrix hh = gates::H;
    shared_ptr<Matrix> H = make_shared<Matrix>(hh);

    Matrix ss = gates::S;
    shared_ptr<Matrix> S = make_shared<Matrix>(ss);

    vector<vector<circuit::Gate>> toffoli = {
        {{I, I, H}},
        {{I}, {C, S}},
        {{C, X}, {I}},
        {{I}, {C, S}},
        {{I}, {C, S}},
        {{I}, {C, S}},
        {{C, X}, {I}},
        {{C, I, S}},
        {{I, I, H}}
    };

    Matrix fin = {{1}};

    for (auto i : toffoli) {
        Matrix mid = controller(i, C, I);
        fin  = mid * fin;
    };

    fin.print();


    vector<vector<circuit::Gate>> bell = {
        {{C, I, X}},
        {{X, I, C}},
        {{X, C, C}},
        {{C, X, C}},
        {{C, X}, {X}},
        {{X}, {X, C}},
        {{X, C}, {X}},
        {{X, I, C}}
    };

    Matrix bin = {{1}};
    for (auto i : bell) {
        Matrix mid = controller(i, C, I);
        //cout << "mid\n";
        //mid.arrayPrint();
        bin =  mid * bin;
        //cout << "bin\n";
        //bin.arrayPrint();
    };
    bin.arrayPrint();


    //vector<vector<circuit::Gate>> range = {
    //    {{C, X}},
    //    {{X, C}},
    //    
    //    {{I}, {C, X}},
    //    {{X, C}, {I}},
    //    
    //    {{C, X}, {I}},
    //    {{I}, {X, C}},
//
    //    {{C, I, X}},
    //    {{X, I, C}},
//
    //    {{I}, {C, X}, {I}},
    //    {{I}, {X, C}, {I}},
//
    //    {{C, C, X}},
    //    {{X, C, C}},
//
    //    {{C, C, X}, {I}},
    //    {{X, C, C}, {I}},
//
    //    {{C, I, C, X}},
    //    {{X, C, I, C}},
//
    //    {{C, X, C}},
//
//
    //    {{I}, {C, X, C}},
    //    {{C, X, C}, {I}},
//
    //    {{C, C, I, X}},
    //    {{X, I, C, C}}
    //};

    //int j = 1;
    //for (auto i : range) {
    //    cout << j << endl;
    //    Matrix mat = controller(i, C, I);
    //    mat.arrayPrint();
    //    j++;
    //};
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