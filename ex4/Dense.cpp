#include "Dense.h"

//
// Dense::Dense() : w(),
//  bias(), activation(Relu)
// {
//   // this->w(w);
//   // this->bias(bias);
//
//   //this->activation = activationType ;
//
// }

Dense::Dense(Matrix& w, Matrix& bias, ActivationType activationType) : w(w),
 bias(bias), activation(activationType)
{
  // this->w(w);
  // this->bias(bias);

  //this->activation = activationType ;

}

Matrix& Dense::getWeights()
{
  return this->w;
}
Matrix& Dense::getBias()
{
  return this->bias;
}
Activation& Dense::getActivation()
{
  return this->activation;
}
Matrix& Dense::operator()( Matrix& matrix )
{

  std::cout << "/* message Dense " << matrix.getRows() << '\n';
  std::cout << "/* message Dense " << matrix.getCols() << '\n';
  //std::cout << "/* message Dense " << (this->w * matrix).getCols() << '\n';
  std::cout << "/* message Dense " << this->w.getRows() << '\n';
    std::cout << "/* message Dense " << this->w.getCols() << '\n';
  return  this->activation(  this->w * matrix + this->bias );

 //(this->w * matrix)
//  return  this->activation( matrix + this->bias );
}
