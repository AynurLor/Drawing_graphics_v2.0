#ifndef CPP4_3DVIEWER_V2_0_0_TRANSFORMMODEL_TRANSFORMMODEL_HPP
#define CPP4_3DVIEWER_V2_0_0_TRANSFORMMODEL_TRANSFORMMODEL_HPP

#include <cmath>

#include "../ObjectDataModel/objectdatamodel.hpp"

namespace s21 {
class TransformModel {
 private:
  TransformModel() = default;
  static TransformModel *transform_;

 public:
  TransformModel(const TransformModel &) = delete;
  void operator=(const TransformModel &) = delete;

  static TransformModel *connect() {
    if (transform_ == nullptr) {
      transform_ = new TransformModel();
    }
    return transform_;
  }

  void Scale(ObjectDataModel &model, float x, float y, float z) {
    if (x != 0 && y != 0 && z != 0) {
      for (auto i = 0; i != model.GetCountVertexes() * 3; ++i) {
        if (i % 3 == 0)
          model.GetVertexes()[i] *= x;
        else if (i == 1 || i % 3 == 1)
          model.GetVertexes()[i] *= y;
        else if (i == 2 || i % 3 == 2)
          model.GetVertexes()[i] *= z;
      }
    }
  }

  void Move(ObjectDataModel &model, float x, float y, float z) {
    for (auto i = 0; i != model.GetCountVertexes() * 3; ++i) {
      if (i % 3 == 0)
        model.GetVertexes()[i] += x;
      else if (i == 1 || i % 3 == 1)
        model.GetVertexes()[i] += y;
      else if (i == 2 || i % 3 == 2)
        model.GetVertexes()[i] += z;
    }
  }

  void Rotate(ObjectDataModel &model, float x, float y, float z) {
    float temp_x = 0.0f, temp_y = 0.0f, temp_z = 0.0f;
    for (auto i = 0; i < model.GetCountVertexes() * 3; i += 3) {
      if (x != 0.0f) {
        temp_x = model.GetVertexes()[i + 0];
        temp_y = model.GetVertexes()[i + 1];
        temp_z = model.GetVertexes()[i + 2];

        model.GetVertexes()[i + 0] = temp_x;
        model.GetVertexes()[i + 2] =
            std::sin(x) * temp_y + std::cos(x) * temp_z;
        model.GetVertexes()[i + 1] =
            std::cos(x) * temp_y - std::sin(x) * temp_z;
      }
      if (y != 0.0f) {
        temp_x = model.GetVertexes()[i + 0];
        temp_y = model.GetVertexes()[i + 1];
        temp_z = model.GetVertexes()[i + 2];
        model.GetVertexes()[i + 0] =
            std::cos(y) * temp_x + std::sin(y) * temp_z;
        model.GetVertexes()[i + 1] = temp_y;
        model.GetVertexes()[i + 2] =
            -std::sin(y) * temp_x + std::cos(y) * temp_z;
      }
      if (z != 0.0) {
        temp_x = model.GetVertexes()[i + 0];
        temp_y = model.GetVertexes()[i + 1];
        temp_z = model.GetVertexes()[i + 2];

        model.GetVertexes()[i + 0] =
            std::cos(z) * temp_x - std::sin(y) * temp_y;
        model.GetVertexes()[i + 1] =
            std::sin(z) * temp_x + std::cos(z) * temp_y;
        model.GetVertexes()[i + 2] = temp_z;
      }
    }
  }
};
}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_TRANSFORMMODEL_TRANSFORMMODEL_HPP
