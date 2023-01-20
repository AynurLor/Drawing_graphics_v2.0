#include "recordmodel.hpp"

#include <QFileDialog>
#include <QImage>
#include <QString>

#define _USE_MATH_DEFINES
#include <cmath>

namespace s21 {
void ImageRecordModel::Entry(ScenePaint *scene, bool x) {
  (void)x;
  if (!scene->size().isEmpty()) {
    QString path_to_save =
        QFileDialog::getSaveFileName(scene, "Загрузить файл", "/Users/",
                                     "All files (*.*);; JPEG Image (*.jpeg);;"
                                     "BMP Image (*.bmp)");
    scene->grab().save(path_to_save);
  }
}

void GifRecordModel::Entry(ScenePaint *scene, bool x) {
  if (!scene->size().isEmpty()) {
    QImage mp[50];
    QGifImage gif;

    for (int i = 0; i != 50; ++i) {
      mp[i] = scene->grab().toImage();
      if (x) {
        TransformModel::connect()->Rotate(*scene->GetModel(), M_PI / 16.0f, 0,
                                          0);
      } else {
        TransformModel::connect()->Rotate(*scene->GetModel(), 0, M_PI / 16.0f,
                                          0);
      }
      scene->InitModel(*scene->GetModel());
      gif.addFrame(mp[i], 200);
    }

    QString path_to_save =
        QFileDialog::getSaveFileName(scene, "Загрузить файл", "/Users/",
                                     "All Files (*.*);; Gif Image (*.gif);;");
    gif.save(path_to_save);
  }
}
}  // namespace s21
