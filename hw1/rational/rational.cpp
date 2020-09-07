#include "rational.h"
#include <stdexcept>
// Libraries may be included as necessary

using namespace std;


Rational::Rational() : n(0), d(1) {}

Rational::Rational(int n, int d) {
    // Since the denominator cannot be zero an exception is thrown
    if (d == 0) {
        throw std::invalid_argument("division by zero");
    }

    // TODO: continue your implementation below.
    // You should likely set the member variables ad then call this->reduce()
    // and this->normalize().
    this->n = n;
    this->d = d;
    this->reduce();
    this->normalize();
}

void Rational::normalize() {
    // In C++ you don't always have to use this-> to denote a member variable.
    // If you omit it, the compiler will infer that n and d are indeed members
    // of Rational. There are two reasons you will see or use this->:
    //
    // 1. If you have a local variable that has the same name as a member
    //    variable, you need to use this-> to differentiate the two. If you
    //    created `int n` on this next line, the compiler would decide that
    //    any consequent uses of that variable refer to the local n, not our
    //    member variable. To specifically access the member n in this
    //    scenario, we'd use this->n.
    //
    // 2. Style. Some people (like me, Noah, the guy writing this) prefer to
    //    to use this-> to make it clear what variables are members when
    //    reading through the code. Others use a prefix (m_, i.e. m_member) or
    //    a suffix (_, i.e. member_) to denote it. In assignments where you
    //    write your own classes, this will be up to you. For now, do as you
    //    wish, but don't forget readability :)
    //
    // And feel free to delete this huge comment.
    if (n == 0 && d != 1) {
        d = 1;
    }
}

Rational Rational::operator+(const Rational& rhs) const {
    // TODO
    Rational new_fraction = Rational();
    new_fraction.n = this->n * rhs.d + this->d * rhs.n;
    new_fraction.d = this->d * rhs.d;
    new_fraction.reduce();
    new_fraction.normalize();
    return new_fraction;
}
Rational Rational::operator+(const int rhs) const{
    Rational new_fraction = Rational();
    new_fraction.n = this->n + rhs * this->d;
    new_fraction.d = this->d;
    new_fraction.reduce();
    new_fraction.normalize();
    return new_fraction;
}

Rational& Rational::operator+=(const Rational& rhs) {
    // TODO
    Rational new_fraction = Rational();
    new_fraction.n = this->n * rhs.d + this->d * rhs.n;
    new_fraction.d = this->d * rhs.d;
    new_fraction.reduce();
    new_fraction.normalize();
    this->n = new_fraction.n;
    this->d = new_fraction.d;
    return *(this);
}
Rational& Rational::operator+=(const int rhs){
    Rational new_fraction = Rational();
    new_fraction.n = this->n + rhs * this->d;
    new_fraction.d = this->d;
    new_fraction.reduce();
    new_fraction.normalize();
    this->n = new_fraction.n;
    this->d = new_fraction.d;
    return *(this);
}
Rational& Rational::operator*=(const Rational& rhs) {
    // TODO
    Rational new_fraction = Rational();
    new_fraction.n = rhs.n * this->n;
    new_fraction.d = rhs.d * this->d;
    new_fraction.reduce();
    new_fraction.normalize();
    this->n = new_fraction.n;
    this->d = new_fraction.d;
    return *(this);
}
Rational& Rational::operator*=(const int rhs){
    this->n *= rhs;
    this->normalize();
    this->reduce();
    return *(this);
}
Rational Rational::operator^(const int rhs) const {
    Rational new_fraction = Rational();
    
    new_fraction.n = 1;
    new_fraction.d = 1;
    if(rhs == 0){
        return new_fraction;
    }
    
    else if(rhs > 0){
        for(int i=0; i < rhs; i++){
            new_fraction.n = new_fraction.n * this->n;
            new_fraction.d = new_fraction.d * this->d;
        }
    }
    else{
        for(int i=0; i < (-1 * rhs); i++){
            new_fraction.n = new_fraction.n * this->d;
            new_fraction.d = new_fraction.d * this->n;
        }
    }
    new_fraction.normalize();
    new_fraction.reduce();
    return new_fraction;
}
Rational Rational::operator*(int rhs) const {
    // TODO
    Rational new_fraction = Rational();
    new_fraction.n = rhs * this->n;
    new_fraction.d = this->d;
    new_fraction.reduce();
    new_fraction.normalize();
    return new_fraction;
}
Rational Rational::operator*(const Rational& rhs) const{
    Rational new_fraction = Rational();
    new_fraction.n = rhs.n * this->n;
    new_fraction.d = rhs.d * this->d;
    new_fraction.reduce();
    new_fraction.normalize();
    return new_fraction;
}
std::ostream& operator<<(std::ostream& out, const Rational& r){
    out << r.n << "/" << r.d;
    return out;
}

std::istream& operator>>(std::istream& in, Rational& r){
    int numerator;
    int denominator;
    char slash = '/';
    if(in >> numerator >> slash >> denominator){
        r.n = numerator;
        r.d = denominator;
        r.normalize();
        r.reduce();
    }
    else{
        r.n = 0;
        r.d = 1;
    }
    return in;

}
// This operator isn't prefixed by Rational:: because it's not actually a
// member of Rational. It just tells the compiler what to do when it sees
// multiplication between an int on the left and a Rational on the right. Our
// friend declaration simply enabled us to access private members on the const
// Rational& rhs in the function body.
//
// Note that we could implement any of the other operators above this same way
// using the corresponding global operator and passing a const Rational& lhs as
// the first argument, it's just a matter of convenience.
Rational operator*(int lhs, const Rational& rhs) {
    // TODO
    Rational new_fraction = Rational();
    new_fraction.n = rhs.n * lhs;
    new_fraction.d = rhs.d;
    new_fraction.reduce();
    new_fraction.normalize();
    return new_fraction;
    
}

Rational operator+(int lhs, const Rational& rhs){
    Rational new_fraction = Rational();
    new_fraction.n = rhs.n + (lhs * rhs.d);
    new_fraction.d = rhs.d;
    new_fraction.reduce();
    new_fraction.normalize();
    return new_fraction;
}

bool Rational::operator==(const Rational& other) const {
    // TODO
    double left;
    double right;
    left = (double)this->n / (double)this->d;
    right = (double)other.n / (double)other.d;
    return left == right;
}
bool Rational::operator!=(const Rational& other) const {

    double left;
    double right;
    left = (double)this->n / (double)this->d;
    right = (double)other.n / (double)other.d;
    return left != right;
}

bool Rational::operator<(const Rational& other) const {
    // TODO
    double left;
    double right;
    left = (double)this->n / (double)this->d;
    right = (double)other.n / (double)other.d;
    return(left < right);
}

// TODO: implement the rest of your prototyped methods
void Rational::reduce(){
    bool negative = false;
    if(n == d && n != 1){
        n = 1;
        d = 1;
        return;
    }
    if(n < 0 && d < 0){
        n = -1 * n;
        d = -1 * d;
    }
    if(n < 0 || d < 0){
        negative = true;
        if(d < 0){
            d = -1 * d;
            n = -1 * n;
        }
    }

    int i;
    if(n < d){
        i = d;
    }
    else{
        i = n;
    }
    for(; i > 1; i--){
        if(n % i == 0 && d % i == 0){
            n = n / i;
            d = d / i;
            break;
        }
    }
    
}