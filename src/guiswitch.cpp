/*** This file is part of FineFramework project ***/

#include "ffw/gui/guiswitch.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiSwitch::GuiSwitch(GuiWindow* context) :
    GuiWidget(context),styleButton(nullptr) {
    setToggleFocus();

    setStyle(&context->getTheme()->swtch, true);
}

///=============================================================================
void ffw::GuiSwitch::setValue(const bool value) {
    setFocus(value);
}

///=============================================================================
bool ffw::GuiSwitch::getValue() const {
    return hasFocus();
}

///=============================================================================
void ffw::GuiSwitch::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    const auto style = getCurrentStyle(styleButton);
    if (style != nullptr) {
        float off = 0;
        if (hasFocus()) {
            off = contentsize.x - contentsize.y;
        }
        const ffw::Pointf buttonSize(contentsize.y, contentsize.y);
        const ffw::Pointf buttonPos(contentoffset.x + off, contentoffset.y);
        renderComponent(buttonPos, buttonSize, style);
    }
}

///=============================================================================
void ffw::GuiSwitch::eventHover(bool gained) {
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiSwitch::eventFocus(bool gained) {
    redraw();

    GuiEvent::Data dat;
    dat.action.value = gained;
    pushEvent(GuiEventType::ACTION, dat);
}

///=============================================================================
void ffw::GuiSwitch::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->swtch, defaults);
}

///=============================================================================
void ffw::GuiSwitch::setStyle(const GuiSwitch::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    styleButton = &style->button;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiSwitch::getMinimumWrapSize() {
    return ffw::Pointi(16, 8);
}