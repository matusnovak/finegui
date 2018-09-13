/* This file is part of FineFramework project */
#ifndef FFW_COLOR
#define FFW_COLOR

#include <ostream>
#include <math.h>
#include <algorithm>

namespace ffw {
    /**
    * @ingroup gui
    * @brief Class that holds floating point color, OpenGL friendly
    * @details You can use this class to represent any RGBA color and
    * pass it to your OpenGL function. This class uses 4 floats
    * to represent color combinations. For example, 100% red color is when
    * r is set to 1.0f and all other (g, b, a) is set to 0.0. 
    * You can also use ffw::rgba function to construct this class with less typing
    * @sa ffw::rgb, ffw::rgba,
    */
    struct Color {
    public:
        float r;
        float g;
        float b;
        float a;
        /**
        * @brief Default constructor, sets color to black with 0% alpha
        */
        inline Color() {
            r = 0;
            g = 0;
            b = 0;
            a = 0;
        }
        /**
        * @brief Construcor, sets the color based on the parameters
        */
        inline Color(float red, float green, float blue, float alpha) {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }
        /**
        * @brief Constructor, sets the color to grayscale with alpha
        */
        inline Color(float val, float alpha) {
            r = val;
            g = val;
            b = val;
            a = alpha;
        }
        /**
        * @brief Copy Constructor
        */
        inline Color(const Color& vec) {
            r = vec.r;
            g = vec.g;
            b = vec.b;
            a = vec.a;
        }
        /**
        * @brief Construcor, sets the color from braced list of 4 floating point values
        */
        inline Color(const std::initializer_list<float>& list) {
            if (list.size() != 4) {
                r = 0;
                g = 0;
                b = 0;
                a = 0;
                return;
            }
            r = *(list.begin());
            g = *(list.begin() + 1);
            b = *(list.begin() + 2);
            a = *(list.begin() + 3);
        }
        /**
        * @brief Sets the color
        */
        inline void set(float red, float green, float blue, float alpha) {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }
        /**
        * @brief Sets the color
        */
        inline void set(float val, float alpha) {
            r = val;
            g = val;
            b = val;
            a = alpha;
        }
        /**
        * @brief Sets the color from another color class
        */
        inline void set(const Color& vec) {
            r = vec.r;
            g = vec.g;
            b = vec.b;
            a = vec.a;
        }
        /**
        * @brief Sets the color from a braced list of 4 floating point values
        */
        inline void set(const std::initializer_list<float>& list) {
            if (list.size() != 4)return;
            r = *(list.begin());
            g = *(list.begin() + 1);
            b = *(list.begin() + 2);
            a = *(list.begin() + 3);
        }
        /**
        * @brief Performs unary minus operation on all r,g,b,a channels
        */
        inline ffw::Color  operator - () const {
            return Color(-r, -g, -b, -a);
        }
        /**
        * @brief Copies values from different color instance
        */
        inline ffw::Color& operator =  (const Color& vec) {
            r = vec.r;
            g = vec.g;
            b = vec.b;
            a = vec.a;
            return *this;
        }
        /**
        * @brief Adds together two colors, returning a copy
        */
        inline ffw::Color  operator +  (const Color& vec) const {
            return Color(r + vec.r, g + vec.g, b + vec.b, a + vec.a);
        }
        /**
        * @brief Adds together two colors
        */
        inline ffw::Color& operator += (const Color& vec) {
            r += vec.r;
            g += vec.g;
            b += vec.b;
            a += vec.a;
            return *this;
        }
        /**
        * @brief Substracts together two colors, returning a copy
        */
        inline ffw::Color  operator -  (const Color& vec) const {
            return Color(r - vec.r, g - vec.g, b - vec.b, a - vec.a);
        }
        /**
        * @brief Substracts together two colors
        */
        inline ffw::Color& operator -= (const Color& vec) {
            r -= vec.r;
            g -= vec.g;
            b -= vec.b;
            a -= vec.a;
            return *this;
        }

        inline ffw::Color  operator /  (const Color& vec) const {
            return Color(r / vec.r, g / vec.g, b / vec.b, a / vec.a);
        }

        inline ffw::Color& operator /= (const Color& vec) {
            r /= vec.r;
            g /= vec.g;
            b /= vec.b;
            a /= vec.a;
            return *this;
        }

        inline ffw::Color  operator *  (const Color& vec) const {
            return Color(r * vec.r, g * vec.g, b * vec.b, a * vec.a);
        }

