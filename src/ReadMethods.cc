#include "headers/Model.h"
#include "headers/Reader.h"

namespace s21 {
Scene* FileReader::ReadScene(const string& path, StateOperationResult* state) {
  ifstream obj_file(path);
  if (!obj_file.is_open()) {
    string error_message = "Не удалось открыть файл";
    state->set_info(path, error_message);
    throw invalid_argument(error_message);
  }
  string line = "";
  vector<float> vertexes;
  vector<unsigned> facets;
  size_t facets_size = 0;
  while (getline(obj_file, line)) {
    std::istringstream stream_line(line);
    std::string type;
    getline(stream_line, type, ' ');
    if (type == "v") {
      parsing_vertex(stream_line, vertexes);

    } else if (type == "f") {
      parsing_facets(stream_line, facets, facets_size);
    }
  }
  obj_file.close();
  float max = 0.;
  for (const float& i : vertexes)
    if (fabs(i) > max) max = fabs(i);
  if (max > 1.)
    for (float& i : vertexes) i /= max / 3;
  Figure figure(vertexes, facets);
  size_t vertexes_size = vertexes.size() / 3;
  figure.set_count_vertexes(vertexes_size);
  figure.set_count_facets(facets_size);
  state->set_info(path, to_string(vertexes_size), to_string(facets_size / 2));
  Scene* scene = new Scene(figure);
  return scene;
}

void FileReader::parsing_vertex(istringstream& stream,
                                vector<float>& vertexes) noexcept {
  string number_line;

  while (stream >> number_line) {
    vertexes.push_back(stof(number_line));
  }
}

void FileReader::parsing_facets(istringstream& stream, vector<unsigned>& facets,
                                size_t& facets_size) noexcept {
  string number_line;
  bool first_element_flag = true;
  unsigned first_element = 0;
  while (stream >> number_line) {
    facets.push_back(stoi(number_line) - 1);
    facets_size += 2;
    if (first_element_flag) {
      first_element = (stoi(number_line) - 1);
      first_element_flag = false;
      continue;
    }
    facets.push_back(stoi(number_line) - 1);
  }
  facets.push_back(first_element);
}
}  // namespace s21