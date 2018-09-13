/* This file is part of FineFramework project */
#ifndef FFW_GUI_FONT
#define FFW_GUI_FONT
#include <vector>
#include "./config.h"
#include "point.h"
namespace ffw {
    /**
     * @ingroup gui
     */
    class FFW_API GuiFont{
    public:
        GuiFont() = default;
        virtual ~GuiFont() = default;

        struct Chunk {
            const std::string::value_type* str;
            size_t len;
            float width;
            float height;
        };

        virtual bool isCreated() const = 0;
        virtual void destroy() = 0;
        virtual ffw::Pointf getStringSize(const std::string& str, float maxWidth, float lineHeight = 1.25f) const = 0;
        virtual float getEmptyLineHeight(float lineHeight = 1.25f) const = 0;
        /**
         * @brief Returns the advance of the codepoint
         * @note This method is not needed if you use your custom implementation of splitString(),
         * getCharIndex(), and getCharPos(). The default implementations use GuiTextWrapper class
         * which uses this method.
         */
        virtual float getCharAdvance(unsigned int c) const = 0;
        virtual std::vector<Chunk> splitString(const std::string& str, float maxWidth, float lineHeight = 1.25f) const;
        virtual size_t getCharIndex(const std::string::value_type* str, size_t len, const Pointf& pos, float* x) const;
        virtual float getCharPos(const std::string::value_type* str, size_t len, size_t index) const;
    };
}
#endif
