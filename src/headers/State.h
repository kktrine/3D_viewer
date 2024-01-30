#ifndef HEADERS_STATE_H
#define HEADERS_STATE_H
#include <iostream>

using std::string;
namespace s21 {
class StateOperationResult {
 public:
  virtual string get_info() const noexcept = 0;
  virtual void set_info(const string& filename, const string& vertex,
                        const string& facets = string()) noexcept = 0;
  virtual ~StateOperationResult(){};

 protected:
  string filename_;
};

class NormalState : public StateOperationResult {
 public:
  static NormalState* get_instance() {
    if (normal_state_instance_ == nullptr) {
      normal_state_instance_ = new NormalState;
    }
    return normal_state_instance_;
  };
  string get_info() const noexcept override;
  void set_info(const string& filename, const string& vertex,
                const string& facets = string()) noexcept override;

 private:
  NormalState(){};
  string vertexes_;
  string facets_;
  static NormalState* normal_state_instance_;
};

class ErrorState : public StateOperationResult {
 public:
  static ErrorState* get_instance() {
    if (error_state_instance_ == nullptr) {
      error_state_instance_ = new ErrorState;
    }
    return error_state_instance_;
  };
  string get_info() const noexcept override;
  void set_info(const string& filename, const string& error,
                const string& error_type = string()) noexcept override;

 private:
  ErrorState(){};
  string error_message_;
  string error_type;
  static ErrorState* error_state_instance_;
};
}  // namespace s21
#endif  // HEADERS_STATE_H
