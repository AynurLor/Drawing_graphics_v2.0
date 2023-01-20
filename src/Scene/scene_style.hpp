#ifndef SCENE_STYLE_H
#define SCENE_STYLE_H

#include "OpenGL/gltypes.h"

namespace s21 {
class SceneStyle {
 public:
  SceneStyle() { InitDefault(); }
  SceneStyle(const SceneStyle &other) = default;
  SceneStyle &operator=(const SceneStyle &other) = default;

  float vertex_color[3];
  float rib_color[3];
  float bg_color[3];
  float vertex_size;
  float rib_size;
  int rib_type;
  int vertex_showness;
  GLushort line_type;
  GLint point_type;
  bool projection;
  bool all_accept;

 private:
  void InitDefault() {
    vertex_color[0] = 0.5451;
    vertex_color[1] = 0.102;
    vertex_color[2] = 0.8588;

    rib_color[0] = 0.2194;
    rib_color[1] = 0.0549;
    rib_color[2] = 0.1804;

    bg_color[0] = 0.6471;
    bg_color[1] = 0.6471;
    bg_color[2] = 0.6471;

    vertex_size = 2.0f;
    rib_size = 0.5f;
    rib_type = 0;
    vertex_showness = 1;

    projection = true;
    all_accept = false;
  }
};
}  // namespace s21

#endif  // SCENE_STYLE_H
