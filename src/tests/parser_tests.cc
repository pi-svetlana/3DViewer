#include <gtest/gtest.h>

#include <deque>

#include "../model/obj_parser.h"

TEST(Parsing, parse_vertexes_file) {
  ObjData obj_data;
  ObjParser parser{&obj_data};
  std::ifstream in("samples/only_vertexes_file", std::fstream::in);
  parser.Parse(in);
  std::vector<Vertex> expected_vertexes{{2., 2., 2.},
                                        {-0.565469, -1.496085, 1.44}};
  ASSERT_EQ(obj_data.vertexes, expected_vertexes);
}

TEST(Parsing, parse_vertexes_indexes_file) {
  ObjData obj_data;
  ObjParser parser{&obj_data};
  std::ifstream in("samples/only_vertexes_indexes_file", std::fstream::in);
  parser.Parse(in);
  std::vector<int> expected_vertexes_indexes{{0, 1, 1, 0,  2,  3,  3,  4,
                                              4, 2, 5, 6,  6,  7,  7,  8,
                                              8, 5, 9, 10, 10, 11, 11, 9}};
  ASSERT_EQ(obj_data.vertex_indexes, expected_vertexes_indexes);
}

TEST(Parsing, parse_vertexes_with_negative_indexes) {
  ObjData obj_data;
  ObjParser parser{&obj_data};
  std::ifstream in("samples/with_negative_indexes_file", std::fstream::in);
  parser.Parse(in);
  std::vector<int> expected_vertexes_indexes{
      {0, 1, 1, 2, 2, 0, 3, 4, 4, 5, 5, 3}};
  ASSERT_EQ(obj_data.vertex_indexes, expected_vertexes_indexes);
}

TEST(Parsing, parse_vertexes_with_negative_indexes_sections) {
  ObjData obj_data;
  ObjParser parser{&obj_data};
  std::ifstream in("samples/with_negative_sections_indexes_file",
                   std::fstream::in);
  parser.Parse(in);
  std::vector<int> expected_vertexes_indexes{
      {0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4}};
  ASSERT_EQ(obj_data.vertex_indexes, expected_vertexes_indexes);
}
