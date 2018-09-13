/*** This file is part of FineFramework project ***/

#include "ffw/gui/guitext.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiText::GuiText(GuiWindow* context) : GuiWidget(context),lastCalculatedWidth(0) {
    setIgnoreUserInput(true);
    setStyle(&context->getTheme()->richText, true);
}

///=============================================================================
ffw::GuiText::Paragraph* ffw::GuiText::addParagraph(const std::string& text) {
    const auto font = getCurrentFont();
    const auto textColor = getStyleGroup()->normal.text.color;
    paragraphs.push_back(Paragraph(font, textColor, text));
    paragraphs.back().recalculate(getVisibleContentSize().x, getCurrentFont(), getLineHeight());
    redraw();
    return &paragraphs.back();
}

///=============================================================================
ffw::GuiText::Paragraph* ffw::GuiText::addParagraph(const std::string& text, const Color& color, const GuiFont* font) {
    paragraphs.push_back(Paragraph(font, color, text));
    paragraphs.back().recalculate(getVisibleContentSize().x, getCurrentFont(), getLineHeight());
    redraw();
    return &paragraphs.back();
}

///=============================================================================
void ffw::GuiText::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    (void)contentsize;
    if (getCurrentFont() == nullptr) return;

    if (!paragraphs.empty()) {
        auto p = contentoffset;
        for (const auto& para : paragraphs) {
            auto height = p.y;

            for (const auto& c : para.chunks) {
                context->drawString(ffw::Pointf(p.x, height), para.font, c.str, c.len, para.color, getLineHeight());
                height += c.height;
            }

            p.y += para.size.y;
        }
    }
}

///=============================================================================
void ffw::GuiText::eventSize(const ffw::Pointf& size) {
    (void)size;
    lastCalculatedWidth = getVisibleContentSize().x;
    recalculateSize(lastCalculatedWidth);
}

///=============================================================================
void ffw::GuiText::Paragraph::recalculate(const float width, const GuiFont* fallback, const float lineHeight) {
    auto f = font;
    if (f == nullptr)f = fallback;

    if (!str.empty()) {
        chunks = f->splitString(str, width, lineHeight);
        size.set(0.0f, 0.0f);
        for (const auto& c : chunks) {
            size.y += c.height;
            size.x = std::max(size.x, c.width);
        }
    }
    else {
        size = ffw::Pointf(width, font->getEmptyLineHeight(lineHeight));
    }
}

///=============================================================================
void ffw::GuiText::recalculateSize(const float width) {
    if (getCurrentFont() != nullptr) {
        for (auto& para : paragraphs) {
            para.recalculate(width, getCurrentFont(), getLineHeight());
        }
    }
}

///=============================================================================
void ffw::GuiText::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->richText, defaults);
}

///=============================================================================
void ffw::GuiText::setStyle(const GuiText::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiText::getMinimumWrapSize() {
    if (getCurrentFont() == nullptr) return 0;
    const auto test = getVisibleContentSize().x;;
    if(test != lastCalculatedWidth) {
        recalculateSize(test);
    }
    ffw::Pointf ret(test, 0);
    for(const auto& para : paragraphs) {
        ret.y += para.size.y;
    }
    return ret;
}
