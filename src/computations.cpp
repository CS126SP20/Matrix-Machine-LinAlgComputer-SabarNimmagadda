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
  MatrixXd Computations::Compute_PermutationMatrix(MatrixXd m) {
      typedef Eigen::Matrix<double, 3, 3> P_Matrix;
      Eigen::FullPivLU<P_Matrix> lu(m);
      P_Matrix p = lu.matrixLU();
      return p;
  }
  MatrixXd Computations::Compute_Inverse(MatrixXd m) {
      return m.inverse();
  }
  MatrixXd Computations::Compute_RREF(MatrixXd m) {
      int lead = 0;
      while (lead < m.rows()) {
          float divisor, multiplier;
          for (int row = 0; row <= m.rows(); row++) {
              divisor = m(lead, lead); //What divides a cell to make its value = 1.
              multiplier = m(row, lead)/ m(lead, lead); //What is multiplied to a cell, so that when it is subtracted the value becomes 0.
              for(int col = 0; col <= m.cols(); col++) {
                  if (lead == row) {
                      m(row,col) / = divisor; //This makes the pivots = 1.
                  } else {
                      m(row,col) -= m(lead, col) * multiplier; //Making everything that is not a pivot = 0;
                  }
              }
          }
          lead++;
      }
      return m;
  }




