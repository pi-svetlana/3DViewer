#include "vertex.h"

#include <cmath>
#define EPSILON 0.00000001


bool Vertex::operator==(const Vertex& rhs) const {
  return (fabs(x - rhs.x) < EPSILON && fabs(y - rhs.y) < EPSILON &&
          fabs(z - rhs.z) < EPSILON);
}
