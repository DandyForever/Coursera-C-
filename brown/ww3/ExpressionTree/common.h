#pragma once

#include <memory>
#include <string>

// Р‘Р°Р·РѕРІС‹Р№ РєР»Р°СЃСЃ Р°СЂРёС„РјРµС‚РёС‡РµСЃРєРѕРіРѕ РІС‹СЂР°Р¶РµРЅРёСЏ
class Expression {
public:
    virtual ~Expression() = default;

    // Р’С‹С‡РёСЃР»СЏРµС‚ Р·РЅР°С‡РµРЅРёРµ РІС‹СЂР°Р¶РµРЅРёСЏ
    virtual int Evaluate() const = 0;

    // Р¤РѕСЂРјР°С‚РёСЂСѓРµС‚ РІС‹СЂР°Р¶РµРЅРёРµ РєР°Рє СЃС‚СЂРѕРєСѓ
    // РљР°Р¶РґС‹Р№ СѓР·РµР» Р±РµСЂС‘С‚СЃСЏ РІ СЃРєРѕР±РєРё, РЅРµР·Р°РІРёСЃРёРјРѕ РѕС‚ РїСЂРёРѕСЂРёС‚РµС‚Р°
    virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

// Р¤СѓРЅРєС†РёРё РґР»СЏ С„РѕСЂРјРёСЂРѕРІР°РЅРёСЏ РІС‹СЂР°Р¶РµРЅРёСЏ
ExpressionPtr Value(int value);
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);