/*** This file is part of FineFramework project ***/

#include <regex>
#include "ffw/gui/guitextedit.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"
#include "ffw/gui/third_party/utfcpp/checked.h"

///=============================================================================
ffw::GuiTextInput::GuiTextInput(GuiWindow* context, bool multiline, bool editable):GuiWidget(context), multiline(multiline),lastCalculatedSize(-1.0f) {
    setStyle(&context->getTheme()->textInput, true);
    hasCtrl = false;
    lastCalculatedHeight = 0.0f;
    hasMouseDown = false;
    lines.push_back(std::unique_ptr<Line>(new Line()));
    regexMatch = std::regex(".*");
}

///=============================================================================
void ffw::GuiTextInput::setValue(const std::string& str) {
    size_t found = std::string::npos;
    size_t begin = 0;
    lines.clear();

    if (multiline) {
        while ((found = str.find('\n', begin)) != std::string::npos) {
            lines.push_back(std::unique_ptr<Line>(new Line(str.substr(begin, found - begin))));
            begin = ++found;
        }
        lines.push_back(std::unique_ptr<Line>(new Line(str.substr(begin, str.size() - begin))));
    } else {
        auto cpy = str;
        cpy.erase(std::remove(cpy.begin(), cpy.end(), '\n'), cpy.end());
        lines.push_back(std::unique_ptr<Line>(new Line(cpy)));
    }

    eventSize(getVisibleContentSize());
    resetSelection();
}

///=============================================================================
std::string ffw::GuiTextInput::getValue() const {
    std::string ret;
    bool first = true;
    for(const auto& line : lines) {
        ret += (first ? "" : "\n") + line->str;
        first = false;
    }
    return ret;
}

///=============================================================================
void ffw::GuiTextInput::appendValue(const std::string& str) {
    auto found = std::string::npos;
    size_t begin = 0;

    if (multiline) {
        while ((found = str.find('\n', begin)) != std::string::npos) {
            lines.push_back(std::unique_ptr<Line>(new Line(str.substr(begin, found - begin))));
            begin = ++found;
        }
        lines.push_back(std::unique_ptr<Line>(new Line(str.substr(begin, str.size() - begin))));
    } else {
        auto cpy = str;
        cpy.erase(std::remove(cpy.begin(), cpy.end(), '\n'), cpy.end());
        if(lines.empty())lines.push_back(std::unique_ptr<Line>(new Line(cpy)));
        else lines.back()->str += cpy;
    }

    eventSize(getVisibleContentSize());
    resetSelection();
}

///=============================================================================
float ffw::GuiTextInput::calculateHeight() const {
    auto height = 0.0f;
    for (auto& line : lines) {
        height += line->size.y;
    }
    return height;
}

///=============================================================================
void ffw::GuiTextInput::pushActionEvent() {
    GuiEvent::Data dat;
    dat.action.value = 1;
    pushEvent(GuiEventType::ACTION, dat);
}

///=============================================================================
ffw::Pointf ffw::GuiTextInput::getMinimumWrapSize() {
    if (getCurrentFont() == nullptr)return 0;
    const auto contentSize = getVisibleContentSize();
    if(std::abs(lastCalculatedSize - contentSize.x) > std::numeric_limits<float>::epsilon()) {
        eventSize(contentSize);
        lastCalculatedHeight = calculateHeight();
    }
    ffw::Pointf ret(contentSize.x, lastCalculatedHeight);
    return ret;
}

///=============================================================================
int ffw::GuiTextInput::getSelectionNumOfLines() const {
    if (getCurrentFont() == nullptr) return 0;
    const auto lineHeight = getCurrentFont()->getEmptyLineHeight(getLineHeight());
    return int(ceil(std::abs(selectionPos.y - cursorPos.y) / lineHeight) + 1);
}

