#include <atomic>
#include <regex>
#include <tinyxml2.h>
#include <tinyxml2.cpp>
#include "ffw/gui/guixmlparser.h"
#include "ffw/gui/guiwindow.h"
#include "ffw/gui/guilayout.h"
#include "ffw/gui/guibox.h"
#include "ffw/gui/guibutton.h"
#include "ffw/gui/guiscrollable.h"
#include "ffw/gui/guibuttontoggle.h"
#include "ffw/gui/guiradio.h"
#include "ffw/gui/guicheckbox.h"
#include "ffw/gui/guiscrollbar.h"
#include "ffw/gui/guiimageviewer.h"
#include "ffw/gui/guitextedit.h"
#include "ffw/gui/guilist.h"
#include "ffw/gui/guiswitch.h"
#include "ffw/gui/guiprogressbar.h"
#include "ffw/gui/guiprogresscircle.h"
#include "ffw/gui/guitab.h"
#include "ffw/gui/guitext.h"

///=============================================================================
static const char* getErrorStr(const tinyxml2::XMLError err) {
    switch (err) {
        case tinyxml2::XMLError::XML_SUCCESS: return "XML_SUCCESS";
        case tinyxml2::XMLError::XML_NO_ATTRIBUTE: return "XML_NO_ATTRIBUTE";
        case tinyxml2::XMLError::XML_WRONG_ATTRIBUTE_TYPE: return "XML_WRONG_ATTRIBUTE_TYPE";
        case tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND: return "XML_ERROR_FILE_NOT_FOUND";
        case tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED: return "XML_ERROR_FILE_COULD_NOT_BE_OPENED";
        case tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR: return "XML_ERROR_FILE_READ_ERROR";
        case tinyxml2::XMLError::XML_ERROR_PARSING_ELEMENT: return "XML_ERROR_PARSING_ELEMENT";
        case tinyxml2::XMLError::XML_ERROR_PARSING_ATTRIBUTE: return "XML_ERROR_PARSING_ATTRIBUTE";
        case tinyxml2::XMLError::XML_ERROR_PARSING_TEXT: return "XML_ERROR_PARSING_TEXT";
        case tinyxml2::XMLError::XML_ERROR_PARSING_CDATA: return "XML_ERROR_PARSING_CDATA";
        case tinyxml2::XMLError::XML_ERROR_PARSING_COMMENT: return "XML_ERROR_PARSING_COMMENT";
        case tinyxml2::XMLError::XML_ERROR_PARSING_DECLARATION: return "XML_ERROR_PARSING_DECLARATION";
        case tinyxml2::XMLError::XML_ERROR_PARSING_UNKNOWN: return "XML_ERROR_PARSING_UNKNOWN";
        case tinyxml2::XMLError::XML_ERROR_EMPTY_DOCUMENT: return "XML_ERROR_EMPTY_DOCUMENT";
        case tinyxml2::XMLError::XML_ERROR_MISMATCHED_ELEMENT: return "XML_ERROR_MISMATCHED_ELEMENT";
        case tinyxml2::XMLError::XML_ERROR_PARSING: return "XML_ERROR_PARSING";
        case tinyxml2::XMLError::XML_CAN_NOT_CONVERT_TEXT: return "XML_CAN_NOT_CONVERT_TEXT";
        case tinyxml2::XMLError::XML_NO_TEXT_NODE: return "XML_NO_TEXT_NODE";
        case tinyxml2::XMLError::XML_ERROR_COUNT: return "XML_ERROR_COUNT";
        default: break;
    }
    return "XML_UNKNOWN_ERROR";
}

///=============================================================================
float ffw::GuiXmlParser::Token::getAttributePixels(const char* key) const {
    const auto ret = getAttributeUnits(key);
    if (ret.getType() != GuiUnits::Type::PIXELS) throw GuiXmlException("attribute: " + std::string(key) + " is not pixels");
    return ret.value;
}

