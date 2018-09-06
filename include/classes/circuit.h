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



// typedef for building blocks of circuit schematic
typedef std::vector<std::pair<math::Matrix, std::vector<math::Ket_ptr>>> momentScheme;
typedef std::vector<momentScheme> schematic;


class Gate {
    /*
     *  An object for multi qubit gates containing a 
     *      vector of "sub gates" that make up a full gate
     *      and a bool whether the Gate is controlled
     * 
     */ 


    private:
        // bool indicating whether Gate is a controlled gate
        bool controlled = false;

        /* 
         *  vector of "sub gates"
         * 
         *  eg:
         *      m0: 2 Gates: {X}, {C, X}
         *      m1: 2 Gates: {I}, {I}, {H}
         *      m2: 1 Gate: {C, I, Z}
         * 
         */ 
        std::vector<std::shared_ptr<math::Matrix>> gates;

    public:
        Gate(){};

        // init Gate for n 'sub-gates'
        Gate(unsigned int n) {
            gates.resize(n);
        };

        // init Gate with a list of 'sub-gates' and check if it's controlled
        Gate(std::initializer_list<std::shared_ptr<math::Matrix>> g) {
            gates = g;
            gateChecker();
        };

        // set a 'sub-gate' in Gate to m and check if gate is controlled
        void setGate(unsigned int index, std::shared_ptr<math::Matrix> m) {
            gates[index] = m;
            gateChecker();
        };

        // set entire Gate with a list of 'sub-gates' and check if gate is controlled
        void setGate(const std::vector<std::shared_ptr<math::Matrix>> g) {
            gates = g;
            gateChecker();
        };

        // checks if Gate contains any controls, and subsequently updates controlled
        void gateChecker() {
            for (auto i : gates) {
                if (i != 0) {
                    if (i -> isControlGate()) {
                        controlled = true;
                    };
                };
            };
        }

        bool containsControl() {
            return controlled;
        };

        std::vector<std::shared_ptr<math::Matrix>> getGate() {
            return gates;
        };
};

/*
 *  The Magic
 *  Creates a moment for a circuit (eg m0, m1, m2)
 *  
 *  iterates through range as 'i'
 *      initialize midres
 *      if 'i' contains a control gate,
 *          do control magic (generalised form of this https://quantumcomputing.stackexchange.com/a/3941 )
 *      else
 *          apply gates in i to midres
 * 
 *      'add' midres to res
 * 
 *  return res
 * 
 *  eg
 *      m0:
 *          range = {{X}, {C, X}}
 * 
 *          i = {X}
 *          gate = X
 *          midres = X
 * 
 *          res = X
 * 
 *          i = {C, X}
 *          gate = C
 *          midres = C
 *          gate = X
 *          midres = C ⨂ X
 *          res = X ⨂ C ⨂ X
 * 
 */ 
math::Matrix momenter(std::vector<Gate> range, std::shared_ptr<math::Matrix> C, std::shared_ptr<math::Matrix> I) {
    math::Matrix res = {{1}};

    for (auto i : range) {
        math::Matrix midres = {{1}};
        if (i.containsControl()) {
            for (auto gate : i.getGate()) {
                if(gate == I || gate == C) {
                    midres = tensorProduct(midres, *gate);
                } else {
                    midres = tensorProduct(midres, *gate - math::In(log(gate -> getXSize()) / log(2)));
                };
            };

            midres = math::In(log(midres.getXSize()) / log(2)) + midres;

        } else {
            for (auto gate : i.getGate()) {
                midres = tensorProduct(midres, *gate);
            };
        };
        res = tensorProduct(res, midres);

    };

    return res;

};

class Circuit
{
    /*
     *  An object containing 
     *      qubits
     *      a schematic of gates
     *      a vector containing all the moments
     *      a matrix for the entire circuit
     * 
     */ 


  private:
    /* 
     *   vector of pointers all qubits in system
     *   eg:
     *   {&q0, &q1, &q3}
     */
    std::vector<math::Ket_ptr> qubits;


    /* 
     *   state of system qubits
     *   initialized to {1} so it doesn't
     *   affect result when multiplied by states
     */
    math::Ket state = {1};


