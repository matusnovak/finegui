/*** This file is part of FineFramework project ***/

#include <assert.h>
#include <climits>
#include "ffw/gui/guiwidget.h"
#include "ffw/gui/guiwindow.h"

#define FLOAT_FIX(n) (std::abs(n - int(n)) > 0.001f ? n : floor(n))
#define VEC2_FIX(v) ffw::Pointf(FLOAT_FIX(v.x), FLOAT_FIX(v.y))

///=============================================================================
static ffw::Rectf RectangleBoolean(const ffw::Pointf& parentpos, const ffw::Pointf& parentsize, const ffw::Pointf& childpos, const ffw::Pointf& childsize){
    ffw::Rectf out;

    ffw::Pointf parentend = parentpos + parentsize;
    ffw::Pointf childend = childpos + childsize;

    out.x = std::max(parentpos.x, childpos.x);
    out.y = std::max(parentpos.y, childpos.y);
    out.z = std::min(parentend.x, childend.x);
    out.w = std::min(parentend.y, childend.y);
    out.z -= out.x;
    out.w -= out.y;

    if(out.z <= 0)out.z = 0;
    if(out.w <= 0)out.w = 0;

    return out;
}

///=============================================================================
ffw::GuiWidget::GuiWidget(GuiWindow* ctx):context(ctx){
    assert(context != NULL && "The context (GuiWindow) must not be NULL!");
    assert(context->getTheme() != NULL && "The context (GuiWindow) has to have a valid theme!");
    widgetStyle = NULL;
    posReal.set(0, 0);
    sizeReal.set(0, 0);
    size.set(0, 0);
    pos.set(0, 0);
    parent = NULL;
    flags.eventpos = false;
    flags.eventsize = false;
    flags.eventdisabled = false;
    flags.eventfocus = false;
    flags.eventhover = false;
    flags.eventinner = false;
    orientation = GuiOrientation::VERTICAL;
    focusType = GuiFocusType::DEFAULT;
    //first = true;
    widgetfont = NULL;
    align = GuiAlign::TOP_LEFT;
    setMargin(0);
    setPadding(0);
    id = UINT_MAX;
    lineHeight = 1.5f;

    flags.hidden = false;
    flags.disabled = false;
    flags.focus = false;
    flags.hover = false;
    flags.wrap = false;
    flags.render = true;
    flags.invalidate = true;
    flags.rearrange = true;
    flags.first = true;
    flags.ignore = false;
}

///=============================================================================
ffw::GuiWidget::GuiWidget(GuiWidget&& other) {
    swap(other);
}

///=============================================================================
void ffw::GuiWidget::swap(GuiWidget& other) {
    if(this != &other) {
        using std::swap;

    }
}

///=============================================================================
ffw::GuiWidget& ffw::GuiWidget::operator = (GuiWidget&& other) {
    if (this != &other) {
        swap(other);
    }
    return *this;
}

///=============================================================================
ffw::GuiWidget::~GuiWidget(){
    deleteWidgetsInternal();
}

///=============================================================================
void ffw::GuiWidget::recalculatePos(){
    if(parent != NULL)posReal = pos.toReal(parent->getVisibleContentSize());
    else posReal = pos.toReal(sizeReal);
}

///=============================================================================
static float getWidgetMargin(ffw::GuiWidget* widget, const ffw::Pointf& contentSize, int side) {
    switch(side) {
        case 0:
        case 2: {
            return widget->getMargin(side).toReal(contentSize.y);
        }

        case 1:
        case 3: {
            return widget->getMargin(side).toReal(contentSize.x);
        }

        default: {
            return 0;
        }
    }
}

///=============================================================================
void ffw::GuiWidget::realignWidgetsHorizontally(size_t start, size_t end, const ffw::Pointf& contentSize) {
    switch(align) {
        case GuiAlign::RIGHT:
        case GuiAlign::BOTTOM_RIGHT:
        case GuiAlign::TOP_RIGHT: {
            float posx = contentSize.x;
            for (size_t t = end; t > start; t--) {
                size_t i = t - 1;
                posx -= getWidgetMargin(widgets[i], contentSize, 1); // left
                posx -= widgets[i]->sizeReal.x; // widget
                widgets[i]->posReal.x = posx;
                posx -= getWidgetMargin(widgets[i], contentSize, 3); // right
            }
            break;
        }
        case GuiAlign::CENTER:
        case GuiAlign::BOTTOM_CENTER:
        case GuiAlign::TOP_CENTER: {
            float width = 0.0f;
            for (size_t i = start; i < end; i++) {
                width += getWidgetMargin(widgets[i], contentSize, 3); // left
                width += widgets[i]->sizeReal.x; // widget
                width += getWidgetMargin(widgets[i], contentSize, 1); // right
            }

            float posx = contentSize.x / 2.0f + width / 2.0f;
            for (size_t t = end; t > start; t--) {
                size_t i = t - 1;
                posx -= getWidgetMargin(widgets[i], contentSize, 1); // left
                posx -= widgets[i]->sizeReal.x; // widget
                widgets[i]->posReal.x = posx;
                posx -= getWidgetMargin(widgets[i], contentSize, 3); // right
            }
            break;
        }
        default: {
            break;
        }
    }
}

