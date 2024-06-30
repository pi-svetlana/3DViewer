#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_POINT_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_POINT_H_

struct Vertex {
  double x;
  double y;
  double z;
  bool operator==(const Vertex& rhs) const;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_POINT_H_
