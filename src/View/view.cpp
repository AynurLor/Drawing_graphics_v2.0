#include "view.h"

#include <QAbstractButton>
#include <QColorDialog>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QUrl>
#include <QWheelEvent>

#include "ui_view.h"

#define HOME 0
#define SCENE 1
#define SCENE_SETTINGS 2

s21::NormalizationParameters *s21::NormalizationParameters::normalization_ =
    nullptr;
s21::TransformModel *s21::TransformModel::transform_ = nullptr;

View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), old_window_pos_(pos()) {
  model_ = new s21::FacadeModel(new s21::ObjectFileReader(), 1.0f);
  controller_ = new s21::FacadeController(model_);
  recorder_ = new s21::RecordModel(new s21::ImageRecordModel());
  scene_style_ = new s21::SceneStyle();

  this->setGeometry(QRect(300, 200, 800, 600));

  ui->setupUi(this);

  settings = new QSettings("Tonijerl", "3DViewer", this);
  ReadSettings();
}

View::~View() {
  delete ui;
  delete model_;
  delete controller_;
  delete scene_style_;
}

void View::ReadSettings() {
  setGeometry(settings->value("geometry", QRect(300, 200, 800, 600)).toRect());
  model_is_inited_ = settings->value("model_is_inited", false).toBool();
  if (model_is_inited_) {
    InitStyleFromSettings();
    controller_->LoadAndDraw(
        settings->value("path", "").toString().toStdString(), ui->scene_widget);
    controller_->InitStyleScene(ui->scene_widget, scene_style_);
  }
}

void View::SaveSettings() {
  settings->setValue("geometry", geometry());
  if (model_is_inited_) {
    settings->setValue("path", QString::fromStdString(controller_->GetPath()));
    settings->setValue("model_is_inited", model_is_inited_);

    settings->setValue("vertexSize", scene_style_->vertex_size);
    settings->setValue("ribSize", scene_style_->rib_size);
    settings->setValue("ribType", scene_style_->rib_type);
    settings->setValue("vertexType", scene_style_->vertex_showness);

    settings->setValue("redBG", scene_style_->bg_color[0]);
    settings->setValue("greenBG", scene_style_->bg_color[1]);
    settings->setValue("blueBG", scene_style_->bg_color[2]);
    settings->setValue("redRib", scene_style_->rib_color[0]);
    settings->setValue("greenRib", scene_style_->rib_color[1]);
    settings->setValue("blueRib", scene_style_->rib_color[2]);
    settings->setValue("redVertex", scene_style_->vertex_color[0]);
    settings->setValue("greenVertex", scene_style_->vertex_color[1]);
    settings->setValue("blueVertex", scene_style_->vertex_color[2]);

    settings->setValue("ProectionStatus", scene_style_->projection);
  }
}

void View::SaveDefaultSettings() {
  settings->setValue("geometry", QRect(300, 200, 800, 600));
  settings->setValue("model_is_inited", false);
}

void View::on_action_mainwinow_triggered() {
  ui->stackedWidget->setCurrentIndex(HOME);
}

void View::on_action_scene_triggered() {
  if (model_is_inited_) {
    ui->stackedWidget->setCurrentIndex(SCENE);
  } else {
    QMessageBox::information(this, "3DViewer_2.0",
                             "You should to load the model!");
  }
}

void View::on_pushButton_load_clicked() {
  QString path =
      QFileDialog::getOpenFileName(0, "Select .obj file", "/Users/", "*.obj");
  if (!path.isEmpty()) {
    controller_->Reset();
    controller_->LoadAndDraw(path.toStdString(), ui->scene_widget);
    on_pushButton_accept_clicked();
    model_is_inited_ = true;
  } else {
    model_is_inited_ = false;
    if (QRect(300, 200, 800, 600) != geometry()) {
      smth_is_happend_ = true;
    } else {
      smth_is_happend_ = false;
    }
  }
}

void View::wheelEvent(QWheelEvent *event) {
  float scale_factor_big = 1.05f;
  float scale_factor_lit = 0.95f;
  if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE) {
    if (event->angleDelta().y() > 0) {
      controller_->ScaleModel(ui->scene_widget, scale_factor_lit,
                              scale_factor_lit, scale_factor_lit);
    }
    if (event->angleDelta().y() < 0) {
      controller_->ScaleModel(ui->scene_widget, scale_factor_big,
                              scale_factor_big, scale_factor_big);
    }
  }
}

