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

#ifndef CLASSES_MATH_H
#define CLASSES_MATH_H

namespace qsim {
    namespace math {

        extern const std::complex<double> I(0,1);
        extern const double pi = std::atan(1) * 4;

        std::complex<double> omega(int n) {
            return std::exp((2 * pi * I) / std::pow(2, n));
        };

        template <typename T> const char* sgn(T val) {
            return (val > 0) ? "" : "-";
        };

        class Matrix {
            private:
                std::vector<std::vector<std::complex<double>>> data;
                std::vector<std::vector<std::complex<double>>>::size_type ySize;
                std::vector<std::complex<double>>::size_type xSize;
                bool control = false;
                bool controlledGate = false;
                const Matrix* gateControlled;
                
            public:


                Matrix() {};


                Matrix(std::initializer_list<std::vector <std::complex <double> > > d) : data(d) {
                    ySize = data.size();
                    xSize = data[0].size();
                    
                };

                Matrix(unsigned int n, unsigned int m) {
                    setSize(n,m);
                };
                Matrix(unsigned int n) {
                    setSize(n,n);
                };

                void setSize(unsigned int n, unsigned int m) {
                    xSize = n;
                    ySize = m;
                    data.resize(ySize, std::vector<std::complex <double> >(xSize));
                };
                
                void setValue(unsigned int y, unsigned int x, const std::complex<double> value) {
                    data[y][x] = value;
                };

                void setControlled(bool val) {
                    controlledGate = val;
                };

                void setData(std::vector<std::vector<std::complex<double>>> d) {
                    data = d;
                };

                void setGateControlled(const Matrix* mat)
                {
                    gateControlled = mat;
                };

                void setControlGate(bool val) {
                    control = val;
                };

                bool isControlGate() {
                    return control;
                };

                bool isControlled()
                {
                    return controlledGate;
                };

                std::vector<std::vector<std::complex<double>>>::size_type getYSize() const {
                    return ySize;
                };

                std::vector<std::complex<double>>::size_type getXSize() const {
                    return xSize;
                };
                
                std::vector<std::vector<std::complex<double>>> getData() const {
                    return data;
                };

                Matrix getGateControlled() const {
                    return *gateControlled;
                };

                std::complex<double> getValue(unsigned int y, unsigned int x) const
                {
                    return data[y][x];
                };

                Matrix controlled() const
                {
                    Matrix res(xSize * 2, ySize * 2);
                    for (int j = 0; j < ySize; j++)
                    {
                        res.setValue(j, j, 1);

                        for (int i = 0; i < xSize; i++)
                        {
                            res.setValue(ySize + j, xSize + i, getValue(j, i));
                        };
                    };
                    res.setGateControlled(this);
                    res.setControlled(true);
                    return res;
                };

                void print() {
                    for (int j = 0; j < ySize; j++)
                    {
                        std::cout.precision(3);
                        std::cout << "|";

                        for (int i = 0; i < xSize; i++)
                        {
                            if (std::imag(data[j][i]) == 0)
                            {
                            
                                std::cout << " " << std::real(data[j][i]) << " ";
                            }
                            else if (real(data[j][i]) == 0)
                            {
                                if (std::abs(std::imag(data[j][i])) == 1.) {
                                    std::cout << " " << sgn(std::imag(data[j][i])) << "i ";
                                } else {
                                    std::cout << " " << std::imag(data[j][i]) << "i ";
                                };
                            }
                            else
                            {
                                if (std::abs(std::imag(data[j][i])) == 1.)
                                {
                                    std::cout << " " << std::real(data[j][i]) << " + "
                                              << " " << sgn(std::imag(data[j][i])) << "i ";
                                } else {
                                    std::cout << " " << std::real(data[j][i]) << " + " << std::imag(data[j][i]) << "i ";
                                };
                            };
                        };

                        std::cout << "|\n";
                    };

                    std::cout << std::endl;
                };

                void noZeroPrint() {
                    for (int j = 0; j < ySize; j++)
                    {
                        std::cout.precision(3);
                        std::cout << "|";

                        for (int i = 0; i < xSize; i++)
                        {
                            if (data[j][i] == 0.) {
                                std::cout << "   ";
                            } else {
                                if (std::imag(data[j][i]) == 0)
                                {
                                
                                    std::cout << " " << std::real(data[j][i]) << " ";
                                }
                                else if (real(data[j][i]) == 0)
                                {
                                    if (std::abs(std::imag(data[j][i])) == 1.) {
                                        std::cout << " " << sgn(std::imag(data[j][i])) << "i ";
                                    } else {
                                        std::cout << " " << std::imag(data[j][i]) << "i ";
                                    };
                                }
                                else
                                {
                                    if (std::abs(std::imag(data[j][i])) == 1.)
                                    {
                                        std::cout << " " << std::real(data[j][i]) << " + "
                                                  << " " << sgn(std::imag(data[j][i])) << "i ";
                                    } else {
                                        std::cout << " " << std::real(data[j][i]) << " + " << std::imag(data[j][i]) << "i ";
                                    };
                                };
                            };
                        };

                        std::cout << "|\n";
                    };

                    std::cout << std::endl;
                };

