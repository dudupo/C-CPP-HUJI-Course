#ifndef   headers_h
#define   headers_h

#include  "headers.h"

#endif


//---------------------

const long DEFAULTCHART = 2;
const long DEFAULTDEGREE = 1;

//---------------------

GField::GField() : GField(DEFAULTCHART, DEFAULTDEGREE) {

}

GField::GField(long chart) {
    this->chart = chart;
    this->degree = DEFAULTDEGREE;
}

GField::GField(long chart, long degree) {
    this->chart = chart;
    this->degree = degree;
}

GField::GField(const GField &source) : GField(source.getChart(), source.getDegree()) {

}

long GField::getChart() const {
    return this->chart;
}

long GField::getDegree() const {
    return this->degree;
}

long GField::getOrder() const {
    return std::pow(this->chart, this->degree);
}

bool GField::isPrime(long number) {
    int lastpow = 0;
    for (int i = 0; i <= std::sqrt(number); i++)
        if ((lastpow = lastpow + 2 * i + 1) == number)
            return false;
    return true;
}

GFNumber *GField::gcd(GFNumber *a, GFNumber *b) {
    return b->getNumber() == 0 ? new GFNumber(*a) : gcd(b, *a % *b);
}

GFNumber *GField::createNumber(long number) {
    return new GFNumber(number, this);
}

void GField::operator=(GField const &assignmented) {
    this->chart = assignmented.getChart();
    this->degree = assignmented.getDegree();
}

bool GField::operator==(GField const &other) {
    return this->getChart() == other.getChart() && this->getOrder() == other.getOrder();
}

bool GField::operator!=(GField const &other) {
    return this->getChart() != other.getChart() || this->getOrder() != other.getOrder();
}

std::ostream &operator<<(std::ostream &os, GField &field) {
    os << "GF(" << field.getChart() << "**" << field.getDegree() << ")";
    return os;
}

std::istream &operator>>(std::istream &is, GField &field) {
    int chart, degree;
    is >> chart >> degree;
    field = GField(chart, degree);
    return is;
}

int main() {
    // GField gf = GField (40 , 5);
    // GFNumber * miki = gf.createNumber(18);
    // GFNumber * kiki = gf.createNumber(12);
    // std::cout << miki->getNumber() << '\n';
    // std::cout << (*miki + *kiki)->getNumber() << '\n';
    // std::cout << (*miki * *kiki)->getNumber() << '\n';
    //
    // GField * gf2 = new GField (3 , 5);
    // GFNumber * miki2 = gf2->createNumber(2);
    //
    //
    // if (*miki2 < *miki ) {
    //   std::cout << " message " << '\n';
    // }
    //
    // if ( GField::isPrime( 9 ) )
    //   std::cout << "/* hi */" << '\n';
    // //((new GField(3 , 2))->createNumber(2) == (new GField(4 , 2))->createNumber(2))+"" <<'\n';
    //
    // std::cout << gf.gcd(miki, kiki)->getNumber() << '\n';
    //
    // std::cout << gf << '\n';
    // std::cin >> gf;
    // std::cout << *miki2 << '\n';
    // std::cout << *miki << '\n';

    GField gf = GField(400, 5);

    long inp;
    std::cin >> inp;
    while (inp) {
        GFNumber *miki = gf.createNumber(inp);
        std::vector<long> v = miki->getPrimeFactors();
        for (auto i = v.begin(); i != v.end(); ++i) {
            std::cout << *i << '\n';
            /* code */
        }
        std::cin >> inp;
    }

    return 0;
}
