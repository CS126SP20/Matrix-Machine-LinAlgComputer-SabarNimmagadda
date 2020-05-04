//
// Created by Sabar Nimmagadda on 4/25/20.
//
#include "Linear Algebra/computations.h"
#include <Eigen/Dense>
#include <Eigen/LU>
#include <iostream>
#include <Eigen/QR>
#include <Eigen/Householder>


using Eigen::MatrixXd;
using std::string;

  void Computations::setDimension(int dim) {
      kDimension = dim;
  }
  MatrixXd Computations::ComputeL(MatrixXd m) {
     typedef Eigen::Matrix<double, 3, 3 > L_Matrix;
     Eigen::FullPivLU<L_Matrix> lu(m);
     //Since the L matrix is a square matrix with the rowsize of the original matrix.
     L_Matrix l = L_Matrix::Identity();
     l.block<3,3>(0,0).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
     return l;
  }
  MatrixXd Computations::ComputeU(MatrixXd m) {
     typedef Eigen::Matrix<double, 3, 3> U_Matrix;
     Eigen::FullPivLU<U_Matrix> lu(m);
     //Since the U matrix has the exact dimensions of the original matrix.
     U_Matrix u = lu.matrixLU().triangularView<Eigen::Upper>();
     return u;
  }
  MatrixXd Computations::ComputePermutationMatrix(MatrixXd m) {
      typedef Eigen::Matrix<double, 3, 3> P_Matrix;
      Eigen::FullPivLU<P_Matrix> lu(m);
      P_Matrix p = lu.matrixLU();
      return p;
  }
  MatrixXd Computations::ComputeInverse(const MatrixXd& m) {
      return m.inverse();
  }

  MatrixXd Computations::ComputeRREF(const MatrixXd& m) {
      int lead = 0;
      MatrixXd out = m;
      while (lead < m.rows()) {
          float divisor, multiplier;
          for (int r = 0; r < m.rows(); r++) {
              if (out(lead, lead) != 0) {
                  divisor = out(lead, lead); //What divides a cell to make its value = 1.
                  multiplier = out(r, lead)/ out(lead, lead); //What is multiplied to a cell, so that when it is subtracted the value becomes 0.
              } else {
                  divisor = 1;
                  multiplier = 1;
              }
              for(int c = 0; c < m.cols(); c++) {
                  if (lead == r) {
                      out(r,c) /= divisor;//This makes the pivots = 1.
                  } else {
                      out(r,c) -= out(lead, c) * multiplier; //Making everything that is not a pivot = 0;
                  }
              }
          }
          lead++;
      }
      return out;
  }

  MatrixXd Computations::ComputeMultiply(MatrixXd m, MatrixXd n) {
      if (m.cols() == n.rows()) {
          return m*n;
      }
  }

  MatrixXd Computations::ComputeR(const MatrixXd& matrix) {
      Eigen::HouseholderQR<M3X3> qr(matrix.rows(), matrix.cols());
      qr.compute(matrix);
      MatrixXd R = qr.matrixQR().triangularView<Eigen::Upper>();
      return R;
  }

  MatrixXd Computations::ComputeQ(const MatrixXd& matrix) {
      Eigen::HouseholderQR<M3X3> qr(matrix.rows(), matrix.cols());
      qr.compute(matrix);
      MatrixXd Q = qr.householderQ();
      return Q;
  }

  MatrixXd Computations::ComputeDotProduct(MatrixXd matrix1, MatrixXd matrix2) {
      for (int i < MatrixApp::)
  }





