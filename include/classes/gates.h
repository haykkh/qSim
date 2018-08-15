/*
 *  MIT License
 *  
 *  Copyright (c) 2018 Hayk Khachatryan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef CLASSES_GATES_H
#define CLASSES_GATES_H

namespace qsim {
namespace gates {

    class Gate {
        public:
            math::Matrix final;

            Gate();

            Gate(math::Matrix gate) : final(gate) {};

            Gate(std::vector<math::Ket> qubits) {

            }
    };

    extern const math::Matrix I = {{1, 0}, {0, 1}};

    /**********************/
    /*                    */
    /* Single qubit gates */
    /*                    */
    /**********************/
    
    // Pauli X/Y/Z
    extern const math::Matrix X = { {0, 1}, 
                                    {1, 0} };
    extern const math::Matrix Y = { {      0, - math::I}, 
                                    {math::I,         0} };
    extern const math::Matrix Z = { {1,  0}, 
                                    {0, -1} };
            
    // the rest
    extern const math::Matrix S = { {1,       0},
                                    {0, math::I} };
    extern const math::Matrix T = { {1,                                0},
                                    {0, std::exp(math::I * math::pi * 0.25)} };
    extern const math::Matrix H = { {1 / sqrt(2),   1 / sqrt(2)},
                                    {1 / sqrt(2), - 1 / sqrt(2)} };
    /*********************/
    /*                   */
    /* Multi qubit gates */
    /*                   */
    /*********************/
    extern const math::Matrix SWAP = { {1, 0, 0, 0},
                                       {0, 0, 1, 0},
                                       {0, 1, 0, 0},
                                       {0, 0, 0, 1} };
    extern const math::Matrix CX = X.controlled();
    extern const math::Matrix CZ = Z.controlled();
    extern const math::Matrix CS = S.controlled();


    extern const math::Matrix CCNOT = X.controlled().controlled();
    extern const math::Matrix CSWAP = SWAP.controlled();

}
};

#endif