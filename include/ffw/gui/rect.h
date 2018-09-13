/* This file is part of FineFramework project */
#ifndef FFW_GUI_RECT
#define FFW_GUI_RECT

#include <ostream>
#include <limits>
#include <cmath>

namespace ffw {
    /**
    * @ingroup gui
    */
    template <class T> struct Rect {
    public:
        T x;
        T y;
        T z;
        T w;

        inline Rect() {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        inline Rect(T compx, T compy, T compz, T compw) {
            x = compx;
            y = compy;
            z = compz;
            w = compw;
        }

        inline Rect(T val) {
            x = val;
            y = val;
            z = val;
            w = val;
        }

        inline Rect(const Rect<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

        inline Rect(const std::initializer_list<T>& list) {
            if (list.size() != 4) {
                x = 0;
                y = 0;
                z = 0;
                w = 0;
                return;
            }
            x = *(list.begin());
            y = *(list.begin() + 1);
            z = *(list.begin() + 2);
            w = *(list.begin() + 3);
        }

        inline void set(T compx, T compy, T compz, T compw) {
            x = compx;
            y = compy;
            z = compz;
            w = compw;
        }

        inline void set(T val) {
            x = val;
            y = val;
            z = val;
            w = val;
        }

        inline void set(const Rect<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

        inline void set(const std::initializer_list<T>& list) {
            if (list.size() != 4)return;
            x = *(list.begin());
            y = *(list.begin() + 1);
            z = *(list.begin() + 2);
            w = *(list.begin() + 3);
        }

        inline ffw::Rect<T>  operator - () const {
            return Rect<T>(-x, -y, -z, -w);
        }

        inline ffw::Rect<T>& operator =  (const Rect<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
            return *this;
        }

        inline ffw::Rect<T>  operator +  (const Rect<T>& vec) const {
            return Rect<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
        }

        inline ffw::Rect<T>& operator += (const Rect<T>& vec) {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            w += vec.w;
            return *this;
        }

        inline ffw::Rect<T>  operator -  (const Rect<T>& vec) const {
            return Rect<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
        }

        inline ffw::Rect<T>& operator -= (const Rect<T>& vec) {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            w -= vec.w;
            return *this;
        }

        inline ffw::Rect<T>  operator /  (const Rect<T>& vec) const {
            return Rect<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
        }

        inline ffw::Rect<T>& operator /= (const Rect<T>& vec) {
            x /= vec.x;
            y /= vec.y;
            z /= vec.z;
            w /= vec.w;
            return *this;
        }

        inline ffw::Rect<T>  operator *  (const Rect<T>& vec) const {
            return Rect<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
        }

        inline ffw::Rect<T>& operator *= (const Rect<T>& vec) {
            x *= vec.x;
            y *= vec.y;
            z *= vec.z;
            w *= vec.w;
            return *this;
        }

        inline ffw::Rect<T>& operator =  (const T& val) {
            x = val;
            y = val;
            z = val;
            w = val;
            return *this;
        }

        inline ffw::Rect<T>  operator +  (const T& val) const {
            return Rect<T>(x + val, y + val, z + val, w + val);
        }

        inline ffw::Rect<T>& operator += (const T& val) {
            x += val;
            y += val;
            z += val;
            w += val;
            return *this;
        }

        inline ffw::Rect<T>  operator -  (const T& val) const {
            return Rect<T>(x - val, y - val, z - val, w - val);
        }

        inline ffw::Rect<T>& operator -= (const T& val) {
            x -= val;
            y -= val;
            z -= val;
            w -= val;
            return *this;
        }

        inline ffw::Rect<T>  operator /  (const T& val) const {
            return Rect<T>(x / val, y / val, z / val, w / val);
        }

        inline ffw::Rect<T>& operator /= (const T& val) {
            x /= val;
            y /= val;
            z /= val;
            w /= val;
            return *this;
        }

        inline ffw::Rect<T>  operator *  (const T& val) const {
            return Rect<T>(x * val, y * val, z * val, w * val);
        }

        inline ffw::Rect<T>& operator *= (const T& val) {
            x *= val;
            y *= val;
            z *= val;
            w *= val;
            return *this;
        }

        inline bool operator != (const Rect<T>& vec) const {
            return !(*this == vec);
        }

        inline bool operator == (const Rect<T>& vec) const {
            return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
        }

        inline ffw::Rect<T>& normalize() {
            float l = sqrtf(x*x + y * y + z * z + w * w);
            if (l > 0) {
                x = x / l;
                y = y / l;
                z = z / l;
                w = w / l;
            }
            return *this;
        }

        inline ffw::Rect<T>& scale(const T val) {
            x = x * val;
            y = y * val;
            z = z * val;
            w = w * val;
            return *this;
        }

        inline double length() const {
            return sqrt(static_cast<double>(x*x + y * y + z * z + w * w));
        }

        inline float lengthf() const {
            return sqrtf(static_cast<float>(x*x + y * y + z * z + w * w));
        }

        inline T lengthSqrd() const {
            return (x*x + y * y + z * z + w * w);
        }

        T& operator [] (size_t i) {
            return ((T*)&x)[i];
        }

        const T& operator [] (size_t i) const {
            return ((T*)&x)[i];
        }

        template <class S>
        inline operator ffw::Rect<S>() const {
            return ffw::Rect<S>((S)x, (S)y, (S)z, (S)w);
        }

        inline Rect<T> round() const {
            return Rect<T>(std::round(x), std::round(y), std::round(z), std::round(w));
        }

        inline Rect<T> floor() const {
            return Rect<T>(std::floor(x), std::floor(y), std::floor(z), std::floor(w));
        }

        inline Rect<T> ceil() const {
            return Rect<T>(std::ceil(x), std::ceil(y), std::ceil(z), std::ceil(w));
        }

#ifdef FFW_VEC4
        inline Rect(const Vec4<T>& vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }

        inline operator Vec4<T>() const {
            return Vec4<T>(x, y, z, w);
        }
#endif
    };
    /**
    * @ingroup gui
    */
    typedef Rect<float> Rectf;
    /**
    * @ingroup gui
    */
    typedef Rect<int> Recti;
    /**
    * @ingroup gui
    */
    typedef Rect<double> Rectd;
    /**
    * @ingroup gui
    */
    template <class T>
    inline std::ostream& operator << (std::ostream& os, const ffw::Rect<T>& rect) {
        os << rect.x << ", " << rect.y << ", " << rect.z << ", " << rect.w;
        return os;
    }
}

namespace ffw {
    template<>
    inline bool ffw::Rect<float>::operator == (const Rect<float>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<float>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<float>::epsilon())return false;
        return true;
    }
    template<>
    inline bool ffw::Rect<double>::operator == (const Rect<double>& vec) const {
        if (fabs(x - vec.x) > std::numeric_limits<double>::epsilon())return false;
        if (fabs(y - vec.y) > std::numeric_limits<double>::epsilon())return false;
        return true;
    }
}
#endif
