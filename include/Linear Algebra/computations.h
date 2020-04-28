//
// Created by Sabar  Nimmagadda on 4/25/20.
//

#ifndef FINALPROJECT_COMPUTATIONS_H
#define FINALPROJECT_COMPUTATIONS_H

#endif //FINALPROJECT_COMPUTATIONS_H
#include <Eigen/Dense>
#include <Eigen/LU>
using Eigen::MatrixXd;
using std::string;
class Computations {
 public:
    void Input_Matrix(string input);
    static MatrixXd Compute_L(MatrixXd m);
    static MatrixXd Compute_U(MatrixXd m);
    static MatrixXd Compute_PermutationMatrix(MatrixXd m);
    static MatrixXd Compute_Inverse(MatrixXd m);
    static MatrixXd Compute_RREF(MatrixXd m);
 private:
    MatrixXd in_matrix;

};