///=============================================================================
void ffw::GuiTextInput::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    (void)contentsize;
    if (getCurrentFont() == nullptr) return;
    
    if (!lines.empty()) {
        const auto lineHeight = getCurrentFont()->getEmptyLineHeight(getLineHeight());
        auto p = contentoffset.ceil(); // Align to integer so we have sharper text

        if (selectionIndex != cursorIndex) {
            const int numOfLines = getSelectionNumOfLines();
            const auto& selectionColor = getCurrentStyle()->function.color;

            // Only one line selected
            if (numOfLines == 1) {
                if (cursorPos.x < selectionPos.x) {
                    // From left to right selection
                    context->drawRectangle(p + cursorPos, ffw::Pointf(selectionPos.x - cursorPos.x, lineHeight), selectionColor);
                } else {
                    // From right to left selection
                    context->drawRectangle(p + selectionPos, ffw::Pointf(cursorPos.x - selectionPos.x, lineHeight), selectionColor);
                }
            }
            else {
                // From top to bottom selection
                if (cursorPos.y < selectionPos.y) {
                    context->drawRectangle(p + cursorPos, ffw::Pointf(contentsize.x - cursorPos.x, lineHeight), selectionColor);

                    for (int i = 1; i < numOfLines - 1; i++) {
                        context->drawRectangle(p + ffw::Pointf(0.0f, cursorPos.y + i * lineHeight), ffw::Pointf(contentsize.x, lineHeight), selectionColor);
                    }

                    if (numOfLines > 1) {
                        context->drawRectangle(p + ffw::Pointf(0.0f, selectionPos.y), ffw::Pointf(selectionPos.x, lineHeight), selectionColor);
                    }
                } 
                // From bottom to top selection
                else {
                    if (numOfLines > 1) {
                        context->drawRectangle(p + selectionPos, ffw::Pointf(contentsize.x - selectionPos.x, lineHeight), selectionColor);
                    }

                    for (int i = 1; i < numOfLines - 1; i++) {
                        context->drawRectangle(p + ffw::Pointf(0.0f, selectionPos.y + i * lineHeight), ffw::Pointf(contentsize.x, lineHeight), selectionColor);
                    }

                    context->drawRectangle(p + ffw::Pointf(0.0f, cursorPos.y), ffw::Pointf(cursorPos.x, lineHeight), selectionColor);
                }
            }
        }

        const auto& textColor = getCurrentStyle()->text.color;
        const auto textFont = getCurrentFont();

        for (const auto& line : lines) {
            auto height = p.y;

            for (const auto& c : line->chunks) {
                context->drawString(ffw::Pointf(p.x, height), textFont, c.str, c.len, textColor, getLineHeight());
                height += c.height;
            }

            p.y += line->size.y;
        }
    }

    if (hasFocus() && cursorIndex == selectionIndex) {
        const auto p = (contentoffset + cursorPos).ceil(); // Align to integer so we have sharper text
        context->drawLine(p, p + ffw::Pointf(0.0f, getCurrentFont()->getEmptyLineHeight(getLineHeight())), getCurrentStyle()->text.color);
    }
}

///=============================================================================
void ffw::GuiTextInput::Line::recalculate(const float width, const GuiFont* font, const float lineHeight) {
    if (!str.empty()) {
        chunks = font->splitString(str, width, lineHeight);
        size.set(0.0f, 0.0f);
        for (const auto& c : chunks) {
            size.y += c.height;
            size.x = std::max(size.x, c.width);
        }
        if (size.y <= 0.0f) {
            size = ffw::Pointf(size.x, font->getEmptyLineHeight(lineHeight));
        }
    }
    else {
        chunks.clear();
        size = ffw::Pointf(width, font->getEmptyLineHeight(lineHeight));
    }
}

///=============================================================================
void ffw::GuiTextInput::recalculateLine(Line& line, const float width) const {
    line.recalculate(width, getCurrentFont(), getLineHeight());
}

///=============================================================================
bool ffw::GuiTextInput::setCursorIndex(const size_t strOffset, const size_t lineNum) {
    if (!lines.empty()) {
        if (lineNum < lines.size()) {
            if (strOffset <= lines[lineNum]->str.size()) {
                cursorIndex.set(strOffset, lineNum);
                if (hasFocus()) {
                    cursorPos = getCursorPos(cursorIndex);
                    redraw();
                    resetSelection();
                    return true;
                }
            }
        }
    }
    return false;
}