void View::keyPressEvent(QKeyEvent *event) {
  float move_factor = 0.1;
  if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE) {
    switch (event->key()) {
      case Qt::Key_Up:
        controller_->MoveModel(ui->scene_widget, 0, move_factor);
        break;
      case Qt::Key_Down:
        controller_->MoveModel(ui->scene_widget, 0, -move_factor);
        break;
      case Qt::Key_Left:
        controller_->MoveModel(ui->scene_widget, -move_factor);
        break;
      case Qt::Key_Right:
        controller_->MoveModel(ui->scene_widget, move_factor);
        break;
      case 16777233:
        controller_->MoveModel(ui->scene_widget, 0, 0, -move_factor);
        break;
      case 16777239:
        controller_->MoveModel(ui->scene_widget, 0, 0, move_factor);
        break;
      default:
        break;
    }
  }
}

void View::mousePressEvent(QMouseEvent *event) {
  if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE &&
      event->buttons() == Qt::LeftButton) {
    mouse_last_pos_ = QVector2D(event->position());
  } else if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE &&
             event->buttons() == Qt::RightButton) {
    mouse_last_pos_ = QVector2D(event->position());
  }
}

void View::mouseMoveEvent(QMouseEvent *event) {
  if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE &&
      event->buttons() == Qt::LeftButton) {
    QVector2D difference = QVector2D(event->position()) - mouse_last_pos_;
    float angle = difference.length() / 128.0f;
    controller_->RotateModel(ui->scene_widget, angle);
  } else if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE &&
             event->buttons() == Qt::RightButton) {
    QVector2D difference = QVector2D(event->position()) - mouse_last_pos_;
    float angle = difference.length() / 128.0f;
    controller_->RotateModel(ui->scene_widget, 0.0f, angle);
  } else if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE &&
             event->buttons() == Qt::MiddleButton) {
    QVector2D difference = QVector2D(event->position()) - mouse_last_pos_;
    float angle = difference.length() / 128.0f;
    controller_->RotateModel(ui->scene_widget, 0.0f, 0.0f, angle);
  }
  mouse_last_pos_ = QVector2D(event->position());
}

void View::on_action_scenesettings_triggered() {
  if (model_is_inited_) {
    ui->stackedWidget->setCurrentIndex(SCENE_SETTINGS);
  }
}

void View::on_action_imagemodel_triggered() {
  if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE) {
    controller_->RecordImageFromScene(ui->scene_widget);
  }
}

void View::on_action_gifmodel_triggered() {
  if (model_is_inited_ && ui->stackedWidget->currentIndex() == SCENE) {
    QMessageBox question(QMessageBox::Question, tr("Задать вращение"),
                         tr("Относительно какой оси вращаем?"),
                         QMessageBox::Yes | QMessageBox::No, this);
    question.addButton("Оси OY", QMessageBox::YesRole);
    question.addButton("Оси OX", QMessageBox::NoRole);
    question.removeButton(question.button(QMessageBox::Yes));
    question.removeButton(question.button(QMessageBox::No));
    auto answer = question.exec();
    if (answer == 0) {
      controller_->RecordGifFromScene(ui->scene_widget, false);
    } else if (answer == 1) {
      controller_->RecordGifFromScene(ui->scene_widget);
    }
  }
}

void View::on_action_modelinfo_triggered() {
  if (model_is_inited_) {
    QString count_of_facets =
        QString::number(controller_->GetDataModel().GetCountFacets());
    QString count_of_vertexes =
        QString::number(controller_->GetDataModel().GetCountVertexes());
    QString name =
        QFileInfo(QString(controller_->GetPath().c_str())).fileName();
    QMessageBox message(QMessageBox::Information, tr("О модели"),
                        "Название модели: " + name + "\n" +
                            "Количество вершин: " + count_of_vertexes + "\n" +
                            "Количество полигонов: " + count_of_facets + "\n");
    message.exec();
  }
}

