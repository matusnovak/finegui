/*** This file is part of FineFramework project ***/

#include "ffw/gui/guibuttontoggle.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiButtonToggle::GuiButtonToggle(GuiWindow* context, const std::string& label) : GuiButton(context, label) {
    setToggleFocus();
}

///=============================================================================
void ffw::GuiButtonToggle::setValue(const bool value) {
    setFocus(value);
}

///=============================================================================
bool ffw::GuiButtonToggle::getValue() const {
    return hasFocus();
}

///=============================================================================
void ffw::GuiButtonToggle::eventFocus(const bool gained) {
    GuiEvent::Data data;
    data.action.value = gained;
    pushEvent(GuiEventType::ACTION, data);
    redraw();
}

///=============================================================================
ffw::GuiButtonTogglePrimary::GuiButtonTogglePrimary(GuiWindow* context, const std::string& label) :
    GuiButtonPrimary(context, label) {

    setToggleFocus();
}

///=============================================================================
void ffw::GuiButtonTogglePrimary::setValue(const bool value) {
    setFocus(value);
}

///=============================================================================
bool ffw::GuiButtonTogglePrimary::getValue() const {
    return hasFocus();
}

///=============================================================================
void ffw::GuiButtonTogglePrimary::eventFocus(const bool gained) {
    GuiEvent::Data data;
    data.action.value = gained;
    pushEvent(GuiEventType::ACTION, data);
    redraw();
}