///=============================================================================
void ffw::GuiWidget::realignWidgetsHorizontallyEnd(size_t start, size_t end, const ffw::Pointf& contentSize, const ffw::Pointf& totalSize) {
    switch (align) {
        case GuiAlign::CENTER:
        case GuiAlign::LEFT:
        case GuiAlign::RIGHT: {
            float diff = contentSize.y / 2.0f - totalSize.y / 2.0f;

            for (size_t i = start; i < end; i++) {
                widgets[i]->posReal.y += diff;
            }
            break;
        }
        case GuiAlign::BOTTOM_CENTER:
        case GuiAlign::BOTTOM_LEFT:
        case GuiAlign::BOTTOM_RIGHT: {
            float diff = contentSize.y - totalSize.y;

            for (size_t i = start; i < end; i++) {
                widgets[i]->posReal.y += diff;
            }
            break;
        }
        default: {
            break;
        }
    }
}

///=============================================================================
void ffw::GuiWidget::realignWidgetsVertically(size_t start, size_t end, const ffw::Pointf& contentSize) {
    switch(align) {
        case GuiAlign::BOTTOM_CENTER:
        case GuiAlign::BOTTOM_LEFT:
        case GuiAlign::BOTTOM_RIGHT: {
            float posx = contentSize.y;
            for (size_t t = end; t > start; t--) {
                size_t i = t - 1;
                posx -= getWidgetMargin(widgets[i], contentSize, 0); // top
                posx -= widgets[i]->sizeReal.y; // widget
                widgets[i]->posReal.y = posx;
                posx -= getWidgetMargin(widgets[i], contentSize, 2); // bottom
            }
            break;
        }
        case GuiAlign::CENTER:
        case GuiAlign::RIGHT:
        case GuiAlign::LEFT: {
            float height = 0.0f;
            for (size_t i = start; i < end; i++) {
                height += getWidgetMargin(widgets[i], contentSize, 0); // top
                height += widgets[i]->sizeReal.y; // widget
                height += getWidgetMargin(widgets[i], contentSize, 2); // bottom
            }

            float posx = contentSize.y / 2.0f + height / 2.0f;
            for (size_t t = end; t > start; t--) {
                size_t i = t - 1;
                posx -= getWidgetMargin(widgets[i], contentSize, 0); // top
                posx -= widgets[i]->sizeReal.y; // widget
                widgets[i]->posReal.y = posx;
                posx -= getWidgetMargin(widgets[i], contentSize, 2); // bottom
            }
            break;
        }
        default: {
            break;
        }
    }
}

///=============================================================================
void ffw::GuiWidget::realignWidgetsVerticallyEnd(size_t start, size_t end, const ffw::Pointf& contentSize, const ffw::Pointf& totalSize) {
    switch (align) {
        case GuiAlign::TOP_CENTER:
        case GuiAlign::CENTER:
        case GuiAlign::BOTTOM_CENTER: {
            float diff = contentSize.x / 2.0f - totalSize.x / 2.0f;

            for (size_t i = start; i < end; i++) {
                widgets[i]->posReal.x = contentSize.x / 2.0f - widgets[i]->sizeReal.x / 2.0f;
            }
            break;
        }
        case GuiAlign::TOP_RIGHT:
        case GuiAlign::RIGHT:
        case GuiAlign::BOTTOM_RIGHT: {
            float diff = contentSize.x - totalSize.x;

            for (size_t i = start; i < end; i++) {
                widgets[i]->posReal.x += diff + (totalSize.x - widgets[i]->getRealSizeWithMargin().x);
            }
            break;
        }
        default: {
            break;
        }
    }
}

