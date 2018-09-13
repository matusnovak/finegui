/*** This file is part of FineFramework project ***/

#include "ffw/gui/guilabel.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiLabel::GuiLabel(GuiWindow* context, const std::string& label):GuiWidget(context),label(label){
    setStyle(&context->getTheme()->label, true);
}

///=============================================================================
void ffw::GuiLabel::setLabel(const std::string& label){
    this->label = label;
    redraw();
}

///=============================================================================
const std::string& ffw::GuiLabel::getLabel() const {
    return label;
}

///=============================================================================
void ffw::GuiLabel::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize){
    context->drawStringAligned(contentoffset, contentsize, getCurrentFont(), getAlign(), label, getCurrentStyle()->text, getLineHeight());
}

///=============================================================================
void ffw::GuiLabel::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->label, defaults);
}

///=============================================================================
void ffw::GuiLabel::setStyle(const GuiLabel::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if(defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiLabel::getMinimumWrapSize() {
    if(getCurrentFont() == nullptr)return 0;
    return getCurrentFont()->getStringSize(label, -1.0f, getLineHeight());
}