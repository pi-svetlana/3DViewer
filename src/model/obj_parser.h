#include <boost/regex.hpp>
#include <exception>
#include <fstream>
#include <regex>

#include "obj_data.h"

#ifndef CPP4_3DVIEWER_V2_0_1_SRC_MODEL_OBJPARSER_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_MODEL_OBJPARSER_H_


class ObjParser {
 private:
  const boost::regex vertex_numbers_regex_{R"(-?\d+\.?\d*([eE][+-]?\d+)?)"};
  const boost::regex vertex_indexes_regex_{
      R"(([-]?\d+)(?:\/[-]?\d*)?(?:\/[-]?\d*)?)"};

  ObjData *data_ = nullptr;
  std::ifstream stream_;

  void ParseLine(std::string &line);
  int NormalizeIndex(int index);
  void CheckData();

 public:
  explicit ObjParser(ObjData *data);
  void Parse(std::ifstream &stream_);
};

class ParsingException : public std::exception {
  const char *error_msg;

 public:
  explicit ParsingException(const char *message) : error_msg(message) {}
  const char *what() const noexcept override { return error_msg; }
};

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_MODEL_OBJPARSER_H_
