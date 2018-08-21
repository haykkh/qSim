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

#ifndef CLASSES_CIRCUIT_H
#define CLASSES_CIRCUIT_H

namespace qsim{
namespace circuit{

class Circuit
{
    /*
     *   example circuit used in comments:
     * 
     *   │q0>  ---|X|--------◼︎---
     *                       │
     *   │q1>  ----●---------│---
     *             │         │
     *   │q2>  ---|X|--|H|---◼︎---
     *      
     *             ^    ^    ^
     *             m0   m1   m2
     */

  private:
    /* 
     *   vector of pointers all qubits in system
     *   eg:
     *   {&q0, &q1, &q3}
     */
    std::vector<math::Ket *> qubits;


    /* 
     *   state of system qubits
     *   initialized to {1} so it doesn't
     *   affect result when multiplied by states
     */
    math::Ket state = {1};


    /*
     *    input vector of circuit
     *   eg:
     *   { { {X, {&q0},     {CX, {&q1, &q2} } }, <- m0: first 'moment'
     *     { {H, {&q2}                      } }, <- m1: second 'moment'
     *     { {CZ,{&q0, &q2}                 } }  <- m2: third 'moment'
     *   }
     */
    std::vector<std::vector<std::pair<math::Matrix, std::vector<math::Ket *>>>> circuit;


    // number of qubits in system
    unsigned int n;


    /* 
     *   matrix of entire circuit
     *   initialized to {1} so it doesn't
     *   affect result when multiplied by moments
     */
    math::Matrix finalCircuit = {{1}};


    /*
     *   vector of time-slices of operations
     *   eg for example circuit above:
     *   
     *   {m0, m1, m2} 
     *   
     *   m0 = |X| ⨂ |X|.controlled
     *   m1 = |𝐼| ⨂ |𝐼| ⨂ |H|
     *   m2 = (|𝐼| ⨂ |Z|).controlled
     */
    std::vector<math::Matrix> moments;

  public:
    Circuit(){};

    Circuit(std::vector<math::Ket *> qubs, std::vector<std::vector<std::pair<math::Matrix, std::vector<math::Ket *>>>> circ){
        qubits = qubs;
        circuit = circ;
        n = qubits.size();
        circuitInitializer();
    };


    void setQubits(const std::vector<math::Ket*> qub) {
        qubits = qub;
        n = qubits.size();
    };


    /*
     *   sets value of circuit
     *   initializes matrix of entire circuit
     *   populates moments
     */
    void setCircuit(const std::vector<std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>>> circ) {
        circuit = circ;
        circuitInitializer();
    };


