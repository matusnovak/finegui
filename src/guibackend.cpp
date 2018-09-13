/*** This file is part of FineFramework project ***/

#include <iomanip>
#include "ffw/gui/guibackend.h"

///=============================================================================
void ffw::GuiBackend::drawStringAligned(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiFont* font, ffw::GuiAlign align, const std::string& str, const ffw::GuiStyle::Text& text, float lineHeight) const {
    if(font == NULL)return;

    const ffw::Pointf& strsize = font->getStringSize(str, -1.0f);
    ffw::Pointf offset = 0;

    switch (align){
    case GuiAlign::LEFT:
        offset.y = size.y/2 - strsize.y/2;
        break;

    case GuiAlign::RIGHT:
        offset.x = size.x - strsize.x;
        offset.y = size.y/2 - strsize.y/2;
        break;

    case GuiAlign::CENTER:
        offset = size/2 - strsize/2;
        break;

    case GuiAlign::TOP_CENTER:
        offset.x = size.x/2 - strsize.x/2;
        break;

    case GuiAlign::TOP_RIGHT:
        offset.x = size.x - strsize.x;
        break;

    case GuiAlign::BOTTOM_LEFT:
        offset.y = size.y - strsize.y;
        break;

    case GuiAlign::BOTTOM_CENTER:
        offset.x = size.x/2 - strsize.x/2;
        offset.y = size.y - strsize.y;
        break;

    case GuiAlign::BOTTOM_RIGHT:
        offset.x = size.x - strsize.x;
        offset.y = size.y - strsize.y;
        break;

    case GuiAlign::TOP_LEFT:
    default:
        break;
    }

    drawString((pos + offset).floor(), font, &str[0], str.size(), text.color, lineHeight);
}