/*** This file is part of FineFramework project ***/

#include "ffw/gui/guilayout.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiLayout::GuiLayout(GuiWindow* context, const GuiOrientation Orientation):GuiWidget(context){
    GuiWidget::setOrientationInternal(Orientation);
    setIgnoreUserInput(true);

    setStyle(&context->getTheme()->layout, true);
}

///=============================================================================
ffw::GuiLayout::~GuiLayout(){
    deleteWidgets();
}

///=============================================================================
ffw::GuiWidget* ffw::GuiLayout::addWidget(GuiWidget* widget){
    return GuiWidget::addWidgetInternal(widget);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiLayout::addWidgetAfter(const GuiWidget* previous, GuiWidget* widget) {
    return GuiWidget::addWidgetAfterInternal(previous, widget);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiLayout::addWidgetBefore(const GuiWidget* next, GuiWidget* widget) {
    return GuiWidget::addWidgetBeforeInternal(next, widget);
}

///=============================================================================
void ffw::GuiLayout::deleteWidgets(){
    GuiWidget::deleteWidgetsInternal();
}

///=============================================================================
bool ffw::GuiLayout::deleteSingleWidget(const GuiWidget* widget){
    return GuiWidget::deleteSingleWidgetInternal(widget);
}

///=============================================================================
void ffw::GuiLayout::setOrientation(const GuiOrientation orient){
    setOrientationInternal(orient);
}

///=============================================================================
void ffw::GuiLayout::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize){
    (void)contentsize;
    (void)contentoffset;
}

///=============================================================================
void ffw::GuiLayout::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->layout, defaults);
}

///=============================================================================
void ffw::GuiLayout::setStyle(const GuiLayout::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if(defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiLayout::getMinimumWrapSize() {
    return 0;
}

