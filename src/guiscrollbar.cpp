/*** This file is part of FineFramework project ***/

#include "ffw/gui/guiscrollbar.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiScrollBar::ButtonLeft::ButtonLeft(GuiWindow* context):GuiButton(context, "") {
    setStyle(&context->getTheme()->scrollbar.buttonLeft, true);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonLeft::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    const auto radius = std::min(contentsize.x, contentsize.y) / 2.0f;
    const auto p = contentoffset + contentsize / 2.0f;
    
    context->drawTriangle(
        ffw::Pointf(p.x + radius, p.y + radius),
        ffw::Pointf(p.x + radius, p.y - radius),
        ffw::Pointf(p.x - radius, p.y),
        getCurrentStyle()->text.color);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonLeft::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollbar.buttonLeft, defaults);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonLeft::setStyle(const ButtonLeft::Style* style, const bool defaults) {
    GuiButton::setStyle(&style->self, defaults);
}

///=============================================================================
ffw::GuiScrollBar::ButtonTop::ButtonTop(GuiWindow* context):GuiButton(context, "") {
    setStyle(&context->getTheme()->scrollbar.buttonTop, true);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonTop::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    const auto radius = std::min(contentsize.x, contentsize.y) / 2.0f;
    const auto p = contentoffset + contentsize / 2.0f;
    
    context->drawTriangle(
        ffw::Pointf(p.x, p.y - radius),
        ffw::Pointf(p.x + radius, p.y + radius),
        ffw::Pointf(p.x - radius, p.y + radius),
        getCurrentStyle()->text.color);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonTop::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollbar.buttonTop, defaults);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonTop::setStyle(const ButtonTop::Style* style, const bool defaults) {
    GuiButton::setStyle(&style->self, defaults);
}

///=============================================================================
ffw::GuiScrollBar::ButtonRight::ButtonRight(GuiWindow* context):GuiButton(context, "") {
    setStyle(&context->getTheme()->scrollbar.buttonRight, true);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonRight::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    const auto radius = std::min(contentsize.x, contentsize.y) / 2.0f;
    const auto p = contentoffset + contentsize / 2.0f;

    context->drawTriangle(
        ffw::Pointf(p.x - radius, p.y + radius),
        ffw::Pointf(p.x - radius, p.y - radius),
        ffw::Pointf(p.x + radius, p.y),
        getCurrentStyle()->text.color);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonRight::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollbar.buttonRight, defaults);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonRight::setStyle(const ButtonRight::Style* style, const bool defaults) {
    GuiButton::setStyle(&style->self, defaults);
}

///=============================================================================
ffw::GuiScrollBar::ButtonBottom::ButtonBottom(GuiWindow* context):GuiButton(context, "") {
    setStyle(&context->getTheme()->scrollbar.buttonBottom, true);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonBottom::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    const auto radius = std::min(contentsize.x, contentsize.y) / 2.0f;
    const auto p = contentoffset + contentsize / 2.0f;

    context->drawTriangle(
        ffw::Pointf(p.x + radius, p.y - radius),
        ffw::Pointf(p.x - radius, p.y - radius),
        ffw::Pointf(p.x, p.y + radius),
        getCurrentStyle()->text.color);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonBottom::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollbar.buttonBottom, defaults);
}

///=============================================================================
void ffw::GuiScrollBar::ButtonBottom::setStyle(const ButtonBottom::Style* style, const bool defaults) {
    GuiButton::setStyle(&style->self, defaults);
}

///=============================================================================
ffw::GuiScrollBar::Scroll::Scroll(GuiWindow* context, const bool vertical):GuiSlider(context, vertical) {
    setStyle(&context->getTheme()->scrollbar.scroll, true);
}

///=============================================================================
void ffw::GuiScrollBar::Scroll::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollbar.scroll, defaults);
}

///=============================================================================
void ffw::GuiScrollBar::Scroll::setStyle(const Scroll::Style* style, const bool defaults) {
    GuiSlider::setStyle(&style->self, defaults);

    if (defaults) {
        barSize = styleBar->defaults.size;
        buttonSize = styleButton->defaults.size;

        if (isVertical()) {
            const auto s = getSize();
            setSize(s.y, s.x);
            std::swap(buttonSize.x, buttonSize.y);
            std::swap(barSize.x, barSize.y);
        }
    }
}