///=============================================================================
void ffw::GuiWidget::arrangeWidgetsHorizontal(GuiWidget* ptr) {
    ffw::Pointf contentSize = getVisibleContentSize();

    float maxheight = 0;
    float left = 0;
    float top = 0;
    size_t realignStart = 0;
    bool realign = false;

    for (size_t i = 0; i < widgets.size(); i++){
        auto w = widgets[i];
        if (w->isHidden())continue;
        // recalculate widget size...
        if (w != ptr)w->recalculateSize(this);

        // get its margin
        const auto& widgetmargin = w->margin;
        float realmargin[4];

        // calculate margin
        realmargin[0] = widgetmargin[0].toReal(contentSize.y);
        realmargin[1] = widgetmargin[1].toReal(contentSize.x);
        realmargin[2] = widgetmargin[2].toReal(contentSize.y);
        realmargin[3] = widgetmargin[3].toReal(contentSize.x);

        if (flags.wrap && size.x != guiWrap()) {
            float test = left + realmargin[3] + w->getRealSize().x;
            if (test > contentSize.x) {
                top += maxheight;
                maxheight = 0;
                left = 0;
                realign = true;
            }
        }

        w->pos.set(guiPixels(floor(left + realmargin[3])), guiPixels(floor(top + realmargin[0])));
        w->recalculatePos();
        left += w->getRealSize().x + realmargin[3] + realmargin[1];

        float testheight = w->getRealSize().y + realmargin[0] + realmargin[2];
        maxheight = std::max(maxheight, testheight);

        if(realign) {
            realign = false;
            realignWidgetsHorizontally(realignStart, i, contentSize);
            realignStart = i;
        }

        totalSize.x = std::max(totalSize.x, left);
        totalSize.y = std::max(totalSize.y, std::max(top + testheight, maxheight));
    }

    if (widgets.size() > 0 && realignStart != widgets.size()) {
        realignWidgetsHorizontally(realignStart, widgets.size(), getVisibleContentSize());
    }

    realignWidgetsHorizontallyEnd(0, widgets.size(), getVisibleContentSize(), totalSize);

    for (auto& w : widgets) {
        w->posReal = w->posReal.floor();
    }
}

///=============================================================================
void ffw::GuiWidget::arrangeWidgetsVertical(GuiWidget* ptr) {
    ffw::Pointf contentSize = getVisibleContentSize();
    
    float maxwidth = 0;
    float left = 0;
    float top = 0;
    size_t realignStart = 0;
    bool realign = false;

    for (size_t i = 0; i < widgets.size(); i++){
        auto w = widgets[i];
        if (w->isHidden())continue;

        // recalculate widget size...
        if (w != ptr)w->recalculateSize(this);

        // get its margin
        const auto& widgetmargin = w->margin;
        float realmargin[4];

        // calculate margin
        realmargin[0] = widgetmargin[0].toReal(contentSize.y);
        realmargin[1] = widgetmargin[1].toReal(contentSize.x);
        realmargin[2] = widgetmargin[2].toReal(contentSize.y);
        realmargin[3] = widgetmargin[3].toReal(contentSize.x);

        if (flags.wrap && size.y != guiWrap()) {
            float test = top + realmargin[0] + w->getRealSize().y;
            if (test > contentSize.y) {
                left += maxwidth;
                maxwidth = 0;
                top = 0;
                realign = true;
            }
        }

        w->pos.set(guiPixels(floor(left + realmargin[3])), guiPixels(floor(top + realmargin[0])));
        w->recalculatePos();
        top += w->getRealSize().y + realmargin[0] + realmargin[2];

        float testwidth = w->getRealSize().x + realmargin[1] + realmargin[3];
        maxwidth = std::max(maxwidth, testwidth);

        if(realign) {
            realign = false;
            realignWidgetsVertically(realignStart, i, contentSize);
            realignStart = i;
        }

        totalSize.x = std::max(totalSize.x, std::max(maxwidth, left + testwidth));
        totalSize.y = std::max(totalSize.y, top);
    }

    if (widgets.size() > 0 && realignStart != widgets.size()) {
        realignWidgetsVertically(realignStart, widgets.size(), getVisibleContentSize());
    }

    realignWidgetsVerticallyEnd(0, widgets.size(), getVisibleContentSize(), totalSize);

    for(auto& w : widgets) {
        w->posReal = w->posReal.floor();
    }
}

///=============================================================================
void ffw::GuiWidget::arrangeWidgetsFixed(GuiWidget* ptr) {
    for (size_t i = 0; i < widgets.size(); i++){
        auto w = widgets[i];
        if (w->isHidden())continue;

        // recalculate widget size...
        if(w != ptr)w->recalculateSize(this);

        w->recalculatePos();

        ffw::Pointf test;
        test = w->getRealPos() + w->getRealSize();

        totalSize.x = std::max(totalSize.x, test.x);
        totalSize.y = std::max(totalSize.y, test.y);
    }
}

