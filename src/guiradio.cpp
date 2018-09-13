/*** This file is part of FineFramework project ***/

#include "ffw/gui/guiradio.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiRadio::Value::Value(){
    value = -1;
}

///=============================================================================
void ffw::GuiRadio::Value::setValue(const int value){
    this->value = value;
    for(auto r : radios){
        if(r->getBaseValue() == value)r->assignValue(true);
        else r->assignValue(false);
    }
}

///=============================================================================
int ffw::GuiRadio::Value::getValue() const{
    return value;
}

///=============================================================================
void ffw::GuiRadio::Value::assign(GuiRadio* radio){
    if(radio != nullptr && std::find(radios.begin(), radios.end(), radio) == radios.end()){
        radios.push_back(radio);
    }
}

///=============================================================================
void ffw::GuiRadio::Value::remove(GuiRadio* radio){
    const auto it = std::find(radios.begin(), radios.end(), radio);
    if(it != radios.end()){
        radios.erase(it);
    }
}

///=============================================================================
void ffw::GuiRadio::Value::clearAllExcept(const GuiRadio* radio){
    for(auto r : radios){
        if(r == radio){
            value = r->getBaseValue();
            break;
        }
    }

    for (auto r : radios) {
        r->assignValue(r == radio);
    }
}

///=============================================================================
size_t ffw::GuiRadio::Value::getNumOfAssigned() const {
    return radios.size();
}

///=============================================================================
ffw::GuiRadio::Button::Button(GuiWindow* context):GuiWidget(context),group(nullptr),parentradio(nullptr){
    setStickyFocus();
    
    setStyle(&context->getTheme()->radio.button, true);
}

///=============================================================================
void ffw::GuiRadio::Button::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize){
    context->drawCircle((contentoffset + contentsize / 2.0f).floor(), std::min(contentsize.x, contentsize.y) / 2.0f, getCurrentStyle()->function.color);
}

///=============================================================================
void ffw::GuiRadio::Button::eventHover(const bool gained){
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiRadio::Button::eventFocus(const bool gained){
    if(gained){
        group->clearAllExcept(parentradio);
        GuiEvent::Data dat;
        dat.action.value = parentradio->getBaseValue();
        parentradio->pushEvent(GuiEventType::ACTION, dat);
        redraw();
    }
}

///=============================================================================
void ffw::GuiRadio::Button::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->radio.button, defaults);
}

///=============================================================================
void ffw::GuiRadio::Button::setStyle(const Button::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiRadio::Button::getMinimumWrapSize() {
    return 0;
}

///=============================================================================
ffw::GuiRadio::GuiRadio(GuiWindow* context, const std::string& label, const int base, GuiRadio* other):GuiWidget(context),label(label){
    basevalue = base;
    setOrientationInternal(GuiOrientation::HORIZONTAL);

    widgetbutton = new GuiRadio::Button(context);
    widgetbutton->addEventCallback([=](GuiEvent e) -> void {
        this->pushEvent(e.type, e.data);
    }, GuiEventType::ACTION, true);

    addWidgetInternal(widgetbutton);
    setStyle(&context->getTheme()->radio, true);

    if(other != nullptr){
        group = other->group;
    } else {
        group = new GuiRadio::Value();
    }

    group->assign(this);
    widgetbutton->group = group;
    widgetbutton->parentradio = this;
}

///=============================================================================
ffw::GuiRadio::~GuiRadio(){
    deleteWidgetsInternal();

    group->remove(this);
    if(group->getNumOfAssigned() == 0){
        delete group;
    }
}

///=============================================================================
void ffw::GuiRadio::setButtonSize(const float width) {
    widgetbutton->setSize(width, width);
}

///=============================================================================
void ffw::GuiRadio::setLabel(const std::string& label){
    this->label = label;
    redraw();
}

///=============================================================================
const std::string& ffw::GuiRadio::getLabel() const {
    return label;
}

///=============================================================================
void ffw::GuiRadio::assignValue(const bool value){
    setFocus(value);
}
///=============================================================================
void ffw::GuiRadio::resetValue(){
    setValue(-1);
}

///=============================================================================
int ffw::GuiRadio::getValue() const {
    return group->getValue();
}

///=============================================================================
int ffw::GuiRadio::getBaseValue() const {
    return basevalue;
}

///=============================================================================
void ffw::GuiRadio::setValue(const int value){
    group->setValue(value);
}

///=============================================================================
void ffw::GuiRadio::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize){
    auto s = widgetbutton->getRealSize();
    s.x += widgetbutton->getMarginInPixels(1);
    s.y = 0;
    context->drawStringAligned(contentoffset + s, contentsize - s, getCurrentFont(), getAlign(), label, getCurrentStyle()->text, getLineHeight());
}

///=============================================================================
void ffw::GuiRadio::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->radio, defaults);
}

///=============================================================================
void ffw::GuiRadio::setStyle(const GuiRadio::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    widgetbutton->setStyle(&style->button, defaults);
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiRadio::getMinimumWrapSize() {
    if(getCurrentFont() == nullptr)return 0;
    auto strsize = static_cast<ffw::Pointf>(getCurrentFont()->getStringSize(label, -1.0f, getLineHeight()));
    strsize.x += widgetbutton->getSize().x.value;
    strsize.y = std::max(strsize.y, widgetbutton->getSize().y.value);
    return strsize;
}