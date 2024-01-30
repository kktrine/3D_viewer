#ifndef HEADERS_READER_H
#define HEADERS_READER_H
#include <fstream>
#include <iostream>
#include <sstream>

#include "Scene.h"
#include "State.h"

using std::ifstream;
using std::invalid_argument;
using std::istringstream;
using std::stoi;
using std::string;
using std::to_string;

namespace s21 {
class BaseFileReader {
 public:
  virtual Scene* ReadScene(const string& path, StateOperationResult* state) = 0;
  virtual ~BaseFileReader(){};
};

class FileReader : public BaseFileReader {
 public:
  FileReader(){};
  ~FileReader(){};
  Scene* ReadScene(const string& path, StateOperationResult* state);

 private:
  void parsing_vertex(istringstream& stream, vector<float>& vertexes) noexcept;
  void parsing_facets(istringstream& stream, vector<unsigned>& facets,
                      size_t& facets_size) noexcept;
};
}  // namespace s21
#endif  // HEADERS_READER_H
