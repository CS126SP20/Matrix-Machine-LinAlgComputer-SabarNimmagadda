// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Eigen/Dense>
using std::string;
using Eigen::MatrixXd;
namespace matrixapp {
enum class AppState {
    kSelecting,
    kInputtingData,
    kSolved,
    kDisplayed,
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
  void DrawErrorMessage();
  void DrawLUAnswer(const MatrixXd& matrix);
  void DrawPermutationAnswer(MatrixXd matrix);
  void DrawRREFAnswer(const MatrixXd& matrix);
  void DrawMultiplicationAnswer(MatrixXd matrix1, MatrixXd matrix2);
  void DrawInverseAnswer(const MatrixXd& matrix);
  void DrawQRAnswer(const MatrixXd& matrix);
  void InputMatrix();
  void ReInputMatrix();
  void ResetData();
  void String_To_Matrix();
  void DrawBackground() const;
  void PrintText(const std::string& text, const cinder::Color color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  void BackToMenu();
  AppState state_;
  std::vector<string> list_of_problems = {
          "RREF",
          "Row Space",
          "Column Space",
          "Null space",
          "LU Decomposition",
          "Permutation Matrix",
          "Inverse",
          "Matrix Multiplication",
          "QR Decomposition"
  };
    typedef Eigen::Matrix<double, 3, 3 > M3X3;
    M3X3 test_mat;
    int problem_type;
    M3X3 in_mat1;
    M3X3 in_mat2;
    std::string input_string = "";
    std::string input_string2 = "";
    std::string str_mat;
    std::string str_mat2;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