        inline ffw::Color& operator *= (const Color& vec) {
            r *= vec.r;
            g *= vec.g;
            b *= vec.b;
            a *= vec.a;
            return *this;
        }
        /**
        * @brief Assigns same value to all RGBA components
        */
        inline ffw::Color& operator =  (const float& val) {
            r = val;
            g = val;
            b = val;
            a = val;
            return *this;
        }
        /**
        * @brief Adds value to all RGBA components, returning a copy
        */
        inline ffw::Color  operator +  (const float& val) const {
            return Color(r + val, g + val, b + val, a + val);
        }
        /**
        * @brief Adds value to all RGBA components
        */
        inline ffw::Color& operator += (const float& val) {
            r += val;
            g += val;
            b += val;
            a += val;
            return *this;
        }
        /**
        * @brief Substracts from all RGBA components, returning a copy
        */
        inline ffw::Color  operator -  (const float& val) const {
            return Color(r - val, g - val, b - val, a - val);
        }
        /**
        * @brief Substracts from all RGBA components
        */
        inline ffw::Color& operator -= (const float& val) {
            r -= val;
            g -= val;
            b -= val;
            a -= val;
            return *this;
        }

        inline ffw::Color  operator /  (const float& val) const {
            return Color(r / val, g / val, b / val, a / val);
        }

        inline ffw::Color& operator /= (const float& val) {
            r /= val;
            g /= val;
            b /= val;
            a /= val;
            return *this;
        }

        inline ffw::Color  operator *  (const float& val) const {
            return Color(r * val, g * val, b * val, a * val);
        }

