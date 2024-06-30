#ifndef CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_CONTEXT_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_CONTEXT_H_

#include <string>

#include "../model/obj_data.h"


class Context {
 public:
  std::string message;
  ObjData *object_ = nullptr;
  virtual void Reset();
  virtual ~Context() = default;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_CONTEXT_H_
