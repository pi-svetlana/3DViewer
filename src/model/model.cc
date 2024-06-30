#include "model.h"

#include "obj_parser.h"

Context *Model::GetContext() { return &context_; }

void Model::OpenFile(std::string file_path) {
  std::ifstream in(file_path);
  try {
    if (in.is_open()) {
      data_ = std::make_unique<ObjData>();
      ObjParser parser{data_.get()};
      parser.Parse(in);
      converter_.SetData(data_.get());
      converter_.CenterAndScale();
      context_.object_ = data_.get();
      NotifyObservers();
      context_.Reset();
    } else {
      context_.message = "File " + file_path + " cannot be open";
      NotifyObservers();
      context_.Reset();
    }
  } catch (ParsingException &e) {
    data_->Reset();
    context_.message = e.what();
    NotifyObservers();
    context_.Reset();
  };
}

void Model::RotateModelX(double angle) {
  converter_.RotateModelX(angle);
  context_.object_ = data_.get();
  NotifyObservers();
  context_.Reset();
}
void Model::RotateModelY(double angle) {
  converter_.RotateModelY(angle);
  context_.object_ = data_.get();
  NotifyObservers();
  context_.Reset();
}
void Model::RotateModelZ(double angle) {
  converter_.RotateModelZ(angle);
  context_.object_ = data_.get();
  NotifyObservers();
  context_.Reset();
}
void Model::ScaleModel(double value) {
  converter_.ScaleModel(value);
  context_.object_ = data_.get();
  NotifyObservers();
  context_.Reset();
}
