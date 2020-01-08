#include <fstream>
#include <iostream>
#include <string>

// #include ""

#include "Matrix.cpp"


static const std::string FAILMSG = std::string("fail test");
static const std::string PASSMSG = std::string("pass test");

void pass(const std::string &test_name) {
    std::cout << PASSMSG << SPACE << test_name << '\n';
}

void fail(const std::string &test_name) {
    std::cout << FAILMSG << SPACE << test_name << '\n';
}

void test_init_matrix() {

    Matrix matrix(3, 4);
    matrix.ones();
    matrix = (matrix * 3);
    std::cout << matrix;
    Matrix matrix2(4, 5);
    matrix2.ones();
    matrix2 = matrix2 * 2;
    std::cout << matrix2;
    std::cout << (matrix * matrix2);
    matrix.plainPrint();
    std::cout << matrix[4] << std::endl;
    std::cout << matrix(1, 1) << std::endl;

    std::cout << matrix2.vectorize() << '\n';

    pass("test_init_matrix");
}

bool readFileToMatrix(const std::string &filePath, Matrix &mat) {
    std::ifstream is;
    is.open(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!is.is_open()) {
        return false;
    }

    long int matByteSize = (long int) mat.getCols() * mat.getRows() * sizeof(float);

    if (is.tellg() != matByteSize) {
        is.close();
        return false;
    }
    is.seekg(0, std::ios_base::beg);
    is >> mat;
    is.close();
    return true;
}

//std::ifstream::binary
void test_reading_matrix() {
    //128, 784
    Matrix weights[3];

    weights[0] = Matrix(28, 28);
    weights[1] = Matrix(128, 784);
    weights[2] = Matrix(128, 1);
    // Matrix matrix (128, 1);
    //matrix.ones();
    readFileToMatrix(std::string("./images/im2"), weights[0]);
    readFileToMatrix(std::string("./parameters/w1"), weights[1]);
    readFileToMatrix(std::string("./parameters/b1"), weights[2]);


    // std::ifstream is1 ( std::string("./images/im2") , std::ios::in | std::ios::binary | std::ios::ate );//  ,std::ios::in | std::ios::binary | std::ios::ate );
    // std::ifstream is2 ( std::string("./parameters/w1") ,std::ios::in | std::ios::binary | std::ios::ate );
    // std::ifstream is3 ( std::string("./parameters/b1") ,std::ios::in | std::ios::binary | std::ios::ate );

    //std::ifstream is ( std::string("./parameters/w1") ,std::ios::in | std::ios::binary | std::ios::ate );
    //s.seekg(0, std::ios_base::beg);
    // is1 >> matrix;
    // is2 >> matrix2;
    // is3 >> matrix3;


    std::cout << weights[0];

    std::cout << weights[2](0, 324) << '\n';
    // Matrix matrix2 (28,28);
    // std::ifstream is2 ( std::string("./images/im2") , std::ios::binary );
    // is2 >> matrix2;
    // matrix2.plainPrint();

    // (matrix + matrix2).plainPrint();
    pass("test_reading_matrix");
}

int main() {
    //test_init_matrix();
    test_reading_matrix();
    return 0;
}
