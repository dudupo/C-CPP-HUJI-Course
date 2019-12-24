
typedef class GFNumber GFNumber;

//#include "GFNumber.h"

class GField {
private:
    /* data */
    long chart;
    long degree;

public:
    GField();

    GField(long chart);

    GField(long chart, long degree);

    GField(const GField &source);

    long getChart() const;

    long getDegree() const;

    long getOrder() const;

    static bool isPrime(long number);

    GFNumber *gcd(GFNumber *a, GFNumber *b);

    GFNumber *createNumber(long number);

    void operator=(GField const &assignmented);

    bool operator==(GField const &assignmented);

    bool operator!=(GField const &assignmented);

    virtual ~GField() {};
};

std::ostream &operator<<(std::ostream &os, GField &field);

std::istream &operator>>(std::istream &is, GField &field);
