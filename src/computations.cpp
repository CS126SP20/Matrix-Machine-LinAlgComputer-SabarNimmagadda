//
// Created by Sabar Nimmagadda on 4/25/20.
//
#include "Linear Algebra/computations.h"
#include <Eigen/LU>

#include <Eigen/QR>
#include <Eigen/Householder>
#include <Eigen/Eigenvalues>


using Eigen::MatrixXd;
using std::string;


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
      if (m.rows() >= 1 && m.cols() >= 1) {
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
  }

  MatrixXd Computations::ComputeMultiply(MatrixXd matrix1, MatrixXd matrix2) {
      if (matrix1.cols() == matrix2.rows()) {
          return matrix1*matrix2;
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

  double Computations::ComputeDotProduct(MatrixXd matrix1, MatrixXd matrix2, int dim) {
      double product = 0;
      for (int i = 0; i < dim; i++) {
          for (int j = 0; j < dim; j++) {
              product += matrix1(i, j) * matrix2(i, j);
          }
      }
      return product;
  }

  VectorXcd Computations::ComputeEigenValues(const MatrixXd& matrix) {
      VectorXcd ret = matrix.eigenvalues();
      return ret;
  }

  MatrixXcd Computations::ComputeEigenVectors(const MatrixXd& matrix) {
      Eigen::EigenSolver<MatrixXd> es(matrix);
      return es.eigenvectors();
  }

  int Computations::ComputeDeterminant(const MatrixXd& matrix) {
      return matrix.determinant();
  }
  MatrixXd Computations::ComputeColSpace(MatrixXd matrix) {
      if (matrix.size() >= 1) {
          Eigen::ColPivHouseholderQR<MatrixXd> qr(matrix);
          MatrixXd new_mat;
          if (qr.rank() != 0) {
              for (auto i : qr.colsPermutation().indices()) {
                  new_mat.col(i) = matrix.col(i);
              }
              return new_mat;
          }
          return new_mat;
      }
  }

  MatrixXd Computations::ComputeRowSpace(MatrixXd matrix) {
      MatrixXd transp = matrix.transpose();
      Eigen::ColPivHouseholderQR<MatrixXd> qr(transp);
      MatrixXd new_mat;
      for (auto i : qr.colsPermutation().indices()) {
          new_mat.col(i) = transp.col(i);
      }
      return new_mat;
  }



