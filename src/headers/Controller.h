#ifndef HEADERS_CONTROLLER_H
#define HEADERS_CONTROLLER_H
#include <vector>

#include "Model.h"
namespace s21 {
class Controller {
 public:
  Controller(){};
  ~Controller(){};
  void ReadFile(const string& path_to_file) { model_.ReadScene(path_to_file); }
  const vector<float>& get_vertexes() { return model_.get_vertexes(); };
  const vector<unsigned>& get_facets() { return model_.get_facets(); }
  const size_t& get_count_vertexes() noexcept {
    return model_.get_count_vertexes();
  }
  const size_t& get_count_facets() noexcept {
    return model_.get_count_facets();
  }
  string get_state_info() const noexcept { return model_.get_state_info(); }
  void rotate(float& x, float& y, float& z) { model_.rotate(x, y, z); }
  void move(const float& x, const float& y, const float& z) {
    model_.move(x, y, z);
  }
  void scale(const float& parameter) { model_.scale(parameter); }

 private:
  Model model_;
};
}  // namespace s21
#endif  // HEADERS_CONTROLLER_H
