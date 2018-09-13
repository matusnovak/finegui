/*** This file is part of FineFramework project ***/

#include "ffw/gui/guidummy.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiDummy::GuiDummy(GuiWindow* context) :
    GuiWidget(context) {
    setDropFocus();

    setHidden(true);
    setStyle(&context->getTheme()->dummy, true);
}

///=============================================================================
void ffw::GuiDummy::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    // void
}

///=============================================================================
void ffw::GuiDummy::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->dummy, defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiDummy::getMinimumWrapSize() {
    return 0;
}

///=============================================================================
void ffw::GuiDummy::setStyle(const GuiDummy::Style* style, const bool defaults) {
    widgetStyle = style;
    if (defaults)setDefaults(&widgetStyle->defaults);
}
