/*** This file is part of FineFramework project ***/

#include "ffw/gui/guibody.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiBody::GuiBody(GuiWindow* context, const GuiOrientation orient):GuiLayout(context, orient) {
    setStyle(&context->getTheme()->body, true);
}

///=============================================================================
void ffw::GuiBody::eventThemeChanged(const GuiTheme* theme, bool defaults) {
    setStyle(&theme->body, defaults);
}

///=============================================================================
void ffw::GuiBody::setStyle(const GuiBody::Style* style, const bool defaults){
    widgetStyle = &style->self;
    if(defaults)setDefaults(&widgetStyle->defaults);
}