#include "rational.h"
#include <iostream>
#include <sstream>

using namespace std;


// Your implementation of the Rational class must provide appropriate
// member and non-member functions such that the following program
// compiles and produces the correct output.
int main() {
    cout << "Constructor and insertion and extraction operators:" << endl;
    Rational r1;
    cout << r1 << endl;
    Rational r2(4, -20);
    cout << r2 << endl;
    Rational r3, r4, r5;
    int x = 2;
    std::stringstream ss("18 /-10 -14 / -6 2/4");
    ss >> r3 >> r4 >> r5;
    // Should yield 3 Rationals: r3=-9/5, r4=7/3, and r5=1/2
    cout << r3 << " " << r4 << " " << r5 << endl;

    cout << "Addition checks: " << endl;
    cout << (r2 + r3) << endl;
    cout << (x + r3) << endl;
    cout << (r3 + x) << endl;
    cout << "Multiplication checks: " << endl;
    cout << (r3 * r4) << endl;
    cout << (6 * r4) << endl;
    cout << (r4 * 6) << endl;
    
    cout << "Exponentiation checks: " << endl;
    cout << (r5 ^ 3) << endl;
    cout << (r5 ^ -2) << endl;
    cout << (r3 ^ 0) << endl;
    return 0;
}
