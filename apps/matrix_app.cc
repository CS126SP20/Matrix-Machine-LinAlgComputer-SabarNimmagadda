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

}

void MatrixApp::update() {
    ui::ScopedWindow window( "Choose problem", ImGuiWindowFlags_MenuBar );

    // setup the window menu bar
    if( ui::BeginMenuBar() ){
        if( ui::BeginMenu( "Problem Type" ) ){
            ui::MenuItem( "RREF" );
            ui::MenuItem( "Row Space" );
            ui::MenuItem( "Column Space");
            ui::MenuItem("Null space");
            ui::MenuItem("LU Decomposition");
            ui::MenuItem( "Permutation Matrix");
            ui::MenuItem( "Inverse");
            ui::MenuItem( "Matrix Multiplication");
            ui::EndMenu();
        }
        ui::EndMenuBar();
    }
    const ImVec2 vec2(500, 500);
    ui::SetWindowSize("Choose problem", vec2);
}

void MatrixApp::draw() {
    DrawBackground();
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const Color color = Color::black();
    if (state_ == AppState::kSelecting) {
        PrintText("Enter Matrix",color, size, center);
    }
    if (state_ == AppState::kSolved) {
        DrawMatrixAnswer();
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
    cinder::gl::clear(Color(1, 0, 0));
}

void MatrixApp::DrawMatrixAnswer() {
    typedef Eigen::Matrix<double, 3, 3 > M3X3;
    M3X3 test_mat;
    test_mat << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    std::stringstream ss;
    Computations::ComputePermutationMatrix(test_mat);
    Computations::ComputeRREF(test_mat);
    Computations::ComputeInverse(test_mat);
    ss << Computations::ComputeL(test_mat);
    PrintText("Your L Matrix is",color,{500,500},{center.x-50,center.y - 50});
    PrintText(ss.str(), color, size , center);
    std::stringstream st;
    st << Computations::ComputeU(test_mat);
    PrintText("Your U Matrix is",color,{500,500},{center.x-50,center.y + 100});
    PrintText(st.str(), color, size, {center.x, center.y + 150});
}

}  // namespace myapp