///=============================================================================
void ffw::GuiWidget::recalculateSize(GuiWidget* caller){
    flags.invalidate = false;

    auto oldSizeReal = sizeReal;
    auto oldTotalSize = totalSize;

    if (parent != NULL) {
        // X set to wrap?
        if (size.x == guiWrap()) {
            sizeReal.x = 0;
        }
        else {
            sizeReal.x = floor(size.x.toReal(parent->getVisibleContentSize().x));
        }

        // Y set to wrap?
        if (size.y == guiWrap()) {
            sizeReal.y = 0;
        }
        else {
            sizeReal.y = floor(size.y.toReal(parent->getVisibleContentSize().y));
        }
    }
    else {
        sizeReal.x = floor(size.x.toReal(100));
        sizeReal.y = floor(size.y.toReal(100));
    }

    //sizeReal.x = ceil(sizeReal.x);
    //sizeReal.y = ceil(sizeReal.y);

    auto min = getMinimumWrapSize();

    totalSize = 0;
    totalSize.x = std::max(totalSize.x, min.x);
    totalSize.y = std::max(totalSize.y, min.y);

    min.x += getPaddingInPixels(1) + getPaddingInPixels(3);
    min.y += getPaddingInPixels(0) + getPaddingInPixels(2);

    switch (orientation) {
        case GuiOrientation::HORIZONTAL: arrangeWidgetsHorizontal(); break;
        case GuiOrientation::VERTICAL: arrangeWidgetsVertical(); break;
        default: arrangeWidgetsFixed();  break;
    }

    totalSize.x = ceil(totalSize.x);
    totalSize.y = ceil(totalSize.y);

    // Wrap X
    if (size.x == ffw::guiWrap()) {
        sizeReal.x = totalSize.x;
        if (padding[1] != GuiUnits::Type::PERCENT)sizeReal.x += padding[1].value;
        if (padding[3] != GuiUnits::Type::PERCENT)sizeReal.x += padding[3].value;
        if (sizeReal.x < min.x)sizeReal.x = min.x;
    }

    // Wrap Y
    if (size.y == ffw::guiWrap()) {
        sizeReal.y = totalSize.y;
        if (padding[0] != GuiUnits::Type::PERCENT)sizeReal.y += padding[0].value;
        if (padding[2] != GuiUnits::Type::PERCENT)sizeReal.y += padding[2].value;
        if (sizeReal.y < min.y)sizeReal.y = min.y;
    }

    if (flags.first) {
        oldSizeReal = sizeReal;
        flags.eventsize = true;
    }

    if(oldSizeReal != sizeReal) {
        if(parent != NULL) {
            if (caller != parent) {
                parent->recalculateSize(this);
                parent->redraw();
            }
        }

        flags.eventsize = true;
        flags.render = true;
    }

    if(oldTotalSize != totalSize) {
        flags.eventinner = true;
    }
}

///=============================================================================
const ffw::GuiFont* ffw::GuiWidget::getCurrentFont() const {
    if(widgetfont == NULL){
        return context->getDefaultFont();
    }
    else return widgetfont;
}

///=============================================================================
void ffw::GuiWidget::checkEvents() {
    if (flags.eventpos) {
        flags.eventpos = false;
        eventPos(posReal);
        GuiEvent::Data dat;
        dat.pos.x = posReal.x;
        dat.pos.y = posReal.y;
        pushEvent(GuiEventType::POSITION, dat);
    }

    if (flags.eventsize) {
        flags.eventsize = false;
        //updateflag = true;
        const auto s = getVisibleContentSize();
        eventSize(s);
        GuiEvent::Data dat;
        dat.size.width = s.x;
        dat.size.height = s.y;
        pushEvent(GuiEventType::SIZE, dat);
    }

    if (flags.eventinner) {
        flags.eventinner = false;
        //updateflag = true;
        const auto s = getInnerContentSize();
        GuiEvent::Data dat;
        dat.inner.width = s.x;
        dat.inner.height = s.y;
        pushEvent(GuiEventType::INNER, dat);
    }

    if (flags.eventdisabled) {
        flags.eventdisabled = false;
        eventDisabled(flags.disabled);
        GuiEvent::Data dat;
        dat.state.disabled = flags.disabled;
        pushEvent(GuiEventType::STATE, dat);
    }

    if (flags.eventfocus) {
        flags.eventfocus = false;
        eventFocus(flags.focus);
        GuiEvent::Data dat;
        dat.focus.gained = flags.focus;
        pushEvent(GuiEventType::FOCUS, dat);
    }

    if (flags.eventhover) {
        flags.eventhover = false;
        eventHover(flags.hover);
        GuiEvent::Data dat;
        dat.hover.gained = flags.hover;
        pushEvent(GuiEventType::HOVER, dat);
    }
}

