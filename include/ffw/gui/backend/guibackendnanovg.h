/* This file is part of FineFramework project */
#ifndef FFW_GUI_BACKEND_NANOVG
#define FFW_GUI_BACKEND_NANOVG

#include <fstream>
#include <nanovg.h>
#include <nanovg_gl_utils.h>
#include "../guiwindow.h"

#define COLOR_TO_NVGCOLOR(c) (nvgRGBAf(c.r, c.g, c.b, c.a))

#ifdef FFW_CLAMP
#define FFW_CLAMP(n, lower, upper) (std::max(lower, std::min(n, upper)))
#endif
#ifndef FFW_FLOAT_EQUAL
#define FFW_FLOAT_EQUAL(a, b) (std::abs(a - b) < 0.001f)
#endif

namespace ffw {
    /**
    * @ingroup gui
    */
    class GuiImageNanoVG: public GuiImage {
    public:
        GuiImageNanoVG(NVGcontext* ctx, const int w, const int h, const int flags, const unsigned char* data):
        ctx(ctx), width(0), height(0) {
            image = nvgCreateImageRGBA(ctx, w, h, flags, data);
            if (image >= 0) {
                nvgImageSize(ctx, image, &width, &height);
            }
        }
        GuiImageNanoVG(NVGcontext* ctx, const std::string& path, const int flags):
        ctx(ctx), width(0), height(0) {
            image = nvgCreateImage(ctx, path.c_str(), flags);
            if (image >= 0) {
                nvgImageSize(ctx, image, &width, &height);
            }
        }
        virtual ~GuiImageNanoVG() {
            nvgDeleteImage(ctx, image);
        }
        void destroy() override {
            nvgDeleteImage(ctx, image);
        }
        bool isCreated() const override {
            return image >= 0;
        }
        int getWidth() const override {
            return width;
        }
        int getHeight() const override {
            return height;
        }
        int getImageId() const {
            return image;
        }
    private:
        NVGcontext * ctx;
        int image;
        int width;
        int height;
    };
    /**
    * @ingroup gui
    */
    class GuiFontNanoVG: public GuiFont {
    public:
        GuiFontNanoVG(NVGcontext* ctx, const std::string& path, const float size):
        ctx(ctx),size(size) {
            font = nvgCreateFont(ctx, "", path.c_str());
        }
        virtual ~GuiFontNanoVG() = default;
        bool isCreated() const override {
            return font >= 0;
        }
        void destroy() override {
            // void
        }
        ffw::Pointf getStringSize(const std::string& str, const float maxWidth, 
            const float lineHeight) const override {

            nvgFontFaceId(ctx, font);
            nvgTextLineHeight(ctx, lineHeight);
            nvgTextLetterSpacing(ctx, 0);
            nvgFontSize(ctx, size);
            float bounds[4];
            nvgTextBoxBounds(
                ctx, 0.0f, 0.0f, maxWidth >= 0.0f ? maxWidth : std::numeric_limits<float>::max(),
                str.c_str(), str.c_str() + str.size(), bounds
            );
            return Pointf(bounds[2], bounds[3] - bounds[1]);
        }
        float getEmptyLineHeight(const float lineHeight) const override {
            return getStringSize("W", -1.0f, lineHeight).y;
        }
        float getCharAdvance(unsigned int c) const override {
            // See the comment on the base GuiFont::getCharAdvance() method to understand!
            // In case you use this method, be aware that canvas.textGlyphPositions uses
            // NanoVG nvgTextGlyphPositions which for some reason are not exactly precise
            // and during the rendering of the text the char advance is slightly smaller.

            /*nvgFontFace(ctx, font);
            // nvgTextLineHeight(ctx, lineHeight);
            nvgFontSize(ctx, size);
            nvgTextLetterSpacing(ctx, 0);

            char buff[5];
            *utf8::append(c, buff) = '\0';

            NVGglyphPosition position = { nullptr, 0, 0, 0 };
            (void)nvgTextGlyphPositions(0.0f, 0.0f, buff, nullptr, &position, 1);
            return position.maxx;*/
            return 0.0f;
        }
        std::vector<Chunk> splitString(const std::string& str, const float maxWidth, 
            const float lineHeight) const override {

            nvgFontFaceId(ctx, font);
            nvgTextLineHeight(ctx, lineHeight);
            nvgTextLetterSpacing(ctx, 0);
            nvgFontSize(ctx, size);
            std::vector<Chunk> ret;

            auto start = str.c_str();
            const auto end = str.c_str() + str.size();
            while (true) {
                const auto initial = ret.size();

                NVGtextRow rows[4];
                const auto total = nvgTextBreakLines(ctx, start, end, maxWidth, rows, 4);

                ret.resize(initial + total);
                for (auto i = 0; i < total; i++) {
                    ret[initial + i].str = rows[i].start;
                    ret[initial + i].len = rows[i].end - rows[i].start;
                    ret[initial + i].width = rows[i].width;
                }

                if (rows[total - 1].next < end) {
                    start = rows[total - 1].next;
                } else {
                    break;
                }
            }
            const auto w = 'W';
            float bounds[4];
            nvgTextBoxBounds(ctx, 0.0f, 0.0f, std::numeric_limits<float>::max(), &w, &w + 1, bounds);
            const auto realLineHeight = bounds[3] - bounds[1];
            for (auto& r : ret) {
                r.height = realLineHeight;
            }
            return ret;
        }
        size_t getCharIndex(const std::string::value_type* str, const size_t len,
            const Pointf& pos, float* x) const override {

            nvgFontFaceId(ctx, font);
            //nvgTextLineHeight(ctx, lineHeight);
            nvgTextLetterSpacing(ctx, 0);
            nvgFontSize(ctx, size);

            const auto begin = str;
            const auto end = str + len;

            std::unique_ptr<NVGglyphPosition[]> positions(new NVGglyphPosition[len]);
            const size_t total = nvgTextGlyphPositions(ctx, 0.0f, 0.0f, begin, end, positions.get(), len);

            for (size_t i = 0; i < total; i++) {
                const auto& p = positions[i];
                // Check if the character is after the position
                if (p.x <= pos.x && p.maxx >= pos.x) {
                    if (x) *x = p.x;
                    return p.str - begin;
                }
            }

            if (x) *x = positions[total - 1].maxx;
            return end - begin;
        }
        float getCharPos(const std::string::value_type* str, const size_t len,
            const size_t index) const override {

            if (index == 0) return 0.0f;

            nvgFontFaceId(ctx, font);
            //nvgTextLineHeight(ctx, lineHeight);
            nvgTextLetterSpacing(ctx, 0);
            nvgFontSize(ctx, size);

            const auto begin = str;
            const auto end = str + len;

            std::unique_ptr<NVGglyphPosition[]> positions(new NVGglyphPosition[len]);
            const auto total = nvgTextGlyphPositions(ctx, 0.0f, 0.0f, begin, end, positions.get(), len);

            // Check if we are looking for an index within the string
            if (index < len) {
                // Then return the position of the character (not the next position)
                for (size_t i = 0; i < len; i++) {
                    if (size_t(positions[i].str - str) >= index) {
                        return positions[i].x;
                    }
                }

                return positions[total - 1].x;
            } else {
                // If we are looking for the index after the string (len == index)
                // then return the position after the last character (the next position)
                return positions[total - 1].maxx;
            }
        }
        float getSize() const {
            return size;
        }
        int getFontFaceId() const {
            return font;
        }
    private:
        NVGcontext * ctx;
        int font;
        float size;
    };
    /**
    * @ingroup gui
    */
    class GuiWindowNanoVG: public GuiWindow {
    public:
        GuiWindowNanoVG(NVGcontext* ctx):ctx(ctx) {
            
        }
        virtual ~GuiWindowNanoVG() {
            destroy();
        }
        void destroy() {
            if (fbo) {
                nvgluDeleteFramebuffer(fbo);
            }
        }
        void resize(const int width, const int height) override {
            if (fbo) {
                nvgluDeleteFramebuffer(fbo);
            }
            fbo = nvgluCreateFramebuffer(ctx, width, height, NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
        }
        void startRender() override {
            nvgluBindFramebuffer(fbo);
            const auto width = getSize().x;
            const auto height = getSize().y;

            glViewport(0, 0, int(width), int(height));

            nvgBeginFrame(ctx, width, height, 1.0f);
        }
        void endRender() override {
            nvgResetScissor(ctx);
            nvgEndFrame(ctx);
            nvgluBindFramebuffer(nullptr);
        }
        void setScissors(const ffw::Pointf& pos, const ffw::Pointf& size) const override {
            nvgScissor(ctx, pos.x, pos.y, size.x, size.y);
        }
        void clearWithColor(const ffw::Color& color) const override {
            nvgBeginPath(ctx);
            nvgRect(ctx, 0.0f, 0.0f, getSize().x, getSize().y);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawRectangle(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const ffw::Color& color) const override {
            nvgBeginPath(ctx);
            nvgRect(ctx, pos.x, pos.y, size.x, size.y);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawRectangleRounded(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const ffw::Color& color, const float tl, const float tr, 
            const float br, const float bl) const override {

            nvgBeginPath(ctx);
            nvgRoundedRectVarying(ctx, pos.x, pos.y, size.x, size.y, tl, tr, br, bl);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawLine(const ffw::Pointf& start, const ffw::Pointf& end,
            const ffw::Color& color, float width) const override {
            nvgBeginPath(ctx);
            nvgMoveTo(ctx, start.x, start.y);
            nvgLineTo(ctx, end.x, end.y);
            nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgStroke(ctx);
        }
        void drawCircle(const ffw::Pointf& pos, const float radius,
            const ffw::Color& color) const override {
            nvgBeginPath(ctx);
            nvgCircle(ctx, pos.x, pos.y, radius);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawArc(const ffw::Pointf& pos, const float inner, const float outer,
            const float start, const float end, const ffw::Color& color) const override {
            nvgBeginPath(ctx);
            const auto p0 = pos + ffw::Pointf(outer, 0).rotate(start);
            const auto p1 = pos + ffw::Pointf(inner, 0).rotate(end);
            nvgMoveTo(ctx, p0.x, p0.y);
            nvgArc(ctx, pos.x, pos.y, outer, float(start * DEG_TO_RAD), float(end * DEG_TO_RAD), NVG_CW);
            nvgLineTo(ctx, p1.x, p1.y);
            nvgArc(ctx, pos.x, pos.y, inner, float(end * DEG_TO_RAD), float(start * DEG_TO_RAD), NVG_CCW);
            nvgClosePath(ctx);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawQuad(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, 
            const ffw::Pointf& p3, const ffw::Color& color) const override {
            nvgBeginPath(ctx);
            nvgMoveTo(ctx, p0.x, p0.y);
            nvgLineTo(ctx, p1.x, p1.y);
            nvgLineTo(ctx, p2.x, p2.y);
            nvgLineTo(ctx, p3.x, p3.y);
            nvgClosePath(ctx);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawString(const ffw::Pointf& pos, const ffw::GuiFont* font, 
            const std::string::value_type* str, const size_t length, const ffw::Color& color,
            const float lineHeight) const override {
            const auto nvgFont = dynamic_cast<const ffw::GuiFontNanoVG*>(font);
            if (nvgFont) {
                nvgFontFaceId(ctx, nvgFont->getFontFaceId());
                nvgTextLineHeight(ctx, lineHeight);
                nvgTextLetterSpacing(ctx, 0);
                nvgFontSize(ctx, nvgFont->getSize());
                nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
                float ascender, descender, lineh = 0.0f;
                nvgTextMetrics(ctx, &ascender, &descender, &lineh);
                nvgTextBox(ctx, pos.x, pos.y + ascender, std::numeric_limits<float>::max(), str, str + length);
            }
        }
        void drawTriangle(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, 
            const ffw::Color& color) const override {
            nvgBeginPath(ctx);
            nvgMoveTo(ctx, p0.x, p0.y);
            nvgLineTo(ctx, p1.x, p1.y);
            nvgLineTo(ctx, p2.x, p2.y);
            nvgClosePath(ctx);
            nvgFillColor(ctx, COLOR_TO_NVGCOLOR(color));
            nvgFill(ctx);
        }
        void drawImage(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const GuiImage* image, const ffw::Recti& sub, bool mirrorX, 
            bool mirrorY, const ffw::Color& color) const override {
            const auto nvgImage = dynamic_cast<const ffw::GuiImageNanoVG*>(image);
            if (nvgImage) {
                int w, h = 0;
                nvgImageSize(ctx, nvgImage->getImageId(), &w, &h);
                const auto subX = sub.x / float(w);
                const auto subY = sub.y / float(h);
                const auto subZ = sub.z / float(w);
                const auto subW = sub.w / float(h);
                const auto pattern = nvgImagePattern(
                    ctx, 
                    pos.x - size.x * (subX / subZ), 
                    pos.y - size.y * (subY / subW), 
                    size.x / subZ,
                    size.y / subW, 
                    0.0f, 
                    nvgImage->getImageId(), 
                    color.a
                );
                nvgBeginPath(ctx);
                nvgRect(ctx, pos.x, pos.y, size.x, size.y);
                nvgFillPaint(ctx, pattern);
                nvgFill(ctx);
            }
        }
        void drawBackground(const ffw::Pointf& pos, const ffw::Pointf& size,
            const ffw::GuiStyle::Background& background, bool ignore) const override {
            if (background.type == ffw::GuiStyle::Background::Type::SIMPLE) {
                if (background.radius[0] > 0.0f || background.radius[1] > 0.0f || 
                    background.radius[2] > 0.0f || background.radius[3] > 0.0f) {
                    nvgBeginPath(ctx);
                    nvgRoundedRectVarying(ctx, pos.x, pos.y, size.x, size.y, 
                        background.radius[0], background.radius[1], 
                        background.radius[2], background.radius[3]);
                    nvgFillColor(ctx, COLOR_TO_NVGCOLOR(background.color));
                    nvgFill(ctx);
                } else {
                    nvgBeginPath(ctx);
                    nvgRect(ctx, pos.x, pos.y, size.x, size.y);
                    nvgFillColor(ctx, COLOR_TO_NVGCOLOR(background.color));
                    nvgFill(ctx);
                }
            }
        }
        void drawBorder(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const ffw::GuiStyle::Border& border) const override {
            if (border.size[0] == border.size[1] && border.size[0] == border.size[2] && border.size[0] == border.size[3]) {
                if (border.color[0] == border.color[1] && border.color[0] == border.color[2] && border.color[0] == border.color[3]) {
                    nvgBeginPath(ctx);
                    const auto borderHalf = border.size[0] / 2.0f;
                    nvgRoundedRectVarying(ctx, pos.x + borderHalf, pos.y + borderHalf, size.x - border.size[0], size.y - border.size[0], border.radius[0], border.radius[1], border.radius[2], border.radius[3]);
                    nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(border.color[0]));
                    nvgStrokeWidth(ctx, border.size[0]);
                    nvgStroke(ctx);
                    return;
                }
            }

            // Top
            nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(border.color[0]));
            nvgBeginPath(ctx);
            nvgMoveTo(ctx, pos.x + border.radius[0], pos.y + border.size[0] / 2.0f);

            auto endX = pos.x + size.x - border.radius[1];
            auto endY = pos.y + border.size[0] / 2.0f;

            nvgStrokeWidth(ctx, border.size[0]);
            nvgLineTo(ctx, endX, endY);

            if (border.radius[1] > 0.1f) {
                const auto cp0 = ffw::Pointf(endX + border.radius[1] / 2.0f, endY);
                const auto cp1 = ffw::Pointf(pos.x + size.x - border.size[1] / 2.0f, pos.y + border.radius[1] / 2.0f);
                const auto end = ffw::Pointf(pos.x + size.x - border.size[1] / 2.0f, pos.y + border.radius[1]);

                if (border.color[0] == border.color[1] && FFW_FLOAT_EQUAL(border.size[0], border.size[1])) {
                    nvgBezierTo(ctx, cp0.x, cp0.y, cp1.x, cp1.y, end.x, end.y);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    nvgBezierTo(ctx, cp0A.x, cp0A.y, cp0B.x, cp0B.y, mid.x, mid.y);

                    nvgStroke(ctx);
                    nvgBeginPath(ctx);
                    nvgMoveTo(ctx, mid.x, mid.y);
                    nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(border.color[1]));

                    nvgBezierTo(ctx, cp1A.x, cp1A.y, cp1B.x, cp1B.y, end.x, end.y);
                }
            }

            endX = pos.x + size.x - border.size[1] / 2.0f;
            endY = pos.y + size.y - border.radius[2];

            nvgStrokeWidth(ctx, border.size[1]);
            nvgLineTo(ctx, endX, endY);

            if (border.radius[2] > 0.1f) {
                const auto cp0 = ffw::Pointf(endX, endY + border.radius[2] / 2.0f);
                const auto cp1 = ffw::Pointf(pos.x + size.x - border.radius[2] / 2.0f, pos.y + size.y - border.size[2] / 2.0f);
                const auto end = ffw::Pointf(pos.x + size.x - border.radius[2], pos.y + size.y - border.size[2] / 2.0f);

                if (border.color[1] == border.color[2] && FFW_FLOAT_EQUAL(border.size[1], border.size[2])) {
                    nvgBezierTo(ctx, cp0.x, cp0.y, cp1.x, cp1.y, end.x, end.y);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    nvgBezierTo(ctx, cp0A.x, cp0A.y, cp0B.x, cp0B.y, mid.x, mid.y);

                    nvgStroke(ctx);
                    nvgBeginPath(ctx);
                    nvgMoveTo(ctx, mid.x, mid.y);
                    nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(border.color[2]));

                    nvgBezierTo(ctx, cp1A.x, cp1A.y, cp1B.x, cp1B.y, end.x, end.y);
                }
            }

            endX = pos.x + border.radius[3];
            endY = pos.y + size.y - border.size[2] / 2.0f;

            nvgStrokeWidth(ctx, border.size[2]);
            nvgLineTo(ctx, endX, endY);

            if (border.radius[3] > 0.1f) {
                const auto cp0 = ffw::Pointf(pos.x + border.radius[3] / 2.0f, endY);
                const auto cp1 = ffw::Pointf(pos.x + border.size[3] / 2.0f, pos.y + size.y - border.radius[3] / 2.0f);
                const auto end = ffw::Pointf(pos.x + border.size[3] / 2.0f, pos.y + size.y - border.radius[3]);

                if (border.color[2] == border.color[3] && FFW_FLOAT_EQUAL(border.size[2], border.size[3])) {
                    nvgBezierTo(ctx, cp0.x, cp0.y, cp1.x, cp1.y, end.x, end.y);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    nvgBezierTo(ctx, cp0A.x, cp0A.y, cp0B.x, cp0B.y, mid.x, mid.y);

                    nvgStroke(ctx);
                    nvgBeginPath(ctx);
                    nvgMoveTo(ctx, mid.x, mid.y);
                    nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(border.color[3]));

                    nvgBezierTo(ctx, cp1A.x, cp1A.y, cp1B.x, cp1B.y, end.x, end.y);
                }
            }

            endX = pos.x + border.size[3] / 2.0f;
            endY = pos.y + border.radius[0];

            nvgStrokeWidth(ctx, border.size[3]);
            nvgLineTo(ctx, endX, endY);

            if (border.radius[0] > 0.1f) {
                const auto cp0 = ffw::Pointf(pos.x + border.size[3] / 2.0f, pos.y + border.radius[0] / 2.0f);
                const auto cp1 = ffw::Pointf(pos.x + border.radius[0] / 2.0f, pos.y + border.size[0] / 2.0f);
                const auto end = ffw::Pointf(pos.x + border.radius[0], pos.y + border.size[0] / 2.0f);

                if (border.color[3] == border.color[0] && FFW_FLOAT_EQUAL(border.size[3], border.size[0])) {
                    nvgBezierTo(ctx, cp0.x, cp0.y, cp1.x, cp1.y, end.x, end.y);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    nvgBezierTo(ctx, cp0A.x, cp0A.y, cp0B.x, cp0B.y, mid.x, mid.y);

                    nvgStroke(ctx);
                    nvgBeginPath(ctx);
                    nvgMoveTo(ctx, mid.x, mid.y);
                    nvgStrokeWidth(ctx, border.size[0]);
                    nvgStrokeColor(ctx, COLOR_TO_NVGCOLOR(border.color[0]));

                    nvgBezierTo(ctx, cp1A.x, cp1A.y, cp1B.x, cp1B.y, end.x, end.y);
                }
            }

            nvgStroke(ctx);
        }

        const NVGLUframebuffer* getFbo() const {
            return fbo;
        }
    private:
        NVGcontext* ctx = nullptr;
        NVGLUframebuffer* fbo = nullptr;
    };
}
#endif
