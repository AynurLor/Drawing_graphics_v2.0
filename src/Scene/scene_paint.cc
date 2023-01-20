#define GL_SILENCE_DEPRECATION

#include "./scene_paint.hpp"

#include <QDebug>

using namespace s21;

ScenePaint::ScenePaint(QWidget *parent) : QOpenGLWidget{parent} {
  style = new SceneStyle();
}

ScenePaint::~ScenePaint() { delete style; }

void ScenePaint::InitModel(ObjectDataModel &m) {
  model = &m;
  repaint();
}

void ScenePaint::InitStyle(SceneStyle &s) {
  style->point_type = s.point_type;
  style->rib_type = s.rib_type;
  style->projection = s.projection;
  style->rib_size = s.rib_size;
  style->vertex_size = s.vertex_size;

  style->bg_color[0] = s.bg_color[0];
  style->bg_color[1] = s.bg_color[1];
  style->bg_color[2] = s.bg_color[2];

  style->rib_color[0] = s.rib_color[0];
  style->rib_color[1] = s.rib_color[1];
  style->rib_color[2] = s.rib_color[2];

  style->vertex_color[0] = s.vertex_color[0];
  style->vertex_color[1] = s.vertex_color[1];
  style->vertex_color[2] = s.vertex_color[2];
  style->line_type = 0xFFFFl;
  if (s.rib_type == 1) {
    style->line_type = 0x3F07;
  }

  repaint();
  update();
}

void ScenePaint::initializeGL() {
  glClearColor(style->bg_color[0], style->bg_color[1], style->bg_color[2], 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void ScenePaint::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);

  float aspected_widget_width = w / 120;
  float aspected_widget_height = h / 120;
  float widget_left = -aspected_widget_width / 2;
  float widget_right = aspected_widget_width / 2;
  float widget_bottom = -aspected_widget_height / 2;
  float widget_top = aspected_widget_height / 2;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (style->projection) {
    glOrtho(widget_left, widget_right, widget_bottom, widget_top, -10, 10);
  } else {
    glFrustum(-2, 2, -1.5, 1.5, -1, 100);
  }
}

void ScenePaint::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(style->bg_color[0], style->bg_color[1], style->bg_color[2], 1.0);

  glLineStipple(1, style->line_type);
  glEnable(GL_LINE_STIPPLE);
  glVertexPointer(3, GL_FLOAT, 0, model->GetVertexes());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (style->point_type != 0) {
    if (style->point_type == 1) {
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_BLEND);
    }
    glPointSize(style->vertex_size);
    glColor3f(style->vertex_color[0], style->vertex_color[1],
              style->vertex_color[2]);
    glDrawElements(GL_POINTS, model->GetCountIndexes(), GL_UNSIGNED_INT,
                   model->GetIndexes());
  }
  glLineWidth(style->rib_size);
  glColor3f(style->rib_color[0], style->rib_color[1], style->rib_color[2]);
  glDrawElements(GL_LINES, model->GetCountIndexes(), GL_UNSIGNED_INT,
                 model->GetIndexes());
  glDisableClientState(GL_VERTEX_ARRAY);
}
