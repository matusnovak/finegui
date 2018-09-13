/*** This file is part of FineFramework project ***/

#include "ffw/gui/guibutton.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiButton::GuiButton(GuiWindow* context, const std::string& label) :
    GuiWidget(context), label(label) {
    setDropFocus();

    setStyle(&context->getTheme()->button, true);
}

///=============================================================================
void ffw::GuiButton::setLabel(const std::string& label) {
    this->label = label;
    redraw();
}

///=============================================================================
const std::string& ffw::GuiButton::getLabel() const {
    return label;
}

///=============================================================================
void ffw::GuiButton::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    context->drawStringAligned(contentoffset, contentsize, getCurrentFont(), getAlign(), label, getCurrentStyle()->text, getLineHeight());
}

///=============================================================================
void ffw::GuiButton::eventHover(const bool gained) {
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiButton::eventFocus(const bool gained) {
    redraw();

    if (!gained || getFocusType() != GuiFocusType::DROP) {
        GuiEvent::Data dat;
        if (getFocusType() == GuiFocusType::DROP)dat.action.value = true;
        else dat.action.value = gained;
        pushEvent(GuiEventType::ACTION, dat);
    }
}

///=============================================================================
void ffw::GuiButton::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->button, defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiButton::getMinimumWrapSize() {
    if (getCurrentFont() == nullptr || label.empty())return 0;
    return getCurrentFont()->getStringSize(label, -1.0f, getLineHeight());
}

///=============================================================================
void ffw::GuiButton::setStyle(const GuiButton::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::GuiButtonPrimary::GuiButtonPrimary(GuiWindow* context, const std::string& label) :
    GuiButton(context, label) {

    setStyle(&context->getTheme()->buttonPrimary, true);
}

///=============================================================================
void ffw::GuiButtonPrimary::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->buttonPrimary, defaults);
}

///=============================================================================
void ffw::GuiButtonPrimary::setStyle(const GuiButtonPrimary::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}