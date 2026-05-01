#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Vec2 {
  float x, y;
  Vec2() : x(0.0f), y(0.0f) {}
  Vec2(float x, float y) : x(x), y(y) {}
};

struct Vec2i {
  int x, y;
  Vec2i() : x(0), y(0) {}
  Vec2i(int x, int y) : x(x), y(y) {}
  bool operator==(const Vec2i& other) const {
    return x == other.x && y == other.y;
  }
};

struct Vec3 {
  float r, g, b;
  Vec3() : r(0.0f), g(0.0f), b(0.0f) {}
  Vec3(float r, float g, float b) : r(r), g(g), b(b) {}
};

#endif