static ffw::GuiUnits strToAttribute(const std::string& str, const char* key) {
    if (str == "auto" || str == "wrap") return ffw::guiWrap();
    if (std::regex_match(str, std::regex("[0-9]+(.[0-9]+)?(px|%)"))) {
        if (str.back() == '%') {
            return ffw::guiPercent(std::stof(str.substr(0, str.size() - 1)));
        }
        else {
            return ffw::guiPixels(std::stof(str.substr(0, str.size() - 2)));
        }
    }
    throw ffw::GuiXmlException("attribute: " + std::string(key) + " is not a valid gui units");
}

///=============================================================================
ffw::GuiUnits ffw::GuiXmlParser::Token::getAttributeUnits(const char* key) const {
    const auto str = getAttributeString(key);
    return strToAttribute(str, key);
}

///=============================================================================
ffw::GuiStyle::Attribute<ffw::GuiUnits> ffw::GuiXmlParser::Token::getAttributeUnitsAttribute(const char* key) const {
    const auto str = getAttributeString(key);

    ffw::GuiStyle::Attribute<ffw::GuiUnits> ret;
    std::string tokens[4];
    size_t i = 0;
    size_t pos = 0;
    size_t found;

    while((found = str.find(' ', pos)) != std::string::npos) {
        tokens[i] = str.substr(pos, found - pos);
        if (str.find_first_not_of(' ') != std::string::npos) {
            i++;
            if (i >= 4) {
                throw GuiXmlException("attribute: " + std::string(key) + " too many values expected exactly 4");
            }
        }
        pos = found + 1;
    }

    if (i == 0) {
        ret[0] = ret[1] = ret[2] = ret[3] = strToAttribute(str, key);
        return ret;
    }

    if (i != 3) {
        throw GuiXmlException("attribute: " + std::string(key) + " too few values expected exactly 4");
    }

    if (pos != str.size()) {
        tokens[i] = str.substr(pos, str.size() - pos);
    }

    ret[0] = strToAttribute(tokens[0], key);
    ret[1] = strToAttribute(tokens[1], key);
    ret[2] = strToAttribute(tokens[2], key);
    ret[3] = strToAttribute(tokens[3], key);
    return ret;
}

///=============================================================================
ffw::GuiUnits2D ffw::GuiXmlParser::Token::getAttributeUnits2D(const char* keyW, const char* keyH) const {
    return GuiUnits2D(
        getAttributeUnits(keyW),
        getAttributeUnits(keyH)
    );
}

///=============================================================================
ffw::GuiAlign ffw::GuiXmlParser::Token::getAttributeAlign(const char* key) const {
    const auto str = getAttributeString(key);
    if (str == "top-left") return GuiAlign::TOP_LEFT;
    if (str == "bottom-left") return GuiAlign::BOTTOM_LEFT;
    if (str == "left") return GuiAlign::LEFT;

    if (str == "top-center") return GuiAlign::TOP_CENTER;
    if (str == "bottom-center") return GuiAlign::BOTTOM_CENTER;
    if (str == "center") return GuiAlign::CENTER;

    if (str == "top-right") return GuiAlign::TOP_RIGHT;
    if (str == "bottom-right") return GuiAlign::BOTTOM_RIGHT;
    if (str == "right") return GuiAlign::RIGHT;

    throw GuiXmlException("unknown align value: \"" + str + "\"");
}

///=============================================================================
ffw::GuiOrientation ffw::GuiXmlParser::Token::getAttributeOrientation(const char* key) const {
    const auto str = getAttributeString(key);
    if (str == "horizontal") return GuiOrientation::HORIZONTAL;
    if (str == "vertical") return GuiOrientation::VERTICAL;
    if (str == "fixed") return GuiOrientation::FIXED;

    throw GuiXmlException("unknown orientation value: \"" + str + "\"");
}

///=============================================================================
bool ffw::GuiXmlParser::Token::getAttributeBool(const char* key) const {
    const auto str = getAttributeString(key);
    if (str == "false") return false;
    if (str == "true") return true;

    throw GuiXmlException("unknown boolean value: \"" + str + "\"");
}

