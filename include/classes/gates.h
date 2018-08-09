#ifndef CLASSES_GATES_H_
#define CLASSES_GATES_H_

namespace qsim {
    namespace gates {
    
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

        extern const math::Matrix CX = { {1, 0, 0, 0},
                                         {0, 1, 0, 0},
                                         {0, 0, 0, 1},
                                         {0, 0, 1, 0} };


        extern const math::Matrix CZ = { {1, 0, 0,   0},
                                         {0, 1, 0,   0},
                                         {0, 0, 1,   0},
                                         {0, 0, 0, - 1} };

        extern const math::Matrix CS = { {1, 0, 0,       0},
                                         {0, 1, 0,       0},
                                         {0, 0, 1,       0},
                                         {0, 0, 0, math::I} };
    
    

        extern const math::Matrix CCNOT = { {1, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 1, 0, 0, 0, 0, 0, 0},                        
                                            {0, 0, 1, 0, 0, 0, 0, 0},                        
                                            {0, 0, 0, 1, 0, 0, 0, 0},                        
                                            {0, 0, 0, 0, 1, 0, 0, 0},                        
                                            {0, 0, 0, 0, 0, 1, 0, 0},                        
                                            {0, 0, 0, 0, 0, 0, 0, 1},                        
                                            {0, 0, 0, 0, 0, 0, 1, 0} };

        extern const math::Matrix CSWAP = { {1, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 1, 0, 0, 0, 0, 0, 0},                        
                                            {0, 0, 1, 0, 0, 0, 0, 0},                        
                                            {0, 0, 0, 1, 0, 0, 0, 0},                        
                                            {0, 0, 0, 0, 1, 0, 0, 0},                        
                                            {0, 0, 0, 0, 0, 0, 1, 0},                        
                                            {0, 0, 0, 0, 0, 1, 0, 0},                        
                                            {0, 0, 0, 0, 0, 0, 0, 1} };
    
    }
};

#endif