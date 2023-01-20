#ifndef CPP4_3DVIEWER_V2_0_0_FACADECONTROLLER_FACADECONTROLLER_HPP
#define CPP4_3DVIEWER_V2_0_0_FACADECONTROLLER_FACADECONTROLLER_HPP

#include "../FacadeModel/facademodel.hpp"

namespace s21 {
class FacadeController {
 private:
  FacadeModel *model_;

 public:
  explicit FacadeController(FacadeModel *model) : model_(model) {}
  ~FacadeController() = default;

  void LoadAndDraw(const std::string &path, ScenePaint *scene) {
    model_->LoadObjectModelAndDraw(path, scene);
  }

  void InitStyleScene(ScenePaint *scene, SceneStyle *style) {
    model_->InitSceneStyle(scene, style);
  }

  void RotateModel(ScenePaint *scene, float x = 0.0f, float y = 0.0f,
                   float z = 0.0f) {
    model_->Rotate(scene, x, y, z);
  }

  void ScaleModel(ScenePaint *scene, float x = 0.0f, float y = 0.0f,
                  float z = 0.0f) {
    model_->Scale(scene, x, y, z);
  }

  void MoveModel(ScenePaint *scene, float x = 0.0f, float y = 0.0f,
                 float z = 0.0f) {
    model_->Move(scene, x, y, z);
  }

  void SetModelNormalizeParameter(float n) { model_->SetNormalizeParameter(n); }

  void SetModelReadStrategy(BaseFileReader *reader) {
    model_->SetReadStrategy(reader);
  }

  void RecordImageFromScene(ScenePaint *scene, bool x = true) {
    model_->RecordImage(scene, x);
  }

  void RecordGifFromScene(ScenePaint *scene, bool x = true) {
    model_->RecordGif(scene, x);
  }

  void Reset() { model_->Reset(); }

  const ObjectDataModel &GetDataModel() { return model_->GetModel(); }
  std::string GetPath() const { return model_->GetPath(); }
};
}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_FACADECONTROLLER_FACADECONTROLLER_HPP
