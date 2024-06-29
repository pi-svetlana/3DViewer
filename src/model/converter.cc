#include "converter.h"


void Converter::ScaleModel(double scale) {
  for (auto& point : data_->vertexes) {
    point.x *= scale;
    point.y *= scale;
    point.z *= scale;
  }
}

void Converter::MoveModel(double move_x, double move_y, double move_z) {
  for (auto& point : data_->vertexes) {
    point.x += move_x;
    point.y += move_y;
    point.z += move_z;
  }
}

void Converter::RotateModelX(double angle) {
  std::vector<Vertex> tmp = data_->vertexes;
  angle = fmod(angle, FULL_ANGLE) * DEGREE_TO_RADIAN;
  for (size_t i = 0; i < data_->vertexes.size(); ++i) {
    data_->vertexes[i].y = tmp[i].y * cos(angle) - tmp[i].z * sin(angle);
    data_->vertexes[i].z = tmp[i].y * sin(angle) + tmp[i].z * cos(angle);
  }
}

void Converter::RotateModelY(double angle) {
  std::vector<Vertex> tmp = data_->vertexes;
  angle = fmod(angle, FULL_ANGLE) * DEGREE_TO_RADIAN;
  for (size_t i = 0; i < data_->vertexes.size(); ++i) {
    data_->vertexes[i].x = tmp[i].x * cos(angle) + tmp[i].z * sin(angle);
    data_->vertexes[i].z = -tmp[i].x * sin(angle) + tmp[i].z * cos(angle);
  }
}

void Converter::RotateModelZ(double angle) {
  std::vector<Vertex> tmp = data_->vertexes;
  angle = fmod(angle, FULL_ANGLE) * DEGREE_TO_RADIAN;
  for (size_t i = 0; i < data_->vertexes.size(); ++i) {
    data_->vertexes[i].x = tmp[i].x * cos(angle) - tmp[i].y * sin(angle);
    data_->vertexes[i].y = tmp[i].x * sin(angle) + tmp[i].y * cos(angle);
  }
}

void Converter::CenterAndScale() {
  double max_x, min_x, max_y, min_y, max_z, min_z;
  max_x = min_x = data_->vertexes.front().x;
  max_y = min_y = data_->vertexes.front().y;
  max_z = min_z = data_->vertexes.front().z;
  for (auto& point : data_->vertexes) {
    max_x = std::max(max_x, point.x);
    max_y = std::max(max_y, point.y);
    max_z = std::max(max_z, point.z);
    min_x = std::min(min_x, point.x);
    min_y = std::min(min_y, point.y);
    min_z = std::min(min_z, point.z);
  }
  double center_x = min_x + (max_x - min_x) / 2;
  double center_y = min_y + (max_y - min_y) / 2;
  double center_z = min_z + (max_z - min_z) / 2;
  MoveModel(-center_x, -center_y, -center_z);
  double x, y, z, max, scale;
  x = max_x - min_x;
  y = max_y - min_y;
  z = max_z - min_z;
  max = std::max(std::max(x, y), z);
  ;
  scale = 1 / max;
  ScaleModel(scale);
}

void Converter::SetData(ObjData* data) { data_ = data; }