void View::closeEvent(QCloseEvent *event) {
  if (smth_is_happend_) {
    auto result =
        QMessageBox::question(this, "Закрытие программы",
                              "Хотите ли вы созранить состояние программы?");
    if (result == QMessageBox::Yes) {
      SaveSettings();
    } else {
      SaveDefaultSettings();
    }
  } else {
    SaveDefaultSettings();
  }
  event->accept();
}

void View::moveEvent(QMoveEvent *event) {
  event->accept();
  if (old_window_pos_ == pos()) {
    smth_is_happend_ = false;
  } else {
    smth_is_happend_ = true;
  }
}

void View::resizeEvent(QResizeEvent *event) {
  event->accept();
  if (QRect(300, 200, 800, 600) == geometry() && !model_is_inited_) {
    smth_is_happend_ = false;
  } else {
    smth_is_happend_ = true;
  }
}

void View::on_pushButton_easteregg_clicked() {
  QDesktopServices::openUrl(
      QUrl("https://pikabu.ru/story/nu_poekhali_9197704"));
}

void View::on_action_aboutprogram_triggered() {
  QDesktopServices::openUrl(QUrl("https://github.com/AynurLor"));
  QDesktopServices::openUrl(QUrl("https://github.com/tonitaga"));
}

void View::on_pushButton_rib_color_clicked() {
  QColor ribs = QColorDialog::getColor(Qt::green, this);
  scene_style_->rib_color[0] = ribs.redF();
  scene_style_->rib_color[1] = ribs.greenF();
  scene_style_->rib_color[2] = ribs.blueF();
}

void View::on_pushButton_vertex_color_clicked() {
  QColor vertexes = QColorDialog::getColor(Qt::green, this);
  scene_style_->vertex_color[0] = vertexes.redF();
  scene_style_->vertex_color[1] = vertexes.greenF();
  scene_style_->vertex_color[2] = vertexes.blueF();
}

void View::on_pushButton_bg_color_clicked() {
  QColor bg = QColorDialog::getColor(Qt::black, this);
  scene_style_->bg_color[0] = bg.redF();
  scene_style_->bg_color[1] = bg.greenF();
  scene_style_->bg_color[2] = bg.blueF();
}

void View::on_pushButton_accept_clicked() {
  smth_is_happend_ = true;
  float vertex_size = ui->comboBox_vertex_size->currentText().toFloat();
  float rib_size = ui->comboBox_rib_size->currentText().toFloat();

  scene_style_->rib_size = rib_size;
  scene_style_->vertex_size = vertex_size;

  scene_style_->rib_type = ui->comboBox_rib_type->currentIndex();
  scene_style_->point_type = ui->comboBox_showness->currentIndex();

  switch (ui->combobox_projection->currentIndex()) {
    case 1:
      scene_style_->projection = true;
      break;
    default:
      scene_style_->projection = false;
  }

  controller_->InitStyleScene(ui->scene_widget, scene_style_);
}

void View::InitStyleFromSettings() {
  scene_style_->rib_size = settings->value("ribSize", 0.5f).toFloat();
  scene_style_->vertex_size = settings->value("vertexSize", 2.0f).toFloat();

  scene_style_->rib_type = settings->value("ribType", 0).toInt();
  scene_style_->vertex_showness = settings->value("vertexType", 1).toInt();

  scene_style_->all_accept = true;
  scene_style_->bg_color[0] = settings->value("redBG", 0.6471).toFloat();
  scene_style_->bg_color[1] = settings->value("greenBG", 0.6471).toFloat();
  scene_style_->bg_color[2] = settings->value("blueBG", 0.6471).toFloat();

  scene_style_->rib_color[0] = settings->value("redRib", 0.2194).toFloat();
  scene_style_->rib_color[1] = settings->value("greenRib", 0.0549).toFloat();
  scene_style_->rib_color[2] = settings->value("blueRib", 0.1804).toFloat();

  scene_style_->vertex_color[0] =
      settings->value("redVertex", 0.5451).toFloat();
  scene_style_->vertex_color[1] =
      settings->value("greenVertex", 0.102).toFloat();
  scene_style_->vertex_color[2] =
      settings->value("blueVertex", 0.8588).toFloat();

  scene_style_->projection = settings->value("ProectionStatus", true).toBool();
}
