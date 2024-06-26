#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_OBJDATA_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_OBJDATA_H_
#include <vector>

#include "vertex.h"


struct ObjData {
  std::vector<Vertex> vertexes;
  std::vector<int> vertex_indexes;
  void Reset() {
    vertexes.clear();
    vertex_indexes.clear();
  }
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_OBJDATA_H_
