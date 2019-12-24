


//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType {
    Relu,
    Softmax
};

// Insert Activation class here...
//ACTIVATION_H



class Activation {

private:
    ActivationType activationType;
public:
    Activation(ActivationType activationType);

    Matrix &operator()(Matrix &);

    ActivationType getActivationType() const;

};

#endif
