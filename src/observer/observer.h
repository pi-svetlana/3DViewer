#ifndef CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_OBSERVER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_OBSERVER_H_

#include "context.h"

class Observer {
 public:
  virtual ~Observer() = default;
  virtual void update(Context *context) = 0;
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_OBSERVER_OBSERVER_H_