///=============================================================================
void ffw::GuiWidget::update(const ffw::Pointf& parentpos, const ffw::Pointf& parentsize, const GuiUserInput& input, ffw::Pointf mousepos, bool mouseout){    
    (void)parentpos;
    (void)parentsize;
    
    if (widgetStyle == NULL && context->getTheme() != NULL) {
        eventThemeChanged(context->getTheme());
    }
    
    if(flags.invalidate){
        recalculateSize();
    }

    // Do not proceed if the widget is hidden
    if (flags.hidden)return;

    checkEvents();

    if (!flags.ignore && !flags.disabled) {
        if (mousepos != mouseOld || !flags.hover){
            if (!mouseout &&
                mousepos.x > posReal.x && mousepos.x < posReal.x + sizeReal.x &&
                mousepos.y > posReal.y && mousepos.y < posReal.y + sizeReal.y) {

                if (!flags.hover) {
                    flags.hover = true;
                    //updateFlag = true;
                    eventHover(true);
                    GuiEvent::Data dat;
                    dat.hover.gained = true;
                    pushEvent(GuiEventType::HOVER, dat);

                }
            }
            else if (flags.hover) {
                flags.hover = false;
                //updateFlag = true;
                eventHover(false);
                GuiEvent::Data dat;
                dat.hover.gained = false;
                pushEvent(GuiEventType::HOVER, dat);
            }
        }

        if(input.mousebtn == ffw::MouseButton::LEFT && input.mousemode != ffw::MouseMode::NONE){
            if (flags.hover && input.mousemode == ffw::MouseMode::PRESSED) {
                // If focus is 'toggle' then only change the focus,
                // otherwise always set the focus to true
                if (focusType == GuiFocusType::TOGGLE) {
                    flags.focus = !flags.focus;
                    eventFocus(flags.focus);
                    GuiEvent::Data dat;
                    dat.focus.gained = flags.focus;
                    pushEvent(GuiEventType::FOCUS, dat);
                }
                else if (!flags.focus) {
                    flags.focus = true;
                    eventFocus(flags.focus);
                    GuiEvent::Data dat;
                    dat.focus.gained = flags.focus;
                    pushEvent(GuiEventType::FOCUS, dat);
                }
            }
            else if (!flags.hover && input.mousemode == ffw::MouseMode::PRESSED) {
                // Clicked outside of the widget, drop the focus if set as 'default'
                if (flags.focus && focusType == GuiFocusType::DEFAULT) {
                    flags.focus = false;
                    eventFocus(flags.focus);
                    GuiEvent::Data dat;
                    dat.focus.gained = flags.focus;
                    pushEvent(GuiEventType::FOCUS, dat);
                }
            }
            else if(input.mousemode == ffw::MouseMode::RELEASED){
                // Drop focus if set as 'drop'
                if (flags.focus && focusType == GuiFocusType::DROP) {
                    flags.focus = false;
                    eventFocus(flags.focus);
                    GuiEvent::Data dat;
                    dat.focus.gained = flags.focus;
                    pushEvent(GuiEventType::FOCUS, dat);
                }
            }
        }

        if(flags.hover && input.mousemode != ffw::MouseMode::NONE){
            eventMouseButton(input.mousebtn, input.mousemode);
            GuiEvent::Data dat;
            dat.mousebtn.button = input.mousebtn;
            dat.mousebtn.mode = input.mousemode;
            pushEvent(GuiEventType::MOUSEBTN, dat);
        }

        if((flags.hover || flags.focus) && mouseOld != mousepos){
            mouseOld = mousepos - posReal - offset;
            mouseOld.x -= getPaddingInPixels(3);
            mouseOld.y -= getPaddingInPixels(0);
            eventMouse(mouseOld);
        }

        if(flags.focus && input.chr != 0xFFFF){
            GuiEvent::Data dat;
            dat.input.chr = input.chr;
            pushEvent(GuiEventType::INPUT, dat);
            eventText(input.chr);
        }

        if(flags.focus && input.keymode != ffw::KeyMode::NONE){
            GuiEvent::Data dat;
            dat.key.key = input.key;
            dat.key.mode = input.keymode;
            pushEvent(GuiEventType::KEY, dat);
            eventKey(input.key, input.keymode);
        }
    }

    if (flags.invalidate) {
        recalculateSize();
    }

    checkEvents();

    if(widgets.size() > 0){
        // Check whenever mouse pos is outside of the visible area
        // If the mouse pos was outside previously (parent) then do 
        // not calculate it -> we don't need it
        if(!mouseout){
            auto mpos = mousepos - posReal;
            auto csize = sizeReal;
            if(mpos.x < 0 || mpos.x > csize.x || mpos.y < 0 || mpos.y > csize.y){
                mouseout = true;
            }
        }

        mousepos = mousepos - getVisibleContentPos() - offset;

        for(auto& w : widgets){
            w->update(getVisibleContentPos(), getVisibleContentSize(), input, mousepos, mouseout);
        }
    }

    if (!flags.ignore && !flags.disabled && flags.hover) {
        if (std::abs(input.scroll.x) > 0.0001f || std::abs(input.scroll.y) > 0.0001f) {
            if(eventScroll(input.scroll)) {
                input.scroll.set(0.0f, 0.0f);
            }
        }
    }

    flags.first = false;
}

