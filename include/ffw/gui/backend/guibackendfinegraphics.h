/* This file is part of FineFramework project */
#ifndef FFW_GUI_BACKEND_NANOVG
#define FFW_GUI_BACKEND_NANOVG

#include <ffw/graphics.h>
#include "../guiwindow.h"

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
    class GuiImageFineGraphics: public GuiImage {
    public:
        GuiImageFineGraphics() = default;
        GuiImageFineGraphics(GLCanvas& canvas, const GLTexture2D& texture, const GLCanvas::ImageFlags::Flag flags = 0):texture(texture) {
            image = canvas.createImage(texture, flags);
        }
        virtual ~GuiImageFineGraphics() = default;
        void destroy() override {
            // void
        }
        bool isCreated() const override {
            return texture.isCreated();
        }
        int getWidth() const override {
            return texture.getWidth();
        }
        int getHeight() const override {
            return texture.getHeight();
        }
        const GLCanvas::Image& getImage() const {
            return image;
        }
    private:
        GLCanvas::Image image;
        const GLTexture2D& texture;
    };
    /**
    * @ingroup gui
    */
    class GuiFontFineGraphics: public GuiFont {
    public:
        GuiFontFineGraphics(GLCanvas& canvas, const std::string& path, const float size):
            canvas(canvas),size(size) {
            font = canvas.createFont(path);

        }
        virtual ~GuiFontFineGraphics() = default;
        bool isCreated() const override {
            return font.isCreated();
        }
        void destroy() override {
            // void
        }
        ffw::Pointf getStringSize(const std::string& str, const float maxWidth, 
            const float lineHeight) const override {
            canvas.fontFace(font);
            canvas.textLineHeight(lineHeight);
            canvas.fontSize(size);
            canvas.textLetterSpacing(0);
            const auto bounds = canvas.textBoxBounds(Vec2f(0.0f, 0.0f), maxWidth >= 0.0f ? maxWidth : std::numeric_limits<float>::max(), str);
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

            /*canvas.fontFace(font);
            // canvas->textLineHeight(lineHeight);
            canvas.fontSize(size);
            canvas.textLetterSpacing(0);

            char buff[5];
            *utf8::append(c, buff) = '\0';

            GLCanvas::GlyphPosition position = { nullptr, 0, 0, 0 };
            (void)canvas.textGlyphPositions(Vec2f(0.0f, 0.0f), buff, nullptr, &position, 1);
            return position.maxx;*/
            return 0.0f;
        }
        std::vector<Chunk> splitString(const std::string& str, const float maxWidth, 
            const float lineHeight) const override {

            canvas.fontFace(font);
            canvas.textLineHeight(lineHeight);
            canvas.fontSize(size);
            canvas.textLetterSpacing(0);
            std::vector<Chunk> ret;

            auto start = str.c_str();
            const auto end = str.c_str() + str.size();
            while (true) {
                const auto initial = ret.size();

                GLCanvas::TextRow rows[4];
                const auto total = canvas.textBreakLines(start, end, maxWidth, rows, 4);

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
            const auto bounds = canvas.textBoxBounds(Vec2f(0.0f, 0.0f), std::numeric_limits<float>::max(), str);
            const auto realLineHeight = bounds[3] - bounds[1];
            for (auto& r : ret) {
                r.height = realLineHeight;
            }
            return ret;
        }
        size_t getCharIndex(const std::string::value_type* str, const size_t len,
            const Pointf& pos, float* x) const override {

            canvas.fontFace(font);
            // canvas->textLineHeight(lineHeight);
            canvas.fontSize(size);
            canvas.textLetterSpacing(0);

            const auto begin = str;
            const auto end = str + len;

            std::unique_ptr<GLCanvas::GlyphPosition[]> positions(new GLCanvas::GlyphPosition[len]);
            const size_t total = canvas.textGlyphPositions(Vec2f(0.0f, 0.0f), begin, end, positions.get(), len);

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

            canvas.fontFace(font);
            // canvas->textLineHeight(lineHeight);
            canvas.fontSize(size);
            canvas.textLetterSpacing(0);

            const auto begin = str;
            const auto end = str + len;

            std::unique_ptr<GLCanvas::GlyphPosition[]> positions(new GLCanvas::GlyphPosition[len]);
            const size_t total = canvas.textGlyphPositions(Vec2f(0.0f, 0.0f), begin, end, positions.get(), len);

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
        const GLCanvas::Font& getCanvasFont() const {
            return font;
        }
    private:
        GLCanvas& canvas;
        GLCanvas::Font font;
        float size;
    };
    /**
    * @ingroup gui
    */
    class GuiWindowFineGraphics: public GuiWindow {
    public:
        GuiWindowFineGraphics(GLCanvas& canvas):canvas(canvas) {
            
        }
        virtual ~GuiWindowFineGraphics() {
            destroy();
        }
        void destroy() {
            fbo.destroy();
            fboTexture.destroy();
        }
        void resize(const int width, const int height) override {
            if (!fbo.isCreated()) {
                fboTexture = GLTexture2D(width, height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                fboStencil = GLRenderbuffer2D(width, height, GL_STENCIL_INDEX8);
                fbo = GLFramebuffer({
                    GLFramebuffer::Attachment(&fboTexture, GL_COLOR_ATTACHMENT0),
                    GLFramebuffer::Attachment(&fboStencil, GL_STENCIL_ATTACHMENT)
                });
                fbo.checkStatus();
                fboTextureImage = canvas.createImage(fboTexture, GLCanvas::ImageFlags::IMAGE_FLIPY);
            }
            fboTexture.resize(width, height, nullptr);
            fboStencil.resize(width, height);
        }
        void startRender() override {
            fbo.bind();
            const auto width = getSize().x;
            const auto height = getSize().y;

            glViewport(0, 0, int(width), int(height));

            canvas.beginFrame(getSize());
        }
        void endRender() override {
            canvas.resetScissor();
            canvas.endFrame();
            fbo.unbind();
        }
        void setScissors(const ffw::Pointf& pos, const ffw::Pointf& size) const override {
            canvas.scissor(pos, size);
        }
        void clearWithColor(const ffw::Color& color) const override {
            canvas.beginPath();
            canvas.rect(Vec2f(0.0f), getSize());
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawRectangle(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const ffw::Color& color) const override {
            canvas.beginPath();
            canvas.rect(pos, size);
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawRectangleRounded(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const ffw::Color& color, const float tl, const float tr, 
            const float br, const float bl) const override {

            canvas.beginPath();
            canvas.roundedRect(pos, size, tl, tr, br, bl);
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawLine(const ffw::Pointf& start, const ffw::Pointf& end,
            const ffw::Color& color, float width) const override {
            canvas.beginPath();
            canvas.moveTo(start);
            canvas.lineTo(end);
            canvas.strokeColor(color);
            canvas.stroke();
        }
        void drawCircle(const ffw::Pointf& pos, const float radius,
            const ffw::Color& color) const override {
            canvas.beginPath();
            canvas.circle(pos, radius);
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawArc(const ffw::Pointf& pos, const float inner, const float outer,
            const float start, const float end, const ffw::Color& color) const override {
            canvas.beginPath();
            const auto p0 = pos + ffw::Pointf(outer, 0).rotate(start);
            const auto p1 = pos + ffw::Pointf(inner, 0).rotate(end);
            canvas.moveTo(p0);
            canvas.arc(pos, outer, start, end, GLCanvas::Winding::CW);
            canvas.lineTo(p1);
            canvas.arc(pos, inner, end, start, GLCanvas::Winding::CCW);
            canvas.closePath();
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawQuad(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, 
            const ffw::Pointf& p3, const ffw::Color& color) const override {
            canvas.beginPath();
            canvas.moveTo(p0);
            canvas.lineTo(p1);
            canvas.lineTo(p2);
            canvas.lineTo(p3);
            canvas.closePath();
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawString(const ffw::Pointf& pos, const ffw::GuiFont* font, 
            const std::string::value_type* str, const size_t length, const ffw::Color& color,
            const float lineHeight) const override {
            const auto fineFont = dynamic_cast<const ffw::GuiFontFineGraphics*>(font);
            if (fineFont) {
                canvas.fontFace(fineFont->getCanvasFont());
                canvas.textLineHeight(lineHeight);
                canvas.textLetterSpacing(0);
                canvas.fontSize(fineFont->getSize());
                canvas.fillColor(color);
                float ascender, descender, lineh = 0.0f;
                canvas.textMetrics(ascender, descender, lineh);
                canvas.textBox(pos + Vec2f(0.0f, ascender), std::numeric_limits<float>::max(), str, str + length);
            }
        }
        void drawTriangle(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, 
            const ffw::Color& color) const override {
            canvas.beginPath();
            canvas.moveTo(p0);
            canvas.lineTo(p1);
            canvas.lineTo(p2);
            canvas.closePath();
            canvas.fillColor(color);
            canvas.fill();
        }
        void drawImage(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const GuiImage* image, const ffw::Recti& sub, bool mirrorX, 
            bool mirrorY, const ffw::Color& color) const override {
            const auto fineImage = dynamic_cast<const ffw::GuiImageFineGraphics*>(image);
            if (fineImage) {
                const auto w = fineImage->getWidth();
                const auto h = fineImage->getHeight();
                const auto subX = sub.x / float(w);
                const auto subY = sub.y / float(h);
                const auto subZ = sub.z / float(w);
                const auto subW = sub.w / float(h);
                const auto pattern = canvas.imagePattern(
                    Vec2f(pos.x - size.x * (subX / subZ), pos.y - size.y * (subY / subW)), 
                    Vec2f(size.x / subZ, size.y / subW), 
                    0.0f, 
                    fineImage->getImage(),
                    color.a
                );
                canvas.beginPath();
                canvas.rect(pos, size);
                canvas.fillPaint(pattern);
                canvas.fill();
            }
        }
        void drawBackground(const ffw::Pointf& pos, const ffw::Pointf& size,
            const ffw::GuiStyle::Background& background, bool ignore) const override {
            if (background.type == ffw::GuiStyle::Background::Type::SIMPLE) {
                if (background.radius[0] > 0.0f || background.radius[1] > 0.0f || 
                    background.radius[2] > 0.0f || background.radius[3] > 0.0f) {
                    canvas.beginPath();
                    canvas.roundedRect(pos, size, 
                        background.radius[0], background.radius[1], 
                        background.radius[2], background.radius[3]);
                    canvas.fillColor(background.color);
                    canvas.fill();
                } else {
                    canvas.beginPath();
                    canvas.rect(pos, size);
                    canvas.fillColor(background.color);
                    canvas.fill();
                }
            }
        }
        void drawBorder(const ffw::Pointf& pos, const ffw::Pointf& size, 
            const ffw::GuiStyle::Border& border) const override {
            if (border.size[0] == border.size[1] && border.size[0] == border.size[2] && border.size[0] == border.size[3]) {
                if (border.color[0] == border.color[1] && border.color[0] == border.color[2] && border.color[0] == border.color[3]) {
                    canvas.beginPath();
                    const auto borderHalf = border.size[0] / 2.0f;
                    canvas.roundedRect(Vec2f(pos.x + borderHalf, pos.y + borderHalf), Vec2f(size.x - border.size[0], size.y - border.size[0]), border.radius[0], border.radius[1], border.radius[2], border.radius[3]);
                    canvas.strokeColor(border.color[0]);
                    canvas.strokeWidth(border.size[0]);
                    canvas.stroke();
                    return;
                }
            }

            // Top
            canvas.strokeColor(border.color[0]);
            canvas.beginPath();
            canvas.moveTo(Vec2f(pos.x + border.radius[0], pos.y + border.size[0] / 2.0f));

            auto endX = pos.x + size.x - border.radius[1];
            auto endY = pos.y + border.size[0] / 2.0f;

            canvas.strokeWidth(border.size[0]);
            canvas.lineTo(Vec2f(endX, endY));

            if (border.radius[1] > 0.1f) {
                const auto cp0 = ffw::Pointf(endX + border.radius[1] / 2.0f, endY);
                const auto cp1 = ffw::Pointf(pos.x + size.x - border.size[1] / 2.0f, pos.y + border.radius[1] / 2.0f);
                const auto end = ffw::Pointf(pos.x + size.x - border.size[1] / 2.0f, pos.y + border.radius[1]);

                if (border.color[0] == border.color[1] && FFW_FLOAT_EQUAL(border.size[0], border.size[1])) {
                    canvas.bezierTo(cp0, cp1, end);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    canvas.bezierTo(cp0A, cp0B, mid);

                    canvas.stroke();
                    canvas.beginPath();
                    canvas.moveTo(mid);
                    canvas.strokeColor(border.color[1]);

                    canvas.bezierTo(cp1A, cp1B, end);
                }
            }

            endX = pos.x + size.x - border.size[1] / 2.0f;
            endY = pos.y + size.y - border.radius[2];

            canvas.strokeWidth(border.size[1]);
            canvas.lineTo(Vec2f(endX, endY));

            if (border.radius[2] > 0.1f) {
                const auto cp0 = ffw::Pointf(endX, endY + border.radius[2] / 2.0f);
                const auto cp1 = ffw::Pointf(pos.x + size.x - border.radius[2] / 2.0f, pos.y + size.y - border.size[2] / 2.0f);
                const auto end = ffw::Pointf(pos.x + size.x - border.radius[2], pos.y + size.y - border.size[2] / 2.0f);

                if (border.color[1] == border.color[2] && FFW_FLOAT_EQUAL(border.size[1], border.size[2])) {
                    canvas.bezierTo(cp0, cp1, end);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    canvas.bezierTo(cp0A, cp0B, mid);

                    canvas.stroke();
                    canvas.beginPath();
                    canvas.moveTo(mid.x);
                    canvas.strokeColor(border.color[2]);

                    canvas.bezierTo(cp1A, cp1B, end);
                }
            }

            endX = pos.x + border.radius[3];
            endY = pos.y + size.y - border.size[2] / 2.0f;

            canvas.strokeWidth(border.size[2]);
            canvas.lineTo(Vec2f(endX, endY));

            if (border.radius[3] > 0.1f) {
                const auto cp0 = ffw::Pointf(pos.x + border.radius[3] / 2.0f, endY);
                const auto cp1 = ffw::Pointf(pos.x + border.size[3] / 2.0f, pos.y + size.y - border.radius[3] / 2.0f);
                const auto end = ffw::Pointf(pos.x + border.size[3] / 2.0f, pos.y + size.y - border.radius[3]);

                if (border.color[2] == border.color[3] && FFW_FLOAT_EQUAL(border.size[2], border.size[3])) {
                    canvas.bezierTo(cp0, cp1, end);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    canvas.bezierTo(cp0A, cp0B, mid);

                    canvas.stroke();
                    canvas.beginPath();
                    canvas.moveTo(mid);
                    canvas.strokeColor(border.color[3]);

                    canvas.bezierTo(cp1A, cp1B, end);
                }
            }

            endX = pos.x + border.size[3] / 2.0f;
            endY = pos.y + border.radius[0];

            canvas.strokeWidth(border.size[3]);
            canvas.lineTo(Vec2f(endX, endY));

            if (border.radius[0] > 0.1f) {
                const auto cp0 = ffw::Pointf(pos.x + border.size[3] / 2.0f, pos.y + border.radius[0] / 2.0f);
                const auto cp1 = ffw::Pointf(pos.x + border.radius[0] / 2.0f, pos.y + border.size[0] / 2.0f);
                const auto end = ffw::Pointf(pos.x + border.radius[0], pos.y + border.size[0] / 2.0f);

                if (border.color[3] == border.color[0] && FFW_FLOAT_EQUAL(border.size[3], border.size[0])) {
                    canvas.bezierTo(cp0, cp1, end);
                }
                else {
                    const auto start = ffw::Pointf(endX, endY);
                    const auto mid = (cp0 + cp1) / 2.0f;

                    const auto cp0A = (start + cp0) / 2.0f;
                    const auto cp0B = (cp0 + mid) / 2.0f;
                    const auto cp1A = (mid + cp1) / 2.0f;
                    const auto cp1B = (cp1 + end) / 2.0f;

                    canvas.bezierTo(cp0A, cp0B, mid);

                    canvas.stroke();
                    canvas.beginPath();
                    canvas.moveTo(mid);
                    canvas.strokeWidth(border.size[0]);
                    canvas.strokeColor(border.color[0]);

                    canvas.bezierTo(cp1A, cp1B, end);
                }
            }

            canvas.stroke();
        }

        const GLFramebuffer& getFbo() const {
            return fbo;
        }
        const GLTexture2D& getFboTexture() const {
            return fboTexture;
        }
        const GLCanvas::Image& getFboTextureImage() const {
            return fboTextureImage;
        }
    private:
        GLCanvas& canvas;
        GLFramebuffer fbo;
        GLTexture2D fboTexture;
        GLRenderbuffer2D fboStencil;
        GLCanvas::Image fboTextureImage;
    };
}
#endif
