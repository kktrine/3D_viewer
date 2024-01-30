#ifndef HEADERS_SCENE_H
#define HEADERS_SCENE_H
#include <cmath>
#include <iostream>
#include <vector>
using std::vector;

namespace s21 {
class Figure {
 public:
  Figure() : count_vertexes_(0), count_facets_(0){};
  Figure(vector<float>& vertexes, vector<unsigned>& facets)
      : vertexes_(vertexes),
        facets_(facets),
        count_vertexes_(0),
        count_facets_(0){};

  ~Figure(){};
  const vector<float>& get_vertexes() noexcept { return vertexes_; }
  const vector<unsigned>& get_facets() noexcept { return facets_; }
  void set_count_vertexes(size_t& count) noexcept { count_vertexes_ = count; }
  void set_count_facets(size_t& count) noexcept { count_facets_ = count; }
  const size_t& get_count_vertexes() noexcept { return count_vertexes_; }
  const size_t& get_count_facets() noexcept { return count_facets_; }
  void rotate_figure(float& x_angle, float& y_angle, float& z_angle) {
    if (fabs(fmod(x_angle, 360.)) > 1e-5 || fabs(fmod(y_angle, 360.)) > 1e-5 ||
        fabs(fmod(z_angle, 360.)) > 1e-5) {
      x_angle /= 180 / M_PI;
      y_angle /= 180 / M_PI;
      z_angle /= 180 / M_PI;

      float cos_x = cosf(x_angle), sin_x = sinf(x_angle), cos_y = cosf(y_angle),
            sin_y = sinf(y_angle), cos_z = cosf(z_angle), sin_z = sinf(z_angle),
            x = 0., y = 0., z = 0.;
      for (unsigned long i = 0; i < count_vertexes_ * 3; i += 3) {
        x = vertexes_[i];
        y = vertexes_[i + 1];
        z = vertexes_[i + 2];
        vertexes_[i] = cos_y * cos_z * x - sin_z * cos_y * y + sin_y * z;
        vertexes_[i + 1] = (sin_x * sin_y * cos_z + sin_z * cos_x) * x +
                           (-sin_x * sin_y * sin_z + cos_x * cos_z) * y -
                           sin_x * cos_y * z;
        vertexes_[i + 2] = (sin_x * sin_z - sin_y * cos_x * cos_z) * x +
                           (sin_x * cos_z + sin_y * sin_z * cos_x) * y +
                           cos_x * cos_y * z;
      }
    }
  }

  void move(const float& move_x, const float& move_y, const float& move_z) {
    if (fabs(move_x) > 1e-3 || fabs(move_y) > 1e-3 || fabs(move_z) > 1e-3)
      for (unsigned long i = 0; i < count_vertexes_ * 3; i += 3) {
        vertexes_[i] += move_x;
        vertexes_[i + 1] += move_y;
        vertexes_[i + 2] += move_z;
      }
  }
  void scale(const float& parameter) {
    if (parameter > 0.001)
      for (unsigned long i = 0; i < count_vertexes_ * 3; ++i)
        vertexes_[i] *= parameter;
  }

 private:
  vector<float> vertexes_;
  vector<unsigned> facets_;
  size_t count_vertexes_;
  size_t count_facets_;
};

class Scene {
 public:
  Figure& get_figure() noexcept { return figure_; }
  Scene() : figure_(){};
  ~Scene(){};
  Scene(Figure& figure) : figure_(figure){};
  void rotate_figure(float& x_angle, float& y_angle, float& z_angle) {
    figure_.rotate_figure(x_angle, y_angle, z_angle);
  }
  void move_figure(const float& move_x, const float& move_y,
                   const float& move_z) {
    figure_.move(move_x, move_y, move_z);
  }
  void scale_figure(const float& parameter) { figure_.scale(parameter); }

 private:
  Figure figure_;
};
}  // namespace s21
#endif  // HEADERS_SCENE_H
