
#ifndef   headers_h
#define   headers_h
#include  "headers.h"
#endif

const int DEFAULTNUMBER = 0;
const int DEFAULTDEEP = 20;

GFNumber::GFNumber () : GFNumber(DEFAULTNUMBER, new GField() ) {
}
GFNumber::GFNumber (long number) : GFNumber(number, new GField() ) {

}
GFNumber::GFNumber (long number, GField * field){
  this->field = field;
  this->number = number % field->getOrder();
}
GFNumber::GFNumber (const GFNumber& gfnumber) : GFNumber( gfnumber.getNumber(), gfnumber.getField() ){

}
long GFNumber::getNumber() const {
  return this->number;
}
GField * GFNumber::getField() const {
  return this->field;
}

GFNumber * GFNumber::abs () {
  return new GFNumber(
     std::abs(this->getNumber()), this->getField());
}


//std::vector<long> & getFactors(GFNumber& number, std::vector<long>& factors);
std::vector<long> & naive (GFNumber& number, std::vector<long>& factors);
std::vector<long> & pollard (GFNumber& number, std::vector<long>& factors, int deep);

// std::vector<long> & getFactors(GFNumber& number, std::vector<long>& factors) {
//
// }

std::vector<long>& naive (GFNumber& number, std::vector<long>& factors) {

  long i;
  for (i = 2; i <= std::sqrt(number.getNumber())
   && (number % i != 0) ; i++ ) { }

  if ( number % i == 0 ) {
    while (number % i == 0 && number >= i) {
      factors.push_back(i);
      number = *(number / i);
      /* code */
    }
    return pollard(number, factors, DEFAULTDEEP);
  }
  else {
    return factors;
  }
}

std::vector<long>& pollard (GFNumber& number,
   std::vector<long>& factors, int deep) {

    if (number == 0 || number == 1 )
      return factors;

    GField * gfield =   number.getField();

    GFNumber * x1     =  gfield->createNumber(0);
    GFNumber * x2     =  gfield->createNumber(0);
    GFNumber p        =  *gfield->createNumber(1);

    long random_parameter = std::rand() % gfield->getOrder();

    std::function<GFNumber*(GFNumber*)> pol =
     [random_parameter](GFNumber *gfnumber)  {
        return *((*gfnumber) * (*gfnumber)) + random_parameter;
    };

    while (p == 1 ) {
       x1 = pol(x1); x2 = pol(pol(x2));
       p = *number.getField()->gcd( (*x1 - *x2)->abs(), new GFNumber(number));
    }

    if ( p == number){
      if (!factors.empty()){
          factors.push_back(p.getNumber());
          return factors;
      }
      return deep > 0 ? pollard(number, factors, deep-1) : naive(number, factors);
    }

    else {
      int step = 0;
      while( *(number % p) == 0 && number >= p ){
        factors.push_back(p.getNumber());
        number = *(number / p);
        step++;
      }
      return pollard(number, factors, DEFAULTDEEP);
    }

}


std::vector<long> GFNumber::getPrimeFactors(){
  std::vector<long> ret; // = std::vector<long>();
  ret.clear();
  GFNumber gfnumber = GFNumber( *this );
  return pollard(gfnumber, ret, DEFAULTDEEP);

}
void GFNumber::printFactors(){
  //todo;
}
bool GFNumber::getIsPrime() {
  return GField::isPrime(this->getNumber());
}
void GFNumber::operator = ( GFNumber const &assignmented ){
  this->number = assignmented.getNumber();
  this->field = new GField(*assignmented.getField());
}
bool GFNumber::operator == ( GFNumber const &other ){
  return this->number == other.getNumber() &&
    *this->getField() == *other.getField();
}
bool GFNumber::operator != ( GFNumber const &other ){
  return this->number != other.getNumber() ||
    *this->getField() != *other.getField();
}

