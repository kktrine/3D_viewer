#include "headers/Model.h"

namespace s21 {
NormalState* NormalState::normal_state_instance_ = nullptr;
ErrorState* ErrorState::error_state_instance_ = nullptr;

string ErrorState::get_info() const noexcept {
  return this->filename_ + "\n" + this->error_message_;
}

void ErrorState::set_info(const string& filename, const string& error,
                          const string& error_type) noexcept {
  this->filename_ = filename;
  this->error_message_ = error;
  this->error_type = error_type;
}

string NormalState::get_info() const noexcept {
  return this->filename_ + "\nvertexes: " + this->vertexes_ +
         "\nfacets: " + this->facets_;
}

void NormalState::set_info(const string& filename, const string& vertex,
                           const string& facets) noexcept {
  this->filename_ = filename;
  this->vertexes_ = vertex;
  this->facets_ = facets;
}

void Model::ReadScene(const string& path) {
  try {
    if (scene_) {
      delete scene_;
    }
    this->ChangeState(NormalState::get_instance());
    scene_ = reader_->ReadScene(path, state_);

  } catch (const invalid_argument& e) {
    scene_ = new Scene();
    set_info(path, e.what());
  }
}

Model::Model() {
  state_ = NormalState::get_instance();
  reader_ = new FileReader();
  scene_ = new Scene();
}

Model::~Model() {
  delete ErrorState::get_instance();
  delete NormalState::get_instance();
  delete reader_;
  if (scene_) delete scene_;
}
}  // namespace s21