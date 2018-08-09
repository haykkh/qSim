#ifndef CLASSES_MATH_H
#define CLASSES_MATH_H

namespace qsim {
    namespace math {

        extern const std::complex<double> I(0,1);
        extern const double pi = std::atan(1) * 4;

        template <typename T> const char* sgn(T val) {
            return (val > 0) ? "" : "-";
        };

        class Matrix {
            public:
                std::vector<std::vector <std::complex <double> > > data;
                std::vector<std::vector <std::complex <double> > >::size_type ySize;
                std::vector<std::complex <double> >::size_type xSize;

                Matrix() {

                };

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

                Matrix adjoint() {
                    Matrix res(xSize, ySize);

                    for (int i = 0; i < ySize; i++){
                        for (int j = 0; j < xSize; j++) {
                            res.data[j][i] = std::conj(data[i][j]);
                        };
                    };

                    return res;
                };

                Matrix operator*=(Matrix const &mat) {
                    Matrix res(xSize, ySize);
                    std::complex<double> midresult = 0;
                    if (xSize != mat.ySize) {
                        throw std::runtime_error("You're trying to multiply Matrices of incompatible sizes!");
                    } else {
                        for (int i = 0; i < ySize; i++)
                        {
                            for (int j = 0; j < mat.xSize; j++)
                            {
                                for (int k = 0; k < mat.ySize; k++) {
                                    midresult += (data[i][k] * mat.data[k][j]);
                                };
                                res.data[i][j] = midresult;
                                midresult = 0;
                            };
                        };
                    };
                    *this = res;
                    return *this;
                };
        };

        Matrix operator*(Matrix &mat1, Matrix &mat2) {
            return mat1 *= mat2;
        };

        // 2 matrix tensor product
        // test this pls
        Matrix tensorProduct (Matrix mat1, Matrix mat2) {
            Matrix res(mat1.xSize * mat2.xSize, mat1.ySize * mat2.ySize);

            for (int y1 = 0; y1 < mat1.ySize; y1++) {
                for (int x1 = 0; x1 < mat1.xSize; x1++) {
                    for (int y2 = 0; y2 < mat2.ySize; y2++) {
                        for (int x2 = 0; x2 < mat2.xSize; x2++) {
                            res.data[mat2.ySize * y1 + y2][mat2.xSize * x1 + x2] = mat1.data[y1][x1] * mat2.data[y2][x2];
                        };
                    };
                };
            };
            return res;
        }

        class Ket
        {
          public:
            std::vector<std::complex<double>> data;
            std::vector<std::complex<double>>::size_type size;

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
                if (size != obj.data.size())
                {
                    throw std::runtime_error("You're trying to add Kets of different sizes!");
                };
                for (unsigned int i = 0; i < size; i++)
                {
                    res.data[i] = data[i] + obj.data[i];
                };
                return res;
            };

            // minusing 2 Kets
            Ket operator-(Ket const &obj) const
            {
                Ket res(size);

                if (size != obj.data.size())
                {
                    throw std::runtime_error("You're trying to add Kets of different sizes!");
                };
                for (unsigned int i = 0; i < size; i++)
                {
                    res.data[i] = data[i] - obj.data[i];
                };
                return res;
            };

            // multiplying two kets
            Ket operator*(Ket const &obj) const
            {
                Ket res(size * obj.size);

                for (unsigned int i = 0; i < size; i++)
                {
                    for (unsigned int j = 0; j < obj.size; j++)
                    {
                        res.data[i * obj.size + j] = data[i] * obj.data[j];
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
                    res.data[i] = data[i] / numerator;
                };
                return res;
            };

            // multiplying a Ket by a number
            Ket operator*(std::complex<double> multiplier) const
            {
                Ket res(size);

                for (unsigned int i = 0; i < size; i++)
                {
                    res.data[i] = data[i] * multiplier;
                };
                return res;
            };

            // assign* a Ket with another
            Ket operator*=(Ket const &obj2) {
                *this = *this + obj2;
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

                for (int gY = 0; gY < mat.ySize; gY++)
                {
                    for (int qS = 0; qS < size; qS++)
                    {
                        midresult += (mat.data[gY][qS] * data[qS]);
                    };
                    res.data[gY] = midresult;
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

    };
};

#endif