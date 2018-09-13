/*** This file is part of FineFramework project ***/

#include "ffw/gui/guilist.h"
#include "ffw/gui/guilayout.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guitheme.h"

///=============================================================================
ffw::GuiList::Value::Value(GuiList* list):parent(list) {
    value = -1;
}

///=============================================================================
void ffw::GuiList::Value::setValue(const int value) {
    auto found = false;
    for (auto r : items) {
        if (r->getBaseValue() == value) {
            r->assignValue(true);
            found = true;
            this->value = value;
        }
        else {
            r->assignValue(false);
        }
    }

    if (value == -1){
        this->value = -1;
    }

    if (value == -1) {
        GuiEvent::Data dat;
        dat.action.value = this->value;
        parent->pushEvent(GuiEventType::ACTION, dat);
    }
}

///=============================================================================
void ffw::GuiList::Value::reset() {
    items.clear();
}

///=============================================================================
int ffw::GuiList::Value::getValue() const {
    return value;
}

///=============================================================================
void ffw::GuiList::Value::assign(GuiList::Item* item) {
    if (item != nullptr && std::find(items.begin(), items.end(), item) == items.end()) {
        items.push_back(item);
    }
}

///=============================================================================
void ffw::GuiList::Value::remove(GuiList::Item* item) {
    for(size_t i = 0; i < items.size(); i++) {
        if(items[i] == item) {
            items.erase(items.begin() + i);
            break;
        }
    }
}

///=============================================================================
void ffw::GuiList::Value::clearAllExcept(const GuiList::Item* item) {
    bool found = false;
    for (auto r : items) {
        if (r == item) {
            value = r->getBaseValue();
            found = true;
            break;
        }
    }

    for (auto r : items) {
        r->assignValue(r == item);
    }

    if (found) {
        GuiEvent::Data dat;
        dat.action.value = value;
        parent->pushEvent(GuiEventType::ACTION, dat);
    }
}
///=============================================================================
ffw::GuiList::Item::Item(GuiWindow* context, const std::string& label, const int base, GuiList::Value* group) :
    GuiWidget(context), label(label), base(base), group(group) {
    if (group) group->assign(this);
    setStickyFocus();
    
    setStyle(&context->getTheme()->list.item, true);
}

///=============================================================================
ffw::GuiList::Item::~Item() {
    if (group) group->remove(this);
}

///=============================================================================
void ffw::GuiList::Item::setGroup(GuiList::Value* group) {
    if (this->group) this->group->remove(this);
    this->group = group;
    this->group->assign(this);
}

///=============================================================================
void ffw::GuiList::Item::setBaseValue(const int base) {
    this->base = base;
}

///=============================================================================
void ffw::GuiList::Item::setLabel(const std::string& label) {
    this->label = label;
    redraw();
}

///=============================================================================
const std::string& ffw::GuiList::Item::getLabel() const {
    return label;
}

///=============================================================================
void ffw::GuiList::Item::assignValue(const bool value) {
    if (value) {
        setFocus(true);
        GuiEvent::Data dat;
        dat.action.value = true;
        pushEvent(GuiEventType::ACTION, dat);
    }
    else {
        setFocus(false);
    }
    redraw();
}

///=============================================================================
bool ffw::GuiList::Item::isSelected() const {
    return (base == group->getValue());
}

///=============================================================================
void ffw::GuiList::Item::eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) {
    context->drawStringAligned(contentoffset, contentsize, getCurrentFont(), getAlign(), label, getCurrentStyle()->text, getLineHeight());
}

///=============================================================================
void ffw::GuiList::Item::eventHover(bool gained) {
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiList::Item::eventFocus(bool gained) {
    if (gained) {
        group->clearAllExcept(this);
    }
    redraw();
}

///=============================================================================
void ffw::GuiList::Item::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->list.item, defaults);
}

///=============================================================================
void ffw::GuiList::Item::setStyle(const Item::Style* style, const bool defaults) {
    widgetStyle = &style->self;
    if (defaults)setDefaults(&widgetStyle->defaults);
}

///=============================================================================
ffw::Pointf ffw::GuiList::Item::getMinimumWrapSize() {
    if (getCurrentFont() == nullptr)return 0;
    return getCurrentFont()->getStringSize(label, -1.0f, getLineHeight());
}

///=============================================================================
ffw::GuiList::GuiList(GuiWindow* context):
    GuiScrollableLayout(context, GuiOrientation::VERTICAL, false, true),group(this),style(nullptr) {
    counter = -1;
    
    setStyle(&context->getTheme()->list, true);
}

///=============================================================================
ffw::GuiList::Item* ffw::GuiList::addItem(const std::string& label) {
    auto item = new GuiList::Item(context, label, ++counter, &group);
    item->setStyle(&this->style->item);
    getInner()->addWidget(item);
    return item;
}

///=============================================================================
ffw::GuiList::Item* ffw::GuiList::addItem(Item* item) {
    getInner()->addWidget(item);
    return item;
}

///=============================================================================
void ffw::GuiList::deleteAllItems() {
    getInner()->deleteWidgets();
    group.reset();
    counter = -1;
}

///=============================================================================
bool ffw::GuiList::deleteItem(const GuiList::Item* item) {
    return getInner()->deleteSingleWidget(item);
}

///=============================================================================
void ffw::GuiList::setSelectedIndex(const int index) {
    group.setValue(index);
}

///=============================================================================
void ffw::GuiList::resetSelected() {
    group.setValue(-1);
}

///=============================================================================
void ffw::GuiList::setSelected(const GuiList::Item* item) {
    if (item != nullptr) {
        group.setValue(item->getBaseValue());
    }
}

///=============================================================================
ffw::GuiList::Item* ffw::GuiList::getSelectedItem() const {
    const auto value = group.getValue();
    for (auto* w : getInner()->getAllWidgets()) {
        const auto item = dynamic_cast<GuiList::Item*>(w);
        if (item != nullptr && item->getBaseValue() == value) {
            return item;
        }
    }
    return nullptr;
}

///=============================================================================
int ffw::GuiList::getSelectedIndex() const {
    return group.getValue();
}

///=============================================================================
void ffw::GuiList::eventHover(bool gained) {
    GuiScrollableLayout::eventHover(gained);
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiList::eventFocus(bool gained) {
    GuiScrollableLayout::eventFocus(gained);
    (void)gained;
    redraw();
}

///=============================================================================
void ffw::GuiList::eventThemeChanged(const GuiTheme* theme, const bool defaults) {
    setStyle(&theme->list, defaults);
}

///=============================================================================
void ffw::GuiList::setStyle(const GuiList::Style* style, const bool defaults) {
    this->style = style;
    GuiScrollable::setStyle(&style->self, defaults);
    if (defaults)setDefaults(&widgetStyle->defaults);
    for(const auto widget : getInner()->getAllWidgets()) {
        auto item = dynamic_cast<GuiList::Item*>(widget);
        if (item != nullptr) {
            item->setStyle(&style->item, defaults);
        }
    }
}
