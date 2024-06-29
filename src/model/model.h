#ifndef VIEWER_SRC_MODEL_MODEL_H_
#define VIEWER_SRC_MODEL_MODEL_H_

#include "../observer/observable.h"
#include "converter.h"
#include "obj_parser.h"


class Model : public Observable {
 public:
  void OpenFile(std::string file_path);

  void RotateModelX(double angle);
  void RotateModelY(double angle);
  void RotateModelZ(double angle);
  void ScaleModel(double value);

 private:
  Context* GetContext() override;

  Converter converter_{};
  std::unique_ptr<ObjData> data_;
  Context context_;
};

#endif  // VIEWER_SRC_MODEL_MODEL_H_