                void arrayPrint() {
                    for (int j = 0; j < ySize; j++)
                    {
                        std::cout.precision(3);
                        std::cout << "|";

                        for (int i = 0; i < xSize; i++)
                        {
                            if (data[j][i] == 0.) {
                                std::cout << "   ";
                            } else {
                                std::cout << " █ ";
                            };
                        };

                        std::cout << "|\n";
                    };

                    std::cout << std::endl;
                };

                Matrix adjoint() {
                    Matrix res(xSize, ySize);

                    for (int i = 0; i < ySize; i++){
                        for (int j = 0; j < xSize; j++) {
                            res.setValue(j, i, std::conj(data[i][j]));
                        };
                    };

                    return res;
                };

                Matrix operator-=(Matrix const &mat) {
                    Matrix res(xSize, ySize);
                    if (xSize != mat.getXSize() || ySize != mat.getYSize()) {
                        throw std::runtime_error("You're trying to minus matrices of incompatible sizes!");
                    } else {
                        for (int j = 0; j < ySize; j++) {
                            for (int i = 0; i < xSize; i++) {
                                res.setValue(j, i, data[j][i] - mat.getValue(j, i));
                            };
                        };
                    };
                    *this = res;
                    return *this;
                };

                Matrix operator+=(Matrix const &mat) {
                    Matrix res(xSize, ySize);
                    if (xSize != mat.getXSize() || ySize != mat.getYSize()) {
                        throw std::runtime_error("You're trying to add matrices of incompatible sizes!");
                    } else {
                        for (int j = 0; j < ySize; j++) {
                            for (int i = 0; i < xSize; i++) {
                                res.setValue(j, i, data[j][i] + mat.getValue(j, i));
                            };
                        };
                    };
                    *this = res;
                    return *this;
                };


                Matrix operator*=(Matrix const &mat) {
                    Matrix res(xSize, ySize);
                    std::complex<double> midresult = 0;
                    if (xSize != mat.getYSize()) {
                        if (xSize == 1 && ySize == 1) {
                            *this = mat;
                            return *this;
                        } else if (mat.getXSize() == 1 && mat.getYSize() == 1) {
                            return *this;
                        };
                        throw std::runtime_error("You're trying to multiply Matrices of incompatible sizes!");
                    } else {
                        for (int j = 0; j < ySize; j++)
                        {
                            for (int i = 0; i < mat.getXSize(); i++)
                            {
                                for (int k = 0; k < mat.getYSize(); k++) {
                                    midresult += (data[i][k] * mat.getValue(k,j));
                                };
                                res.setValue(i, j, midresult);
                                midresult = 0;
                            };
                        };
                    };
                    *this = res;
                    return *this;
                };

                Matrix operator*=(std::complex<double> multiplier) {
                    Matrix res(xSize, ySize);
                    for (int j = 0; j < ySize; j++) {
                        for (int i = 0; i < xSize; i++) {
                            res.setValue(j, i, data[j][i] * multiplier);
                        };
                    };
                    *this = res;
                    return *this;
                };

                Matrix operator/=(std::complex<double> divider) {
                    Matrix res(xSize, ySize);
                    for (int j = 0; j < ySize; j++) {
                        for (int i = 0; i < xSize; i++) {
                            res.setValue(j, i, data[j][i] / divider);
                        };
                    };
                    *this = res;
                    return *this;
                };
        };

        Matrix operator*(Matrix mat1, Matrix mat2) {
            return mat1 *= mat2;
        };

        Matrix operator-(Matrix mat1, Matrix mat2) {
            return mat1 -= mat2;
        };

        Matrix operator+(Matrix mat1, Matrix mat2) {
            return mat1 += mat2;
        };

        Matrix operator*(Matrix mat1, std::complex<double> multiplier) {
            return mat1 *= multiplier;
        };

        Matrix operator/(Matrix mat1, std::complex<double> divider){
            return mat1 /= divider;
        };

        // 2 matrix tensor product
        Matrix tensorProduct (Matrix mat1, Matrix mat2) {
            Matrix res(mat1.getXSize() * mat2.getXSize(), mat1.getYSize() * mat2.getYSize());

            for (int y1 = 0; y1 < mat1.getYSize(); y1++) {
                for (int x1 = 0; x1 < mat1.getXSize(); x1++) {
                    for (int y2 = 0; y2 < mat2.getYSize(); y2++) {
                        for (int x2 = 0; x2 < mat2.getXSize(); x2++) {
                            res.setValue(mat2.getYSize() * y1 + y2, mat2.getXSize() * x1 + x2, mat1.getValue(y1, x1) * mat2.getValue(y2, x2));
                        };
                    };
                };
            };
            return res;
        }

        Matrix multiplyerApplicator(Matrix multiplyer, Matrix gate, Matrix identity, std::vector<char> range)
        {
            Matrix res = multiplyer;
            for (int m = 0; m < range.size(); m++)
            {
                switch(range[m]) {
                    case 'I': {
                        res = tensorProduct(res, identity);
                    };

                    case 'T': {
                        res = tensorProduct(res ,gate);
                    };
                };
            };
            return res;
        };

