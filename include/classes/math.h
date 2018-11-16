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

        // imaginary number
        extern const std::complex<double> I(0,1);
        
        // π
        extern const double pi = std::atan(1) * 4;

        // exp[2πi / 2^n]
        std::complex<double> omega(int n) {
            return std::exp((2 * pi * I) / std::pow(2, n));
        };

        /*
         *  Returns:
         *          ""  if val > 0
         *          "-" if val < 0
         */
        template <typename T> const char* sgn(T val) {
            return (val > 0) ? "" : "-";
        };

        class Matrix {
            /*
             *  Used as a representation for gates and circuits
             *  an n-qubit gate is a matrix of size 2^n x 2^n
             */ 


            private:

                // data of matrix 
                std::vector<std::vector<std::complex<double>>> data;
                
                // Number of row elements
                std::vector<std::vector<std::complex<double>>>::size_type ySize;
                
                // Number of column elements
                std::vector<std::complex<double>>::size_type xSize;
                
                // indicating whether this gate controls another qubit
                bool control = false;

                // indicating whether this gate is controlled by another qubit
                bool controlledGate = false;
                
                // typedef for a shared_ptr to a matrix 
                typedef std::shared_ptr<Matrix> Matrix_ptr;

                // pointer to the gate that is controlled by this gate
                Matrix_ptr gateControlled;
                
            public:


                Matrix() {};

                /*
                 *  Init matrix with:
                 *          data = d
                 *          ySize = number of rows in d
                 *          xSize = number of columns in d
                 */ 
                Matrix(std::initializer_list<std::vector <std::complex <double> > > d) : data(d) {
                    ySize = data.size();
                    xSize = data[0].size();
                    
                };

                // Init matrix of size m x n
                Matrix(unsigned int n, unsigned int m) {
                    setSize(n,m);
                };

                // Init square matrix of size n x n
                Matrix(unsigned int n) {
                    setSize(n,n);
                };

                // Set size of matrix to m x n
                void setSize(unsigned int n, unsigned int m) {
                    xSize = n;
                    ySize = m;
                    data.resize(ySize, std::vector<std::complex <double> >(xSize));
                };
                
                // Set value at (x,y) to value
                void setValue(unsigned int y, unsigned int x, const std::complex<double> value) {
                    data[y][x] = value;
                };

                // Set whether this gate is controlled by another qubit
                void setControlled(bool val) {
                    controlledGate = val;
                };

                // Set data = d and resize
                void setData(std::vector<std::vector<std::complex<double>>> d) {
                    data = d;
                    ySize = data.size();
                    xSize = data[0].size();
                };

                // Specify pointer of gate that is controlled by this gate
                void setGateControlled(const Matrix_ptr mat)
                {
                    gateControlled = mat;
                };

                // Set whether this gate controls another qubit
                void setControlGate(bool val) {
                    control = val;
                };

                // Returns whether this gate controls another qubit
                bool isControlGate() {
                    return control;
                };

                // Returns whether this gate is controlled by another qubit
                bool isControlled()
                {
                    return controlledGate;
                };

                // Returns number of rows of matrix
                std::vector<std::vector<std::complex<double>>>::size_type getYSize() const {
                    return ySize;
                };

                // Returns number of columns of matrix
                std::vector<std::complex<double>>::size_type getXSize() const {
                    return xSize;
                };
                
                // Returns a vector<vector>> list of data
                std::vector<std::vector<std::complex<double>>> getData() const {
                    return data;
                };

                // returns the pointer to the gate that is controlled by this gate
                Matrix getGateControlled() const {
                    return *gateControlled;
                };

                // get the value of this matrix at (x,y)
                std::complex<double> getValue(unsigned int y, unsigned int x) const
                {
                    return data[y][x];
                };

                // returns this gate controlled 
                Matrix controlled() const
                {
                    // init matrix twice the size of *this
                    Matrix res(xSize * 2, ySize * 2);

                    // make the top left quadrant an identity matrix
                    for (int j = 0; j < ySize; j++)
                    {
                        res.setValue(j, j, 1);

                        for (int i = 0; i < xSize; i++)
                        {
                            res.setValue(ySize + j, xSize + i, getValue(j, i));
                        };
                    };

                    // set the gate that is being controlled
                    res.setGateControlled(std::make_shared<Matrix>(*this));

                    // set this gate to be controlled
                    res.setControlled(true);

                    return res;
                };

                // prints the matrix
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

                // prints all non-zero elements
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

                // prints an box array (█ for all non-zero elements)
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

                // returns the adjoint of *this matrix
                Matrix adjoint() {
                    Matrix res(xSize, ySize);

                    for (int i = 0; i < ySize; i++){
                        for (int j = 0; j < xSize; j++) {
                            res.setValue(j, i, std::conj(data[i][j]));
                        };
                    };

                    return res;
                };

                // Subtract matrices
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

                // Add matrices
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

                // Multiply matrices
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

                // Multiply matrix by a number
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

                // Divice matrix by a number
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

        // Multiply matrices
        Matrix operator*(Matrix mat1, Matrix mat2) {
            return mat1 *= mat2;
        };

        // Subtract matrices
        Matrix operator-(Matrix mat1, Matrix mat2) {
            return mat1 -= mat2;
        };

        // Add matrices
        Matrix operator+(Matrix mat1, Matrix mat2) {
            return mat1 += mat2;
        };

        // Multiply matrix by number
        Matrix operator*(Matrix mat1, std::complex<double> multiplier) {
            return mat1 *= multiplier;
        };

        // Divice matrix by number
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

        // not in use
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

        // Returns identity matrix of size 2^n x 2^n
        Matrix In(unsigned int n) {
            Matrix res(std::pow(2, n));

            for (unsigned int i = 0; i < std::pow(2,n); i++) {
                res.setValue(i, i, 1);
            };

            return res;
        };


        class Ket
        {
            /*
             *  Ket vector (column vector in Dirac (bra-ket) notation)
             *  Used as a representation for qubits
             *  an n qubit system is a vector of size 2^n
             */ 

            private:
                // data of vector
                std::vector<std::complex<double>> data;

                // size of vector
                std::vector<std::complex<double>>::size_type size;

                // the state of a qubit in binary form (eg '1', '0', '101', '010011' etc)
                std::vector<int> state;

            public:
                Ket(){

                };

                /*
                 * Init ket with:
                 *          data = d
                 *          size = number of elements in d
                 */
                Ket(std::initializer_list<std::complex<double>> d) : data(d)
                {
                    size = d.size();
                };

                // Init ket of size n
                Ket(unsigned int n)
                {
                    setSize(n);
                };

                // Set size of ket to n
                void setSize(unsigned int n)
                {
                    size = n;
                    data.resize(n);
                };

                // Set value at index to value
                void setValue(unsigned int index, const std::complex<double> value) {
                    data[index] = value;
                }

                // add value as the last element of ket
                void push_back(std::complex<double> value) {
                    data.insert(data.end(), value);
                };

                //Populates state in binary form based on values in data 
                void initState() {
                    int index = distance(data.begin(), find(data.begin(), data.end(), 1.0)) + 1;
                    
                    int size = getSize();
                    state.clear();

                    while (size > 1) {
                        if (index > size / 2) {
                            index -= size / 2;
                            state.push_back(1);
                        } else {
                            state.push_back(0);
                        };

                        size /= 2;
                    };
                };

                // returns binary form of state
                std::vector<int> getState() {
                    initState();

                    return state;
                };

                // prints binary form of state (eg '1', '0', '101', '010011' etc) 
                void printState() {
                    std::cout << std::endl;
                    for (auto i : state) {
                        std::cout << i;
                    };
                    std::cout << std::endl;
                };

                // get value at index
                std::complex<double> getValue(unsigned int index) const {
                    return data[index];
                }

                // get entire vector
                std::vector<std::complex<double>> getData() const {
                    return data;
                }

                // get number of elements in vector
                std::vector<std::complex<double>>::size_type getSize() const {
                    return size;
                };


                // Simulates measuring the qubit 
                /*
                 *  p: vector of cumulative probabilities
                 *      eg for data = ( 0.5,    0, 0.5,   0,  0.5,    0, 0.5,   0)
                 *                p = (0.25, 0.25, 0.5, 0.5, 0.75, 0.75, 1.0, 1.0) 
                 * 
                 *  then generates a random number, rnd, in (0,1)
                 *  
                 *  then check where in p rnd falls and sets that to the var qub
                 *      eg for rnd = 0.37
                 *         it falls between the second and third element
                 *         => third element is 1
                 *         => qub = 2
                 *         => qubit is in state 00100000
                 * 
                 *         for rnd = 0.02
                 *         before 1st element
                 *         => 1st element is 1
                 *         => qub = 0
                 *         => qubit in state 10000000
                 * 
                 *  When it has figured out the state
                 *  it resets this qubit to all zero elements
                 *  then sets the value at the qub index to 1
                 * 
                 */ 
                void measure(){

                    std::vector<double> p; 
                    double summer;

                    for (auto q : data) {
                        summer += std::pow(std::abs(q), 2);
                        p.push_back(summer);
                    };

                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<> dis(0,1);
                    double rnd = dis(gen);

                    int qub = std::upper_bound(p.begin(), p.end(), rnd) - p.begin();

                    data = std::vector<std::complex<double>>(size);

                    setValue(qub, 1);

                }

                // prints qubit
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

        
        typedef std::shared_ptr<Ket> Ket_ptr;
        typedef std::shared_ptr<Matrix> Matrix_ptr;

    }; // end namespace math
}; // end namespace qsim

#endif