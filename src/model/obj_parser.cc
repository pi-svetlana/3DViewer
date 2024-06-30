#include "obj_parser.h"

#include <boost/regex.hpp>
#include <iostream>
#include <string>

void ObjParser::Parse(std::ifstream &in_stream) {
  std::string line;
  while (std::getline(in_stream, line)) {
    ParseLine(line);
  }
  CheckData();
}

void ObjParser::CheckData() {
  if (data_->vertexes.empty()) {
    throw ParsingException("File is invalid");
  }
  if (!data_->vertex_indexes.empty()) {
    int max = *std::max_element(data_->vertex_indexes.begin(),
                                data_->vertex_indexes.end());
    if (max > data_->vertexes.size() - 1) {
      throw ParsingException("File is invalid");
    }
  }
}

void ObjParser::ParseLine(std::string &line) {
  if (line.empty()) {
    return;
  }
  if (line[0] == 'v' && line[1] == ' ') {
    const std::vector<boost::smatch> matches{
        boost::sregex_iterator{line.cbegin(), line.cend(),
                               vertex_numbers_regex_},
        boost::sregex_iterator{}};
    if (matches.size() >= 3) {
      data_->vertexes.push_back({std::stod(matches[0].str(0)),
                                 std::stod(matches[1].str(0)),
                                 std::stod(matches[2].str(0))});
    }
  }
  if (line[0] == 'f') {
    const std::vector<boost::smatch> matches{
        boost::sregex_iterator{line.cbegin(), line.cend(),
                               vertex_indexes_regex_},
        boost::sregex_iterator{}};
    if (matches.size() >= 2) {
      int matches_first_element;

      for (int i = 0; i < matches.size(); i++) {
        int parsed_number = std::stoi(matches[i].str(0));
        if (parsed_number > 0) {
          parsed_number -= 1;
        } else {
          parsed_number = NormalizeIndex(parsed_number);
        }
        if (i == 0) {
          matches_first_element = parsed_number;
        }

        data_->vertex_indexes.push_back(parsed_number);
        if (i != 0) {
          data_->vertex_indexes.push_back(parsed_number);
        }
      }
      data_->vertex_indexes.push_back(matches_first_element);
    }
  }
}

int ObjParser::NormalizeIndex(int index) {
  size_t vertexes_size = data_->vertexes.size();
  int normalized_index = index + static_cast<int>(vertexes_size);

  if (normalized_index < 0) throw ParsingException("File parsing error");
  return normalized_index;
}
ObjParser::ObjParser(ObjData *data) : data_(data) {}
