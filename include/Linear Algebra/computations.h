//
// Created by Sabar  Nimmagadda on 4/25/20.
//

#ifndef FINALPROJECT_COMPUTATIONS_H
#define FINALPROJECT_COMPUTATIONS_H


#include <Eigen/Dense>
#include <Eigen/LU>
#include <Eigen/src/Core/Matrix.h>

using Eigen::MatrixXd;
using std::string;
class Computations {

public:
    static MatrixXd ComputeL(MatrixXd matrix);
    static MatrixXd ComputeU(MatrixXd matrix);
    static MatrixXd ComputePermutationMatrix(MatrixXd matrix);
    static MatrixXd ComputeInverse(const MatrixXd& m);
    static MatrixXd ComputeRREF(const MatrixXd& m);
    static MatrixXd ComputeMultiply(MatrixXd matrix1, MatrixXd matrix2);
    static MatrixXd ComputeRowSpace(MatrixXd matrix);
    static MatrixXd ComputeColSpace(MatrixXd matrix);
    static MatrixXd ComputeQ(const MatrixXd& matrix);
    static MatrixXd ComputeR(const MatrixXd& matrix);
    static MatrixXd ComputeDotProduct(MatrixXd matrix1, MatrixXd matrix2);
    static MatrixXd ComputeEigenValues(MatrixXd matrix);
    static MatrixXd ComputeEigenVectors(MatrixXd matrix);
    void setDimension(int dim);
 private:
    typedef Eigen::Matrix<double, 3, 3 > M3X3;
    int kDimension;
};
#endif //FINALPROJECT_COMPUTATIONS_H