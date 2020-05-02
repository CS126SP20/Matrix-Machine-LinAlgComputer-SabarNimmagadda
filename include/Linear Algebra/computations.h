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
    //typedef Eigen::Matrix<double, 3, 3> Matrix3d;

public:
    void Input_Matrix(string input);
    static MatrixXd ComputeL(MatrixXd matrix);
    static MatrixXd ComputeU(MatrixXd matrix);
    static MatrixXd ComputePermutationMatrix(MatrixXd matrix);
    static MatrixXd ComputeInverse(MatrixXd m);
    static MatrixXd ComputeRREF(MatrixXd m);
    static MatrixXd ComputeMultiply(MatrixXd matrix1, MatrixXd matrix2);
    static MatrixXd ComputeRowSpace(MatrixXd matrix);
    static MatrixXd ComputeColSpace(MatrixXd matrix);
 private:
    MatrixXd in_matrix;

};
#endif //FINALPROJECT_COMPUTATIONS_H