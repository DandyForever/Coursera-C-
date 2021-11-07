#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

// РћРїСЂРµРґРµР»РёС‚Рµ РєР»Р°СЃСЃС‹ Unit, Building, Tower Рё Fence С‚Р°Рє, С‡С‚РѕР±С‹ РѕРЅРё РЅР°СЃР»РµРґРѕРІР°Р»РёСЃСЊ РѕС‚
// GameObject Рё СЂРµР°Р»РёР·РѕРІС‹РІР°Р»Рё РµРіРѕ РёРЅС‚РµСЂС„РµР№СЃ.

class Unit: public GameObject {
public:
    explicit Unit(geo2d::Point position): geometry(position) {}

    bool Collide(const GameObject& that) const override {
        return that.CollideWith(*this);
    }
    bool CollideWith(const Unit& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
    geo2d::Point GetGeometry() const { return geometry; }

private:
    geo2d::Point geometry;
};

class Building: public GameObject {
public:
    explicit Building(geo2d::Rectangle geometry): geometry(geometry) {}

    bool Collide(const GameObject& that) const override {
        return that.CollideWith(*this);
    }
    bool CollideWith(const Unit& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Building& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;

    geo2d::Rectangle GetGeometry() const { return geometry; }

private:
    geo2d::Rectangle geometry;
};

class Tower: public GameObject {
public:
    explicit Tower(geo2d::Circle geometry): geometry(geometry) {}

    bool Collide(const GameObject& that) const override {
        return that.CollideWith(*this);
    }
    bool CollideWith(const Unit& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Building& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Tower& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Fence& that) const override;
    
    geo2d::Circle GetGeometry() const { return geometry; }

private:
    geo2d::Circle geometry;
};

class Fence: public GameObject {
public:
    explicit Fence(geo2d::Segment geometry): geometry(geometry) {}

    bool Collide(const GameObject& that) const override {
        return that.CollideWith(*this);
    }
    bool CollideWith(const Unit& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Building& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Tower& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    bool CollideWith(const Fence& that) const override {
        return geo2d::Collide(geometry, that.GetGeometry());
    }
    geo2d::Segment GetGeometry() const { return geometry; }

private:
    geo2d::Segment geometry;
};

bool Unit::CollideWith(const Building& that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Unit::CollideWith(const Tower& that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Unit::CollideWith(const Fence& that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Building::CollideWith(const Tower& that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Building::CollideWith(const Fence& that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

bool Tower::CollideWith(const Fence& that) const {
    return geo2d::Collide(geometry, that.GetGeometry());
}

// Р РµР°Р»РёР·СѓР№С‚Рµ С„СѓРЅРєС†РёСЋ Collide РёР· С„Р°Р№Р»Р° GameObject.h

bool Collide(const GameObject& first, const GameObject& second) {
    return second.Collide(first);
}

void TestAddingNewObjectOnMap() {
    // Р®РЅРёС‚-С‚РµСЃС‚ РјРѕРґРµР»РёСЂСѓРµС‚ СЃРёС‚СѓР°С†РёСЋ, РєРѕРіРґР° РЅР° РёРіСЂРѕРІРѕР№ РєР°СЂС‚Рµ СѓР¶Рµ РµСЃС‚СЊ РєР°РєРёРµ-С‚Рѕ РѕР±СЉРµРєС‚С‹,
    // Рё РјС‹ С…РѕС‚РёРј РґРѕР±Р°РІРёС‚СЊ РЅР° РЅРµС‘ РЅРѕРІС‹Р№, РЅР°РїСЂРёРјРµСЂ, РїРѕСЃС‚СЂРѕРёС‚СЊ РЅРѕРІРѕРµ Р·РґР°РЅРёРµ РёР»Рё Р±Р°С€РЅСЋ.
    // РњС‹ РјРѕР¶РµРј РµРіРѕ РґРѕР±Р°РІРёС‚СЊ, С‚РѕР»СЊРєРѕ РµСЃР»Рё РѕРЅ РЅРµ РїРµСЂРµСЃРµРєР°РµС‚СЃСЏ РЅРё СЃ РѕРґРЅРёРј РёР· СЃСѓС‰РµСЃС‚РІСѓСЋС‰РёС….
    using namespace geo2d;

    const vector<shared_ptr<GameObject>> game_map = {
            make_shared<Unit>(Point{3, 3}),
            make_shared<Unit>(Point{5, 5}),
            make_shared<Unit>(Point{3, 7}),
            make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
            make_shared<Tower>(Circle{Point{9, 4}, 1}),
            make_shared<Tower>(Circle{Point{10, 7}, 1}),
            make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
    };

    for (size_t i = 0; i < game_map.size(); ++i) {
        Assert(
                Collide(*game_map[i], *game_map[i]),
                "An object doesn't collide with itself: " + to_string(i)
        );

        for (size_t j = 0; j < i; ++j) {
            Assert(
                    !Collide(*game_map[i], *game_map[j]),
                    "Unexpected collision found " + to_string(i) + ' ' + to_string(j)
            );
        }
    }

    auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
    ASSERT(!Collide(*new_warehouse, *game_map[0]));
    ASSERT( Collide(*new_warehouse, *game_map[1]));
    ASSERT(!Collide(*new_warehouse, *game_map[2]));
    ASSERT( Collide(*new_warehouse, *game_map[3]));
    ASSERT( Collide(*new_warehouse, *game_map[4]));
    ASSERT(!Collide(*new_warehouse, *game_map[5]));
    ASSERT(!Collide(*new_warehouse, *game_map[6]));

    auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
    ASSERT(!Collide(*new_defense_tower, *game_map[0]));
    ASSERT(!Collide(*new_defense_tower, *game_map[1]));
    ASSERT(!Collide(*new_defense_tower, *game_map[2]));
    ASSERT( Collide(*new_defense_tower, *game_map[3]));
    ASSERT( Collide(*new_defense_tower, *game_map[4]));
    ASSERT(!Collide(*new_defense_tower, *game_map[5]));
    ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestAddingNewObjectOnMap);
    return 0;
}