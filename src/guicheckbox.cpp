/*** This file is part of FineFramework project ***/

#include "ffw/gui/guicheckbox.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiCheckbox::Button::Button(GuiWindow* context):GuiWidget(context){
    setToggleFocus();

    setStyle(&context->getTheme()->checkbox.button, true);
}

///=============================================================================
void ffw::GuiCheckbox::Button::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize){
    const auto width = std::min(contentsize.x, contentsize.y) / 2.0f;
    auto p = contentoffset + contentsize / 2.0f;
    context->drawLine(
        ffw::Pointf(p.x - width, p.y).floor(),
        ffw::Pointf(p.x - width / 2.0f, p.y + width).ceil(),
        getCurrentStyle()->function.color,
        2.0f
    );
    context->drawLine(
        ffw::Pointf(p.x - width / 2.0f, p.y + width).ceil(),
        ffw::Pointf(p.x + width, p.y - width).floor(),
        getCurrentStyle()->function.color,
        2.0f
    );
}

///=============================================================================
void ffw::GuiCheckbox::Button::eventHover(const bool gained){
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiCheckbox::Button::eventFocus(const bool gained){
    redraw();

    GuiEvent::Data dat;
    dat.action.value = gained;
    pushEvent(GuiEventType::ACTION, dat);
}

///=============================================================================
void ffw::GuiCheckbox::Button::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->checkbox.button, defaults);
}

///=============================================================================
void ffw::GuiCheckbox::Button::setStyle(const GuiCheckbox::Button::Style* style, const bool defaults){
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiCheckbox::Button::getMinimumWrapSize() {
    return 8.0f;
}

///=============================================================================
ffw::GuiCheckbox::GuiCheckbox(GuiWindow* context, const std::string& label):GuiWidget(context),label(label){
    setOrientationInternal(GuiOrientation::HORIZONTAL);
    setToggleFocus();

    widgetbutton = new GuiCheckbox::Button(context);
    widgetbutton->addEventCallback([=](GuiEvent e) -> void {
        this->pushEvent(e.type, e.data);
    }, GuiEventType::ACTION, true);

    addWidgetInternal(widgetbutton);
    setStyle(&context->getTheme()->checkbox, true);
}

///=============================================================================
void ffw::GuiCheckbox::setLabel(const std::string& label){
    this->label = label;
    redraw();
}

///=============================================================================
const std::string& ffw::GuiCheckbox::getLabel() const {
    return label;
}

///=============================================================================
void ffw::GuiCheckbox::setValue(const bool value){
    setFocus(value);
}

///=============================================================================
bool ffw::GuiCheckbox::getValue() const {
    return hasFocus();
}

///=============================================================================
void ffw::GuiCheckbox::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize){
    auto s = widgetbutton->getRealSize();
    s.x += widgetbutton->getMarginInPixels(1);
    s.y = 0;
    context->drawStringAligned(contentoffset + s, contentsize - s, getCurrentFont(), getAlign(), label, getCurrentStyle()->text, getLineHeight());
}

///=============================================================================
void ffw::GuiCheckbox::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->checkbox, defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiCheckbox::getMinimumWrapSize() {
    if(getCurrentFont() == nullptr)return 0;
    auto strsize = static_cast<ffw::Pointf>(getCurrentFont()->getStringSize(label, -1.0f, getLineHeight()));
    const auto& buttonSize = widgetbutton->getRealSizeWithMargin();
    strsize.x += buttonSize.x;
    strsize.y = std::max(strsize.y, buttonSize.y);

    return strsize;
}

///=============================================================================
void ffw::GuiCheckbox::setStyle(const GuiCheckbox::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    widgetbutton->setStyle(&style->button, defaults);
    if (defaults)setDefaults(&widgetStyle->defaults);
}