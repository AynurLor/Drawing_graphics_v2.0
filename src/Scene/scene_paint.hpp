#ifndef CPP4_3DVIEWER_V2_0_0_SCENE_SCENE_PAINT_HPP_
#define CPP4_3DVIEWER_V2_0_0_SCENE_SCENE_PAINT_HPP_

#include <QOpenGLWidget>

#include "../ObjectDataModel/objectdatamodel.hpp"
#include "scene_style.hpp"

namespace s21 {
class ScenePaint : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit ScenePaint(QWidget *parent = nullptr);
  ~ScenePaint();

  void InitModel(s21::ObjectDataModel &);
  void InitStyle(s21::SceneStyle &);
  s21::ObjectDataModel *GetModel() { return model; };

 private:
  s21::ObjectDataModel *model;
  s21::SceneStyle *style;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};
}  // end namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_SCENE_SCENE_PAINT_HPP_
