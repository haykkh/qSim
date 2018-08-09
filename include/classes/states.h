#ifndef CLASSES_STATES_H_
#define CLASSES_STATES_H_

namespace qsim {
    namespace states{

        // 1 qubit Pauli states
        extern const math::Ket x0 = { 1 / sqrt(2),  1 / sqrt(2)       };
        extern const math::Ket x1 = { 1 / sqrt(2), -1 / sqrt(2)       };
        extern const math::Ket y0 = { 1 / sqrt(2),  math::I / sqrt(2) };
        extern const math::Ket y1 = { 1 / sqrt(2), -math::I / sqrt(2) };
        extern const math::Ket z0 = {           1,                  0 };
        extern const math::Ket z1 = {           0,                  1 };

        // 2 qubit Pauli states
        extern const math::Ket z00 = {1, 0, 0, 0};
        extern const math::Ket z01 = {0, 1, 0, 0};
        extern const math::Ket z10 = {0, 0, 1, 0};
        extern const math::Ket z11 = {0, 0, 0, 1};

        // 2 qubit Bell states (EPR pairs)
        extern const math::Ket b00 = (z00 + z11) / sqrt(2);
        extern const math::Ket b01 = (z00 - z11) / sqrt(2);
        extern const math::Ket b10 = (z01 + z10) / sqrt(2);
        extern const math::Ket b11 = (z01 - z10) / sqrt(2);
    };
};

#endif