///=============================================================================
void ffw::GuiWidget::traverseBackground(const ffw::Pointf& p, const ffw::Pointf& s){
    const auto* style = getCurrentStyle();

    if(style != NULL && style->background && style->background.color.a >= 1.0f) {
        context->drawBackground(p, s, style->background);
    }
    
    if(parent != NULL){
        parent->traverseBackground(p, s);
    }

    if(style != NULL && style->background){
        context->drawBackground(p, s, style->background);
    }
}

///=============================================================================
void ffw::GuiWidget::renderComponent(const ffw::Pointf& p, const ffw::Pointf& s, const ffw::GuiStyle* style) {
    if (style == NULL)return;

    // draw background
    if (style->background) {
        context->drawBackground(p, s, style->background);
    }

    // draw border
    if (style->border) {
        context->drawBorder(p, s, style->border);
    }
}

///=============================================================================
void ffw::GuiWidget::render(const ffw::Pointf& clippos, const ffw::Pointf& clipsize, const ffw::Pointf& off, bool clear){
    if (sizeReal.x <= 0 || sizeReal.y <= 0)return;
    if (flags.hidden)return;
    
    auto posRealOffset = off + posReal;
    ffw::Rectf cliparea = RectangleBoolean(clippos, clipsize, posRealOffset, sizeReal);
    ffw::Pointf childclippos(cliparea.x, cliparea.y);
    ffw::Pointf childclipsize(cliparea.z, cliparea.w);

    if(childclipsize.x > 0 && childclipsize.y > 0){
    
        if(flags.render){
            flags.render = false;
        
            context->setScissors(VEC2_FIX(childclippos), VEC2_FIX(childclipsize));
        
            if(clear){
                context->clearWithColor(rgba(0x00000000));

                // Go up through every parent and draw its background
                if(parent != NULL){
                    parent->traverseBackground(posRealOffset, sizeReal);
                }
            }

            const auto* style = getCurrentStyle();
            const auto& contentpos = off + getVisibleContentPos() + offset;

            if (style != NULL) {
                // render the base for the widget
                renderComponent(posRealOffset, sizeReal, style);
                
                // render derived class specific components
                eventRender(contentpos, getVisibleContentSize());
            }

            //const auto parentpos = off + getVisibleContentPos();
            for(auto& w : widgets){
                w->render(childclippos, childclipsize, contentpos, false);
            }
        } else {
            const auto contentpos = off + getVisibleContentPos() + offset;
            for(auto& w : widgets){
                w->render(childclippos, childclipsize, contentpos, true);
            }
        }
    }
}

///=============================================================================
ffw::Pointf ffw::GuiWidget::getAbsolutePos() const {
    if (parent == NULL)return posReal;
    auto parentpos = parent->getAbsolutePos();
    parentpos.x += parent->getPaddingInPixels(3);
    parentpos.y += parent->getPaddingInPixels(0);
    parentpos += parent->getOffset();
    return parentpos + posReal;
}

///=============================================================================
ffw::Pointf ffw::GuiWidget::getVisibleContentSize() const {
    ffw::Pointf contentSize = sizeReal;
    contentSize.y -= getPaddingInPixels(0);
    contentSize.x -= getPaddingInPixels(1);
    contentSize.y -= getPaddingInPixels(2);
    contentSize.x -= getPaddingInPixels(3);
    return contentSize;
}

///=============================================================================
ffw::Pointf ffw::GuiWidget::getVisibleContentPos() const {
    ffw::Pointf contentPos = posReal;

    // Top
    contentPos.y += padding[0].toReal(sizeReal.y);

    // Left
    contentPos.x += padding[3].toReal(sizeReal.x);

    return contentPos;
}

///=============================================================================
void ffw::GuiWidget::setWrap(bool wrap){
    flags.wrap = wrap;
    flags.invalidate = true;
}

