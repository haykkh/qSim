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
    extern const math::Matrix CX = control(X);
    extern const math::Matrix CZ = control(Z);
    extern const math::Matrix CS = control(S);


    extern const math::Matrix CCNOT = control(control(X));
    extern const math::Matrix CSWAP = control(SWAP);

}
};

#endif