/*** This file is part of FineFramework project ***/

#include <sstream>
#include <iomanip>
#include "ffw/gui/guiprogresscircle.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
static float clamp(const float n, const float lower, const float upper) {
    return std::max(lower, std::min(n, upper));
}

///=============================================================================
static std::string toStrPrecision(const float val, const int dec) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(dec) << val;
    return stream.str();
}

///=============================================================================
ffw::GuiProgressCircle::GuiProgressCircle(GuiWindow* context) : GuiWidget(context) {
    setStyle(&context->getTheme()->progressCircle, true);
    thickness = 10;
    percent = 0.0f;
}

///=============================================================================
void ffw::GuiProgressCircle::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    auto radius = std::min(contentsize.x, contentsize.y) / 2;
    radius -= thickness;

    static const float step = 360.0f / 100.0f;
    const auto start = 270.0f;
    const auto end = 270.0f + percent * step;

    context->drawArc(contentoffset + contentsize / 2.0f, radius, radius + thickness, start, end, getCurrentStyle()->function.color);

    context->drawArc(contentoffset + contentsize / 2.0f, radius, radius + thickness, end, 360.0f + start, getCurrentStyle()->function.secondary);

    const auto font = getCurrentFont();
    if (font != nullptr) {

        const auto str = toStrPrecision(percent, 1) + "%";
        context->drawStringAligned(contentoffset, contentsize, font, getAlign(), str, getCurrentStyle()->text.color, getLineHeight());
    }
}

///=============================================================================
void ffw::GuiProgressCircle::setValue(const float value) {
    percent = ::clamp(value, 0.0f, 100.0f);
    redraw();
}

///=============================================================================
void ffw::GuiProgressCircle::setThickness(const float val) {
    thickness = val;
    redraw();
}

///=============================================================================
void ffw::GuiProgressCircle::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->progressCircle, defaults);
}

///=============================================================================
void ffw::GuiProgressCircle::setStyle(const GuiProgressCircle::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiProgressCircle::getMinimumWrapSize() {
    const auto font = getCurrentFont();
    if (font == nullptr)return ffw::Pointf(32, 32);
    else {
        const auto s = font->getStringSize("100.0%", -1.0f, getLineHeight());
        const auto diamer = float(sqrt(s.x*s.x + s.y*s.y));
        return ffw::Pointf(diamer + thickness * 2);
    }
}