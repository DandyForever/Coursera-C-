#include <string>
#include <cmath>
#include <memory>
#include <iomanip>
#include <sstream>

using namespace std;

class Figure {
public:
    virtual string Name () const = 0;
    virtual double Perimeter () const = 0;
    virtual double Area () const = 0;
};

class Triangle : public Figure {
public:
    explicit Triangle (int a, int b, int c) {
        a_ = a;
        b_ = b;
        c_ = c;
    }
    string Name () const override {
        return "TRIANGLE";
    }

    double Perimeter () const override {
        return a_ + b_ + c_;
    }

    double Area () const override {
        double p = Perimeter() / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    int a_;
    int b_;
    int c_;
};

class Rect : public  Figure {
public:
    explicit Rect (int width, int height) {
        width_ = width;
        height_ = height;
    }

    string Name () const override  {
        return "RECT";
    }

    double Perimeter () const override {
        return 2 * (width_ + height_);
    }

    double Area () const override {
        return width_ * height_;
    }

private:
    int width_;
    int height_;
};

class Circle : public Figure {
public:
    explicit Circle (int r) {
        r_ = r;
    }

    string Name () const override  {
        return "CIRCLE";
    }
    double Perimeter () const override {
        return 2 * 3.14 * r_;
    }
    double Area () const override {
        return 3.14 * r_ * r_;
    }

private:
    int r_;
};

shared_ptr<Figure> CreateFigure (istringstream& is) {
    string type;
    is >> type;
    if (type == "TRIANGLE") {
        int a = 0, b = 0, c = 0;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (type == "RECT") {
        int w = 0, h = 0;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    } else if (type == "CIRCLE") {
        int r = 0;
        is >> r;
        return make_shared<Circle>(r);
    }
}
