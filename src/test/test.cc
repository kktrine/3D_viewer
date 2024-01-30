#include <gtest/gtest.h>

#include "../headers/Controller.h"

using s21::Controller;

#define EPS 1e-6
Controller contr;

TEST(reading, with_vertexes_and_facets) {
  std::string file_path = "test/test_with_facets.obj";

  contr.ReadFile(file_path);
  int count_vertexes = 7, count_facets = 18;
  ASSERT_EQ(count_vertexes, contr.get_count_vertexes());
  ASSERT_EQ(count_facets, contr.get_count_facets() / 2);

  std::vector<float> correct_vertexes = {2.0 / (12.2 / 3),
                                         12.2 / (12.2 / 3),
                                         0.0,
                                         0.0,
                                         0.0,
                                         1.0 / (12.2 / 3),
                                         7.0 / (12.2 / 3),
                                         1.11 / (12.2 / 3),
                                         0.23 / (12.2 / 3),
                                         0.0,
                                         1.0 / (12.2 / 3),
                                         1.0 / (12.2 / 3),
                                         2.1 / (12.2 / 3),
                                         0.0,
                                         0.0,
                                         1.0 / (12.2 / 3),
                                         1.0 / (12.2 / 3),
                                         2.2 / (12.2 / 3),
                                         1.0 / (12.2 / 3),
                                         1.0 / (12.2 / 3),
                                         1.0 / (12.2 / 3)};
  std::vector<unsigned> correct_facets = {0, 6, 6, 4, 4, 0, 0, 2, 2, 0, 2, 6,
                                          6, 2, 0, 3, 3, 2, 2, 0, 0, 1, 1, 0,
                                          1, 3, 3, 1, 4, 6, 6, 7, 7, 4, 5, 5};
  std::vector<float> vertexes = contr.get_vertexes();
  std::vector<unsigned> facets = contr.get_facets();
  for (int i = 0; i < (int)correct_vertexes.size(); ++i) {
    ASSERT_NEAR(correct_vertexes[i], vertexes[i], EPS);
  }
  ASSERT_EQ(correct_facets, facets);
  ASSERT_EQ(contr.get_state_info(), file_path + "\nvertexes: 7\nfacets: 18");
}

TEST(reading, file_not_found) {
  std::string file_path = "test/allo.obj";
  contr.ReadFile(file_path);
  ASSERT_EQ(contr.get_state_info(), file_path + "\nНе удалось открыть файл");
  ASSERT_TRUE(contr.get_facets().empty() && contr.get_count_facets() == 0);
  ASSERT_TRUE(contr.get_vertexes().empty() && contr.get_count_vertexes() == 0);
}

TEST(reading, file_not_found_2) {
  std::string file_path = "test/allo_2.obj";
  contr.ReadFile(file_path);
  ASSERT_EQ(contr.get_state_info(), file_path + "\nНе удалось открыть файл");
  ASSERT_TRUE(contr.get_facets().empty() && contr.get_count_facets() == 0);
  ASSERT_TRUE(contr.get_vertexes().empty() && contr.get_count_vertexes() == 0);
}

TEST(reading, file_without_facets) {
  std::string file_path = "test/test_without_facets.obj";
  int count_facets = 0;
  contr.ReadFile(file_path);
  ASSERT_EQ(count_facets, contr.get_count_facets());
  ASSERT_EQ(contr.get_state_info(), file_path + "\nvertexes: 7\nfacets: 0");
}

TEST(move, subtest_1) {
  std::string file_path = "test/file_for_testing_changes.obj";
  contr.ReadFile(file_path);
  float x = 1, y = 1, z = 3;
  contr.move(x, y, z);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(2, vertexes[0], EPS);
  ASSERT_NEAR(2, vertexes[1], EPS);
  ASSERT_NEAR(4, vertexes[2], EPS);
  ASSERT_NEAR(2, vertexes[3], EPS);
  ASSERT_NEAR(2, vertexes[4], EPS);
  ASSERT_NEAR(4, vertexes[5], EPS);
  ASSERT_NEAR(2, vertexes[6], EPS);
  ASSERT_NEAR(2, vertexes[7], EPS);
  ASSERT_NEAR(4, vertexes[8], EPS);
}

TEST(move, subtest_2) {
  std::string file_path = "test/file_for_testing_changes.obj";
  contr.ReadFile(file_path);
  contr.move(-2, -2, 6);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(-1, vertexes[0], EPS);
  ASSERT_NEAR(-1, vertexes[1], EPS);
  ASSERT_NEAR(7, vertexes[2], EPS);
  ASSERT_NEAR(-1, vertexes[3], EPS);
  ASSERT_NEAR(-1, vertexes[4], EPS);
  ASSERT_NEAR(7, vertexes[5], EPS);
  ASSERT_NEAR(-1, vertexes[6], EPS);
  ASSERT_NEAR(-1, vertexes[7], EPS);
  ASSERT_NEAR(7, vertexes[8], EPS);
}

