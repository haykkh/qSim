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
            std::cout << "nono" << std::endl;

            circuitInitializer();
        };

        void circuitInitializer() {
            std::vector<math::Matrix> matrices;
            math::Matrix multiplyer = {{1}};
            std::vector<bool> range;

            std::cout << "test?" << std::endl;
            for (auto i : circuit) {
                range = std::vector<bool>(qubits.size());
                multiplyer = {{1}};
                std::cout << "Gate:" << std::endl;
                i.first.print();

                if (i.first.getXSize() != std::pow(2, i.second.size())) {
                    throw std::runtime_error("Invalid number of qubits to apply gate to");
                };

                if (i.second == qubits) {
                    finalCircuit *= i.first;
                } else {
                    std::cout << "qubits:" << std::endl;
                    for (auto j : i.second) {
                        j->print();
                        range[objectFinder(j)] = true;
                    };
                };
                std::cout << "before matrix for loop\nrange:\n";
                for (auto i : range) {
                    std::cout << i << std::endl;
                }
                for (int m = 0; m < range.size(); m++) {
                    if (range[m] == 1) {
                        std::cout << "yes range\n";
                        multiplyer = tensorProduct(multiplyer, i.first);
                        multiplyer.print();
                    } else {
                        std::cout << "no range\n";
                        multiplyer = tensorProduct(multiplyer, gates::I);
                        multiplyer.print();
                    };
                };

                std::cout << "after matrix for loop\n";


                multiplyer.print();
                finalCircuit = multiplyer * finalCircuit;

                std::cout << "qaqa" << std::endl;

            };

            finalCircuit.print();




        };

        int objectFinder(math::Ket *qub)
        {
            std::vector<math::Ket*>::iterator i = qubits.begin();
            i = find (qubits.begin(), qubits.end(), qub);
            int b = distance (qubits.begin (), i);
            return b;
        }

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