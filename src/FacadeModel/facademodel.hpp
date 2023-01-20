#ifndef CPP4_3DVIEWER_V2_0_0_FACADEMODEL_FACADEMODEL_HPP
#define CPP4_3DVIEWER_V2_0_0_FACADEMODEL_FACADEMODEL_HPP

#include "../FileReader/filereader.hpp"
#include "../NormalizationParameters/normalizationparameters.hpp"
#include "../ObjectDataModel/objectdatamodel.hpp"
#include "../RecordModel/recordmodel.hpp"
#include "../Scene/scene_paint.hpp"
#include "../Scene/scene_style.hpp"
#include "../TransformModel/transformmodel.hpp"

namespace s21 {
class FacadeModel {
 private:
  FileReader *reader_;
  RecordModel *recorder_;
  ObjectDataModel data_model_{};
  bool model_is_inited_{false};
  float normalize_parameter_;
  std::string path_;

 public:
  /**
   * @param reader Базовый парсер который будет использоваться для чтения файла
   * @param normalize_to Параметр нормализации -
   * если максимальное значение в массиве вершин модели будет равно 100,
   * а normalize_to будет равен 7.0f то максимальное значение станет равным 7.0f
   * и все остальные значения подстроятся
   */
  explicit FacadeModel(BaseFileReader *reader, float normalize_to = 10.0f)
      : reader_(new FileReader(reader)),
        recorder_(new RecordModel(new ImageRecordModel)),
        normalize_parameter_(normalize_to) {}
  ~FacadeModel() {
    delete reader_;
    delete recorder_;
  }

  void LoadObjectModelAndDraw(const std::string &path, ScenePaint *scene) {
    auto result = reader_->Read(path.c_str());
    if (result.second) {
      NormalizationParameters::connect()->Normalize(result.first,
                                                    normalize_parameter_);
      data_model_ = result.first;
      scene->InitModel(data_model_);
      model_is_inited_ = true;
      path_ = path;
    }
  }

  void InitSceneStyle(ScenePaint *scene, SceneStyle *style) {
    scene->InitStyle(*style);
  }

  void RecordImage(ScenePaint *scene, bool x = true) {
    recorder_->SetRecordStrategy(new ImageRecordModel());
    recorder_->Record(scene, x);
  }

  void RecordGif(ScenePaint *scene, bool x = true) {
    recorder_->SetRecordStrategy(new GifRecordModel());
    recorder_->Record(scene, x);
  }

  void Scale(ScenePaint *scene, float x = 1.0f, float y = 1.0f,
             float z = 1.0f) {
    if (model_is_inited_) {
      TransformModel::connect()->Scale(data_model_, x, y, z);
      scene->InitModel(data_model_);
    }
  }

  void Move(ScenePaint *scene, float x = 0.0f, float y = 0.0f, float z = 1.0f) {
    if (model_is_inited_) {
      TransformModel::connect()->Move(data_model_, x, y, z);
      scene->InitModel(data_model_);
    }
  }

  void Rotate(ScenePaint *scene, float x = 0.0f, float y = 0.0f,
              float z = 1.0f) {
    if (model_is_inited_) {
      TransformModel::connect()->Rotate(data_model_, x, y, z);
      scene->InitModel(data_model_);
    }
  }

  void SetNormalizeParameter(float normalize_to) {
    normalize_parameter_ = normalize_to;
  }

  void SetReadStrategy(BaseFileReader *reader) {
    reader_->SetParseStrategy(reader);
  }

  const ObjectDataModel &GetModel() { return data_model_; }
  std::string GetPath() const { return path_; }

  void Reset() { reader_->Reset(); }
};
}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_FACADEMODEL_FACADEMODEL_HPP
