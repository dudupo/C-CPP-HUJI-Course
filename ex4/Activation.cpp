#ifndef LAMBDA

#define UNUSED(x) (void)(x)
#define LAMBDA(fun)  void (*fun)(float&, void *, int, int) = \
        [] (float& s, void * args, int i, int j)


#define UNUSED_LAMBDA() \
        UNUSED(args); \
        UNUSED(i); \
        UNUSED(j)
#endif

#include <cmath>
#include "Activation.h"


static Matrix &reluFun(Matrix &matrix) {
    LAMBDA(fun) {
        UNUSED_LAMBDA();

        if (s < 0) {
            s = 0;
        }
    };
    matrix.forEach(fun, nullptr);
    return matrix;
}

static Matrix& SoftmaxFun(Matrix &matrix) {

    LAMBDA(fun) {
        UNUSED_LAMBDA();
        s = std::exp(s);
        *((float *) args) += s;
        std::cout << s << std::endl;
    };

    float *args = new float(0);

    matrix.forEach(fun, (void *) args);

    LAMBDA(fun2) {
        UNUSED_LAMBDA();
        s /=  *((float *) args);
        std::cout << s << std::endl;
    };

    matrix.forEach(fun2, (void *) args);

    delete args;
    return matrix;
}


Activation::Activation(ActivationType activationType) {
    this->activationType = activationType;
}

Matrix &Activation::operator()(Matrix &matrix) {

    if (this->activationType == Relu) {
        return reluFun(matrix);
    } else if (this->activationType == Softmax) {
        return SoftmaxFun(matrix);
    }

    return matrix;
}

ActivationType Activation::getActivationType() const {
    return this->activationType;
}
