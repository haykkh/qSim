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
        math::Matrix finalCircuit;

    public:
        Circuit() {};

        Circuit(std::vector<math::Ket*> qubs, std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> circ){
            qubits = qubs;
            circuit = circ;
            n = qubits.size();
        };

        void setQubits(const std::vector<math::Ket*> qub) {
            qubits = qub;
        };

        void setCircuit(const std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> circ) {
            circuit = circ;
        };

        std::vector<math::Ket*> getQubits() const {
            return qubits;
        };

        std::vector<std::pair<math::Matrix, std::vector<math::Ket*>>> getCircuit() const {
            return circuit;
        };

}; // end class Circuit

}; // namespace circuit
}; // namespace qsim

#endif