///=============================================================================
void ffw::GuiTextInput::moveCursor(const bool forward) {
    if (!lines.empty()) {
        if (forward) {
            const auto& current = lines[cursorIndex.y];
            if (cursorIndex.x == current->str.size()) {
                if (cursorIndex.y + 1 < lines.size()) {
                    cursorIndex.x = 0;
                    cursorIndex.y += 1;
                }
            }
            else {
                const char* it = &current->str[cursorIndex.x];
                utf8::next<const char*>(it, current->str.c_str() + current->str.size());
                cursorIndex.x = it - current->str.c_str();
            }
        }
        else {
            const auto& current = lines[cursorIndex.y];
            if (cursorIndex.x == 0) {
                if (cursorIndex.y > 0) {
                    cursorIndex.y--;
                    cursorIndex.x = lines[cursorIndex.y]->str.size();
                } else {
                    cursorIndex.x = 0;
                }
            } else {
                const char* it = &current->str[cursorIndex.x];
                utf8::previous<const char*>(it, current->str.c_str() + current->str.size());
                cursorIndex.x = it - current->str.c_str();
            }
        }

        cursorPos = getCursorPos(cursorIndex);
        redraw();
        resetSelection();
    }
}

///=============================================================================
void ffw::GuiTextInput::eventSize(const ffw::Pointf& size) {
    if (getCurrentFont() != nullptr && std::abs(lastCalculatedSize - size.x) > std::numeric_limits<float>::epsilon()) {
        lastCalculatedSize = size.x;
        for (auto& line : lines) {
            recalculateLine(*line, size.x);
        }
        if(hasFocus()) {
            cursorPos = getCursorPos(cursorIndex);
        }
        lastCalculatedHeight = calculateHeight();
        resetSelection();
    }
}

///=============================================================================
std::pair<ffw::Pointf, ffw::Point<size_t>> ffw::GuiTextInput::getCursorIndex(const ffw::Pointf& mouse) {
    std::pair<ffw::Pointf, ffw::Point<size_t>> ret;

    if (getCurrentFont() == nullptr) {
        ret.second = 0;
        ret.first = 0;
        return ret;
    }

    const auto font = getCurrentFont();

    auto testH = 0.0f;
    size_t y = 0;
    for (auto& line : lines) {
        if (mouse.y >= testH && mouse.y < testH + line->size.y) {
            ret.second.y = y;
            ret.second.x = 0;
            ret.first.x = 0.0f;
            ret.first.y = testH;
            ret.first = ret.first.floor();

            auto height = testH;
            for (size_t i = 0; i < line->chunks.size(); i++) {
                const auto& c = line->chunks[i];
                height += c.height;
                if (height >= mouse.y) {
                    size_t cLen;
                    if (i + 1 < line->chunks.size()) {
                        cLen = line->chunks[i + 1].str - c.str;
                    } else {
                        cLen = std::strlen(c.str);
                    }
                    const auto index = font->getCharIndex(c.str, cLen, mouse, &ret.first.x);
                    ret.second.x = (c.str - line->str.c_str()) + index;
                    break;
                }
                ret.first.y += c.height;
            }

            return ret;
        }

        testH += line->size.y;
        y++;
    }

    ret.second = 0;
    ret.first = 0.0f;

    return ret;
}

///=============================================================================
ffw::Pointf ffw::GuiTextInput::getCursorPos(const ffw::Point<size_t>& index) {
    ffw::Pointf ret;

    const auto indexY = index.y >= lines.size() ? lines.size() : index.y;

    const auto font = getCurrentFont();

    for (const auto& line : lines) {
        if (&line == &lines[indexY]) {
            if (index.x == 0) return ret;
            for (size_t i = 0; i < line->chunks.size(); i++) {
                const auto& c = line->chunks[i];
                const size_t from = c.str - line->str.c_str();
                size_t cLen;
                if (i + 1 < line->chunks.size()) {
                    cLen = line->chunks[i + 1].str - c.str;
                }
                else {
                    cLen = std::strlen(c.str);
                }
                const size_t to = from + cLen;
                if (index.x == to) {
                    ret.x = font->getCharPos(c.str, cLen, cLen);
                    return ret;
                }
                if (index.x >= from && index.x < to) {
                    ret.x = font->getCharPos(c.str, cLen, index.x - (c.str - line->str.c_str()));
                    return ret;
                }
                if (i + 1 == line->chunks.size()) {
                    ret.x = c.width;
                    return ret;
                }
                ret.y += c.height;
            }
            return ret;
        }

        ret.y += line->size.y;
    }

    return ret;
}

