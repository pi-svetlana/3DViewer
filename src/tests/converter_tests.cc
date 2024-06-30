#include <gtest/gtest.h>

#include "../model/converter.h"


ObjData mod;
ObjData res;

void InitObj(ObjData *mod, ObjData *res) {
  mod->vertexes = {{0, 0, 0}, {0, 0, 2}, {0, 2, 0}, {0, 2, 2},
                   {2, 0, 0}, {2, 0, 2}, {2, 2, 0}, {2, 2, 2}};
  res->vertexes = {{-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, -0.5},
                   {-0.5, 0.5, 0.5},   {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5},
                   {0.5, 0.5, -0.5},   {0.5, 0.5, 0.5}};
}

TEST(ScaleModel, Test_1) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.ScaleModel(2);
  converter.ScaleModel(0.5);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(ScaleModel, Test_2) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.ScaleModel(1.7);
  converter.ScaleModel(1 / 1.7);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(MoveModel, Test_1) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.MoveModel(2, 4, 7);
  converter.MoveModel(-2, -4, -7);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(MoveModel, Test_2) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.MoveModel(1.7, 3.455, 24.7356);
  converter.MoveModel(-1.7, -3.455, -24.7356);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(RotateModelX, Test_1) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.RotateModelX(120);
  converter.RotateModelX(240);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(MoveModelX, Test_2) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.RotateModelX(137);
  converter.RotateModelX(-137);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(RotateModelY, Test_1) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.RotateModelY(120);
  converter.RotateModelY(240);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(MoveModelY, Test_2) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.RotateModelY(137);
  converter.RotateModelY(-137);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(RotateModelZ, Test_1) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.RotateModelZ(120);
  converter.RotateModelZ(240);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(MoveModelZ, Test_2) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  converter.RotateModelZ(137);
  converter.RotateModelZ(-137);
  ASSERT_EQ(mod.vertexes, res.vertexes);
}

TEST(CenterAndScale, Test_1) {
  InitObj(&mod, &res);
  Converter converter;
  converter.SetData(&mod);
  converter.CenterAndScale();
  ASSERT_EQ(mod.vertexes, res.vertexes);
}
