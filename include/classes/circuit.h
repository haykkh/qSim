#ifndef CLASSES_CIRCUIT_H
#define CLASSES_CIRCUIT_H

namespace qsim{
namespace circuit{

class Circuit
{
    private:
        std::vector<math::Ket*> qubits;
        math::Ket state = {1};
        std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> circuit;
        unsigned int n;
        math::Matrix finalCircuit = {{1}};
        std::vector<int> range;

    public:
        Circuit() {};

        Circuit(std::vector<math::Ket*> qubs, std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> circ){
            qubits = qubs;
            circuit = circ;
            n = qubits.size();
            range.resize(n);

            //circuitInitializer();
        };

        void setQubits(const std::vector<math::Ket*> qub) {
            qubits = qub;
            n = qubits.size();
        };

        void setCircuit(const std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> circ) {
            circuit = circ;
            circuitInitializer();
        };

        void circuitInitializer() {
            std::vector<math::Matrix> matrices;
            math::Matrix multiplyer = {{1}};
            std::vector<bool> range;
            int trueNumber;

            for (auto i : circuit) {
                range = std::vector<bool>(qubits.size());
                multiplyer = {{1}};

                if (i.first.getXSize() != std::pow(2, i.second.size())) {
                    throw std::runtime_error("Invalid number of qubits to apply gate to");
                };

                if (i.second == qubits) {
                    finalCircuit = i.first * finalCircuit;
                } else {
                    for (auto j : i.second) {
                        range[objectFinder(j)] = true;
                    };
                };

                if (i.first.getXSize() >= 4) {
                    if (i.first.isControlled()) {
                        if (adjacent(i.second)) {
                            int controlCount = 0;
                            math::Matrix buffer = i.first;
                            
                            while (buffer.isControlled()) {
                                buffer = buffer.getControlGate();
                                controlCount++;
                            };

                            int controlQubit = objectFinder(i.second[controlCount]);

                            for (int k = range.size() - 1; k >= controlQubit; k--) {
                                if (range[k] == 1)
                                {
                                    multiplyer = tensorProduct(buffer, multiplyer);
                                }
                                else
                                {
                                    multiplyer = tensorProduct(gates::I, multiplyer);
                                };
                            };

                            for (int k = 0; k < controlCount; k++) {
                                multiplyer = multiplyer.controlled();
                            };

                        } else {
                            std::cout << "make adjacent" << std::endl;
                        }
                    } else {
                        std::cout << "probably need to swap these" << std::endl;
                    }
                } else {
                    multiplyer = math::multiplyerApplicator(multiplyer, i.first, gates::I, range);
                };


                //std::cout << "Gate: " << std::endl;
                //i.first.print();
                //multiplyer.print();
                finalCircuit  = finalCircuit * multiplyer;
            };
        };

        int objectFinder(math::Ket *q)
        {
            std::vector<math::Ket*>::iterator i = qubits.begin();
            i = find (qubits.begin(), qubits.end(), q);
            int b = distance (qubits.begin (), i);
            return b;
        }

        bool adjacent(std::vector<math::Ket *> qub){
            for (int i = 0; i < qub.size() - 1; i++) {
                if (std::abs(objectFinder(qub[i]) - objectFinder(qub[i+1])) != 1) {
                    return false;
                };
            };
            return true;
        };

        std::vector<math::Ket*> getQubits() const {
            return qubits;
        };

        std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> getCircuit() const {
            return circuit;
        };

        math::Matrix getFinalCircuit() {
            return finalCircuit;
        }

}; // end class Circuit

}; // namespace circuit
}; // namespace qsim

#endif