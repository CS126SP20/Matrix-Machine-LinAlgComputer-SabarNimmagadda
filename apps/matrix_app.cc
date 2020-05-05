// Copyright (c) 2020 Sabar Nimmagadda. All rights reserved.

#include "matrix_app.h"

#include <cinder/app/App.h>
#include <Eigen/Dense>
#include <cinder/gl/gl.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <Linear Algebra/computations.h>
#include <iostream>
#include <utility>
#include "CinderImGui.h"
using Eigen::MatrixXd;
namespace matrixapp {
using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using std::string;
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";

MatrixApp::MatrixApp()
    : state_{AppState::kSelecting} {}


void MatrixApp::setup() {
    ui::initialize();
    test_mat << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
}

void MatrixApp::update() {
    if (state_ == AppState::kInputtingData) {
        InputMatrix();
        String_To_Matrix();
    }
}

void MatrixApp::draw() {
    DrawBackground();
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const Color color = Color::black();
    if (state_ == AppState::kSelecting) {
        PrintText("WELCOME",color, size, {500,500});
        ui::ScopedWindow window( "Choose problem", ImGuiWindowFlags_MenuBar );
        if( ui::BeginMenuBar() ){
            if( ui::BeginMenu( "Problem Type" )) {
                if (ui::MenuItem( "RREF" )) {
                    problemType = ProblemType::RREF;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Row Space" )) {
                    problemType = ProblemType::RowSpace;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Column Space")) {
                    problemType = ProblemType::ColumnSpace;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem("LU Decomposition")) {
                    problemType = ProblemType::LUDecomposition;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Permutation Matrix")) {
                    problemType = ProblemType::PermutationMatrix;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Inverse")) {
                    problemType = ProblemType::Inverse;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Matrix Multiplication")) {
                    problemType = ProblemType::MatrixMultiplication;
                    state_ = AppState::kInputtingData;
                }
                if (ui::MenuItem("QR Decomposition")) {
                    problemType = ProblemType::QRDecomposition;
                    state_ = AppState::kInputtingData;
                }
                if (ui::MenuItem("Dot Product")) {
                    problemType = ProblemType::DotProduct;
                    state_ = AppState::kInputtingData;
                }
                if (ui::MenuItem("Eigen Vectors")) {
                    problemType = ProblemType::EigenVectors;
                    state_ = AppState::kInputtingData;
                }
                if (ui::MenuItem("Eigen Values")) {
                    problemType = ProblemType::EigenValues;
                    state_ = AppState::kInputtingData;
                }
                if (ui::MenuItem("Determinant")) {
                    problemType = ProblemType::Determinant;
                    state_ = AppState::kInputtingData;
                }
                ui::EndMenu();
            }
            ui::EndMenuBar();
        }
        const ImVec2 vec2(500, 500);
        ui::SetWindowSize("Choose problem", vec2);
    }
    if (state_ == AppState::kSolved) {
        if (problemType == ProblemType::QRDecomposition) {
            DrawQRAnswer(in_mat1);
        }
        if (problemType == ProblemType::LUDecomposition) {
            DrawLUAnswer(in_mat1);
        }
        if (problemType == ProblemType::PermutationMatrix) {
            DrawPermutationAnswer(in_mat1);
        }
        if (problemType == ProblemType::RREF) {
            DrawRREFAnswer(in_mat1);
        }
        if (problemType == ProblemType::EigenValues) {
            DrawEigenValuesAnswer(in_mat1);
        }
        if (problemType == ProblemType::Inverse) {
            DrawInverseAnswer(in_mat1);
        }
        if (problemType == ProblemType::EigenVectors) {
            DrawEigenVectorsAnswer(in_mat1);
        }
        if (problemType == ProblemType::DotProduct) {
            DrawDotProductAnswer(in_mat1, in_mat2);
        }
        if (problemType == ProblemType::MatrixMultiplication) {
            DrawMultiplicationAnswer(in_mat1, in_mat2);
        }
        if (problemType == ProblemType::Determinant) {
            DrawDeterminantAnswer(in_mat1);
        }
        if (problemType == ProblemType::RowSpace) {
            DrawRowSpaceAnswer(in_mat1);
        }
        if (problemType == ProblemType::ColumnSpace) {
            DrawColSpaceAnswer(in_mat1);
        }
    }
}

void MatrixApp::keyDown(KeyEvent event) {
}

void MatrixApp::PrintText(const string& text, const Color color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
    cinder::gl::color(color);
    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, 30))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 1, 0))
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}
void MatrixApp::DrawBackground() const {
    cinder::gl::clear(Color(0, 0, 0));
}
void MatrixApp::DrawLUAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeL(matrix);
    PrintText("Your L Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    std::stringstream st;
    st << Computations::ComputeU(matrix);
    PrintText("Your U Matrix is",color,{500,500},{center.x-50,center.y + 150});
    PrintText(st.str(), color, size, {center.x, center.y + 200});
    BackToMenu();
}

