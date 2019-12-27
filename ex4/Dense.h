

#ifndef DENSE
#define DENSE

#include "Matrix.h"
#include "Activation.h"

/**
 * Dense, represent one layer.
 */
class Dense
{
private:
    Matrix &w;
    Matrix &bias;
    Activation activation;
public:
    /**
     * Dense constructor
     * @param w              the weights matrix.
     * @param bias           the bias matrix.
     * @param activationType the type of the activation function
     */
    Dense(Matrix &w, Matrix &bias, ActivationType activationType);
    /**
     * getWeights returns a reffernce to the matrix weights.
     * @return a reffernce to the matrix weights.
     */
    Matrix &getWeights();
    /**
     * getBias returns a reffernce to the matrix biases.
     * @return a reffernce to the matrix biases.
     */
    Matrix &getBias();
    /**
     * operator() calculate the layer step on the given matrix.
     * @return [description]
     */
    Matrix &operator()(Matrix &);
    /**
     * getActivation returns a reffernce to the activation function
     * @return a reffernce to the activation function.
     */
    Activation &getActivation();
};

#endif
