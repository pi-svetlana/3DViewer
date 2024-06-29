#ifndef VIEWER_SRC_CONTROLLER_CONTROLLER_H_
#define VIEWER_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

class Controller {
 private:
  Model* model_;

 public:
  explicit Controller(Model* model);

  void RotateModelX(double angle);
  void RotateModelY(double angle);
  void RotateModelZ(double angle);
  void ScaleModel(double value);
  void OpenFile(std::string file_path);
};

#endif  // VIEWER_SRC_CONTROLLER_CONTROLLER_H_
