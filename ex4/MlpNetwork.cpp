#include "MlpNetwork.h"

MlpNetwork::MlpNetwork(Matrix weights[4], Matrix biases[4]) {

    for (int i = 0; i < 3; i++) {
        this->layers[i] = new Dense(weights[i], biases[i], Relu);
    }
    this->layers[3] = new Dense(weights[3], biases[3], Softmax);
}


Digit MlpNetwork::operator()(Matrix &matrix) {
    Digit *digit = new Digit;

    digit->probability = 0;
    digit->value = 0;

    Matrix &ref(matrix);
    for (int i = 0; i < 4; i++) {
        ref = (*(this->layers[i]))(ref);
    }
    LAMBDA(fun) {
        UNUSED_LAMBDA();

        if (((Digit *) args)->probability < s) {
            ((Digit *) args)->probability = s;
            ((Digit *) args)->value = i;
        }

    };

    void *args = (void *) (digit);
    ref.forEach(fun, args);
    ref.freeMatrix();
    Digit ret = *digit;
    delete digit;
    return ret;
}
