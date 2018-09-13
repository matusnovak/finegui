/* This file is part of FineFramework project */
#ifndef FFW_GUI_STYLE
#define FFW_GUI_STYLE

#include <map>
#include <limits>
#include "./config.h"
#include "color.h"
#include "point.h"

namespace ffw {
    /**
    * @ingroup gui
    */
    enum class GuiAlign {
        LEFT = 0,
        CENTER,
        RIGHT,
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT,
    };
    /**
    * @ingroup gui
    */
    class GuiUnits {
    public:
        enum Type {
            PERCENT,
            PIXELS,
            WRAP,
        };
        inline GuiUnits() :value(0) {
            
        }
        inline GuiUnits(float val, bool percentage) :value(percentage ? -val : val) {
            
        }
        inline GuiUnits(float val) :value(val) {
            
        }
        inline bool operator == (const GuiUnits& other) const {
            if (value == std::numeric_limits<float>::infinity() && other.value == std::numeric_limits<float>::infinity())return true;
            return std::fabs(value - other.value) < std::numeric_limits<float>::epsilon();
        }
        inline bool operator != (const GuiUnits& other) const {
            if (value == std::numeric_limits<float>::infinity() && other.value == std::numeric_limits<float>::infinity())return false;
            return std::fabs(value - other.value) >= std::numeric_limits<float>::epsilon();
        }
        inline bool operator == (float v) const {
            return std::fabs(value - v) < std::numeric_limits<float>::epsilon();
        }
        inline bool operator != (float v) const {
            return std::fabs(value - v) >= std::numeric_limits<float>::epsilon();
        }
        inline bool operator == (Type t) const {
            switch(t) {
                case Type::PIXELS: return value >= 0;
                case Type::PERCENT: return value < 0;
                case Type::WRAP: return value == std::numeric_limits<float>::infinity();
                default: break;
            }
            return false;
        }
        inline bool operator != (Type t) const {
            switch(t) {
                case Type::PIXELS: return value < 0;
                case Type::PERCENT: return value >= 0;
                case Type::WRAP: return value != std::numeric_limits<float>::infinity();
                default: break;
            }
            return false;
        }
        inline friend std::ostream& operator << (std::ostream& os, const GuiUnits& V) {
            os << (V.value < 0 ? -V.value : V.value) << (V.value < 0 ? "%" : "px");
            return os;
        }
        inline float toReal(float val) const {
            if (value == std::numeric_limits<float>::infinity())return 0;
            else if (value < 0) {
                return float((-value / 100.0f) * val);
            }
            else {
                return value;
            }
        }
        inline void setPixels(float px) {
            value = px;
        }
        inline void setPercent(float pc) {
            value = -pc;
        }
        inline Type getType() const {
            if (value == std::numeric_limits<float>::infinity())return Type::WRAP;
            if (value < 0)return Type::PERCENT;
            return Type::PIXELS;
        }
        float value;
    };
    inline bool operator == (float left, const GuiUnits& right){
        return std::fabs(right.value - left) < std::numeric_limits<float>::epsilon();
    }
    inline bool operator != (float left, const GuiUnits& right){
        return std::fabs(right.value - left) >= std::numeric_limits<float>::epsilon();
    }
    /**
    * @ingroup gui
    */
    inline GuiUnits guiPixels(float pixels) {
        return GuiUnits(pixels, false);
    }
    /**
    * @ingroup gui
    */
    inline GuiUnits guiPercent(float percent) {
        return GuiUnits(percent, true);
    }
    /**
    * @ingroup gui
    */
    inline GuiUnits guiWrap() {
        return GuiUnits(std::numeric_limits<float>::infinity());
    }
    /**
    * @ingroup gui
    */
    class GuiUnits2D: public ffw::Point<GuiUnits> {
    public:
        GuiUnits2D():ffw::Point<GuiUnits>(guiPixels(0), guiPixels(0)){
        }

        GuiUnits2D(const GuiUnits x, const GuiUnits y):ffw::Point<GuiUnits>(x, y) {
        }