        Matrix In(unsigned int n) {
            Matrix res(std::pow(2, n));

            for (unsigned int i = 0; i < std::pow(2,n); i++) {
                res.setValue(i, i, 1);
            };

            return res;
        };


        class Ket
        {
            private:
                std::vector<std::complex<double>> data;
                std::vector<std::complex<double>>::size_type size;

            public:
                Ket(){

                };

                Ket(std::initializer_list<std::complex<double>> d) : data(d)
                {
                    size = d.size();
                };

                Ket(unsigned int n)
                {
                    setSize(n);
                };

                void setSize(unsigned int n)
                {
                    size = n;
                    data.resize(n);
                };

                void setValue(unsigned int index, const std::complex<double> value) {
                    data[index] = value;
                }


                std::complex<double> getValue(unsigned int index) const {
                    return data[index];
                }

                std::vector<std::complex<double>> getData() const {
                    return data;
                }

                std::vector<std::complex<double>>::size_type getSize() const {
                    return size;
                };

                void print()
                {
                    std::cout << std::endl;

                    for (int j = 0; j < size; j++)
                    {
                        std::cout.precision(3);
                        if (imag(data[j]) == 0)
                        {

                            std::cout << "| " << real(data[j]) << " |\n";
                        }
                        else if (real(data[j]) == 0)
                        {
                            std::cout << "| " << imag(data[j]) << "i |\n";
                        }
                        else
                        {
                            std::cout << "| " << real(data[j]) << " + " << imag(data[j]) << "i |\n";
                        };
                    };

                    std::cout << std::endl;
                };

                /**************/
                /*            */
                /*  Operator  */
                /*  overload  */
                /*            */
                /**************/

                // adding 2 Kets
                Ket operator+(Ket const &obj) const
                {
                    Ket res(size);
                    if (size != obj.getSize())
                    {
                        throw std::runtime_error("You're trying to add Kets of different sizes!");
                    };
                    for (unsigned int i = 0; i < size; i++)
                    {
                        res.setValue(i, data[i] + obj.getValue(i));                    
                    };
                    return res;
                };

                // minusing 2 Kets
                Ket operator-(Ket const &obj) const
                {
                    Ket res(size);

                    if (size != obj.getSize())
                    {
                        throw std::runtime_error("You're trying to add Kets of different sizes!");
                    };
                    for (unsigned int i = 0; i < size; i++)
                    {
                        res.setValue(i, data[i] - obj.getValue(i));
                    };
                    return res;
                };

                // multiplying two kets
                Ket operator*(Ket const &obj) const
                {
                    Ket res(size * obj.getSize());

                    for (unsigned int i = 0; i < size; i++)
                    {
                        for (unsigned int j = 0; j < obj.getSize(); j++)
                        {
                            res.setValue(i * obj.getSize() + j, data[i] * obj.getValue(j));
                        };
                    };
                    return res;
                };

                // dividing a Ket by a number
                Ket operator/(std::complex<double> numerator) const
                {
                    Ket res(size);

                    for (unsigned int i = 0; i < size; i++)
                    {
                        res.setValue(i, data[i] / numerator);
                    };
                    return res;
                };

                // multiplying a Ket by a number
                Ket operator*(std::complex<double> multiplier) const
                {
                    Ket res(size);

                    for (unsigned int i = 0; i < size; i++)
                    {
                        res.setValue(i, data[i] * multiplier);
                    };
                    return res;
                };

                // assign* a Ket with another
                Ket operator*=(Ket const &obj2) {
                    *this = *this * obj2;
                    return *this;
                }

                // assign+ a Ket with another
                Ket operator+=(Ket const &obj2)
                {
                    *this = *this + obj2;
                    return *this;
                };

                // assign- a Ket with another
                Ket operator-=(Ket const &obj2)
                {
                    *this = *this - obj2;
                    return *this;
                };

                // assign* a Ket with a number
                Ket operator*=(std::complex<double> multiplier)
                {
                    *this = *this * multiplier;
                    return *this;
                };

                // assign/ a Ket with a number
                Ket operator/=(std::complex<double> numerator)
                {
                    *this = *this / numerator;
                    return *this;
                };

                // assign* apply a gate onto a Ket
                Ket operator*=(Matrix mat)
                {
                    Ket res(size);
                    std::complex<double> midresult = 0;

                    for (int gY = 0; gY < mat.getYSize(); gY++)
                    {
                        for (int qS = 0; qS < size; qS++)
                        {
                            midresult += (mat.getValue(gY,qS) * data[qS]);
                        };
                        res.setValue(gY, midresult);
                        midresult = 0;
                    };

                    *this = res;
                    return *this;
                };

        };



        // Apply a gate onto a Ket
        Ket operator*(Matrix mat, Ket ket)
        {
            return ket *= mat;
        };


    }; // end namespace math
}; // end namespace qsim

#endif