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
                    problem_type = 1;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Row Space" )) {
                    problem_type = 2;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Column Space")) {
                    problem_type = 3;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem("Null space")) {
                    problem_type = 4;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem("LU Decomposition")) {
                    problem_type = 5;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Permutation Matrix")) {
                    problem_type = 6;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Inverse")) {
                    problem_type = 7;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Matrix Multiplication")) {
                    problem_type = 8;
                    state_ = AppState::kInputtingData;
                }
                ui::EndMenu();
            }
            ui::EndMenuBar();
        }
        const ImVec2 vec2(500, 500);
        ui::SetWindowSize("Choose problem", vec2);
    }
    if (state_ == AppState::kInputtingData) {
        InputMatrix();
        String_To_Matrix();
    }
    if (state_ == AppState::kSolved) {
        if (problem_type == 5) {
            DrawLUAnswer(in_mat1);
        }
        if (problem_type == 6) {
            DrawPermutationAnswer(in_mat1);
        }
        if (problem_type == 1) {
            DrawRREFAnswer(in_mat1);
        }
        if (problem_type == 8) {
            DrawMultiplicationAnswer(in_mat1, in_mat2);
        }
        if (problem_type == 7) {
            DrawInverseAnswer(in_mat1);
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
    ResetData();
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
    ResetData();
}

void MatrixApp::DrawRREFAnswer(MatrixXd matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeRREF(std::move(matrix));
    PrintText("Your Row Reduced Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
    ResetData();
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
    ResetData();
}

void MatrixApp::DrawInverseAnswer(MatrixXd matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputeInverse(std::move(matrix));
    PrintText("The Inverse Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    BackToMenu();
    ResetData();
}

void MatrixApp::InputMatrix() {
    if (problem_type != 8) { //TODO: Make sure you remove all magic numbers.
        ui::InputInt("Enter dimension",  &kDimension);
        ui::InputText("Input matrix", &input_string);
        str_mat = input_string;
    } else {
        ui::InputInt("Enter dimension",  &kDimension);
        ui::InputText("Input first matrix", &input_string);
        ui::InputText("Input second matrix", &input_string2);
        str_mat = input_string;
        str_mat2 = input_string2;
    }
}

void MatrixApp::String_To_Matrix() {
    int mat_size = kDimension *kDimension;
    if (problem_type != 8 && str_mat.size() == mat_size * 2 && mat_size != 0) { // <= size * 2
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
    } else {
        //TODO: Make and change to error state;
    }
}

void MatrixApp::BackToMenu() {
    const cinder::ivec2 button_size = {500, 50};
    if (ui::Button("BACK TO MAIN MENU", button_size)) {
        state_ = AppState::kSelecting;
    }
}

void MatrixApp::ResetData() {
    const cinder::ivec2 button_size = {500, 50};
    if (ui::Button("RESET MATRICES", button_size)) {
        str_mat = "";
        str_mat2 = "";
        in_mat1.setZero();
        in_mat2.setZero();
    }
}


}  // namespace myapp