bool GFNumber::executeBooleanOperation(GFNumber const &other,
  std::function<bool(long,long)> _operator_) {
    if ( *this->getField() != *other.getField()) {
      std::cerr << "error" << '\n';
    }
    return _operator_(this->getNumber(), other.getNumber());
}
GFNumber * GFNumber::executeArithmetic(long other,
  std::function<long(long,long)> _operator_) {
    return new GFNumber( _operator_(this->getNumber(), other) %
     this->getField()->getOrder(), this->getField());
}
GFNumber * GFNumber::executeArithmetic(GFNumber const &other,
  std::function<long(long,long)> _operator_) {
    if ( *this->getField() != *other.getField()) {
      std::cout << "error" << '\n';
    }
    return executeArithmetic(other.getNumber(), _operator_);
}

bool GFNumber::operator >= ( GFNumber const &other ){
  return this->executeBooleanOperation(other, std::greater_equal<long>());
}
bool GFNumber::operator <= ( GFNumber const &other ){
  return this->executeBooleanOperation(other, std::less_equal<long>());
}
bool GFNumber::operator >  ( GFNumber const &other ){
  return this->executeBooleanOperation(other, std::greater<long>());
}
bool GFNumber::operator <  ( GFNumber const &other ){
  return this->executeBooleanOperation(other, std::less<long>());
}
std::ostream& operator << (std::ostream& os, GFNumber & gfnumber) {
  os << gfnumber.getNumber() << " " << *gfnumber.getField();
  return os;
}
std::istream& operator >> (std::istream& is, GFNumber & gfnumber) {
  int number; GField field;
  is >> number >> field;
  gfnumber = GFNumber(number, &field);
  return is;
}
GFNumber * GFNumber::operator / ( GFNumber const &other ) {
  return this->executeArithmetic(other, std::divides<long>());
}
GFNumber * GFNumber::operator * ( GFNumber const &other ) {
  return this->executeArithmetic(other, std::multiplies<long>());
}
GFNumber * GFNumber::operator + ( GFNumber const &other ) {
  return this->executeArithmetic(other, std::plus<long>());
}
GFNumber * GFNumber::operator - ( GFNumber const &other ) {
  return this->executeArithmetic(other, std::minus<long>());
}
GFNumber * GFNumber::operator % ( GFNumber const &other ) {
  return this->executeArithmetic(other, std::modulus<long>());
}
GFNumber * GFNumber::operator / ( long other ) {
  return this->executeArithmetic(other, std::divides<long>());
}
GFNumber * GFNumber::operator * ( long other ) {
  return this->executeArithmetic(other, std::multiplies<long>());
}
GFNumber * GFNumber::operator + ( long other ) {
  return this->executeArithmetic(other, std::plus<long>());
}
GFNumber * GFNumber::operator - ( long other ) {
  return this->executeArithmetic(other, std::minus<long>());
}
GFNumber * GFNumber::operator % ( long other ) {
  return this->executeArithmetic(other, std::modulus<long>());
}
void GFNumber::operator += ( GFNumber const &other ){
  this->operator=(*(*this + other));
}
void GFNumber::operator -= ( GFNumber const &other ){
  this->operator=(*(*this - other));
}
void GFNumber::operator *= ( GFNumber const &other ){
  this->operator=(*(*this * other));
}
void GFNumber::operator /= ( GFNumber const &other ){
  this->operator=(*(*this / other));
}
void GFNumber::operator %= ( GFNumber const &other ){
  this->operator=(*(*this % other));
}
void GFNumber::operator += ( long other) {
  this->operator=(*(*this + other));
}
void GFNumber::operator -= ( long other) {
  this->operator=(*(*this - other));
}
void GFNumber::operator *= ( long other) {
  this->operator=(*(*this * other));
}
void GFNumber::operator /= ( long other) {
  this->operator=(*(*this / other));
}
void GFNumber::operator %= ( long other) {
  this->operator=(*(*this % other));
}
bool GFNumber::operator == ( long other ) {
  return this->getNumber() == other;
}
bool GFNumber::operator != ( long other ) {
  return this->getNumber() != other;
}
bool GFNumber::operator >= ( long other ) {
  return this->getNumber() >= other;
}
bool GFNumber::operator <= ( long other ) {
  return this->getNumber() <= other;
}
bool GFNumber::operator >  ( long other ) {
  return this->getNumber()  > other;
}
bool GFNumber::operator <  ( long other ) {
  return this->getNumber()  < other;
}