///=============================================================================
void ffw::GuiTextInput::resetSelection() {
    selectionPos = cursorPos;
    selectionIndex = cursorIndex;
}

///=============================================================================
void ffw::GuiTextInput::eventHover(const bool gained) {
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiTextInput::eventFocus(const bool gained) {
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiTextInput::eventMouse(const ffw::Pointf& pos) {
    if (hasMouseDown) {
        const auto& pair = getCursorIndex(pos);
        if (pair.second != selectionIndex) {
            selectionIndex = pair.second;
            selectionPos = pair.first;
            redraw();
        }
    }
}

///=============================================================================
bool ffw::GuiTextInput::eventScroll(const ffw::Pointf& scroll) {
    return false;
}

///=============================================================================
void ffw::GuiTextInput::eventMouseButton(const ffw::MouseButton button, const ffw::MouseMode mode) {
    if (mode == ffw::MouseMode::PRESSED && button == ffw::MouseButton::LEFT) {
        const auto& pair = getCursorIndex(getMousePos());
        cursorPos = pair.first;
        cursorIndex = pair.second;
        resetSelection();
        redraw();
        hasMouseDown = true;
    }
    if (mode == ffw::MouseMode::RELEASED && button == ffw::MouseButton::LEFT) {
        hasMouseDown = false;
    }
}

///=============================================================================
void ffw::GuiTextInput::deleteSelection() {
    if (cursorIndex.y < lines.size()) {
        if (selectionIndex == cursorIndex) {
            return;
        }
        else if (selectionIndex.y == cursorIndex.y) {
            // Remove selection only from one line
            size_t len;
            if (cursorIndex.x > selectionIndex.x)len = cursorIndex.x - selectionIndex.x;
            else len = selectionIndex.x - cursorIndex.x;

            const auto pos = std::min(selectionIndex.x, cursorIndex.x);

            auto& previous = lines[cursorIndex.y];
            previous->str = previous->str.erase(pos, len);
            cursorIndex.x = pos;

            recalculateLine(*lines[cursorIndex.y], lastCalculatedSize);
        }
        else {
            // Remove selection from multiple lines
            // Remove first line
            auto firstPos = cursorIndex;
            if (selectionIndex.y < cursorIndex.y) {
                firstPos = selectionIndex;
            }
            auto lastPos = selectionIndex;
            if (selectionIndex.y < cursorIndex.y) {
                lastPos = cursorIndex;
            }

            // Modify first line
            auto& first = lines[firstPos.y];
            first->str = first->str.substr(0, firstPos.x);

            // Append last line
            auto& last = lines[lastPos.y];
            first->str += last->str.substr(lastPos.x, last->str.size() - lastPos.x);

            // Remove all lines except the first one
            if (firstPos.y != lastPos.y) {
                lines.erase(lines.begin() + (firstPos.y + 1), lines.begin() + lastPos.y + 1);
            }

            cursorIndex.y = firstPos.y;
            cursorIndex.x = firstPos.x;
            
            recalculateLine(*lines[cursorIndex.y], lastCalculatedSize);
        }
        cursorPos = getCursorPos(cursorIndex);

        const auto test = lastCalculatedHeight;
        lastCalculatedHeight = calculateHeight();
        if (std::abs(test - lastCalculatedHeight) > std::numeric_limits<float>::epsilon()) {
            invalidate();
            redraw();
        }
        else {
            redraw();
        }
        resetSelection();
    }
}

///=============================================================================
void ffw::GuiTextInput::splitLineAtCursor() {
    if (!multiline)return;

    if (cursorIndex.y < lines.size()) {
        if (hasSelection()) {
            deleteSelection();
        }

        lines.insert(lines.begin() + cursorIndex.y + 1, std::unique_ptr<Line>(new Line()));

        auto& previous = lines[cursorIndex.y];
        auto& inserted = lines[cursorIndex.y + 1];

        inserted->str = previous->str.substr(cursorIndex.x);
        previous->str = previous->str.substr(0, cursorIndex.x);

        recalculateLine(*previous, lastCalculatedSize);
        recalculateLine(*inserted, lastCalculatedSize);

        cursorIndex.y += 1;
        cursorIndex.x = 0;
        cursorPos = getCursorPos(cursorIndex);

        const auto test = lastCalculatedHeight;
        lastCalculatedHeight = calculateHeight();
        if (std::abs(test - lastCalculatedHeight) > std::numeric_limits<float>::epsilon()) {
            invalidate();
            redraw();
        }
        else {
            redraw();
        }

        resetSelection();
    }
}

///=============================================================================
void ffw::GuiTextInput::insertAtCursor(const std::string& str) {
    auto cpy = str;
    if (multiline) {
        cpy.erase(std::remove(cpy.begin(), cpy.end(), '\n'), cpy.end());
    }

    if(cursorIndex.y < lines.size()) {
        if (hasSelection()) {
            deleteSelection();
        }

        auto& line = lines[cursorIndex.y];
        bool inserted = false;
        if(cursorIndex.x < line->str.size()) {
            line->str.insert(cursorIndex.x, cpy);
            inserted = true;
        } else if(cursorIndex.x == line->str.size()) {
            line->str.append(cpy);
            inserted = true;
        }

        if(inserted) {
            cursorIndex.x += cpy.size();
            recalculateLine(*line, lastCalculatedSize);
            cursorPos = getCursorPos(cursorIndex);
            const auto test = lastCalculatedHeight;
            lastCalculatedHeight = calculateHeight();
            if(std::abs(test - lastCalculatedHeight) > std::numeric_limits<float>::epsilon()) {
                invalidate();
            } else {
                redraw();
            }
        }
    } else {
        lines.push_back(std::unique_ptr<Line>(new Line()));
        lines.back()->str = cpy;
        recalculateLine(*lines.back(), lastCalculatedSize);
        const auto test = lastCalculatedHeight;
        lastCalculatedHeight = calculateHeight();
        if (std::abs(test - lastCalculatedHeight) > std::numeric_limits<float>::epsilon()) {
            invalidate();
            redraw();
        }
        else {
            redraw();
        }
    }

    resetSelection();
}

///=============================================================================
void ffw::GuiTextInput::removeAtCursor(const bool forward) {
    if (hasSelection()) {
        deleteSelection();
        return;
    }

    if (cursorIndex.y < lines.size()) {
        auto& line = lines[cursorIndex.y];
        bool removed = false;
        if(forward) {
            if (cursorIndex.x + 1 <= line->str.size()) {
                const char* posToEraseAt = &line->str[cursorIndex.x];
                const char* nextpos = posToEraseAt;
                utf8::next<const char*>(nextpos, &line->str[0] + line->str.size());
                const auto num = nextpos - posToEraseAt;
                line->str.erase(cursorIndex.x, num);
                removed = true;
                recalculateLine(*line, lastCalculatedSize);
            } else {
                // User wants to remove '\n' so we will merge this line with the next one
                if (cursorIndex.x == line->str.size() && cursorIndex.y + 1 < lines.size()) {
                    auto& next = lines[cursorIndex.y + 1];
                    line->str += next->str;
                    lines.erase(lines.begin() + cursorIndex.y + 1);
                    removed = true;
                    recalculateLine(*line, lastCalculatedSize);
                }
            }
        } else {
            if (cursorIndex.x > 0 && cursorIndex.x <= line->str.size()) {
                const char* nextpos = &line->str[cursorIndex.x];
                const char* posToEraseAt = nextpos;
                utf8::previous<const char*>(nextpos, &line->str[0] + line->str.size());
                const auto num = posToEraseAt - nextpos;
                cursorIndex.x = cursorIndex.x - num;
                line->str.erase(cursorIndex.x, num);
                removed = true;
                recalculateLine(*line, lastCalculatedSize);
            } else {
                // User wants to remove '\n' so we will merge this line with the previous one
                if (cursorIndex.x == 0 && cursorIndex.y > 0) {
                    auto& previous = lines[cursorIndex.y - 1];
                    cursorIndex.x = previous->str.size();
                    previous->str += line->str;
                    lines.erase(lines.begin() + cursorIndex.y);
                    cursorIndex.y -= 1;
                    removed = true;
                    recalculateLine(*previous, lastCalculatedSize);
                }
            }
        }

        if(removed) {
            cursorPos = getCursorPos(cursorIndex);
            const auto test = lastCalculatedHeight;
            lastCalculatedHeight = calculateHeight();
            if (std::abs(test - lastCalculatedHeight) > std::numeric_limits<float>::epsilon()) {
                invalidate();
                redraw();
            }
            else {
                redraw();
            }
        }
    }

    resetSelection();
}

///=============================================================================
void ffw::GuiTextInput::eventText(uint32_t chr) {
    std::string result;
    utf8::utf32to8(&chr, &chr + 1, std::back_inserter(result));

    insertAtCursor(result);
    // Validate input
    if (!multiline && cursorIndex.y < lines.size() && !std::regex_match(lines[cursorIndex.y]->str, regexMatch)) {
        removeAtCursor(false);
    }

    resetSelection();
}

///=============================================================================
void ffw::GuiTextInput::moveCursorToEnd() {
    if (!lines.empty()) {
        auto& last = lines[lines.size() - 1];
        setCursorIndex(last->str.size(), lines.size() - 1);
    }
}

///=============================================================================
void ffw::GuiTextInput::moveCursorToStart() {
    if (!lines.empty()) {
        setCursorIndex(0, 0);
    }
}

///=============================================================================
void ffw::GuiTextInput::eventKey(ffw::Key key, ffw::KeyMode mode) {
    if(mode == ffw::KeyMode::PRESSED || mode == ffw::KeyMode::REPEAT) {
        switch(key) {
            case ffw::Key::BACKSPACE: {
                removeAtCursor(false);
                break;
            }
            case ffw::Key::FUNCTION_DELETE: {
                removeAtCursor(true);
                break;
            }
            case ffw::Key::ARROW_LEFT: {
                moveCursor(false);
                break;
            }
            case ffw::Key::ARROW_RIGHT: {
                moveCursor(true);
                break;
            }
            case ffw::Key::ENTER:
            case ffw::Key::NUMPAD_ENTER: {
                splitLineAtCursor();
                break;
            }
            case ffw::Key::CONTROL_LEFT:
            case ffw::Key::CONTROL_RIGHT: {
                hasCtrl = true;
                break;
            }
            case ffw::Key::FUNCTION_HOME: {
                if (!lines.empty()) {
                    if (hasCtrl) moveCursorToStart();
                    else setCursorIndex(0, cursorIndex.y);
                }
                break;
            }
            case ffw::Key::FUNCTION_END: {
                if (!lines.empty()) {
                    if (hasCtrl) {
                        moveCursorToEnd();
                    }
                    else {
                        auto& current = lines[cursorIndex.y];
                        setCursorIndex(current->str.size(), cursorIndex.y);
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
    }

    if (mode == ffw::KeyMode::RELEASED) {
        switch (key) {
            case ffw::Key::CONTROL_LEFT:
            case ffw::Key::CONTROL_RIGHT: {
                hasCtrl = false;
                break;
            }
            default: {
                break;
            }
        }
    }
}

///=============================================================================
void ffw::GuiTextInput::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->textInput, defaults);
}

///=============================================================================
void ffw::GuiTextInput::setStyle(const GuiTextInput::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::GuiScrollableTextInput::Inner::Inner(GuiWindow* context, const bool editable):GuiTextInput(context, true, editable) {
    setStyle(&context->getTheme()->textArea.inner, true);
}

///=============================================================================
void ffw::GuiScrollableTextInput::Inner::setStyle(const Inner::Style* style, const bool defaults) {
    GuiTextInput::setStyle(&style->self, defaults);
}

///=============================================================================
void ffw::GuiScrollableTextInput::Inner::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->textArea.inner, defaults);
}

///=============================================================================
ffw::GuiScrollableTextInput::GuiScrollableTextInput(GuiWindow* context, const bool editable):
    GuiScrollable(context, textinput = new GuiScrollableTextInput::Inner(context, editable), false, true) {
    setStyle(&context->getTheme()->textArea, true);
}

///=============================================================================
void ffw::GuiScrollableTextInput::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->textArea, defaults);
}

///=============================================================================
void ffw::GuiScrollableTextInput::setStyle(const GuiScrollableTextInput::Style* style, const bool defaults) {
    GuiScrollable::setStyle(&style->self, defaults);
    textinput->setStyle(&style->inner, defaults);
    if (defaults)setDefaults(&widgetStyle->defaults);
}