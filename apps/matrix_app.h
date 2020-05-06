// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Eigen/Dense>
using std::string;
using Eigen::MatrixXd;
namespace matrixapp {

/**
 * The enums for the state of the program.
 */
enum class AppState {
    kSelecting,
    kInputtingData,
    kSolved,
};
class MatrixApp : public cinder::app::App {
 public:
  MatrixApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  int kDimension;

private:

  /**
   * This function calls the ComputeLU() function, and is
   * responsible for drawing out the answer for the LU
   * problem type in the output screen.
   * @param matrix the matrix whose LU decomposition is taking place.
   */
  void DrawLUAnswer(const MatrixXd& matrix);

  /**
   * This function calls the ComputePermutation() function, and is
   * responsible for drawing out the answer for the permutation matrix
   * problem type in the output screen.
   * @param matrix the matrix whose permutation matrix is to be found.
   */
  void DrawPermutationAnswer(MatrixXd matrix);

  /**
   * This function calls the ComputeRREF() function, and is
   * responsible for drawing out the answer for the echelon form matrix
   * problem type in the output screen.
   * @param matrix the matrix whose RREF is to be found.
   */
  void DrawRREFAnswer(const MatrixXd& matrix);

  /**
   * This function calls the ComputeMultiply() function, and is
   * responsible for drawing out the answer for the multiplication matrix
   * of two input matrices in the output screen.
   * @param matrix1 the matrix whose matrix multiplication is to be found.
   * @param matrix2 the matrix whose matrix multiplication is to be found.
   */
  void DrawMultiplicationAnswer(MatrixXd matrix1, MatrixXd matrix2);

  /**
   * This function calls the ComputeInverse() function, and is
   * responsible for drawing out the inverse matrix of the input.
   * @param matrix the inputted matrix whose inverse is to be found.
   */
  void DrawInverseAnswer(const MatrixXd& matrix);

  /**
   * The function responsible for drawing the answer for QR decomposition.
   * This call the ComputeQ() and ComputeR() functions.
   * @param matrix the matrix to be inputted
   */
  void DrawQRAnswer(const MatrixXd& matrix);

  /**
   * This function calls the ComputeDotProduct() function, and is
   * responsible for drawing out the answer for the dot product
   * of two input matrices in the output screen.
   * @param matrix1 the matrix whose dot product is to be found.
   * @param matrix2 the matrix whose dot product is to be found.
   */
  void DrawDotProductAnswer(MatrixXd matrix1, MatrixXd matrix2);

  /**
   * This function calls the ComputeEigenVectors() function, and is
   * responsible for drawing out the answer for the eigen vectors of a marix.
   * @param matrix The matrix whose eigen vectors are to be found.
   */
  void DrawEigenVectorsAnswer(MatrixXd matrix);

  /**
   * This function calls the ComputeEigenVectors() function, and
   * is responsible for drawing out the answer for the eigen values of a matrix.
   * @param matrix
   */
  void DrawEigenValuesAnswer(MatrixXd matrix);

  /**
   * This function is responsible for outputting the determinant of the input matrix.
   * It calls the ComputeDeterminant() function.
   * @param matrix the matrix whose determinant is to be found.
   */
  void DrawDeterminantAnswer(const MatrixXd& matrix);

  /**
   * This function outputs the answer for the row space of a matrix,
   * and it calls the ComputeRowSpace() function.
   * @param matrix the matrix whose Row Space is to be found.
   */
  void DrawRowSpaceAnswer(const MatrixXd& matrix);

  /**
   * This function outputs the answer for the column space of a matrix,
   * and it calls the ComputeColSpace() function.
   * @param matrix the matrix whose Col Space is to be found.
   */
  void DrawColSpaceAnswer(const MatrixXd& matrix);

  /**
   * This function inputs the matrix from the user in the form of a string.
   */
  void InputMatrix();

  /**
   * This function converts the string matrix input from the user into an Eigen::Matrix.
   */
  void String_To_Matrix();

  /**
   * This function draws the background screen of the application.
   */
  void DrawBackground() const;

  /**
   * This function is called in every draw answer function to output text and matrices.
   */
  void PrintText(const std::string& text, const cinder::Color color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  /**
  * This function returns the user to the main menu.
  */
  void BackToMenu();

  /**
   * This function calls all the other draw answer functions, to make the code inside Draw()
   * more readable and concise.
   */
  void DrawAnswer();

  /**
   * This function creates the menu that was initially created within Draw(),
   * which sets the problem type for different click actions.
   */
  void CreateMenu();

  /**
   * This is the enum class for every type of problem.
   */
  enum class ProblemType {
          RREF,
          RowSpace,
          ColumnSpace,
          LUDecomposition,
          PermutationMatrix,
          Inverse,
          MatrixMultiplication,
          QRDecomposition,
          Determinant,
          EigenValues,
          EigenVectors,
          DotProduct
  };
    typedef Eigen::Matrix<double, 3, 3> M3X3;
    M3X3 test_mat;
    std::string input_string = "";
    std::string input_string2 = "";
    std::string str_mat;
    std::string str_mat2;
    AppState state_;
    ProblemType problemType;
    M3X3 in_mat1;
    M3X3 in_mat2;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
