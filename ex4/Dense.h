

#ifndef DENSE
#define DENSE

#include "Matrix.h"
#include "Activation.h"

class Dense
{

private:

  Matrix& w;
  Matrix& bias;
  Activation activation;

public:
  Dense();
  Dense(Matrix& w, Matrix& bias, ActivationType activationType);
  Matrix& getWeights();
  Matrix& getBias();
  Matrix& operator()( Matrix& );
  Activation& getActivation();
};

#endif
