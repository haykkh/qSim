#include "../include/qSim.h"

using namespace std;
using namespace qsim;
using namespace math;

int main() {
    Ket k0 = states::z0;
    Ket k1 = states::z0;
    Ket k2 = states::z0;

    Ket* q0 = &k0;
    Ket* q1 = &k1;
    Ket* q2 = &k2;

    vector<Ket*> qubits = {q0, q1, q2};

    Matrix H = gates::H;

    circuit::Circuit hadamard;

    hadamard.setQubits(qubits);

    circuit::schematic scheme;

    circuit::momentScheme moment;

    for (auto i : qubits) {
        moment.push_back({H, {i}});
    };

    scheme = {moment};

    hadamard.setCircuit(scheme);

    Matrix fc = hadamard.getFinalCircuit();


    cout << "\nCircuit matrix:\n";
    fc.print();

    Ket state = k0 * k1 * k2;

    cout << "\nSystem starting state:\n";
    state.print();

    state *= fc;

    cout << "\nSystem state after circuit:\n";
    state.print();

    state.measure();

    cout << "\nSystem state after measurement:\n";
    state.print();

}