///=============================================================================
class ffw::GuiXmlParser::XmlToken: public Token {
public:
    XmlToken(const tinyxml2::XMLElement* element):element(element) {
        
    }
    virtual ~XmlToken() = default;
    const char* getKey() const {
        return element->Name();
    }
    bool hasAttribute(const char* key) const override {
        return element->FindAttribute(key) != nullptr;
    }
    std::string getAttributeString(const char* key) const override {
        const auto attr = element->FindAttribute(key);
        if (!attr) throw GuiXmlNotFound("attribute: \"" + std::string(key) + "\" not found");
        return attr->Value();
    }
    int getAttributeInt(const char* key) const override {
        const auto attr = element->FindAttribute(key);
        if (!attr) throw GuiXmlNotFound("attribute: \"" + std::string(key) + "\" not found");
        int ret = 0;
        const auto err = attr->QueryIntValue(&ret);
        if (err != tinyxml2::XML_SUCCESS) {
            throw GuiXmlException("attribute: " + std::string(key) + " is not a valid integer");
        }
        return ret;
    }
    float getAttributeFloat(const char* key) const override {
        const auto attr = element->FindAttribute(key);
        if (!attr) throw GuiXmlNotFound("attribute: \"" + std::string(key) + "\" not found");
        float ret = 0;
        const auto err = attr->QueryFloatValue(&ret);
        if (err != tinyxml2::XML_SUCCESS) {
            throw GuiXmlException("attribute: " + std::string(key) + " is not a valid floating point");
        }
        return ret;
    }
    std::string getContent() const override {
        const auto str = element->GetText();
        return str ? str : "";
    }
private:
    const tinyxml2::XMLElement* element;
};

#define IF_ATTRIBUTE_EXP(key, exp) if (token.hasAttribute(key)) { exp; }
#define RESET_AND_RETURN(ptr) auto cpy = ptr.get(); ptr.release(); return cpy;