    // prints circuit as shown above
    void print() {
    };
    
    
    // creates moments and final circuit matrix
    void circuitInitializer() {
        // matrix of a time-slice of operations within the circuit
        math::Matrix moment = {{1}};
        math::Matrix C = {{1}};
        math::Matrix I = gates::I;

        /*
         *   a vector showing which qubits are operated on
         *   'I' : identity (qubit left alone)
         *   'C' : control qubit
         *   'T' : target qubit
         *   eg:
         * 
         *   for m0: range = {'T','C','T'}
         *   for m1: range = {'I','I','T'}
         *   for m2: range = {'C','I','T'}
         * 
         *   initialised to 'I's
         */
        std::vector<std::shared_ptr<math::Matrix>> range(n, std::make_shared<math::Matrix>(I));




        /*
         *   i of format:
         *   { {Gate, {qubits}}, {Gate, {qubits}} }
         */
        for (auto i : circuit) {

            // reset range to all 'I'
            range = std::vector<std::shared_ptr<math::Matrix>>(n, std::make_shared<math::Matrix>(I));

            //reset moment
            moment = {{1}};

            std::vector<const math::Matrix> buffers;
            
            for (auto j : i) {

                if (j.first.getXSize() != std::pow(2, j.second.size())) {
                    throw std::runtime_error("Invalid number of qubits to apply gate to");
                };

                if (j.second == qubits) {
                    moments.push_back(j.first);
                    finalCircuit = finalCircuit * j.first;
                } else {
                    int controlCount = 0;

                    math::Matrix buffer = j.first;

                    while (buffer.isControlled()) {
                        buffer = buffer.getControlGate();
                        controlCount++;
                    };
                    buffers.push_back(buffer);


                    for (int q = 0; q < controlCount; q++) {
                        range[objectFinder(j.second[q])] = std::make_shared<math::Matrix>(C);
                    };

                    for (int q = controlCount; q < j.second.size(); q++){
                        range[objectFinder(j.second[q])] = std::make_shared<math::Matrix>(buffers.back());
                    }

                }

            }

            for (int k = range.size() - 1; k >= 0; k--)
            {
                if (range[k] == std::make_shared<math::Matrix>(C))
                {
                    moment = moment.controlled();
                }
                else
                {
                    moment = tensorProduct(*range[k], moment);
                };
            }

            moments.push_back(moment);
            finalCircuit = finalCircuit * moment;
            
            //// if gate operates on a different number of qubits than specified
            //if (i.first.getXSize() != std::pow(2, i.second.size())) {
            //    throw std::runtime_error("Invalid number of qubits to apply gate to");
            //};
            //
            //
            ///*
            // *   if vector of qubits is identical
            // *   in order and contents to entire system qubits
            // */
            //if (i.second == qubits) {
            //    // add gate to moments
            //    // 'add' gate to finalCircuit
            //    moments.push_back(i.first);
            //    finalCircuit = finalCircuit * i.first;
            //} else {
            //    /*
            //     *   how many controls on gate
            //     *   eg CNOT : 1; CCNOT : 2
            //     */
            //    int controlCount = 0;
//
            //    /*
            //     *   eventually becomes the gate being controlled
            //     *   eg CNOT or CCNOT: NOT; CSWAP : SWAP
            //     */
            //    math::Matrix buffer = i.first;
//
            //    // populates buffer and counts up controlCount
            //    while (buffer.isControlled())
            //    {
            //        buffer = buffer.getControlGate();
            //        controlCount++;
            //    };
//
            //    // populate range with 'C's for control qubits
            //    for (int q = 0; q < controlCount; q++) {
            //        range[objectFinder(i.second[q])] = 'C';
            //    };
            //    // populate range with 'T's for target qubits
            //    for (int q = controlCount; q < i.second.size(); q++) {
            //        range[objectFinder(i.second[q])] = 'T';
            //    }
//
            //    // if gate.xSize >= 4 (ie multi qubit gate)
            //    if (i.first.getXSize() >= 4)
            //    {
            //        // if gate is a controlled gate
            //        if (i.first.isControlled())
            //        {
//
            //            /*
            //             *   Creates moment matrix up until the control qubit
            //             *   eg 
            //             *      ---●---
            //             *         │   
            //             *      --|X|--   moment = |X| ⨂ |𝐼|
            //             * 
            //             *      -------
            //             */
            //            for (int k = range.size() - 1; k >= 0 ; k--)
            //            {
//
            //                
            //                switch(range[k]){
            //                    // if gate not on qubit, apply identity
            //                    case 'I': {
            //                        moment = tensorProduct(gates::I, moment);
            //                        break;
            //                    };
            //                    // if qubit is controlled
            //                    case 'C' : {
            //                        moment = moment.controlled();
            //                        break;
            //                    };
            //                    // if gate on qubit, apply gate
            //                    case 'T' : {
            //                        moment = tensorProduct(buffer, moment);
            //                        break;
            //                    };
            //                };
            //            
            //            };
            //        }
//
            //        // else gate not controlled
            //        else
            //        {
            //            std::cout << "probably need to swap these" << std::endl;
            //        }
            //    }
//
            //    // else single qubit gate
            //    else
            //    {
            //        moment = math::multiplyerApplicator(moment, i.first, gates::I, range);
            //    };
            //};    
            //
            ////std::cout << "Gate: " << std::endl;
            ////i.first.print();
            ////moment.print();
            //
            //// append moment to moments vector
            //moments.push_back(moment);
            //
            //// 'add' moment to finalCircuit
            //finalCircuit  =   finalCircuit * moment;
        };
    };
    
    
    // returns the index of a qubit in 'qubits' vector
    int objectFinder(math::Ket *q){
        std::vector<math::Ket*>::iterator i = qubits.begin();
        i = find (qubits.begin(), qubits.end(), q);
        int b = distance (qubits.begin (), i);
        return b;
    }
    
    // checks whether qubits input are adjacent
    bool adjacent(std::vector<math::Ket *> qub){
        for (int i = 0; i < qub.size() - 1; i++) {
            // if the distance between qub[i] and qub[i+1] isn't 1 they are not adjacent
            if (std::abs(objectFinder(qub[i]) - objectFinder(qub[i+1])) != 1) {
                return false;
            };
        };
        return true;
    };


    std::vector<math::Ket*> getQubits() const {
        return qubits;
    };


    std::vector<std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>>> getCircuit() const {
        return circuit;
    };


    math::Matrix getMoment(int i) {
        return moments[i];
    };


    std::vector<math::Matrix> getMoments() {
        return moments;
    };


    math::Matrix getFinalCircuit() {
        return finalCircuit;
    }
        

}; // end class Circuit

}; // namespace circuit
}; // namespace qsim

#endif