void MatrixApp::DrawDotProductAnswer(MatrixXd matrix1, MatrixXd matrix2) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeDotProduct(std::move(matrix1), std::move(matrix2), kDimension);
    PrintText("Your Dot Product is", color, {500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size, center);
    BackToMenu();
}

void MatrixApp::DrawPermutationAnswer(MatrixXd matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputePermutationMatrix(std::move(matrix));
    PrintText("Your Permutation Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
}

void MatrixApp::DrawRREFAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeRREF(matrix);
    PrintText("Your Row Reduced Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
}

void MatrixApp::DrawMultiplicationAnswer(MatrixXd matrix1, MatrixXd matrix2) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeMultiply(std::move(matrix1), std::move(matrix2));
    PrintText("The product Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
}

void MatrixApp::DrawInverseAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeInverse(matrix);
    PrintText("The Inverse Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
}

void MatrixApp::DrawQRAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeQ(matrix);
    PrintText("Your Q Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    std::stringstream st;
    st << Computations::ComputeR(matrix);
    PrintText("Your R Matrix is",color,{500,500},{center.x-50,center.y + 150});
    PrintText(st.str(), color, size, {center.x, center.y + 200});
    BackToMenu();
}

void MatrixApp::DrawEigenVectorsAnswer(MatrixXd matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeEigenVectors(matrix);
    PrintText("The Matrix of EigenVectors is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
}

void MatrixApp::DrawEigenValuesAnswer(MatrixXd matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeEigenValues(matrix);
    PrintText("The Eigenvalues are",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
}

void MatrixApp::DrawDeterminantAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeDeterminant(matrix);
    PrintText("Your determinant is", color, {500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size, center);
    BackToMenu();
}

void MatrixApp::DrawColSpaceAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    try {
        Computations::ComputeColSpace(matrix);
        Computations::ComputeRowSpace(matrix);
    } catch (int a) {

    }
    ss << Computations::ComputeEigenVectors(matrix);
    PrintText("Your Column Space Matrix is", color, {500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size, center);
    BackToMenu();
}

void MatrixApp::DrawRowSpaceAnswer(const MatrixXd& matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeEigenVectors(matrix);
    PrintText("Your Row Space Matrix is", color, {500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size, center);
    BackToMenu();
}

void MatrixApp::InputMatrix() {
    if (problemType != ProblemType::DotProduct && problemType != ProblemType::MatrixMultiplication) {
        ui::InputInt("Enter dimension",  &kDimension);
        ui::InputText("Input matrix", &input_string);
    } else {
        ui::InputInt("Enter dimension",  &kDimension);
        ui::InputText("Input first matrix", &input_string);
        ui::InputText("Input second matrix", &input_string2);
        str_mat2 = input_string2;
    }
    str_mat = input_string;
}


void MatrixApp::String_To_Matrix() {
    int mat_size = kDimension *kDimension;
    if ( problemType != ProblemType::DotProduct
     && problemType != ProblemType::MatrixMultiplication
     && str_mat.size() == mat_size * 2 && mat_size != 0) { // <= size * 2
        //TODO: Make dynamic.
        //When the computation only needs one matrix.
        std::istringstream ss(str_mat);
        for (int r = 0; r < kDimension; r++) {
            for (int c = 0; c < kDimension; c++) {
                int elem;
                ss >> elem;
                in_mat1(r, c) = elem;
            }
        }
        std::cout << in_mat1;
        state_ = AppState::kSolved;
    } else if (str_mat.size() == mat_size * 2 && str_mat2.size() == mat_size * 2 && mat_size != 0){
        //Made else if instead of else, because size cannot be zero ever.
        std::istringstream ss1(str_mat);
        std::istringstream ss2(str_mat2);
        for (int r = 0; r < kDimension; r++) {
            for (int c = 0; c < kDimension; c++) {
                int elem1;
                int elem2;
                ss1 >> elem1;
                ss2 >> elem2;
                in_mat1(r, c) = elem1;
                in_mat2(r, c) = elem2;
            }
        }
        std::cout << in_mat1 << std::endl;
        std::cout << in_mat2;
        state_ = AppState::kSolved;
    }
}

void MatrixApp::BackToMenu() {
    const cinder::ivec2 button_size = {500, 50};
    if (ui::Button("BACK TO MAIN MENU", button_size)) {
        state_ = AppState::kSelecting;
        input_string = "";
        input_string2 = "";
        kDimension = 0;
    }
}


}  // namespace myapp