///=============================================================================
void ffw::GuiXmlParser::Visitor::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)acceptor;
    (void)window;
    (void)child;
    throw GuiXmlException("children are not allowed inside of \"" + getKey() + "\"");
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiWidget::defaults(const Token& token, GuiWidget* instance, const Registry* registry, bool padding, bool margin) const {
    if (!instance) throw GuiXmlException("VisitorGuiWidget cannot parse a null widget, please contact the developer");
    IF_ATTRIBUTE_EXP("width", instance->setSize(token.getAttributeUnits("width"), instance->getSize().y));
    IF_ATTRIBUTE_EXP("height", instance->setSize(instance->getSize().x, token.getAttributeUnits("height")));
    IF_ATTRIBUTE_EXP("left", instance->setPos(token.getAttributeUnits("left"), instance->getPos().y));
    IF_ATTRIBUTE_EXP("top", instance->setPos(instance->getPos().x, token.getAttributeUnits("top")));
    IF_ATTRIBUTE_EXP("align", instance->setAlign(token.getAttributeAlign("align")));
    if (padding) {
        IF_ATTRIBUTE_EXP("padding-top", instance->setPaddingTop(token.getAttributeUnits("padding-top")));
        IF_ATTRIBUTE_EXP("padding-left", instance->setPaddingLeft(token.getAttributeUnits("padding-left")));
        IF_ATTRIBUTE_EXP("padding-right", instance->setPaddingRight(token.getAttributeUnits("padding-right")));
        IF_ATTRIBUTE_EXP("padding-bottom", instance->setPaddingBottom(token.getAttributeUnits("padding-bottom")));
        IF_ATTRIBUTE_EXP("padding", {
            const auto attrs = token.getAttributeUnitsAttribute("padding");
            instance->setPadding(attrs[0], attrs[1], attrs[2], attrs[3]);
            });
    }
    if (margin) {
        IF_ATTRIBUTE_EXP("margin-top", instance->setMarginTop(token.getAttributeUnits("margin-top")));
        IF_ATTRIBUTE_EXP("margin-left", instance->setMarginLeft(token.getAttributeUnits("margin-left")));
        IF_ATTRIBUTE_EXP("margin-right", instance->setMarginRight(token.getAttributeUnits("margin-right")));
        IF_ATTRIBUTE_EXP("margin-bottom", instance->setMarginBottom(token.getAttributeUnits("margin-bottom")));
        IF_ATTRIBUTE_EXP("margin", {
            const auto attrs = token.getAttributeUnitsAttribute("margin");
            instance->setMargin(attrs[0], attrs[1], attrs[2], attrs[3]);
            });
    }
    IF_ATTRIBUTE_EXP("disabled", instance->setDisabled(token.getAttributeBool("disabled")));
    IF_ATTRIBUTE_EXP("offset-x", instance->setOffset(Pointf(token.getAttributePixels("offset-x"), token.getAttributePixels("offset-y"))));
    IF_ATTRIBUTE_EXP("offset-y", instance->setWrap(token.getAttributeBool("wrap")));
    IF_ATTRIBUTE_EXP("hidden", instance->setHidden(token.getAttributeBool("hidden")));
    IF_ATTRIBUTE_EXP("hover", instance->setHover(token.getAttributeBool("hover")));
    IF_ATTRIBUTE_EXP("focus", instance->setFocus(token.getAttributeBool("focus")));
    IF_ATTRIBUTE_EXP("ignore-input", instance->setIgnoreUserInput(token.getAttributeBool("ignore-input")));
    IF_ATTRIBUTE_EXP("id", instance->setID(token.getAttributeInt("id")));
    IF_ATTRIBUTE_EXP("ref", instance->setRef(token.getAttributeString("ref")));
    std::string fontStr;
    IF_ATTRIBUTE_EXP("font", fontStr = token.getAttributeString("font"));
    if (!fontStr.empty()) instance->setFont(registry->getFont(fontStr));
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiWindow::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    window->setSize(
        token.getAttributePixels("width"),
        token.getAttributePixels("height")
    );
    IF_ATTRIBUTE_EXP("orientation", window->getLayout()->setOrientation(token.getAttributeOrientation("orientation")));
    IF_ATTRIBUTE_EXP("wrap", window->getLayout()->setWrap(token.getAttributeBool("wrap")));
    IF_ATTRIBUTE_EXP("offset-x", window->getLayout()->setOffset(Pointf(token.getAttributePixels("offset-x"), window->getLayout()->getOffset().y)));
    IF_ATTRIBUTE_EXP("offset-y", window->getLayout()->setOffset(Pointf(window->getLayout()->getOffset().x, token.getAttributePixels("offset-y"))));
    IF_ATTRIBUTE_EXP("align", window->getLayout()->setAlign(token.getAttributeAlign("align")));
    IF_ATTRIBUTE_EXP("padding-top", window->getLayout()->setPaddingTop(token.getAttributeUnits("padding-top")));
    IF_ATTRIBUTE_EXP("padding-left", window->getLayout()->setPaddingLeft(token.getAttributeUnits("padding-left")));
    IF_ATTRIBUTE_EXP("padding-right", window->getLayout()->setPaddingRight(token.getAttributeUnits("padding-right")));
    IF_ATTRIBUTE_EXP("padding-bottom", window->getLayout()->setPaddingBottom(token.getAttributeUnits("padding-bottom")));
    IF_ATTRIBUTE_EXP("padding", window->getLayout()->setPadding(token.getAttributeUnits("padding")));
    return nullptr;
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiWindow::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)acceptor;
    window->getLayout()->addWidget(child);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiBox::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiBox>(new GuiBox(
        window,
        token.getAttributeString("label"),
        token.getAttributeOrientation("orientation")
    ));
    defaults(token, ptr.get(), registry);
    IF_ATTRIBUTE_EXP("wrap", ptr->getInner()->setWrap(token.getAttributeBool("wrap")));
    IF_ATTRIBUTE_EXP("align", ptr->getInner()->setAlign(token.getAttributeAlign("align")));
    ptr->setAlign(GuiAlign::TOP_LEFT);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiBox::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    dynamic_cast<GuiBox*>(acceptor)->getInner()->addWidget(child);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiButton::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiButton>(new GuiButton(
        window,
        token.getContent()
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiButtonToggle::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiButtonToggle>(new GuiButtonToggle(
        window,
        token.getContent()
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiButtonPrimary::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiButtonPrimary>(new GuiButtonPrimary(
        window,
        token.getContent()
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiLabel::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiLabel>(new GuiLabel(
        window,
        token.getContent()
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiLayout::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiLayout>(new GuiLayout(
        window,
        token.getAttributeOrientation("orientation")
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiLayout::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    dynamic_cast<GuiLayout*>(acceptor)->addWidget(child);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiVerticalLayout::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiVerticalLayout>(new GuiVerticalLayout(
        window
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiVerticalLayout::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    dynamic_cast<GuiVerticalLayout*>(acceptor)->addWidget(child);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiHorizontalLayout::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiHorizontalLayout>(new GuiHorizontalLayout(
        window
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiHorizontalLayout::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    dynamic_cast<GuiHorizontalLayout*>(acceptor)->addWidget(child);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiScrollableLayout::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiScrollableLayout>(new GuiScrollableLayout(
        window,
        token.getAttributeOrientation("orientation"),
        token.getAttributeBool("scroll-x"),
        token.getAttributeBool("scroll-y")
    ));
    IF_ATTRIBUTE_EXP("wrap", ptr->getInner()->setWrap(token.getAttributeBool("wrap")));
    IF_ATTRIBUTE_EXP("align", ptr->getInner()->setAlign(token.getAttributeAlign("align")));
    IF_ATTRIBUTE_EXP("padding-top", ptr->getInner()->setPaddingTop(token.getAttributeUnits("padding-top")));
    IF_ATTRIBUTE_EXP("padding-left", ptr->getInner()->setPaddingLeft(token.getAttributeUnits("padding-left")));
    IF_ATTRIBUTE_EXP("padding-right", ptr->getInner()->setPaddingRight(token.getAttributeUnits("padding-right")));
    IF_ATTRIBUTE_EXP("padding-bottom", ptr->getInner()->setPaddingBottom(token.getAttributeUnits("padding-bottom")));
    IF_ATTRIBUTE_EXP("padding", {
        const auto attrs = token.getAttributeUnitsAttribute("padding");
        ptr->getInner()->setPadding(attrs[0], attrs[1], attrs[2], attrs[3]);
    });
    defaults(token, ptr.get(), registry, false, true);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiScrollableLayout::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    dynamic_cast<GuiScrollableLayout*>(acceptor)->getInner()->addWidget(child);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiRadio::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    std::string groupStr;
    IF_ATTRIBUTE_EXP("group", groupStr = token.getAttributeString("group"));
    GuiRadio* other = nullptr;
    if (!groupStr.empty()) {
        try {
            other = window->findByRef<GuiRadio>(groupStr);
        }
        catch (std::exception& e) {
            throw GuiXmlException("unable to find radio group by ref: \"" + groupStr + "\"");
        }
    }
    auto ptr = std::unique_ptr<GuiRadio>(new GuiRadio(
        window,
        token.getContent(),
        token.getAttributeInt("base"),
        other
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiCheckbox::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiCheckbox>(new GuiCheckbox(
        window,
        token.getContent()
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiSlider::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiSlider>(new GuiSlider(
        window,
        token.getAttributeBool("vertical")
    ));
    IF_ATTRIBUTE_EXP("value", ptr->setValue(token.getAttributeFloat("value")));
    IF_ATTRIBUTE_EXP("inversed", ptr->setInversed(token.getAttributeBool("inversed")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiScrollBar::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiScrollBar>(new GuiScrollBar(
        window,
        token.getAttributeBool("vertical")
    ));
    IF_ATTRIBUTE_EXP("value", ptr->setValue(token.getAttributeFloat("value")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiImageViewer::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiImageViewer>(new GuiImageViewer(
        window,
        registry->getImage(token.getAttributeString("image"))
    ));
    try {
        const auto x = token.getAttributeInt("sub-x");
        const auto y = token.getAttributeInt("sub-y");
        const auto w = token.getAttributeInt("sub-w");
        const auto h = token.getAttributeInt("sub-h");
        ptr->setSubsection(x, y, w, h);
    } catch (GuiXmlNotFound& e) {
        (void)e;
    }
    IF_ATTRIBUTE_EXP("label", ptr->setLabel(token.getAttributeString("label")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiTextInput::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    bool multiline = false;
    bool editable = true;
    IF_ATTRIBUTE_EXP("multiline", multiline = token.getAttributeBool("multiline"));
    IF_ATTRIBUTE_EXP("editable", editable = token.getAttributeBool("editable"));
    auto ptr = std::unique_ptr<GuiTextInput>(new GuiTextInput(
        window, multiline, editable
    ));
    ptr->setValue(token.getContent());
    IF_ATTRIBUTE_EXP("match", ptr->setMatch(token.getAttributeString("match")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiScrollableTextInput::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    bool editable = true;
    IF_ATTRIBUTE_EXP("editable", editable = token.getAttributeBool("editable"));
    auto ptr = std::unique_ptr<GuiScrollableTextInput>(new GuiScrollableTextInput(
        window, editable
    ));
    ptr->setValue(token.getContent());
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiList::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiList>(new GuiList(
        window
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiList::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    auto item = dynamic_cast<GuiList::Item*>(child);
    auto target = dynamic_cast<GuiList*>(acceptor);
    if (!item) throw GuiXmlException("list expects a widget of type \"list-item\"");
    item->setGroup(target->getGroup());
    item->setBaseValue(target->getInner()->getAllWidgets().size());
    target->addItem(item);
    if (item->hasFocus()) {
        target->setSelected(item);
    }
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiListItem::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiList::Item>(new GuiList::Item(
        window, token.getContent(), 0, nullptr
    ));
    defaults(token, ptr.get(), registry);
    IF_ATTRIBUTE_EXP("selected", ptr->setFocus(token.getAttributeBool("selected")));
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiSwitch::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiSwitch>(new GuiSwitch(
        window
    ));
    IF_ATTRIBUTE_EXP("value", ptr->setValue(token.getAttributeBool("value")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiProgressBar::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiProgressBar>(new GuiProgressBar(
        window
    ));
    IF_ATTRIBUTE_EXP("value", ptr->setValue(token.getAttributeFloat("value")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiProgressCircle::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiProgressCircle>(new GuiProgressCircle(
        window
    ));
    IF_ATTRIBUTE_EXP("value", ptr->setValue(token.getAttributeFloat("value")));
    IF_ATTRIBUTE_EXP("thickness", ptr->setThickness(token.getAttributeFloat("thickness")));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiTabs::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiTabs>(new GuiTabs(
        window
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiTabs::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    // Tabs are automatically added within VisitorGuiTabLayout::accept
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiTabLayout::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto parent = dynamic_cast<GuiTabs*>(acceptor);
    if (!parent) throw GuiXmlException("widget: \"tab\" can be only added into widget: \"tabs\"");

    const auto ptr = parent->addTab(token.getAttributeString("label"), 
        new GuiLayout(window, token.getAttributeOrientation("orientation"))
    );
    defaults(token, ptr->getTargetWidget(), registry);
    return ptr;
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiTabLayout::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    dynamic_cast<GuiLayout*>(dynamic_cast<GuiTabs::Button*>(acceptor)->getTargetWidget())->addWidget(child);
}

///=============================================================================
void ffw::GuiXmlParser::VisitorGuiText::addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const {
    (void)window;
    // Paras are automatically added within VisitorGuiTextPara::accept
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiText::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto ptr = std::unique_ptr<GuiText>(new GuiText(
        window
    ));
    defaults(token, ptr.get(), registry);
    RESET_AND_RETURN(ptr);
}

static inline unsigned char charToByte(const char b) {
    if (b >= 'A' && b <= 'F') return b - 'A' + 10;
    if (b >= 'a' && b <= 'f') return b - 'a' + 10;
    if (b >= '0' && b <= '9') return b - '0';
    return 0;
}

static ffw::Color strToColorHex(const std::string& str) {
    if (str.empty() || str.size() != 7 || str[0] != '#') return ffw::Color();
    return ffw::rgb(
        (charToByte(str[1]) << 4) | charToByte(str[2]),
        (charToByte(str[3]) << 4) | charToByte(str[4]),
        (charToByte(str[5]) << 4) | charToByte(str[6])
    );
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::VisitorGuiTextPara::accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const {
    auto parent = dynamic_cast<GuiText*>(acceptor);
    if (!parent) throw GuiXmlException("widget: \"para\" can be only added into widget: \"text\"");
    std::string colorStr;
    std::string fontStr;
    IF_ATTRIBUTE_EXP("color", colorStr = token.getAttributeString("color"));
    IF_ATTRIBUTE_EXP("font", fontStr = token.getAttributeString("font"));
    const GuiFont* font = parent->getCurrentFont();
    ffw::Color color = parent->getStyleGroup()->normal.text.color;
    if (!fontStr.empty()) font = registry->getFont(fontStr);
    if (!colorStr.empty()) {
        color = strToColorHex(colorStr);
    }
    parent->addParagraph(token.getContent(), color, font);
    return nullptr;
}

///=============================================================================
static const ffw::GuiXmlParser::VisitorGuiWindow visitorGuiWindow;
static const ffw::GuiXmlParser::VisitorGuiLayout visitorGuiLayout;
static const ffw::GuiXmlParser::VisitorGuiLabel visitorGuiLabel;
static const ffw::GuiXmlParser::VisitorGuiButton visitorGuiButton;
static const ffw::GuiXmlParser::VisitorGuiButtonToggle visitorGuiButtonToggle;
static const ffw::GuiXmlParser::VisitorGuiButtonPrimary visitorGuiButtonPrimary;
static const ffw::GuiXmlParser::VisitorGuiBox visitorGuiBox;
static const ffw::GuiXmlParser::VisitorGuiVerticalLayout visitorGuiVerticalLayout;
static const ffw::GuiXmlParser::VisitorGuiHorizontalLayout visitorGuiHorizontalLayout;
static const ffw::GuiXmlParser::VisitorGuiScrollableLayout visitorGuiScrollableLayout;
static const ffw::GuiXmlParser::VisitorGuiRadio visitorGuiRadio;
static const ffw::GuiXmlParser::VisitorGuiCheckbox visitorGuiCheckbox;
static const ffw::GuiXmlParser::VisitorGuiSlider visitorGuiSlider;
static const ffw::GuiXmlParser::VisitorGuiScrollBar visitorGuiScrollbar;
static const ffw::GuiXmlParser::VisitorGuiImageViewer visitorGuiImageViewer;
static const ffw::GuiXmlParser::VisitorGuiTextInput visitorGuiTextInput;
static const ffw::GuiXmlParser::VisitorGuiScrollableTextInput visitorGuiScrollableTextInput;
static const ffw::GuiXmlParser::VisitorGuiList visitorGuiList;
static const ffw::GuiXmlParser::VisitorGuiListItem visitorGuiListItem;
static const ffw::GuiXmlParser::VisitorGuiSwitch visitorGuiSwitch;
static const ffw::GuiXmlParser::VisitorGuiProgressBar visitorGuiProgressBar;
static const ffw::GuiXmlParser::VisitorGuiProgressCircle visitorGuiProgressCircle;
static const ffw::GuiXmlParser::VisitorGuiTabLayout visitorGuiTabLayout;
static const ffw::GuiXmlParser::VisitorGuiTabs visitorGuiTabs;
static const ffw::GuiXmlParser::VisitorGuiText visitorGuiText;
static const ffw::GuiXmlParser::VisitorGuiTextPara visitorGuiTextPara;

///=============================================================================
ffw::GuiXmlParser::GuiXmlParser(GuiWindow& window, const Registry& registry):window(window),registry(registry) {
    visitors = {
    { visitorGuiWindow.getKey(), &visitorGuiWindow },
    { visitorGuiLayout.getKey(), &visitorGuiLayout },
    { visitorGuiLabel.getKey(), &visitorGuiLabel },
    { visitorGuiButton.getKey(), &visitorGuiButton },
    { visitorGuiButtonToggle.getKey(), &visitorGuiButtonToggle },
    { visitorGuiBox.getKey(), &visitorGuiBox },
    { visitorGuiVerticalLayout.getKey(), &visitorGuiVerticalLayout },
    { visitorGuiHorizontalLayout.getKey(), &visitorGuiHorizontalLayout },
    { visitorGuiScrollableLayout.getKey(), &visitorGuiScrollableLayout },
    { visitorGuiButtonPrimary.getKey(), &visitorGuiButtonPrimary },
    { visitorGuiRadio.getKey(), &visitorGuiRadio },
    { visitorGuiCheckbox.getKey(), &visitorGuiCheckbox },
    { visitorGuiSlider.getKey(), &visitorGuiSlider },
    { visitorGuiScrollbar.getKey(), &visitorGuiScrollbar },
    { visitorGuiImageViewer.getKey(), &visitorGuiImageViewer },
    { visitorGuiTextInput.getKey(), &visitorGuiTextInput },
    { visitorGuiScrollableTextInput.getKey(), &visitorGuiScrollableTextInput },
    { visitorGuiList.getKey(), &visitorGuiList },
    { visitorGuiListItem.getKey(), &visitorGuiListItem },
    { visitorGuiSwitch.getKey(), &visitorGuiSwitch },
    { visitorGuiProgressBar.getKey(), &visitorGuiProgressBar },
    { visitorGuiProgressCircle.getKey(), &visitorGuiProgressCircle },
    { visitorGuiTabLayout.getKey(), &visitorGuiTabLayout },
    { visitorGuiTabs.getKey(), &visitorGuiTabs },
    { visitorGuiText.getKey(), &visitorGuiText },
    { visitorGuiTextPara.getKey(), &visitorGuiTextPara },
    };
}

///=============================================================================
void ffw::GuiXmlParser::parse(const char* src, const size_t len) {
    tinyxml2::XMLDocument document;

    if (!src) throw GuiXmlException("invalid input string");
    const auto err = document.Parse(src, len);
    if (err != tinyxml2::XMLError::XML_SUCCESS) {
        throw GuiXmlException("failed to parse document, error: " + std::string(getErrorStr(err)) + " at: " + document.ErrorStr());
    }

    if (std::string(document.RootElement()->Name()) != "window") {
        throw GuiXmlException("root must start with: \"window\" element");
    }

    recursive(document.RootElement(), nullptr);
}

///=============================================================================
ffw::GuiWidget* ffw::GuiXmlParser::recursive(tinyxml2::XMLElement* elem, GuiWidget* parent) {
    std::unique_ptr<GuiWidget> widget;
    const auto visitor = getVisitor(elem->Name());
    auto disabled = false;
    try {
        const auto token = XmlToken(elem);
        widget.reset(visitor->accept(parent, &window, token, &registry));
        IF_ATTRIBUTE_EXP("disabled", disabled = token.getAttributeBool("disabled"));
    }
    catch (std::exception& e) {
        throw GuiXmlException("error while parsing widget: \"" + visitor->getKey() + "\", error: " + std::string(e.what()));
    }

    auto it = elem->FirstChildElement();
    while (it) {
        std::unique_ptr<GuiWidget> w(recursive(it, widget.get()));
        visitor->addWidget(widget.get(), &window, w.get());
        w.release();
        it = it->NextSiblingElement();
    }
    if (disabled) widget->setDisabled(true);
    const auto ret = widget.get();
    widget.release();
    return ret;
}

///=============================================================================
const ffw::GuiXmlParser::Visitor* ffw::GuiXmlParser::getVisitor(const std::string& key) {
    const auto it = visitors.find(key);
    if (it == visitors.end()) {
        throw GuiXmlException("unknown widget: \"" + key + "\", error: no acceptor found");
    }
    return it->second;
}
