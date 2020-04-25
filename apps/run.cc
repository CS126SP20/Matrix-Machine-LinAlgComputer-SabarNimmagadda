// Copyright (c) 2020 Sabar Nimmagadda. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include "my_app.h"
#include <Eigen/dense>

using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("The Matrix Machine");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
