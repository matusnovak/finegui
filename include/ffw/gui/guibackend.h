/* This file is part of FineFramework project */
#ifndef FFW_GUI_BACKEND
#define FFW_GUI_BACKEND
#include "./config.h"
#include "guistyle.h"
#include "guifont.h"
#include "point.h"
#include "rect.h"
#include "color.h"
#include "constants.h"
#include "third_party/utfcpp/checked.h"

namespace ffw {
    class GuiImage;
    class GuiFont;
    /**
     * @ingroup gui
     */
    class FFW_API GuiBackend {
    public:
        // The following must be implemented!
        virtual void resize(int width, int height) = 0;
        virtual void startRender() = 0;
        virtual void endRender() = 0;
        virtual void setScissors(const ffw::Pointf& pos, const ffw::Pointf& size) const = 0;
        virtual void clearWithColor(const ffw::Color& color, const ffw::Pointf& pos, const ffw::Pointf& size) const = 0;
        virtual void drawRectangle(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::Color& color) const = 0;
        virtual void drawRectangleRounded(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::Color& color, float tl, float tr, float br, float bl) const = 0;
        virtual void drawLine(const ffw::Pointf& start, const ffw::Pointf& end, const ffw::Color& color, float width = 1.0f) const = 0;
        virtual void drawCircle(const ffw::Pointf& pos, float radius, const ffw::Color& color) const = 0;
        virtual void drawArc(const ffw::Pointf& pos, float inner, float outer, float start, float end, const ffw::Color& color) const = 0;
        virtual void drawQuad(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, const ffw::Pointf& p3, const ffw::Color& color) const = 0;
        virtual void drawString(const ffw::Pointf& pos, const ffw::GuiFont* font, const std::string::value_type* str, size_t length, const ffw::Color& color, float lineHeight = 1.25f) const = 0;
        virtual void drawTriangle(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, const ffw::Color& color) const = 0;
        virtual void drawImage(const ffw::Pointf& pos, const ffw::Pointf& size, const GuiImage* image, const ffw::Recti& sub, bool mirrorX, bool mirrorY, const ffw::Color& color) const = 0;
        virtual void drawBackground(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiStyle::Background& background, bool ignore = false) const = 0;
        virtual void drawBorder(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiStyle::Border& border) const = 0;

        // The following can be overriden
        virtual void drawStringAligned(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiFont* font, ffw::GuiAlign align, const std::string& str, const ffw::GuiStyle::Text& text, float lineHeight = 1.25f) const;
    };
}
#endif
