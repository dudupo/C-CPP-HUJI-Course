#include "Dense.h"


Dense::Dense(Matrix &w, Matrix &bias, ActivationType activationType) : w(w),
                                                                       bias(bias), activation(activationType)
                                                                       {

}


Matrix &Dense::getWeights()
{
    return this->w;
}

Matrix &Dense::getBias()
{
    return this->bias;
}

Activation &Dense::getActivation()
{
    return this->activation;
}

Matrix &Dense::operator()(Matrix &matrix)
{

    Matrix& ref  = (this->w * matrix) += this->bias;
    Matrix& ret  = *(new Matrix(this->activation(   ref)));
    ref.freeMatrix();
    delete &ref;
    matrix = ret;
    delete &ret;
    return matrix;
}
