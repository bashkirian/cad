#ifndef LINE
#define LINE

#include <cmath>

struct vector2d {
  double x;
  double y;
};

struct vector3d {
  double x;
  double y;
  double z;
};

class Curve {
  protected:
  vector2d center;

  public:
  Curve(double x, double y) {
    center.x = x;
    center.y = y;
  };
  virtual ~Curve() = default;
  virtual vector3d equation(double t) = 0;
  virtual vector3d der1(double t) = 0;
  virtual double GetRadius() = 0;
  
};

class Circle : public Curve {
  double radius;

  public:
  virtual ~Circle() = default;
  Circle(double x0, double y0, double new_radius) : Curve(x0, y0), radius(new_radius) {};
  
  vector3d equation(double t) override {
    return {center.x + radius * cos(t), center.y + radius * sin(t), 0}; // уравнение круга r * cos(t), r * sin(t)
  }

  vector3d der1(double t) override {
    return {-sin(t), cos(t), 0};
  }

  double GetRadius() override {
    return radius;
  }
};

class Ellipse : public Curve {
  private:
  struct EllipseRadiuses {
    double a;
    double b;
  };
  EllipseRadiuses radiuses;

  public:
  virtual ~Ellipse() = default;
  Ellipse(double x0, double y0, double a, double b) : Curve(x0, y0) {
    radiuses.a = a;
    radiuses.b = b;
  };

  vector3d equation(double t) override {
    return { center.x + radiuses.a * sin(t), center.y + radiuses.b * cos(t), 0}; // уравнение эллипса a * cos(t), b * sin(t)
  }

  vector3d der1(double t) override {
    return { radiuses.a * cos(t), -radiuses.b * sin(t), 0};
  }

  double GetRadius() override {
    return radiuses.a + radiuses.b;
  }
};

class Spiral : public Curve {
  double step;
  double radius;
  public:
  virtual ~Spiral() = default;

  Spiral(double x0, double y0, double new_radius, double new_step) : 
    Curve(x0, y0), radius(new_radius), step(new_step) {};

  vector3d equation(double t) override {
    return {center.x + radius * cos(t), center.y + radius * sin(t), step * t};
  };

  vector3d der1(double t) override {
    return {-radius * sin(t), radius * cos(t), step};
  }

  double GetRadius() override {
    return radius;
  }
};

#endif