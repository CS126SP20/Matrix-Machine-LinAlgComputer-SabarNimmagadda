//
// Created by Sabar  Nimmagadda on 4/25/20.
//

#ifndef FINALPROJECT_COMPUTATIONS_H
#define FINALPROJECT_COMPUTATIONS_H


#include <Eigen/Dense>
#include <Eigen/LU>
#include <Eigen/src/Core/Matrix.h>

using Eigen::MatrixXd;
using Eigen::VectorXcd;
using Eigen::MatrixXcd;
using std::string;
class Computations {

public:
    /**
     * This computes the L matrix in LU decomposition.
     * @param matrix the matrix whose decomposition is taking place.
     * @return the L matrix.
     */
    static MatrixXd ComputeL(MatrixXd matrix);

    /**
     * This computes the U matrix in the LU decomposition.
     * @param matrix the matrix whose decomposition is taking place.
     * @return the U matrix.
     */
    static MatrixXd ComputeU(MatrixXd matrix);

    /**
     * This computes the permutation matrix.
     * @param matrix the matrix whose permutation matrix is being computed.
     * @return the permutation matrix.
     */
    static MatrixXd ComputePermutationMatrix(MatrixXd matrix);

    /**
     * This computes the inverse of a matrix.
     * @param matrix the matrix whose inverse is being computed.
     * @return
     */
    static MatrixXd ComputeInverse(const MatrixXd& matrix);

    /**
     * This computes the RREF of a matrix.
     * @param matrix whose RREF is being calculated.
     * @return the RREF of the matrix.
     */
    static MatrixXd ComputeRREF(const MatrixXd& matrix);

    /**
     * This computes the matrix product of two inputted matrices.
     * @param matrix1 the first matrix in the product.
     * @param matrix2 the second matrix in the product.
     * @return the multiplication matrix.
     */
    static MatrixXd ComputeMultiply(MatrixXd matrix1, MatrixXd matrix2);

    /**
     * This function computes the row space of a matrix.
     * @param matrix the matrix whose rowspace is being computed.
     * @return the matrix form of the row space.
     */
    static MatrixXd ComputeRowSpace(MatrixXd matrix);

    /**
     * This function computes the column space of a matrix.
     * @param matrix the matrix whose column space is being computed.
     * @return the matrix form of the column space.
     */
    static MatrixXd ComputeColSpace(MatrixXd matrix);

    /**
     * This computes the determinant of the inputted matrix.
     * @param matrix whose determinant is being computed.
     * @return the determinant.
     */
    static int ComputeDeterminant(const MatrixXd& matrix);

    /**
     * This computes the Q matrix in a QR decomposition.
     * @param matrix whose decomposition is taking place.
     * @return the Q matrix.
     */
    static MatrixXd ComputeQ(const MatrixXd& matrix);
    /**
     * This computes the R matrix in a QR decomposition.
     * @param matrix whose decomposition is taking place
     * @return the R matrix.
     */
    static MatrixXd ComputeR(const MatrixXd& matrix);

    /**
     * This computes the dot product of two matrices.
     * @param matrix1 first matrix.
     * @param matrix2 second matrix.
     * @param dim the dimension of the matrices.
     * @return the dot product.
     */
    static double ComputeDotProduct(MatrixXd matrix1, MatrixXd matrix2, int dim);

    /**
     * This computes the eigen values of a matrix.
     * @param matrix whose eigen values are being computed.
     * @return the vector of all of the eigen values.
     */
    static VectorXcd ComputeEigenValues(const MatrixXd& matrix);

    /**
     * This computes the eigen vectors of a matrix.
     * @param matrix the matrix whose eigen vectors are being computed.
     * @return the matrix of eigen vectors.
     */
    static MatrixXcd ComputeEigenVectors(const MatrixXd& matrix);
 private:
    typedef Eigen::Matrix<double, 3, 3 > M3X3;

};
#endif //FINALPROJECT_COMPUTATIONS_H