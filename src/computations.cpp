//
// Created by Sabar Nimmagadda on 4/25/20.
//
#include "Linear Algebra/computations.h"
#include <Eigen/Dense>
#include <Eigen/LU>
#include <iostream>

using Eigen::MatrixXd;
using std::string;
  MatrixXd Computations::Compute_L(MatrixXd m) {
     typedef Eigen::Matrix<double, 3, 3 > L_Matrix;
     Eigen::FullPivLU<L_Matrix> lu(m);
     //Since the L matrix is a square matrix with the rowsize of the original matrix.
     L_Matrix l = L_Matrix::Identity();
     l.block<3,3>(0,0).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
     return l;
 }
 MatrixXd Computations::Compute_U(MatrixXd m) {
     typedef Eigen::Matrix<double, 3, 3> U_Matrix;
     Eigen::FullPivLU<U_Matrix> lu(m);
     //Since the U matrix has the exact dimensions of the original matrix.
     U_Matrix u = lu.matrixLU().triangularView<Eigen::Upper>();
     return u;
 }