    /*
     *   input vector of circuit
     *   eg:
     *   { 
     *     { {X, {&q0},     {CX, {&q1, &q2} } }, <- m0: first 'moment'
     *     { {H, {&q2}                      } }, <- m1: second 'moment'
     *     { {CZ,{&q0, &q2}                 } }  <- m2: third 'moment'
     *   }
     */
    schematic circuit;


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

    // initialize Circuit with qubits and circuit schematic
    Circuit(std::vector<math::Ket_ptr> qubs, schematic circ){
        qubits = qubs;
        circuit = circ;
        n = qubits.size();
        circuitInitializer();
    };

    // set the qubits of the circuit
    void setQubits(const std::vector<math::Ket_ptr> qub) {
        qubits = qub;
        n = qubits.size();
    };


    /*
     *   sets value of circuit
     *   initializes matrix of entire circuit
     *   populates moments
     */
    void setCircuit(const schematic circ) {
        circuit = circ;
        circuitInitializer();
    };


    // prints circuit as shown above
    void print() {
    };
    
    
    // creates moments and final circuit matrix
    void circuitInitializer() {
        // matrix of a time-slice of operations within the circuit
        // eg m0, m1, m2
        math::Matrix moment = {{1}};
        
        // control gate used later for all controls
        math::Matrix cc = (math::In(1) - gates::Z) / 2;

        // set cc to be controlled
        cc.setControlGate(true);

        // shared_ptr of cc, used where a pointer is required instead of actual gate
        std::shared_ptr<math::Matrix> C = std::make_shared<math::Matrix>(cc);

        // identity matrix and its shared_ptr
        math::Matrix ii = gates::I;
        std::shared_ptr<math::Matrix> I = std::make_shared<math::Matrix>(ii);

        math::Matrix null = {{1}};


        /*
         *   a vector showing which qubits are operated on
         *   a vector showing which gate is operated on which qubit
         *   eg:
         * 
         *   for m0: range = {{X}, {C, X}}
         *   for m1: range = {{I}, {I}, {H}}
         *   for m2: range = {{C, I, Z}}
         * 
         *   initialised to {I}s
         */
        std::vector<Gate> range(n, {I});


    



        /*
         *   i of format:
         *   { {Gate, {qubits}}, {Gate, {qubits}} }
         */
        for (auto i : circuit) {

            // reset range to all {I}
            range = std::vector<Gate>(n, {I});


            //reset moment
            moment = {{1}};

            /* 
             *  a vector of gates that are being controlled
             *  
             *  eg:
             *  for CX, X would be added to buffers 
             *  for CCY, Y would be added to buffers
             */
            std::vector<math::Matrix> buffers;
            
            /* 
             *  j of format:
             *  {Gate, {qubits}}
             */
            for (auto j : i) {

                // index of first qubit worked in j
                int minQubit = n - 1;

                // index of last qubit worked in j
                int maxQubit = 0;

                // find minQubit and maxQubit
                for (auto k : j.second) {
                    if (objectFinder(qubits, k) < minQubit) {
                        minQubit = objectFinder(qubits, k);
                    };
                    if (objectFinder(qubits, k) > maxQubit) {
                        maxQubit = objectFinder(qubits, k);
                    };
                };

                /*
                 *  A Gate containing the 'sub-gates' in j
                 *  to be inserted to range later on
                 */
                Gate midrange(maxQubit - minQubit + 1);

                // a copy of qubits containing the qubits acted on in midrange
                std::vector<math::Ket_ptr> midrangeQubitsCopy(qubits.begin() + minQubit, qubits.begin() + maxQubit + 1);

                /*
                 *  if gate operates on a different number
                 *  of qubits than specified
                 */
                if (j.first.getXSize() != std::pow(2, j.second.size())) {
                    throw std::runtime_error("Invalid number of qubits to apply gate to");
                };

                /*  
                 *  if vector of qubits is identical in order
                 *  and contents to entire system qubits
                 */
                if (j.second == qubits) {
                    // add gate to moments
                    // 'add' gate to finalCircuit
                    moments.push_back(j.first);
                    finalCircuit = j.first * finalCircuit;
                } else {

                    /*
                     *  how many controls on the gate
                     *  eg CNOT : 1; CCNOT : 2
                     */ 
                    int controlCount = 0;

                    /*
                     *  eventually becomes the gate being controlled
                     *  eg: CNOT or CCNOT: NOT; CSWAP : SWAP
                     */
                    math::Matrix buffer = j.first;

                    // populates buffer and counts up controlCount
                    while (buffer.isControlled()) {
                        buffer = buffer.getGateControlled();
                        controlCount++;
                    };


                    // adds buffer gate to buffers
                    buffers.push_back(buffer);

                    // shows which qubit has been deleted from range
                    std::vector<int> deletes(n, 0);

                    /*
                     *  populated midrange with
                     *      C for control qubits
                     *      shared_ptr(gate) for other gates
                     *  removes {I}s at index of every gate/C added to midrange
                     * 
                     */                    
                    for (int q = 0; q < j.second.size(); q++) {

                        // index of j.second[q] qubit in qubits
                        int index = objectFinder(qubits, j.second[q]);

                        // index of j.second[q] qubit in midrangeQubitsCopy
                        int midIndex = objectFinder(midrangeQubitsCopy, j.second[q]);

                        // empty j.second[q] qubit reference from midrangeQubitsCopy
                        midrangeQubitsCopy[midIndex] = 0;
                        

                        if (q < controlCount) {
                            // add control gate
                            midrange.setGate(midIndex, C);
                        } else {
                            // add target gate
                            midrange.setGate(midIndex, std::make_shared<math::Matrix>(buffers.back()));
                            buffers.back().setData({{1}});
                        };

                        // counts how many qubits up to index have been deleted from range
                        int deletedTillNow = std::count(deletes.begin(), deletes.begin() + index, 1);

                        // remove {I} at j.second[q] index 
                        range.erase(range.begin() + index - deletedTillNow);

                        // sets index of qubit as '1' in deletes
                        deletes[index] = 1;


                    };

                    /*
                     *  iterates through midrangeQubitsCopy
                     *  and adds I to remaining qubits that haven't been
                     *  controlled or targetted
                     * 
                     */ 
                    for (auto q : midrangeQubitsCopy) {
                        if (q != 0) {
                            
                            // index of j.second[q] qubit in qubits
                            int index = objectFinder(qubits, q);
                            
                            // index of j.second[q] qubit in midrangeQubitsCopy
                            int midIndex = objectFinder(midrangeQubitsCopy, q);
                            
                            // add I to midrange
                            midrange.setGate(midIndex, I);

                            // counts how many qubits up to index have been deleted from range
                            int deletedTillNow = std::count(deletes.begin(), deletes.begin() + index, 1);

                            // remove {I} at j.second[q] index
                            range.erase(range.begin() + index - deletedTillNow);
                            
                            // sets index of qubit as '1' in deletes
                            deletes[index] = 1;
                        };
                    };

                    // insert midrange into range at index: minQubit's 
                    range.insert(range.begin() + minQubit, midrange);

                }
            };

            // creates moment from the created range
            moment = momenter(range, C, I);

            // append moment to moments
            moments.push_back(moment);

            // 'add' moment to finalCircuit
            finalCircuit = moment * finalCircuit;

        };
    };
    
    
    // returns the index of a qubit in 'qubits' vector
    int objectFinder(std::vector<math::Ket_ptr> vec, math::Ket_ptr q){
        std::vector<math::Ket_ptr>::iterator i = vec.begin();
        i = find (vec.begin(), vec.end(), q);
        int b = distance (vec.begin (), i);
        return b;
    };
    
    // checks whether qubits input are adjacent
    bool adjacent(std::vector<math::Ket_ptr> qub){
        for (int i = 0; i < qub.size() - 1; i++) {
            // if the distance between qub[i] and qub[i+1] isn't 1 they are not adjacent
            if (std::abs(objectFinder(qubits, qub[i]) - objectFinder(qubits, qub[i+1])) != 1) {
                return false;
            };
        };
        return true;
    };


    std::vector<math::Ket_ptr> getQubits() const {
        return qubits;
    };


    std::vector<std::vector<std::pair<math::Matrix, std::vector<math::Ket_ptr>>>> getCircuit() const {
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