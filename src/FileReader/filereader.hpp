#ifndef CPP4_3DVIEWER_V2_0_0_FILEREADER_FILEREADER_HPP
#define CPP4_3DVIEWER_V2_0_0_FILEREADER_FILEREADER_HPP

#include <iostream>

#include "../ObjectDataModel/objectdatamodel.hpp"

namespace s21 {
class BaseFileReader {
 public:
  virtual ~BaseFileReader(){};
  virtual std::pair<ObjectDataModel &, bool> Parse(const char *) = 0;
  virtual void Clean() = 0;
};

class FileReader {
 private:
  BaseFileReader *reader_;

 public:
  FileReader(BaseFileReader *reader) : reader_(reader){};
  ~FileReader() { delete reader_; }

  void SetParseStrategy(BaseFileReader *reader) {
    if (reader_ != nullptr) {
      delete reader_;
    }
    reader_ = reader;
  }

  std::pair<ObjectDataModel &, bool> Read(const char *path) {
    return reader_->Parse(path);
  }

  void Reset() { reader_->Clean(); }
};

class ObjectFileReader : public BaseFileReader {
 private:
  ObjectDataModel model_;

 public:
  std::pair<ObjectDataModel &, bool> Parse(const char *path) override;
  ~ObjectFileReader() override { model_.DeallocateMemory(); }

  void Clean() override { model_.Reset(); }

 private:
  void CountVertexesFacets(FILE *file);
  void InitializeVertexesIndexes(FILE *file);
  void InitializeVertexes(char *line, int *current_index);
  void InitializeIndexes(char *line, int *current_index);
};
}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_FILEREADER_FILEREADER_HPP
