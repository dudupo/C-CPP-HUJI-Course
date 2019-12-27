//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
                                  {64,  128},
                                  {20,  64},
                                  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
                               {64,  1},
                               {20,  1},
                               {10,  1}};
/**
 * MlpNetwork, holds the layers and performs
 * the calculations.
 */
class MlpNetwork
{
private:
    Dense *layers[MLP_SIZE];
public:
    /**
     * constructor, construct the network.
     * @param weights, the weights matrixes.
     * @param biases, the biases matrixes.
     */
    MlpNetwork(Matrix weights[], Matrix biases[]);
    /**
     * perform the calculations of given image,
     * and returns the gussed digit.
     * @return the digit with height probability.
     */
    Digit operator()(Matrix &);
};
#endif // MLPNETWORK_H
