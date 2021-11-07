#include <iostream>
#include "Common.h"

using namespace std;

// Р­С‚РѕС‚ С„Р°Р№Р» СЃРґР°С‘С‚СЃСЏ РЅР° РїСЂРѕРІРµСЂРєСѓ
// Р—РґРµСЃСЊ РЅР°РїРёС€РёС‚Рµ СЂРµР°Р»РёР·Р°С†РёСЋ РЅРµРѕР±С…РѕРґРёРјС‹С… РєР»Р°СЃСЃРѕРІ-РїРѕС‚РѕРјРєРѕРІ `IShape`

// РќР°РїРёС€РёС‚Рµ СЂРµР°Р»РёР·Р°С†РёСЋ С„СѓРЅРєС†РёРё

class RectangleShape : public IShape {
public:
    std::unique_ptr<IShape> Clone() const override {
        return make_unique<RectangleShape>(*this);
    }

    void SetPosition(Point position) override {
        position_ = position;
    }
    Point GetPosition() const override {
        return position_;
    }

    void SetSize(Size size) override {
        size_ = size;
    }
    Size GetSize() const override {
        return size_;
    }

    void SetTexture(std::shared_ptr<ITexture> texture) override {
        texture_ = texture;
    }
    ITexture* GetTexture() const override {
        return texture_.get();
    }

    // Р РёСЃСѓРµС‚ С„РёРіСѓСЂСѓ РЅР° СѓРєР°Р·Р°РЅРЅРѕРј РёР·РѕР±СЂР°Р¶РµРЅРёРё
    void Draw(Image& image) const override {
//        std::cout << "Inside draw rect" << std::endl;
        int ps_x = image[0].length(), ps_y = image.size();
        Size picture_size = {ps_x, ps_y};
//        std::cout << "Before loop" << std::endl;
        for (size_t x = position_.x; x < position_.x + size_.width; x++) {
            for (size_t y = position_.y; y < position_.y + size_.height; y++) {
                size_t texture_x = x - position_.x;
                size_t texture_y = y - position_.y;
                if (x < picture_size.width && y < picture_size.height) {
                    if (texture_ && texture_x < texture_->GetSize().width && texture_y < texture_->GetSize().height)
                        image[y][x] = texture_->GetImage()[texture_y][texture_x];
                    else
                        image[y][x] = '.';
                }
            }
        }
    }
private:
    Point position_;
    Size size_;
    std::shared_ptr<ITexture> texture_;
};

class EllipticShape : public IShape {
public:
    std::unique_ptr<IShape> Clone() const override {
        return make_unique<EllipticShape>(*this);
    }

    void SetPosition(Point position) override {
        position_ = position;
    }
    Point GetPosition() const override {
        return position_;
    }

    void SetSize(Size size) override {
        size_ = size;
    }
    Size GetSize() const override {
        return size_;
    }

    void SetTexture(std::shared_ptr<ITexture> texture) override {
        texture_ = texture;
    }
    ITexture* GetTexture() const override {
        return texture_.get();
    }

    // Р РёСЃСѓРµС‚ С„РёРіСѓСЂСѓ РЅР° СѓРєР°Р·Р°РЅРЅРѕРј РёР·РѕР±СЂР°Р¶РµРЅРёРё
    void Draw(Image& image) const override {
//        std::cout << "Inside draw Ellips" << std::endl;
        int ps_x = image[0].length(), ps_y = image.size();
        Size picture_size = {ps_x, ps_y};
//        std::cout << "Before loop" << std::endl;
        for (int x = position_.x; x < position_.x + size_.width; x++) {
            for (int y = position_.y; y < position_.y + size_.height; y++) {
                int texture_x = x - position_.x;
                int texture_y = y - position_.y;
                if (x < picture_size.width && y < picture_size.height) {
                    if (IsPointInEllipse({texture_x, texture_y}, size_)) {
//                        std::cout << texture_->GetSize().width << " " << texture_->GetSize().height << std::endl;
                        if (texture_ && texture_x < texture_->GetSize().width && texture_y < texture_->GetSize().height)
                            image[y][x] = texture_->GetImage()[texture_y][texture_x];
                        else
                            image[y][x] = '.';
                    }
                }
            }
        }
    }
private:
    Point position_;
    Size size_;
    std::shared_ptr<ITexture> texture_;
};

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case (ShapeType::Rectangle):
            return make_unique<RectangleShape>();
            break;
        case (ShapeType::Ellipse):
            return make_unique<EllipticShape>();
            break;
    }
}