///=============================================================================
void ffw::GuiWidget::setOrientationInternal(GuiOrientation o){
    orientation = o;
    flags.invalidate = true;
}

///=============================================================================
void ffw::GuiWidget::setID(const unsigned long id){
    this->id = id;
}

///=============================================================================
void ffw::GuiWidget::setRef(std::string ref) {
    this->ref = std::move(ref);
    this->context->addRef(this);
}

///=============================================================================
unsigned long ffw::GuiWidget::getID() const {
    return id;
}

///=============================================================================
ffw::GuiWidget* ffw::GuiWidget::addWidgetInternal(GuiWidget* widget){
    if(widget != NULL){
        widgets.push_back(widget);
        widget->setParent(this);
        flags.invalidate = true;
    }
    return widget;
}

///=============================================================================
ffw::GuiWidget* ffw::GuiWidget::addWidgetAfterInternal(const GuiWidget* previous, GuiWidget* widget) {
    if (widget == NULL || previous == NULL)return NULL;
    auto it = std::find(widgets.begin(), widgets.end(), previous);
    if (it == widgets.end()) {
        widgets.push_back(widget);
        widget->setParent(this);
    }
    else {
        widgets.insert(it + 1, widget);
        widget->setParent(this);
    }
    flags.invalidate = true;
    return widget;
}

///=============================================================================
ffw::GuiWidget* ffw::GuiWidget::addWidgetBeforeInternal(const GuiWidget* next, GuiWidget* widget) {
    if (widget == NULL || next == NULL)return NULL;
    auto it = std::find(widgets.begin(), widgets.end(), next);
    if (it == widgets.end()) {
        widgets.push_back(widget);
        widget->setParent(this);
    }
    else {
        widgets.insert(it, widget);
        widget->setParent(this);
    }
    flags.invalidate = true;
    return widget;
}

///=============================================================================
void ffw::GuiWidget::deleteWidgetsInternal() {
    for (auto& w : widgets) {
        delete w;
    }
    widgets.clear();
    flags.invalidate = true;
}

///=============================================================================
bool ffw::GuiWidget::deleteSingleWidgetInternal(const GuiWidget* widget) {
    auto it = std::find(widgets.begin(), widgets.end(), widget);
    if (it == widgets.end())return false;

    widgets.erase(it);
    return true;
}

///=============================================================================
void ffw::GuiWidget::setSize(const ffw::Point<GuiUnits>& s){
    if (size.x == s.x && size.y == s.y) return;
    size.set(s.x, s.y);
    flags.invalidate = true;
    flags.rearrange = true;
}

///=============================================================================
void ffw::GuiWidget::setOffset(const ffw::Pointf off){
    offset.set(off);
    redraw();
}

///=============================================================================
const ffw::Pointf& ffw::GuiWidget::getOffset() const {
    return offset;
}

///=============================================================================
void ffw::GuiWidget::setPos(GuiUnits posx, GuiUnits posy){
    if(pos.x == posx && pos.y == posy)return;

    pos.set(posx, posy);
    recalculatePos();
}

///=============================================================================
void ffw::GuiWidget::setPadding(GuiUnits top, GuiUnits right, GuiUnits bottom, GuiUnits left){
    padding[0] = top;
    padding[1] = right;
    padding[2] = bottom;
    padding[3] = left;
    flags.invalidate = true;
}

///=============================================================================
void ffw::GuiWidget::setMargin(GuiUnits top, GuiUnits right, GuiUnits bottom, GuiUnits left){
    margin[0] = top;
    margin[1] = right;
    margin[2] = bottom;
    margin[3] = left;
    if(parent != NULL)parent->flags.invalidate = true;
    else flags.invalidate = true;
}

///=============================================================================
float ffw::GuiWidget::getPaddingInPixels(int side) const {
    if(side == 1 || side == 3){
        return padding[side].toReal(sizeReal.x);
    } else if(side == 0 || side == 2){
        return padding[side].toReal(sizeReal.y);
    }
    return 0;
}

///=============================================================================
float ffw::GuiWidget::getMarginInPixels(int side) const {
    if(side == 1 || side == 3){
        if(parent != NULL){
            return margin[side].toReal(parent->getVisibleContentSize().x);
        } else {
            return margin[side].toReal(sizeReal.x);
        }
    } else if(side == 0 || side == 2){
        if(parent != NULL){
            return margin[side].toReal(parent->getVisibleContentSize().y);
        } else {
            return margin[side].toReal(sizeReal.y);
        }
    }
    return 0;
}


