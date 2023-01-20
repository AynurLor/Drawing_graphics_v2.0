#ifndef CPP4_3DVIEWER_V2_0_0_OBJECTDATAMODEL_OBJECTDATAMODEL_HPP
#define CPP4_3DVIEWER_V2_0_0_OBJECTDATAMODEL_OBJECTDATAMODEL_HPP

namespace s21 {
class ObjectDataModel {
 private:
  float *vertexes_;
  int *indexes_;
  int count_vertexes_;
  int count_indexes_;
  int count_facets_;

 public:
  ObjectDataModel()
      : vertexes_(nullptr),
        indexes_(nullptr),
        count_vertexes_(0),
        count_indexes_(0),
        count_facets_(0) {}

  ObjectDataModel(const ObjectDataModel &other)
      : vertexes_(other.vertexes_),
        indexes_(other.indexes_),
        count_vertexes_(other.count_vertexes_),
        count_indexes_(other.count_indexes_),
        count_facets_(other.count_facets_) {}

  ~ObjectDataModel() = default;

  ObjectDataModel &operator=(const ObjectDataModel &other) = default;

  /*===================Public=methods===================*/

  float *GetVertexes() { return vertexes_; }
  int *GetIndexes() { return indexes_; }
  int GetCountVertexes() const { return count_vertexes_; }
  int GetCountIndexes() const { return count_indexes_; }
  int GetCountFacets() const { return count_facets_; }

  void SetCountVertexes(int count) { count_vertexes_ = count; }
  void SetCountIndexes(int count) { count_indexes_ = count; }
  void SetCountFacets(int count) { count_facets_ = count; }

  void AllocateMemory() {
    vertexes_ = new float[count_vertexes_ * 3]();
    indexes_ = new int[count_indexes_]();
  }
  void DeallocateMemory() {
    if (vertexes_ != nullptr) delete[] vertexes_;
    if (indexes_ != nullptr) delete[] indexes_;
  }

  void Reset() {
    DeallocateMemory();
    count_facets_ = 0;
    count_indexes_ = 0;
    count_vertexes_ = 0;
  }
};
}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_OBJECTDATAMODEL_OBJECTDATAMODEL_HPP
