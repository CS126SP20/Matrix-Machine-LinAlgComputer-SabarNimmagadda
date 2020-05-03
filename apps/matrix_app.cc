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
    string input = reinterpret_cast<const char *>(ui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf)));
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
            if( ui::BeginMenu( "Problem Type" )){
                if (ui::MenuItem( "RREF" )) {
                    //state_ == AppState::kInputtingData;
                    //INput matrix;
                    Computations::ComputeRREF(test_mat);
                }
                ui::MenuItem( "Row Space" );
                ui::MenuItem( "Column Space");
                ui::MenuItem("Null space");
                if (ui::MenuItem("LU Decomposition")) {
                    problem_type = 5;
                    state_= AppState::kInputtingData;
                }
                if (ui::MenuItem( "Permutation Matrix")) {
                    problem_type = 6;
                    state_= AppState::kInputtingData;
                }
                ui::MenuItem( "Inverse");
                ui::MenuItem( "Matrix Multiplication");
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
        state_ = AppState::kSolved;
    }
    if (state_ == AppState::kSolved) {
        if (problem_type == 5) {
            DrawLUAnswer(in_mat1);
        }
        if (problem_type == 6) {
            DrawPermutationAnswer(in_mat2);
        }
    }
}

void MatrixApp::keyDown(KeyEvent event) {
    if(event.getChar() == 'a') {
        state_ = AppState::kSolved;
    }
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
void MatrixApp::DrawLUAnswer(MatrixXd matrix) {
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
}

void MatrixApp::DrawPermutationAnswer(MatrixXd matrix) {
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    ss << Computations::ComputePermutationMatrix(matrix);
    PrintText("Your Permutation Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
}

void MatrixApp::InputMatrix() {
    if (problem_type != 9) {
        str_mat = reinterpret_cast<const char *>(ui::InputText("Input matrix", inputBuf, IM_ARRAYSIZE(inputBuf)));
    }
    str_mat = reinterpret_cast<const char *>(ui::InputText("Input first matrix", inputBuf, IM_ARRAYSIZE(inputBuf)));
    str_mat2 = reinterpret_cast<const char *>(ui::InputText("Input second matrix", inputBuf, IM_ARRAYSIZE(inputBuf)));
}

void MatrixApp::String_To_Matrix() {
    if (problem_type != 9) {
        //When the computation only needs one matrix.
        std::istringstream ss(str_mat);
        do {
            string cell;
            ss >> cell;
            int element = std::stoi(cell);
            in_mat1 << element;
        } while (ss);
    } else {
        std::istringstream ss1(str_mat);
        std::istringstream ss2(str_mat2);
        do {
            string cell1;
            string cell2;
            ss1 >> cell1;
            ss2 >> cell2;
            int element1 = std::stoi(cell1);
            int element2 = std::stoi(cell2);
            in_mat1 << element1;
            in_mat2 << element2;
        } while (ss1 && ss2);
    }
}


}  // namespace myapp