TEST(scale, t1) {
  std::string file_path = "test/file_for_testing_changes.obj";
  contr.ReadFile(file_path);
  contr.scale(3);
  int status = 0;
  std::vector<float> vertexes = contr.get_vertexes();
  for (int i = 0; i < (int)contr.get_count_vertexes() * 3; ++i) {
    if (vertexes[i] != 3) {
      status = 1;
    }
  }
  ASSERT_EQ(0, status);
}

TEST(scale, t2) {
  std::string file_path = "test/file_for_testing_changes.obj";
  contr.ReadFile(file_path);
  contr.scale(0.5);
  int status = 0;
  std::vector<float> vertexes = contr.get_vertexes();
  for (int i = 0; i < (int)contr.get_count_vertexes() * 3; ++i) {
    if (vertexes[i] != 0.5) {
      status = 1;
    }
  }
  ASSERT_EQ(0, status);
}

TEST(rotate, x_rotate) {
  std::string file_path = "test/file_for_testing_rotate.obj";
  contr.ReadFile(file_path);
  float x = 30, y = 0, z = 0;
  contr.rotate(x, y, z);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(1, vertexes[0], EPS);
  ASSERT_NEAR(sqrt(3) / 2 - 0.5, vertexes[1], EPS);
  ASSERT_NEAR(sqrt(3) / 2 + 0.5, vertexes[2], EPS);
  ASSERT_NEAR(1, vertexes[3], EPS);
  ASSERT_NEAR(sqrt(3) / 2, vertexes[4], EPS);
  ASSERT_NEAR(0.5, vertexes[5], EPS);
  ASSERT_NEAR(1, vertexes[6], EPS);
  ASSERT_NEAR(0, vertexes[7], EPS);
  ASSERT_NEAR(0, vertexes[8], EPS);
}

TEST(rotate, y_rotate) {
  std::string file_path = "test/file_for_testing_rotate.obj";
  contr.ReadFile(file_path);
  float x = 0, y = 45, z = 0;
  contr.rotate(x, y, z);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(sqrt(2), vertexes[0], EPS);
  ASSERT_NEAR(1, vertexes[1], EPS);
  ASSERT_NEAR(0, vertexes[2], EPS);
  ASSERT_NEAR(sqrt(2) / 2, vertexes[3], EPS);
  ASSERT_NEAR(1, vertexes[4], EPS);
  ASSERT_NEAR(-(sqrt(2) / 2), vertexes[5], EPS);
  ASSERT_NEAR(sqrt(2) / 2, vertexes[6], EPS);
  ASSERT_NEAR(0, vertexes[7], EPS);
  ASSERT_NEAR(-(sqrt(2) / 2), vertexes[8], EPS);
}

TEST(rotate, z_rotate) {
  std::string file_path = "test/file_for_testing_rotate.obj";
  contr.ReadFile(file_path);
  float x = 0, y = 0, z = 60;
  contr.rotate(x, y, z);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(0.5 - sqrt(3) / 2, vertexes[0], EPS);
  ASSERT_NEAR(sqrt(3) / 2 + 0.5, vertexes[1], EPS);
  ASSERT_NEAR(1, vertexes[2], EPS);
  ASSERT_NEAR(0.5 - sqrt(3) / 2, vertexes[3], EPS);
  ASSERT_NEAR(sqrt(3) / 2 + 0.5, vertexes[4], EPS);
  ASSERT_NEAR(0, vertexes[5], EPS);
  ASSERT_NEAR(0.5, vertexes[6], EPS);
  ASSERT_NEAR(sqrt(3) / 2, vertexes[7], EPS);
  ASSERT_NEAR(0, vertexes[8], EPS);
}

TEST(rotate, x_z_rotate) {
  std::string file_path = "test/file_for_testing_rotate.obj";
  contr.ReadFile(file_path);
  float x = 90, y = 0, z = 90;
  contr.rotate(x, y, z);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(-1, vertexes[0], EPS);
  ASSERT_NEAR(-1, vertexes[1], EPS);
  ASSERT_NEAR(1, vertexes[2], EPS);
  ASSERT_NEAR(-1, vertexes[3], EPS);
  ASSERT_NEAR(0, vertexes[4], EPS);
  ASSERT_NEAR(1, vertexes[5], EPS);
  ASSERT_NEAR(0, vertexes[6], EPS);
  ASSERT_NEAR(0, vertexes[7], EPS);
  ASSERT_NEAR(1, vertexes[8], EPS);
}

TEST(rotate, rotate_360) {
  std::string file_path = "test/file_for_testing_rotate.obj";
  contr.ReadFile(file_path);
  float x = 360, y = 360, z = 360;
  contr.rotate(x, y, z);
  std::vector<float> vertexes = contr.get_vertexes();
  ASSERT_NEAR(1, vertexes[0], EPS);
  ASSERT_NEAR(1, vertexes[1], EPS);
  ASSERT_NEAR(1, vertexes[2], EPS);
  ASSERT_NEAR(1, vertexes[3], EPS);
  ASSERT_NEAR(1, vertexes[4], EPS);
  ASSERT_NEAR(0, vertexes[5], EPS);
  ASSERT_NEAR(1, vertexes[6], EPS);
  ASSERT_NEAR(0, vertexes[7], EPS);
  ASSERT_NEAR(0, vertexes[8], EPS);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
