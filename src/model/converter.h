#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_CONVERTER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_CONVERTER_H_

#include <iostream>
#include <vector>

#include "../model/obj_data.h"

#define FULL_ANGLE 360
#define DEGREE_TO_RADIAN M_PI / 180

class Converter {
 public:
  ~Converter() = default;

  void ScaleModel(double scale);
  void MoveModel(double move_x, double move_y, double move_z);
  void RotateModelX(double angle);
  void RotateModelY(double angle);
  void RotateModelZ(double angle);
  void CenterAndScale();
  void SetData(ObjData *data);

 private:
  ObjData *data_ = nullptr;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_CONVERTER_H_