///=============================================================================
ffw::GuiScrollBar::GuiScrollBar(GuiWindow* context, const bool vertical) :GuiWidget(context){
    setDropFocus();

    if (vertical) {
        const auto s = getSize();
        setSize(s.y, s.x);
    }

    if (vertical) {
        left = new GuiScrollBar::ButtonTop(context);
        right = new GuiScrollBar::ButtonBottom(context);
    } else {
        left = new GuiScrollBar::ButtonLeft(context);
        right = new GuiScrollBar::ButtonRight(context);
    }
    slider = new GuiScrollBar::Scroll(context, vertical);

    left->setMargin(0);
    right->setMargin(0);
    slider->setMargin(0);

    recalculate(getVisibleContentSize());

    if (vertical) {
        this->setOrientationInternal(ffw::GuiOrientation::VERTICAL);
    }
    else {
        this->setOrientationInternal(ffw::GuiOrientation::HORIZONTAL);
    }

    setStyle(&context->getTheme()->scrollbar, true);

    slider->setRange(0, 100);
    slider->setValue(50);
    slider->addEventCallback([=](GuiEvent e) -> void {
        this->pushEvent(e.type, e.data);
    }, GuiEventType::ACTION, true);
    increments = 10;

    left->addEventCallback(&GuiScrollBar::buttonCallback, this, GuiEventType::ACTION, true);
    right->addEventCallback(&GuiScrollBar::buttonCallback, this, GuiEventType::ACTION, true);

    this->addWidgetInternal(left);
    this->addWidgetInternal(slider);
    this->addWidgetInternal(right);
}

///=============================================================================
void ffw::GuiScrollBar::setButtonLength(const GuiUnits length) {
    auto s = slider->getButtonSize();
    if (slider->isVertical()) {
        s.y = length;
        slider->setButtonSize(s);
    }
    else {
        s.x = length;
        slider->setButtonSize(s);
    }
}

///=============================================================================
void ffw::GuiScrollBar::buttonCallback(ffw::GuiEvent e) {
    if (e.type == ffw::GuiEventType::ACTION) {
        const auto val = slider->getValue();

        if (e.widget == left) {
            slider->setValue(val + (getInversed() ? +increments : -increments));

        }
        else {
            slider->setValue(val + (getInversed() ? -increments : +increments));
        }

        redraw();
    }
}

///=============================================================================
void ffw::GuiScrollBar::recalculate(const ffw::Pointf& s) {
    if (slider->isVertical()) {
        left->setSize(s.x, s.x);
        right->setSize(s.x, s.x);
        slider->setSize(s.x, s.y - s.x * 2);
		auto btn = slider->getButtonSize();
		btn.x = s.x - 2.0f;
		slider->setButtonSize(btn);
    }
    else {
        left->setSize(s.y, s.y);
        right->setSize(s.y, s.y);
        slider->setSize(s.x - s.y * 2, s.y);
		auto btn = slider->getButtonSize();
		btn.y = s.y - 2.0f;
		slider->setButtonSize(btn);
    }
    invalidate();
}

///=============================================================================
void ffw::GuiScrollBar::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    (void)contentoffset;
    (void)contentsize;
}

///=============================================================================
void ffw::GuiScrollBar::eventSize(const ffw::Pointf& s) {
    recalculate(s);
    redraw();
}

///=============================================================================
void ffw::GuiScrollBar::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollbar, defaults);
}

///=============================================================================
void ffw::GuiScrollBar::setStyle(const GuiScrollBar::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
    slider->setStyle(&style->scroll, defaults);
    if(slider->isVertical()) {
        dynamic_cast<ButtonTop*>(left)->setStyle(&style->buttonTop, defaults);
        dynamic_cast<ButtonBottom*>(right)->setStyle(&style->buttonBottom, defaults);
    } else {
        dynamic_cast<ButtonLeft*>(left)->setStyle(&style->buttonLeft, defaults);
        dynamic_cast<ButtonRight*>(right)->setStyle(&style->buttonRight, defaults);
    }
    if (defaults) {
        if (isVertical()) {
            const auto s = getSize();
            setSize(s.y, s.x);
        }
    }
}

///=============================================================================
ffw::Pointf ffw::GuiScrollBar::getMinimumWrapSize() {
    ffw::Pointf s;

    const auto slidermin = slider->getMinimumWrapSize();
    const auto leftmin = left->getMinimumWrapSize();
    const auto rightmin = left->getMinimumWrapSize();

    if (slider->isVertical()) {
        s.x = std::max(slidermin.x, std::max(leftmin.x, rightmin.x));
        s.y = slidermin.y + leftmin.y + rightmin.y;
    }
    else {
        s.x = slidermin.x + leftmin.x + rightmin.x;
        s.y = std::max(slidermin.y, std::max(leftmin.y, rightmin.y));
    }

    return s;
}