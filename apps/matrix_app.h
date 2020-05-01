// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>


namespace matrixapp {
enum class AppState {
    kSelecting,
    kInputtingData,
    kSolved,
    kExplaining,
    kDone,
};
class MatrixApp : public cinder::app::App {
 public:
  MatrixApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

private:
  void DrawErrorMessage();
  void DrawMatrixAnswer();
  void DrawVectorSpaceAnswer();
  void DrawAfterMessage();
  void DrawBackground() const;
  void PrintText(const std::string& text, const cinder::Color color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  AppState state_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
