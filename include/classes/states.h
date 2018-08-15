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