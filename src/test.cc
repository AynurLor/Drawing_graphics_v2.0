#include "FileReader/filereader.hpp"
#include "gtest/gtest.h"

s21::FileReader reader(new s21::ObjectFileReader());

TEST(test_no_file, parsing_test) {
  auto result = reader.Read("");
  ASSERT_EQ(result.second, false);
}

TEST(test_file, parsing_tes_2) {
  auto result = reader.Read("./models/cube.obj");
  ASSERT_EQ(result.second, true);
  ASSERT_EQ(result.first.GetCountVertexes(), 8);
  ASSERT_EQ(result.first.GetCountFacets(), 12);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
