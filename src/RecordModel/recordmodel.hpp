#ifndef CPP4_3DVIEWER_V2_0_0_RECORDMODEL_RECORDMODEL_HPP
#define CPP4_3DVIEWER_V2_0_0_RECORDMODEL_RECORDMODEL_HPP

#include "../Scene/scene_paint.hpp"
#include "../TransformModel/transformmodel.hpp"
#include "GifSource/qgifimage.h"

namespace s21 {
class BaseRecordModel {
 public:
  virtual ~BaseRecordModel(){};
  virtual void Entry(ScenePaint *scene, bool x) = 0;
};

class RecordModel {
 private:
  BaseRecordModel *recorder_;

 public:
  RecordModel(BaseRecordModel *recorder) : recorder_(recorder) {}
  ~RecordModel() { delete recorder_; }

  void SetRecordStrategy(BaseRecordModel *recorder) {
    if (recorder_ != nullptr) {
      delete recorder_;
    }
    recorder_ = recorder;
  }

  void Record(ScenePaint *scene, bool x = true) { recorder_->Entry(scene, x); }
};

class ImageRecordModel : public BaseRecordModel {
 public:
  ImageRecordModel() = default;
  ~ImageRecordModel() override{};

  void Entry(ScenePaint *scene, bool x = true) override;
};

class GifRecordModel : public BaseRecordModel {
 public:
  GifRecordModel() = default;
  ~GifRecordModel() override{};

  void Entry(ScenePaint *scene, bool x = true) override;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_0_RECORDMODEL_RECORDMODEL_HPP