///=============================================================================
void ffw::GuiWidget::setTheme(const GuiTheme* theme, const bool defaults) {
    if (theme == NULL)return;
    eventThemeChanged(theme, defaults);
    flags.render = true;
    for (auto& w : widgets) {
        w->setTheme(theme, defaults);
    }
}

///=============================================================================
void ffw::GuiWidget::setStyleGroup(const GuiWidget::Style* style) {
    if (style == NULL)return;
    widgetStyle = style;
}

///=============================================================================
const ffw::GuiStyle* ffw::GuiWidget::getCurrentStyle(const GuiWidget::Style* group) const {
    if (group == NULL)return NULL;
    if (flags.disabled)return &group->disabled;
    if (flags.focus)return &group->active;
    if (flags.hover)return &group->hover;
    return &group->normal;
}

///=============================================================================
void ffw::GuiWidget::setAlign(GuiAlign a) {
    align = a;
}

///=============================================================================
ffw::GuiAlign ffw::GuiWidget::getAlign() const {
    return align;
}

///=============================================================================
void ffw::GuiWidget::setHidden(bool h) {
    if(flags.hidden != h) {
        flags.hidden = h;
        if (parent != NULL)parent->flags.invalidate = true;
    }
}

///=============================================================================
const ffw::Point<ffw::GuiUnits>& ffw::GuiWidget::getPos() const {
    return pos;
}

///=============================================================================
const ffw::Point<ffw::GuiUnits>& ffw::GuiWidget::getSize() const {
    return size;
}

///=============================================================================
void ffw::GuiWidget::setParent(GuiWidget* parent_){
    parent = parent_;
}

///=============================================================================
const ffw::GuiWidget* ffw::GuiWidget::getParent() const {
    return parent;
}

///=============================================================================
void ffw::GuiWidget::setFont(const GuiFont* font){
    widgetfont = font;
    flags.render = true;
}

///=============================================================================
const ffw::GuiFont* ffw::GuiWidget::getFont() const {
    return widgetfont;
}

///=============================================================================
void ffw::GuiWidget::pushEvent(GuiEventType type, GuiEvent::Data data) {
    if (!eventCallbacks.empty()) {
        context->pushEvent(eventCallbacks, GuiEvent(this, type, data));
    }
}

///=============================================================================
bool ffw::GuiWidget::shouldRedraw() const {
    return flags.render;
}

///=============================================================================
void ffw::GuiWidget::redraw(){
    flags.render = true;
    for(auto w : widgets){
        w->redraw();
    }
}

///=============================================================================
void ffw::GuiWidget::invalidate(){
    flags.invalidate = true;
}

///=============================================================================
void ffw::GuiWidget::setIgnoreUserInput(bool d) {
    flags.ignore = d;
    for (auto& w : widgets)w->setIgnoreUserInput(d);
}

///=============================================================================
void ffw::GuiWidget::setFocus(bool f){
    if (flags.focus != f) {
        flags.eventfocus = true;
        flags.render = true;
    }
    flags.focus = f;
    for (auto& w : widgets)w->setFocus(f);
}

///=============================================================================
void ffw::GuiWidget::setDisabled(bool d) {
    if (flags.disabled != d) {
        flags.eventdisabled = true;
        flags.render = true;
    }
    flags.disabled = d;
    for (auto& w : widgets)w->setDisabled(d);
}

///=============================================================================
void ffw::GuiWidget::setHover(bool h){
    if (flags.hover != h) {
        flags.eventhover = true;
        flags.render = true;
    }
    flags.hover = h;
    for (auto& w : widgets)w->setHover(h);
}

///=============================================================================
void ffw::GuiWidget::eventPos(const ffw::Pointf& pos) {
    (void)pos;
}
void ffw::GuiWidget::eventSize(const ffw::Pointf& size) {
    (void)size;
}
void ffw::GuiWidget::eventHover(bool gained) {
    (void)gained;
}
void ffw::GuiWidget::eventFocus(bool gained) {
    (void)gained;
}
void ffw::GuiWidget::eventMouse(const ffw::Pointf& mousePos) {
    (void)mousePos;
}
bool ffw::GuiWidget::eventScroll(const ffw::Pointf& scroll) {
    (void)scroll;
    return false;
}
void ffw::GuiWidget::eventMouseButton(ffw::MouseButton button, ffw::MouseMode mode) {
    (void)button;
    (void)mode;
}
void ffw::GuiWidget::eventText(uint32_t chr) {
    (void)chr;
}
void ffw::GuiWidget::eventKey(ffw::Key key, ffw::KeyMode mode) {
    (void)key;
    (void)mode;
}
void ffw::GuiWidget::eventDisabled(bool disabled) {
    (void)disabled;
}