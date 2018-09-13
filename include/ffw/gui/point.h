/* This file is part of FineFramework project */
#ifndef FFW_GUI_POINT
#define FFW_GUI_POINT

#include <ostream>
#include <limits>
#include <cmath>
#include "constants.h"

namespace ffw {
    /**
    * @ingroup gui
    */
    template <class T> struct Point {
    public:
        T x;
        T y;

        inline Point() {
            x = T(0);
            y = T(0);
        }

        inline Point(T compx, T compy) {
            x = compx;
            y = compy;
        }

        inline Point(T Value) {
            x = Value;
            y = Value;
        }

        inline Point(const Point<T>& vec) {
            x = vec.x;
            y = vec.y;
        }

        inline Point(std::initializer_list<T> list) {
            if (list.size() != 2) {
                x = T(0);
                y = T(0);
                return;
            }
            x = *(list.begin());
            y = *(list.begin() + 1);
        }

        inline void set(T compx, T compy) {
            x = compx;
            y = compy;
        }

        inline void set(T Value) {
            x = Value;
            y = Value;
        }

        inline void set(const Point<T>& vec) {
            x = vec.x;
            y = vec.y;
        }

        inline void set(const std::initializer_list<T>& list) {
            if (list.size() == 2) {
                x = *(list.begin());
                y = *(list.begin() + 1);
            }
        }

        inline ffw::Point<T>  operator - () const {
            return Point<T>(-x, -y);
        }

        inline ffw::Point<T>& operator =  (const Point<T>& vec) {
            x = vec.x;
            y = vec.y;
            return *this;
        }

        inline ffw::Point<T>  operator +  (const Point<T>& vec) const {
            return Point<T>(x + vec.x, y + vec.y);
        }

        inline ffw::Point<T>& operator += (const Point<T>& vec) {
            x += vec.x;
            y += vec.y;
            return *this;
        }

        inline ffw::Point<T>  operator -  (const Point<T>& vec) const {
            return Point<T>(x - vec.x, y - vec.y);
        }

        inline ffw::Point<T>& operator -= (const Point<T>& vec) {
            x -= vec.x;
            y -= vec.y;
            return *this;
        }

        inline ffw::Point<T>  operator /  (const Point<T>& vec) const {
            return Point<T>(x / vec.x, y / vec.y);
        }

        inline ffw::Point<T>& operator /= (const Point<T>& vec) {
            x /= vec.x;
            y /= vec.y;
            return *this;
        }

        inline ffw::Point<T>  operator *  (const Point<T>& vec) const {
            return Point<T>(x * vec.x, y * vec.y);
        }

        inline ffw::Point<T>& operator *= (const Point<T>& vec) {
            x *= vec.x;
            y *= vec.y;
            return *this;
        }

        inline ffw::Point<T>& operator =  (const T& val) {
            x = val;
            y = val;
            return *this;
        }

        inline ffw::Point<T>  operator +  (const T& val) const {
            return Point<T>(x + val, y + val);
        }

        inline ffw::Point<T>& operator += (const T& val) {
            x += val;
            y += val;
            return *this;
        }

        inline ffw::Point<T>  operator -  (const T& val) const {
            return Point<T>(x - val, y - val);
        }

        inline ffw::Point<T>& operator -= (const T& val) {
            x -= val;
            y -= val;
            return *this;
        }

        inline ffw::Point<T>  operator /  (const T& val) const {
            return Point<T>(x / val, y / val);
        }

        inline ffw::Point<T>& operator /= (const T& val) {
            x /= val;
            y /= val;
            return *this;
        }

        inline ffw::Point<T>  operator *  (const T& val) const {
            return Point<T>(x * val, y * val);
        }

        inline ffw::Point<T>& operator *= (const T& val) {
            x *= val;
            y *= val;
            return *this;
        }

        inline bool operator != (const Point<T>& vec) const {
            return !(*this == vec);
        }

        inline bool operator == (const Point<T>& vec) const {
            return (x == vec.x && y == vec.y);
        }

        inline ffw::Point<T>& rotate(const double deg) {
            auto v = *this;
            x = T(v.x*std::cos(deg*DEG_TO_RAD) - v.y*std::sin(deg*DEG_TO_RAD));
            y = T(v.x*std::sin(deg*DEG_TO_RAD) + v.y*std::cos(deg*DEG_TO_RAD));
            return *this;
        }

        inline ffw::Point<T>& rotateRad(const double rad) {
            auto v = *this;
            x = T(v.x*std::cos(rad) - v.y*std::sin(rad));
            y = T(v.x*std::sin(rad) + v.y*std::cos(rad));
            return *this;
        }

        inline ffw::Point<T>& normalize() {
            const auto l = sqrtf(x*x + y * y);
            if (l > 0) {
                x = T(x / l);
                y = T(y / l);
            }
            return *this;
        }

        inline ffw::Point<T>& scale(T val) {
            x = x * val;
            y = y * val;
            return *this;
        }

        inline double length() const {
            return sqrt(static_cast<double>(x*x + y * y));
        }

        inline float lengthf() const {
            return sqrtf(static_cast<float>(x*x + y * y));
        }

        inline T lengthSqrd() const {
            return (x*x + y * y);
        }

        T& operator [] (size_t i) {
            return ((T*)&x)[i];
        }

        const T& operator [] (size_t i) const {
            return ((T*)&x)[i];
        }

        template <class S>
        inline operator ffw::Point<S>() const {
            return ffw::Point<S>(S(x), S(y));
        }

        inline Point<T> round() const {
            return Point<T>(std::round(x), std::round(y));
        }

        inline Point<T> floor() const {
            return Point<T>(std::floor(x), std::floor(y));
        }

        inline Point<T> ceil() const {
            return Point<T>(std::ceil(x), std::ceil(y));
        }

#ifdef FFW_VEC4
        inline Point(const Vec2<T>& vec) {
            x = vec.x;
            y = vec.y;
        }

        inline operator Vec2<T>() const {
            return Vec2<T>(x, y);
        }
#endif
    };
    /**
    * @ingroup gui
    */
    typedef Point<float> Pointf;
    /**
    * @ingroup gui
    */
    typedef Point<int> Pointi;
    /**
    * @ingroup gui
    */
    typedef Point<double> Pointd;
    /**
    * @ingroup gui
    */
    template <class T>
    inline T dot(const ffw::Point<T>& v1, const ffw::Point<T>& v2) {
        return (v1.x*v2.x + v1.y*v2.y);
    }
    /**
    * @ingroup gui
    */
    template <class T>
    inline T distance(const Point<T>& v1, const Point<T>& v2) {
        auto v = v2 - v1;
        return static_cast<T>(v.length());
    }
    /**
    * @ingroup gui
    */
    template <class T>
    inline Point<T> middle(const Point<T>& v1, const Point<T>& v2) {
        auto v = (v2 - v1) / 2.0;
        return v1 + v;
    }
    /**
    * @ingroup gui
    */
    template <class T>
    inline ffw::Point<T> normalize(const Point<T>& vec) {
        auto copy = vec;
        copy.normalize();
        return copy;
    }
    /**
    * @ingroup gui
    */
    template <class T>
    inline double angle(const ffw::Point<T>& v1, const ffw::Point<T>& v2) {
        const auto dot = (v1.x*v2.x + v1.y*v2.y);
        const auto v1Length = std::sqrt(v1.x*v1.x + v1.y*v1.y);
        const auto v2Length = std::sqrt(v2.x*v2.x + v2.y*v2.y);
        return static_cast<double>(std::acos(dot / (v1Length*v2Length))*RAD_TO_DEG);
    }
    /**
    * @ingroup gui
    */
    template <class T>
    inline double angleRad(const ffw::Point<T>& v1, const ffw::Point<T>& v2) {
        const auto dot = (v1.x*v2.x + v1.y*v2.y);
        const auto v1Length = std::sqrt(v1.x*v1.x + v1.y*v1.y);
        const auto v2Length = std::sqrt(v2.x*v2.x + v2.y*v2.y);
        return static_cast<double>(std::acos(dot / (v1Length*v2Length)));
    }
    /**
    * @ingroup gui
    */
    template <class T>
    inline std::ostream& operator << (std::ostream& os, const ffw::Point<T>& vec) {
        os << vec.x << ", " << vec.y;
        return os;
    }
};

namespace ffw {
    template<>
    inline bool ffw::Point<float>::operator == (const Point<float>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<float>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<float>::epsilon())return false;
        return true;
    }
    template<>
    inline bool ffw::Point<double>::operator == (const Point<double>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<double>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<double>::epsilon())return false;
        return true;
    }
}

#endif
