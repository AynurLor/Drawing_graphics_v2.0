#include <cstring>

#include "filereader.hpp"

namespace s21 {
std::pair<ObjectDataModel &, bool> ObjectFileReader::Parse(const char *path) {
  std::pair<ObjectDataModel &, bool> result = {model_, true};
  FILE *file;
  if ((file = fopen(path, "r")) != nullptr) {
    CountVertexesFacets(file);
    model_.AllocateMemory();
    InitializeVertexesIndexes(file);
  } else {
    result.second = false;
  }
  fclose(file);
  return result;
}

void ObjectFileReader::CountVertexesFacets(FILE *file) {
  char line[512] = {0};
  while (fgets(line, 510, file) != nullptr) {
    if (line[0] == 'v' && line[1] == ' ') {
      model_.SetCountVertexes(model_.GetCountVertexes() + 1);
    } else if (line[0] == 'f' && line[1] == ' ') {
      model_.SetCountFacets(model_.GetCountFacets() + 1);
      for (std::size_t i = 0; i != strlen(line); ++i)
        if (line[i] == ' ' && isdigit(line[i + 1]))
          model_.SetCountIndexes(model_.GetCountIndexes() + 1);
    }
  }
  model_.SetCountIndexes(model_.GetCountIndexes() * 2);
  fseek(file, 0, SEEK_SET);
}

void ObjectFileReader::InitializeVertexesIndexes(FILE *file) {
  char line[512] = {0};
  int current_vertex = 0, current_index = 0;
  while ((fgets(line, sizeof(line), file)) != nullptr) {
    if (line[0] == 'v' && line[1] == ' ') {
      InitializeVertexes(line, &current_vertex);
    } else if (line[0] == 'f' && line[1] == ' ') {
      InitializeIndexes(line, &current_index);
    }
  }
}

void ObjectFileReader::InitializeVertexes(char *line, int *current_index) {
  sscanf(line, "v %f %f %f", &model_.GetVertexes()[*current_index],
         &model_.GetVertexes()[*current_index + 1],
         &model_.GetVertexes()[*current_index + 2]);
  *current_index += 3;
}

void ObjectFileReader::InitializeIndexes(char *line, int *current_index) {
  int stored_value = 0, first_value = 0, current_value = 0;
  for (std::size_t i = 0; i < strlen(line); i++) {
    if (line[i] == ' ' && isdigit(line[i + 1])) {
      current_value += 1;
      char *value = &line[i];
      while (isdigit(line[i])) {
        i++;
        value++;
        value = &line[i];
      }
      stored_value = atoi(value) - 1;
      model_.GetIndexes()[*current_index] = stored_value;

      if (current_value == 1) {
        first_value = stored_value;
        (*current_index) += 1;
      } else {
        model_.GetIndexes()[++(*current_index)] = stored_value;
        (*current_index) += 1;
      }
    }
  }
  model_.GetIndexes()[(*current_index)++] = first_value;
}
}  // namespace s21
