/*** This file is part of FineFramework project ***/

#include "ffw/gui/guiprogressbar.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
static float clamp(const float n, const float lower, const float upper) {
    return std::max(lower, std::min(n, upper));
}

///=============================================================================
ffw::GuiProgressBar::GuiProgressBar(GuiWindow* context) : GuiWidget(context),innerStyle(nullptr) {
    
    setStyle(&context->getTheme()->progressBar, true);
    percent = 0.0f;
}

///=============================================================================
void ffw::GuiProgressBar::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    const auto width = float((percent / 100.0f) * contentsize.x);
    if(width > 0) {
        renderComponent(contentoffset, ffw::Pointf(width, contentsize.y), getCurrentStyle(innerStyle));
    }
}

///=============================================================================
void ffw::GuiProgressBar::setValue(const float value) {
    percent = ::clamp(value, 0.0f, 100.0f);
    redraw();
}

///=============================================================================
void ffw::GuiProgressBar::setInnerStyleGroup(const GuiWidget::Style* style) {
    innerStyle = style;
    redraw();
}

///=============================================================================
void ffw::GuiProgressBar::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->progressBar, defaults);
}

///=============================================================================
void ffw::GuiProgressBar::setStyle(const GuiProgressBar::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    innerStyle = &style->inner;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiProgressBar::getMinimumWrapSize() {
    return ffw::Pointi(16, 8);
}