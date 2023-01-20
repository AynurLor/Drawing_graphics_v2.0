#ifndef CPP4_3DVIEWER_V2_0_0_VIEW_VIEW_H
#define CPP4_3DVIEWER_V2_0_0_VIEW_VIEW_H

#include <QMainWindow>
#include <QSettings>
#include <QVector2D>

#include "../FacadeController/facadecontroller.hpp"
#include "../RecordModel/recordmodel.hpp"
#include "../Scene/scene_paint.hpp"
#include "../Scene/scene_style.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

  void ReadSettings();
  void SaveSettings();
  void SaveDefaultSettings();

 private slots:
  void on_action_mainwinow_triggered();
  void on_action_scene_triggered();
  void on_pushButton_load_clicked();
  void on_action_scenesettings_triggered();
  void on_action_imagemodel_triggered();
  void on_action_gifmodel_triggered();
  void on_action_modelinfo_triggered();
  void on_pushButton_easteregg_clicked();
  void on_action_aboutprogram_triggered();

  void on_pushButton_rib_color_clicked();
  void on_pushButton_vertex_color_clicked();
  void on_pushButton_bg_color_clicked();
  void on_pushButton_accept_clicked();

 private:
  Ui::View *ui;

  s21::FacadeController *controller_;
  s21::FacadeModel *model_;
  s21::RecordModel *recorder_;

  bool model_is_inited_{false};
  bool smth_is_happend_{false};
  QVector2D mouse_last_pos_;
  QPoint old_window_pos_;
  s21::SceneStyle *scene_style_;
  QSettings *settings;

  void InitStyleFromSettings();

 protected:
  void wheelEvent(QWheelEvent *);
  void keyPressEvent(QKeyEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void closeEvent(QCloseEvent *);
  void moveEvent(QMoveEvent *);
  void resizeEvent(QResizeEvent *);
};
#endif  // !CPP4_3DVIEWER_V2_0_0_VIEW_VIEW_H
