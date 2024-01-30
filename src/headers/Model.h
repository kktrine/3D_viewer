#ifndef HEADERS_MODEL_H
#define HEADERS_MODEL_H
#include <cmath>

#include "Reader.h"
#include "Scene.h"
#include "State.h"

using std::string;
namespace s21 {
class Model {
 public:
  Model();
  ~Model();
  string get_state_info() const noexcept { return state_->get_info(); }
  void set_info(const string& filename, const string& vertexes,
                const string& indexes) noexcept {
    ChangeState(NormalState::get_instance());
    return state_->set_info(filename, vertexes, indexes);
  }
  void set_info(const string& filename, const string& error_message) noexcept {
    ChangeState(ErrorState::get_instance());
    return state_->set_info(filename, error_message);
  }
  void ReadScene(const string& path);
  const vector<float>& get_vertexes() {
    return scene_->get_figure().get_vertexes();
  };
  const vector<unsigned>& get_facets() {
    return scene_->get_figure().get_facets();
  }
  const size_t& get_count_vertexes() noexcept {
    return scene_->get_figure().get_count_vertexes();
  }
  const size_t& get_count_facets() noexcept {
    return scene_->get_figure().get_count_facets();
  }
  void rotate(float& x, float& y, float& z) { scene_->rotate_figure(x, y, z); }
  void move(const float& x, const float& y, const float& z) {
    scene_->move_figure(x, y, z);
  }
  void scale(const float& parameter) { scene_->scale_figure(parameter); }

 private:
  StateOperationResult* state_;
  BaseFileReader* reader_;
  Scene* scene_;

  void ChangeState(StateOperationResult* new_state) noexcept {
    state_ = new_state;
  }
};
}  // namespace s21
#endif  // HEADERS_MODEL_H
