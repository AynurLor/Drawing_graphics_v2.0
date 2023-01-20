#ifndef CPP4_3DVIEWER_V2_0_0_NORMALIZATIONPARAMETERS_NORMALIZATIONPARAMETERS_HPP
#define CPP4_3DVIEWER_V2_0_0_NORMALIZATIONPARAMETERS_NORMALIZATIONPARAMETERS_HPP

#include "../ObjectDataModel/objectdatamodel.hpp"

namespace s21 {
class NormalizationParameters {
 private:
  NormalizationParameters() = default;
  static NormalizationParameters *normalization_;

 public:
  NormalizationParameters(const NormalizationParameters &) = delete;
  void operator=(const NormalizationParameters &) = delete;

  static NormalizationParameters *connect() {
    if (normalization_ == nullptr) {
      normalization_ = new NormalizationParameters();
    }
    return normalization_;
  }

  void Normalize(ObjectDataModel &model, float normalize_to) {
    auto vertexes = model.GetVertexes();
    float max = vertexes[0];
    for (int i = 1; i != model.GetCountVertexes() * 3; ++i)
      if (vertexes[i] > max) max = vertexes[i];
    float aspect = max / normalize_to;

    for (int i = 0; i != model.GetCountVertexes() * 3; ++i)
      model.GetVertexes()[i] /= aspect;
  }
};
}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_NORMALIZATIONPARAMETERS_NORMALIZATIONPARAMETERS_HPP
