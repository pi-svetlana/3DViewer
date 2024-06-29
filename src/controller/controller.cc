#include "controller.h"

Controller::Controller(Model *model) : model_(model) {}

void Controller::OpenFile(std::string file_path) {
  model_->OpenFile(file_path);
}
void Controller::RotateModelX(double angle) { model_->RotateModelX(angle); }
void Controller::RotateModelY(double angle) { model_->RotateModelY(angle); }
void Controller::RotateModelZ(double angle) { model_->RotateModelZ(angle); }
void Controller::ScaleModel(double value) { model_->ScaleModel(value); }