        inline ffw::Color& operator *= (const float& val) {
            r *= val;
            g *= val;
            b *= val;
            a *= val;
            return *this;
        }
        /**
        * @brief Checks if this instance is not equal to other one, using epsilon
        */
        inline bool operator != (const Color& vec) const {
            return !(*this == vec);
        }
        /**
        * @brief Checks if this instance is equal to other one, using epsilon
        */
        inline bool operator == (const Color& vec) const {
            if (fabs(r - vec.r) > std::numeric_limits<float>::epsilon())return false;
            if (fabs(g - vec.g) > std::numeric_limits<float>::epsilon())return false;
            if (fabs(b - vec.b) > std::numeric_limits<float>::epsilon())return false;
            if (fabs(a - vec.a) > std::numeric_limits<float>::epsilon())return false;
            return true;
        }
        /**
        * @brief Clamps all RGBA components so that all values are between 0.0 and 1.0
        * @note Does not perform a normalization!
        */
        inline ffw::Color& clamp() {
            r = std::max(0.0f, std::min(r, 1.0f));
            g = std::max(0.0f, std::min(r, 1.0f));
            b = std::max(0.0f, std::min(r, 1.0f));
            a = std::max(0.0f, std::min(r, 1.0f));
            return *this;
        }
        /**
        * @brief Normalises a color
        * @note Color is treated as a 3D vector but alpha is ignored and clamped instead.
        */
        inline ffw::Color& normalize() {
            float l = sqrtf(r*r + g*g + b*b);
            if (l > 0) {
                r = r / l;
                g = g / l;
                b = b / l;
                if (a > 1.0f)a = 1.0f;
                if (a < 0.0f)a = 0.0f;
            }
            return *this;
        }
        /**
        * @brief Scales all RGBA components with single value
        */
        inline ffw::Color& scale(const float val) {
            r = r*val;
            g = g*val;
            b = b*val;
            a = a*val;
            return *this;
        }
        /**
        * @brief Returns the length of a vector (color is treated as a vector)
        */
        inline double length() const {
            return sqrt(static_cast<double>(r*r + g*g + b*b + a*a));
        }
        /**
        * @brief Returns the length of a vector (color is treated as a vector)
        */
        inline float lengthf() const {
            return sqrtf(static_cast<float>(r*r + g*g + b*b + a*a));
        }
        /**
        * @brief Returns the squared length of a vector (color is treated as a vector)
        */
        inline float lengthSqrd() const {
            return (r*r + g*g + b*b + a*a);
        }
		/**
		* @brief Returns the inverted R, G, and B components
		*/
		inline Color inverted() const {
			return Color(1.0f - r, 1.0f - g, 1.0f - b, a);
        }
    };
    /**
    * @ingroup gui
    * @brief Constructs ffw::Color from a hexadecimal value.
    * @details For example, ffw::rgb(0xFF0080) returns 100% red and 50% blue.
    * Alpha is set to 100%.
    * @warning Make sure to use 0xRRGGBB formula. For example, using 0xFF00 in this function would 
    * result of color with 0% red, 100% green, and 0% blue. Also, using 0xFF would result in
    * complete blue color. 
    */
    inline Color rgb(unsigned long hex) {
        return Color(
            ((hex & 0xFF0000) >> 16) / 255.0f,
            ((hex & 0x00FF00) >> 8) / 255.0f,
            (hex & 0x0000FF) / 255.0f,
            1.0f
        );
    }
    /**
    * @ingroup gui
    * @brief Constructs ffw::Color from three 8-bit balues.
    * @details For example, ffw::rgb(255, 0, 128) returns 100% red and 50% blue. 
    * Alpha is set to 100%.
    */
    inline Color rgb(unsigned char r, unsigned char g, unsigned char b) {
        return Color(
            r / 255.0f,
            g / 255.0f,
            b / 255.0f,
            1.0f
        );
    }
    /**
    * @ingroup gui
    * @brief Constructs ffw::Color from a hexadecimal value with alpha.
    * @details For example, ffw::rgba(0xFF0080BF) returns 100% red, 50% blue, and 80% alpha.
    * @warning Make sure to use 0xRRGGBBAA formula. For example, using 0xFF0080 in this function would 
    * result of color with 0% red, 100% green, 0% blue, and 50% alpha. Also, using 0xFF would result in
    * complete black color with 100% alpha. 
    */
    inline Color rgba(unsigned long hex) {
        return Color(
            ((hex & 0xFF000000) >> 24) / 255.0f,
            ((hex & 0x00FF0000) >> 16) / 255.0f,
            ((hex & 0x0000FF00) >> 8) / 255.0f,
            (hex & 0x000000FF) / 255.0f
        );
    }
    /**
    * @ingroup gui
    * @brief Constructs ffw::Color from three 8-bit balues with alpha
    * @details For example, ffw::rgba(255, 0, 128, 191) returns 100% red, 50% blue, and 80% alpha.
    */
    inline Color rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return Color(
            r / 255.0f,
            g / 255.0f,
            b / 255.0f,
            a / 255.0f
        );
    }
    /**
    * @ingroup gui
    * @brief Constructs ffw::Color from HSL values
    * @param h The hue component in range [0, 1]
    * @param s The saturation component in range [0, 1]
    * @param l The luminance component in range [0, 1]
    * @param a The alpha component in range [0, 1]
    * @details For example, ffw::hsl(0.8f, 0.5f, 0.5f) returns purple color with 50% saturation and
    * 50% luminance.
    */
    inline Color hsl(const float h, const float s, const float l, const float a = 1.0f) {
        // Converted from JavaScript to C++ from https://gist.github.com/mjackson/5311256
        if (s <= 0.0f) return Color(l, l, l, 1.0f);
        static const auto hue2rgb = [](float p, float q, float t) {
            if (t < 0.0f) t += 1;
            if (t > 1.0f) t -= 1;
            if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
            if (t < 1.0f / 2.0f) return q;
            if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
            return p;
        };

        const auto q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
        const auto p = 2.0f * l - q;

        return Color(
            hue2rgb(p, q, h + 1.0f / 3.0f),
            hue2rgb(p, q, h),
            hue2rgb(p, q, h - 1.0f / 3.0f),
            a
        );
    }
    /**
    * @ingroup gui
    * @brief Constructs ffw::Color from HSV values
    * @param h The hue component in range [0, 1]
    * @param s The saturation component in range [0, 1]
    * @param v The value component in range [0, 1]
    * @param a The alpha component in range [0, 1]
    */
    inline Color hsv(const float h, const float s, const float v, const float a = 1.0f) {
        // Converted from JavaScript to C++ from https://gist.github.com/mjackson/5311256
        const auto i = int(h * 6.0f);
        const auto f = h * 6.0f - i;
        const auto p = v * (1.0f - s);
        const auto q = v * (1.0f - f * s);
        const auto t = v * (1.0f - (1.0f - f) * s);
        switch (i % 6) {
            case 0: return Color(v, t, p, a);
            case 1: return Color(q, v, p, a);
            case 2: return Color(p, v, t, a);
            case 3: return Color(p, q, v, a);
            case 4: return Color(t, p, v, a);
            case 5: return Color(v, p, q, a);
            default: return Color(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    /**
    * @ingroup gui
    * @brief Normalizes a color returning a copy (won't modify the original)
    */
    inline ffw::Color normalize(const Color& col) {
        auto copy = col;
        copy.normalize();
        return copy;
    }
    /**
    * @ingroup gui
    * @brief Clamps a color between 0.0 and 1.0 values returning 
    * a copy (won't modify the original)
    */
    inline ffw::Color clamp(const ffw::Color& color) {
        return ffw::Color(color).clamp();
    }
    /**
    * @ingroup gui
    */
    inline std::ostream& operator << (std::ostream& os, const ffw::Color& color) {
        os << color.r << ", " << color.g << ", " << color.b << ", " << color.a;
        return os;
    }
};
#endif
