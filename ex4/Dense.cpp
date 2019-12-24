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

Dense::Dense(Matrix &w, Matrix &bias, ActivationType activationType) : w(w),
                                                                       bias(bias), activation(activationType) {

}

//Dense& Dense::operator=(const Dense& other){
//
//}

Matrix &Dense::getWeights() {
    return this->w;
}

Matrix &Dense::getBias() {
    return this->bias;
}

Activation &Dense::getActivation() {
    return this->activation;
}

Matrix &Dense::operator()(Matrix &matrix) {
    return this->activation(this->w * matrix + this->bias);
}
