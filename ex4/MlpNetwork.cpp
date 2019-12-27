#include "MlpNetwork.h"
const int ZERO = 0;
const int LASTRELULAYER = 3;
const int SOFTMAXLAYER = 3;
const float ZEROF = 0.f;

/**
* constructor, construct the network.
* @param weights, the weights matrixes.
* @param biases, the biases matrixes.
*/
MlpNetwork::MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
{

        for (int i = ZERO; i < LASTRELULAYER; i++)
        {
                this->layers[i] = new Dense(weights[i], biases[i], Relu);
        }
        this->layers[SOFTMAXLAYER] = new Dense(weights[SOFTMAXLAYER],
                 biases[SOFTMAXLAYER], Softmax);
}
/**
* perform the calculations of given image,
* and returns the gussed digit.
* @return the digit with height probability.
*/
Digit MlpNetwork::operator()(Matrix &matrix)
{
        Digit *digit = new Digit;

        digit->probability = ZEROF;
        digit->value = ZERO;

        Matrix &ref(matrix);
        for (int i = ZERO; i < MLP_SIZE; i++)
        {
                ref = (*(this->layers[i]))(ref);
        }
        LAMBDA(fun)
        {
                UNUSED_LAMBDA();

                if (((Digit *) args)->probability < s)
                {
                        ((Digit *) args)->probability = s;
                        ((Digit *) args)->value = i;
                }

        };

        void *args = (void *) (digit);
        ref._forEach(fun, args);
        ref._freeMatrix();
        Digit ret = *digit;
        delete digit;
        return ret;
}
