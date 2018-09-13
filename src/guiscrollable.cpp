/*** This file is part of FineFramework project ***/

#include "ffw/gui/guiscrollable.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiScrollable::GuiScrollable(GuiWindow* context, GuiWidget* widget, const bool hori, const bool vert) :GuiWidget(context) {
    setIgnoreUserInput(false);

    GuiWidget::setWrap(true);
    GuiWidget::setOrientationInternal(GuiOrientation::HORIZONTAL);

    thickness = 14;
    scrollInc = 20.0f;

    inner = widget;
    inner->setMargin(0);
    inner->addEventCallback(&GuiScrollable::widgetEvent, this, GuiEventType::ALL, true);
    inner->setPadding(2);

    GuiWidget::addWidgetInternal(inner);
    if (vert) {
        vscroll = new ffw::GuiScrollBar(context, true);
        vscroll->setMargin(0);
        vscroll->addEventCallback(&GuiScrollable::widgetEvent, this, GuiEventType::ALL, true);
        vscroll->setValue(0);
        vscroll->setRange(0, 0);
        GuiWidget::addWidgetInternal(vscroll);
    }
    else {
        vscroll = nullptr;
    }
    if (hori) {
        hscroll = new ffw::GuiScrollBar(context, false);
        hscroll->setMargin(0);
        hscroll->addEventCallback(&GuiScrollable::widgetEvent, this, GuiEventType::ALL, true);
        hscroll->setValue(0);
        hscroll->setRange(0, 0);
        GuiWidget::addWidgetInternal(hscroll);
    }
    else {
        hscroll = nullptr;
    }

    setStyle(&context->getTheme()->scrollable, true);
    eventSize(getVisibleContentSize());
}

///=============================================================================
ffw::Pointf ffw::GuiScrollable::getScrollValues() const {
    ffw::Pointf values;
    if (hscroll != nullptr)values.x = hscroll->getValue();
    if (vscroll != nullptr)values.y = vscroll->getValue();
    return values;
}

///=============================================================================
void ffw::GuiScrollable::widgetEvent(const ffw::GuiEvent e) {
    if (e.widget == vscroll && e.type == ffw::GuiEventType::ACTION) {
        auto off = inner->getOffset();
        inner->setOffset(ffw::Pointf(off.x, -vscroll->getValue()).floor());
    }

    if (e.widget == hscroll && e.type == ffw::GuiEventType::ACTION) {
        auto off = inner->getOffset();
        inner->setOffset(ffw::Pointf(-hscroll->getValue(), off.y).floor());
    }

    if (e.widget == inner && e.type == ffw::GuiEventType::INNER) {
        const auto total = inner->getInnerContentSize();
        const auto visible = inner->getVisibleContentSize();
        ffw::Pointf diff = (total - visible).floor();

        if (diff.x > 0 && hscroll != nullptr) {
            hscroll->setRange(0, diff.x);
            hscroll->setButtonLength(ffw::guiPercent((visible.x / total.x) * 100.0f));
        }
        else if (hscroll != nullptr) {
            hscroll->setRange(0, 0);
        }

        if (diff.y > 0 && vscroll != nullptr) {
            vscroll->setRange(0, diff.y);
            vscroll->setButtonLength(ffw::guiPercent((visible.y / total.y) * 100.0f));
        }
        else if (vscroll != nullptr) {
            vscroll->setRange(0, 0);
        }
    }
}

///=============================================================================
void ffw::GuiScrollable::setScrollValues(const float hori, const float vert) {
    if (hscroll != nullptr) {
        hscroll->setValue(hori);
    }
    if (vscroll != nullptr) {
        vscroll->setValue(vert);
    }
    inner->setOffset(ffw::Pointf(hori, vert));
}

///=============================================================================
void ffw::GuiScrollable::setScrollbarThickness(const float px) {
    thickness = px;
    eventSize(getVisibleContentSize());
}

///=============================================================================
void ffw::GuiScrollable::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    (void)contentoffset;
    (void)contentsize;
}

///=============================================================================
void ffw::GuiScrollable::eventSize(const ffw::Pointf& size) {
    auto ss = size;
    if (vscroll != nullptr) {
        ss.x -= thickness;
        if (hscroll != nullptr) {
            vscroll->setSize(thickness, size.y - thickness);
        }
        else {
            vscroll->setSize(thickness, size.y);
        }
        ss.x -= vscroll->getPaddingInPixels(3) - vscroll->getPaddingInPixels(1);
    }
    if (hscroll != nullptr) {
        ss.y -= thickness;
        hscroll->setSize(size.x, thickness);
        ss.y -= hscroll->getPaddingInPixels(0) - hscroll->getPaddingInPixels(2);
    }

    inner->setSize(ss.x, ss.y);
    invalidate();

    const auto total = inner->getInnerContentSize();
    ffw::Pointf diff = (total - size).floor();
    
    if (diff.x > 0 && hscroll != nullptr) {
        hscroll->setRange(0, diff.x);
        hscroll->setButtonLength(ffw::guiPercent((size.x / total.x) * 100.0f));
    }
    else if (hscroll != nullptr) {
        hscroll->setRange(0, 0);
    }

    if (diff.y > 0 && vscroll != nullptr) {
        vscroll->setRange(0, diff.y);
        vscroll->setButtonLength(ffw::guiPercent((size.y / total.y) * 100.0f));
    }
    else if (vscroll != nullptr) {
        vscroll->setRange(0, 0);
    }
}

///=============================================================================
bool ffw::GuiScrollable::eventScroll(const ffw::Pointf& scroll) {
    bool ret = false;

    if (vscroll != nullptr) {
        float old = vscroll->getValue();
        vscroll->setValue(old - scroll.y * scrollInc);
        ret |= std::abs(old - vscroll->getValue()) > 0.0001f;
    }

    if (hscroll != nullptr) {
        float old = hscroll->getValue();
        hscroll->setValue(old - scroll.x * scrollInc);
        ret |= std::abs(old - hscroll->getValue()) > 0.0001f;
    }

    return ret;
}

///=============================================================================
void ffw::GuiScrollable::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollable, defaults);
}

///=============================================================================
void ffw::GuiScrollable::setStyle(const GuiScrollable::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (hscroll)hscroll->setStyle(&style->scrollbarH, defaults);
    if (vscroll)vscroll->setStyle(&style->scrollbarV, defaults);
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiScrollable::getMinimumWrapSize() {
    auto s = inner->getMinimumWrapSize();

    if (vscroll != nullptr) {
        s.x += vscroll->getMinimumWrapSize().x;
    }
    if (hscroll != nullptr) {
        s.y += hscroll->getMinimumWrapSize().y;
    }

    return s;
}

///=============================================================================
ffw::GuiScrollableLayout::GuiScrollableLayout(GuiWindow* context, GuiOrientation orientation, bool hori, bool vert):
    GuiScrollable(context, new ffw::GuiLayout(context, orientation), hori, vert){
    getInner()->setSize(guiPercent(100.0f), guiWrap());
    
    setStyle(&context->getTheme()->scrollableLayout, true);
}

///=============================================================================
void ffw::GuiScrollableLayout::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->scrollableLayout, defaults);
}

///=============================================================================
void ffw::GuiScrollableLayout::setStyle(const GuiScrollableLayout::Style* style, const bool defaults) {
    GuiScrollable::setStyle(&style->self, defaults);
    getInner()->setStyle(&style->inner, defaults);
}