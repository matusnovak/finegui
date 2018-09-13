#include "ffw/gui/guifont.h"
#include "ffw/gui/guitextwrapper.h"

///=============================================================================
std::vector<ffw::GuiFont::Chunk> ffw::GuiFont::splitString(const std::string& str, const float maxWidth, const float lineHeight) const {
    std::vector<Chunk> chunks;
    auto wrapper = GuiTextWrapper<char>(&str[0], &str[0] + str.size());
    const auto height = getEmptyLineHeight(lineHeight);
    while (const auto token = wrapper.next(this, maxWidth)) {
        chunks.push_back(Chunk());
        auto& it = chunks.back();
        it.str = token.str;
        it.len = token.len;
        it.width = token.width;
        it.height = height;
    }
    return chunks;
}

///=============================================================================
size_t ffw::GuiFont::getCharIndex(const std::string::value_type* str, const size_t len, const Pointf& pos, float* x) const {
    auto it = str;
    const auto end = str + len;
    auto width = 0.0f;
    while (it != end) {
        const auto current = it - str;
        const auto chr = utf8::next(it, end);
        const auto advance = getCharAdvance(chr);
        if (width <= pos.x && width + advance >= pos.x) {
            if (x) *x = width;
            return current;
        }
        width += advance;
        //utf8::advance(it, 1, end);
    }
    if (x) *x = width;
    return it - str;
}

///=============================================================================
float ffw::GuiFont::getCharPos(const std::string::value_type* str, const size_t len, const size_t index) const {
    auto it = str;
    const auto end = str + len;
    auto width = 0.0f;
    while (it != end) {
        const auto current = it - str;
        const auto chr = utf8::next(it, end);
        const auto advance = getCharAdvance(chr);
        if (index == size_t(it - str)) {
            return width + advance;
        }
        width += advance;
        //utf8::advance(it, 1, end);
    }
    return width;
}