        inline ffw::Pointf toReal(const ffw::Pointf& size) const {
            return ffw::Pointf(x.toReal(size.x), y.toReal(size.y));
        }
    };
    /**
    * @ingroup gui
    */
    class GuiStyle {
    public:
        template <class T>
        class Attribute {
        public:
            inline Attribute() {
                val[0] = T(0);
                val[1] = T(0);
                val[2] = T(0);
                val[3] = T(0);
            }
            inline Attribute(T v) {
                val[0] = v;
                val[1] = v;
                val[2] = v;
                val[3] = v;
            }
            inline Attribute(T top, T right, T bottom, T left) {
                val[0] = top;
                val[1] = right;
                val[2] = bottom;
                val[3] = left;
            }
            inline Attribute(const Attribute& other) {
                val[0] = other.val[0];
                val[1] = other.val[1];
                val[2] = other.val[2];
                val[3] = other.val[3];
            }
            inline Attribute(const std::initializer_list<float>& list) {
                val[0] = *list.begin();
                val[1] = *(list.begin() +1);
                val[2] = *(list.begin() +2);
                val[3] = *(list.begin() +3);
            }
            inline Attribute& operator = (const T& value) {
                val[0] = val[1] = val[2] = val[3] = value;
                return *this;
            }
            inline T& operator [] (size_t i) {
                return val[i];
            }
            inline const T& operator [] (size_t i) const {
                return val[i];
            }
            inline bool operator == (const Attribute& other) const {
                return (val[0] == other.val[0] && val[1] == other.val[1] && val[2] == other.val[2] && val[3] == other.val[3]);
            }
            inline bool operator != (const Attribute& other) const {
                return !(*this == other);
            }
            inline friend std::ostream& operator << (std::ostream& os, const Attribute& a) {
                os << a.val[0] << ", " << a.val[1] << ", " << a.val[2] << ", " << a.val[3] << std::endl;
                return os;
            }
            T val[4];
        };
        class Border {
        public:
            typedef Attribute<float> Size;
            typedef Attribute<float> Radius;
            typedef Attribute<ffw::Color> Color;
            inline Border():
                size(0),radius(0),color(ffw::rgb(0xFFFFFF)) {
            }
            inline Border(const Attribute<float>& s, const Attribute<float>& r, const Attribute<ffw::Color>& c):
                size(s),radius(r),color(c) {
            }
            inline operator bool() const {
                return (size[0] > 0 || size[1] > 0 || size[2] > 0 || size[3] > 0);
            }
            Size size;
            Radius radius;
            Color color;
        };

        typedef Border Outline;
        typedef GuiStyle::Attribute<GuiUnits> Padding;
        typedef GuiStyle::Attribute<GuiUnits> Margin;

        class Background {
        public:
            typedef Attribute<float> Radius;
            enum class Type {
                NONE = 0,
                SIMPLE,
            };
            inline Background():
                radius(0),color(ffw::rgb(0x000000)),type(Type::NONE) {
            }
            inline Background(const ffw::Color& c) :
                radius(0), color(c), type(Type::SIMPLE) {
            }
            inline Background(const Attribute<float>& r, const ffw::Color& c):
                radius(r),color(c),type(Type::SIMPLE) {
            }
            Attribute<float> radius;
            ffw::Color color;
            Type type;
            inline operator bool() const {
                return type != Type::NONE;
            }
        };

        class Text {
        public:
            inline Text():
                color(ffw::rgb(0xFFFFFF)) {
            }
            inline Text(const ffw::Color& c):
                color(c) {
            }
            ffw::Color color;
        };

        class Function {
        public:
            inline Function() :
                color(ffw::rgb(0xFFFFFF)),secondary(ffw::rgb(0xFFFFFF)) {
            }
            inline Function(const ffw::Color& c):
                color(c),secondary(c) {
            }
            inline Function(const ffw::Color& c, const ffw::Color& s) :
                color(c), secondary(s) {
            }
            ffw::Color color;
            ffw::Color secondary;
        };
        inline GuiStyle() {
            
        }
        inline GuiStyle(const Background& b, const Border& br, const Outline& ou, const Text& t, const Function& f):
            background(b),border(br),outline(ou),text(t),function(f){
        }

        Background background;
        Border border;
        Outline outline;
        Text text;
        Function function;
    };
    /**
    * @ingroup gui
    */
    class GuiDefaults {
    public:
        inline GuiDefaults() :
            margin(0), padding(0), align(GuiAlign::TOP_LEFT), size(GuiUnits2D(guiPercent(100), guiWrap())) {
        }
        inline GuiDefaults(const GuiStyle::Margin& m, const GuiStyle::Padding& p, GuiAlign a, const GuiUnits2D& s):
            margin(m),padding(p),align(a),size(s){
        }
        inline GuiDefaults(float m, float p, GuiAlign a, const GuiUnits2D& s) :
            margin(m), padding(p), align(a), size(s) {
        }
        GuiStyle::Margin margin;
        GuiStyle::Padding padding;
        GuiAlign align;
        GuiUnits2D size;
    };
};
#endif