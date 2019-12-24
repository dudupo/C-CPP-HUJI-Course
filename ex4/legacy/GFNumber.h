class GFNumber {
private:
    /* data */
    long number;
    GField *field;

public:
    GFNumber();

    GFNumber(long number);

    GFNumber(long number, GField *field);

    GFNumber(const GFNumber &gfnumber);

    long getNumber() const;

    GField *getField() const;

    GFNumber *abs();

    std::vector<long> getPrimeFactors();

    void printFactors();

    bool getIsPrime();

    void operator=(GFNumber const &assignmented);

    bool operator==(GFNumber const &other);

    bool operator!=(GFNumber const &other);

    void operator+=(GFNumber const &other);

    void operator-=(GFNumber const &other);

    void operator*=(GFNumber const &other);

    void operator/=(GFNumber const &other);

    void operator%=(GFNumber const &other);

    bool operator==(long other);

    bool operator!=(long other);

    void operator+=(long other);

    void operator-=(long other);

    void operator*=(long other);

    void operator/=(long other);

    void operator%=(long other);

    bool operator>=(long other);

    bool operator<=(long other);

    bool operator>(long other);

    bool operator<(long other);

    bool operator>=(GFNumber const &other);

    bool operator<=(GFNumber const &other);

    bool operator>(GFNumber const &other);

    bool operator<(GFNumber const &other);

    GFNumber *operator/(GFNumber const &other);

    GFNumber *operator*(GFNumber const &other);

    GFNumber *operator+(GFNumber const &other);

    GFNumber *operator-(GFNumber const &other);

    GFNumber *operator%(GFNumber const &other);

    GFNumber *operator/(long other);

    GFNumber *operator*(long other);

    GFNumber *operator+(long other);

    GFNumber *operator-(long other);

    GFNumber *operator%(long other);

    bool executeBooleanOperation(GFNumber const &other,
                                 std::function<bool(long, long)> _operator_);

    GFNumber *executeArithmetic(long other,
                                std::function<long(long, long)> _operator_);

    GFNumber *executeArithmetic(GFNumber const &other,
                                std::function<long(long, long)> _operator_);

    virtual ~GFNumber() {};
};

std::ostream &operator<<(std::ostream &os, GFNumber &gfnumber);

std::istream &operator>>(std::istream &is, GFNumber &gfnumber);
