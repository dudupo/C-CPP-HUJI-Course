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


static Matrix& reluFun ( Matrix& matrix )
{
        Matrix& ref (matrix);
        LAMBDA(fun) {
                UNUSED_LAMBDA();

                if ( s < 0  )
                {
                        s = 0;
                }
        };
        std::cout << "/* relu */" << '\n';
        ref.forEach(fun, nullptr);
        return ref;
}
static Matrix& SoftmaxFun ( Matrix& matrix )
{
        Matrix& ref (matrix);
        LAMBDA(fun) {
                UNUSED_LAMBDA();
                s = std::exp(s);
                *((float *) args) += s;

                std::cout << *((float *) args) << '\n';
        };

        float * args = new float(0);

        ref.forEach(fun, (void *) args);
        return ref * ((float) 1 / args[0] );
}


Activation::Activation(ActivationType activationType )
{
        this->activationType = activationType;
}
Matrix& Activation::operator()( Matrix& matrix )
{
        std::cout << "/* message  Activation */" << '\n';
        if ( this->activationType == Relu)
        {
                return reluFun(matrix);
        }
        else if ( this->activationType == Softmax )
        {
                return SoftmaxFun(matrix);
        }
        std::cout << "/* message  Activation */" << '\n';
        return matrix;
}
ActivationType Activation::getActivationType() const {
        return this->activationType;
}
