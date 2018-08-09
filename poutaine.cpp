#include <vector>
#include <complex>
#include <iostream>

using namespace std;

int main() {
    std::initializer_list<std::complex <double> > small = {0, 1};
    vector<std::complex <double> > balls(small);

    for (int i = 0; i < 2; i++) {
        cout << balls[i] << endl;
    };
    return 0;
}