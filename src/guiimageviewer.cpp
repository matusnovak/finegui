/*** This file is part of FineFramework project ***/

#include "ffw/gui/guiimageviewer.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guiimage.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiImageViewer::GuiImageViewer(GuiWindow* context, const GuiImage* image) : GuiWidget(context) {
    setIgnoreUserInput(true);
    img = nullptr;
    setStyle(&context->getTheme()->imageViewer, true);
    setImage(image);
}

///=============================================================================
void ffw::GuiImageViewer::setImage(const GuiImage* image) {
    img = image;
    if(image != nullptr)setSubsection(0, 0, img->getWidth(), img->getHeight());
    else setSubsection(0, 0, 0, 0);
    setMirror(false, false);
    redraw();
}

///=============================================================================
void ffw::GuiImageViewer::setSubsection(const int posx, const int posy, const int width, const int height) {
    sub.set(posx, posy, width, height);
    redraw();
}

///=============================================================================
void ffw::GuiImageViewer::setMirror(const bool mirrorX, const bool mirrorY) {
    mirror.set(mirrorX, mirrorY);
    redraw();
}

///=============================================================================
void ffw::GuiImageViewer::setLabel(const std::string& label){
    this->label = label;
    redraw();
}

///=============================================================================
const std::string& ffw::GuiImageViewer::getLabel() const {
    return label;
}

///=============================================================================
void ffw::GuiImageViewer::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    context->drawImage(contentoffset, contentsize, img, sub, mirror.x, mirror.y, getCurrentStyle()->function.color);
    context->drawStringAligned(contentoffset, contentsize, getCurrentFont(), getAlign(), label, getCurrentStyle()->text, getLineHeight());
}

///=============================================================================
void ffw::GuiImageViewer::eventHover(const bool gained) {
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiImageViewer::eventFocus(const bool gained) {
    redraw();

    if (!gained || getFocusType() != GuiFocusType::DROP) {
        GuiEvent::Data dat;
        if (getFocusType() == GuiFocusType::DROP)dat.action.value = true;
        else dat.action.value = gained;
        pushEvent(GuiEventType::ACTION, dat);
    }
}

///=============================================================================
void ffw::GuiImageViewer::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->imageViewer, defaults);
}

///=============================================================================
void ffw::GuiImageViewer::setStyle(const GuiImageViewer::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiImageViewer::getMinimumWrapSize() {
    if (img == nullptr)return 0;
    if(getSize().x == guiWrap() && getSize().y == guiWrap()) {
        return static_cast<ffw::Pointf>(ffw::Pointi(sub.z, sub.w));
    }
    else if(getSize().x == guiWrap()) {
        const auto aspect = sub.z / static_cast<float>(sub.w);
        const auto s = getVisibleContentSize();
        return ffw::Pointf(s.y * aspect, s.y);
    }
    else if (getSize().y == guiWrap()) {
        const auto aspect = sub.z / static_cast<float>(sub.w);
        const auto s = getVisibleContentSize();
        return ffw::Pointf(s.x, s.x / aspect);
    }
    else {
        return static_cast<ffw::Pointf>(ffw::Pointi(sub.z, sub.w));
    }
}