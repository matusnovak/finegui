#include <ffw/gui.h>

class GuiWidgetNull: public ffw::GuiWidget {
public:
    GuiWidgetNull(ffw::GuiWindow* context):GuiWidget(context) {
    }
    virtual ~GuiWidgetNull() {
    }
    ffw::Pointf getMinimumWrapSize() override {
        return 0;
    }
private:
    void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override {
        (void)contentoffset;
        (void)contentsize;
    }
    void eventPos(const ffw::Pointf& p) override {
        (void)p;
    }
    void eventSize(const ffw::Pointf& s) override {
        (void)s;
    }
    void eventHover(bool gained) override {
        (void)gained;
    }
    void eventFocus(bool gained) override {
        (void)gained;
    }
    void eventMouse(const ffw::Pointf& p) override {
        (void)p;
    }
    bool eventScroll(const ffw::Pointf& s) override {
        (void)s;
        return false;
    }
    void eventMouseButton(ffw::MouseButton button, ffw::MouseMode mode) override {
        (void)button;
        (void)mode;
    }
    void eventText(uint32_t chr) override {
        (void)chr;
    }
    void eventKey(ffw::Key key, ffw::KeyMode mode) override {
        (void)key;
        (void)mode;
    }
    void eventDisabled(bool disabled) override {
        (void)disabled;
    }
    void eventThemeChanged(const ffw::GuiTheme* theme, const bool defaults) override {
        (void)defaults;
        (void)theme;
    }
};

class GuiFontNull: public ffw::GuiFont {
public:
    GuiFontNull() {
        points = 0;
    }
    virtual ~GuiFontNull() {
    }
    bool isCreated() const override {
        return true;
    }
    void destroy() override {
    }
    void create(int pixels) {
        points = pixels;
    }
    ffw::Pointf getStringSize(const std::string& str, float maxWidth, float lineHeight = 1.25) const override {
      return getStringSizeFunc(str, lineHeight);
    }
    float getCharAdvance(unsigned int c) const override {
        (void)c;
        return (float)points;
    }
    float getEmptyLineHeight(float lineHeight) const override {
        return points * lineHeight;
    }
private:
    template<class T>
    ffw::Pointf getStringSizeFunc(const T& str, float lineHeight) const {
        ffw::Pointf s(0, float(points * lineHeight));
        float width = 0;
        for (const auto& c : str) {
            if (c == '\n') {
                s.y += int(points * lineHeight);
                width = std::max(s.x, width);
                s.x = 0;
            }
            else {
                width += points;
            }
        }
        s.x = std::max(s.x, width);
        return s;
    }
    int points;
};

class GuiWindowNull : public ffw::GuiWindow {
public:
    GuiWindowNull() {
        counter = 0;
    }
    virtual ~GuiWindowNull() {
    }
     void resize(int width, int height) override {
         (void)width;
         (void)height;
    }
    void drawRectangle(const ffw::Pointf& p, const ffw::Pointf& s, const ffw::Color& color) const override {
        (void)p;
        (void)s;
        (void)color;
    }
    void drawTriangle(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, const ffw::Color& color) const override {
        (void)p0;
        (void)p1;
        (void)p2;
        (void)color;
    }
    void drawRectangleRounded(const ffw::Pointf& p, const ffw::Pointf& s, const ffw::Color& color, float tl, float tr, float br, float bl) const override {
        (void)p;
        (void)s;
        (void)color;
        (void)tl;
        (void)tr;
        (void)br;
        (void)bl;
    }
    void drawBackground(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiStyle::Background& background, bool ignore) const override {
        (void)pos;
        (void)size;
        (void)background;
        (void)ignore;
    }
    void drawBorder(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiStyle::Border& border) const override {
        (void)pos;
        (void)size;
        (void)border;
    }
    void drawLine(const ffw::Pointf& start, const ffw::Pointf& end, const ffw::Color& color, float width) const override {
        (void)start;
        (void)end;
        (void)color;
        (void)width;
    }
    void drawCircle(const ffw::Pointf& p, float radius, const ffw::Color& color) const override {
        (void)p;
        (void)radius;
        (void)color;
    }
    void drawArc(const ffw::Pointf& p, float inner, float outer, float start, float end, const ffw::Color& color) const override {
        (void)p;
        (void)inner;
        (void)outer;
        (void)start;
        (void)end;
        (void)color;
    }
    void drawQuad(const ffw::Pointf& p0, const ffw::Pointf& p1, const ffw::Pointf& p2, const ffw::Pointf& p3, const ffw::Color& color) const override {
        (void)p0;
        (void)p1;
        (void)p2;
        (void)p3;
        (void)color;
    }
    void drawString(const ffw::Pointf& p, const ffw::GuiFont* font, const std::string::value_type* str, size_t length, const ffw::Color& color, float lineHeight = 1.25f) const override {
        (void)p;
        (void)font;
        (void)str;
        (void)length;
        (void)color;
        (void)lineHeight;
    }
    void drawImage(const ffw::Pointf& p, const ffw::Pointf& s, const ffw::GuiImage* image, const ffw::Recti& sub, bool mirrorX, bool mirrorY, const ffw::Color& color) const override {
        (void)p;
        (void)s;
        (void)image;
        (void)sub;
        (void)mirrorX;
        (void)mirrorY;
        (void)color;
    }
    void startRender() override {
    }
    void endRender() override {
    }
    void setScissors(const ffw::Pointf& p, const ffw::Pointf& s) const override {
        counter++;
        (void)p;
        (void)s;
    }
    void clearWithColor(const ffw::Color& color) const override {
        (void)color;
    }
    int renderCounter() const {
        return counter;
    }
    void clearCounter() {
        counter = 0;
    }
private:
    mutable int counter;
};

class GuiWidgetNullSticky : public GuiWidgetNull {
public:
    GuiWidgetNullSticky(ffw::GuiWindow* context):GuiWidgetNull(context) {
        GuiWidget::setStickyFocus();
    }
    virtual ~GuiWidgetNullSticky() {

    }
};

class GuiWidgetNullToggle : public GuiWidgetNull {
public:
    GuiWidgetNullToggle(ffw::GuiWindow* context) :GuiWidgetNull(context) {
        GuiWidget::setToggleFocus();
    }
    virtual ~GuiWidgetNullToggle() {

    }
};

class GuiWidgetNullDrop : public GuiWidgetNull {
public:
    GuiWidgetNullDrop(ffw::GuiWindow* context) :GuiWidgetNull(context) {
        GuiWidget::setDropFocus();
    }
    virtual ~GuiWidgetNullDrop() {

    }
};

class GuiEventCatcher {
public:
    GuiEventCatcher() {

    }
    ~GuiEventCatcher() {

    }
    void widgetEvent(ffw::GuiEvent e) {
        events.push_back(e);
    }
    void reset() {
        events.clear();
    }
    size_t count(ffw::GuiEventType type, ffw::GuiWidget* widget = NULL) {
        size_t cnt = 0;
        for (const auto& e : events) {
            if (widget != NULL && e.type == type && e.widget == widget)cnt++;
            if (widget == NULL && e.type == type)cnt++;
        }
        return cnt;
    }
    ffw::GuiEvent get(ffw::GuiEventType type, ffw::GuiWidget* widget = NULL) {
        for (const auto& e : events) {
            if (widget != NULL && e.type == type && e.widget == widget)return e;
            if (widget == NULL && e.type == type)return e;
        }
        throw std::out_of_range("No event found!");
    }
    std::vector<ffw::GuiEvent> events;
};

#include "nullstyles.h"

#define TEST_SETUP_WINDOW(w, h) \
    GuiWindowNull gui; \
    GuiFontNull font; \
    font.create(8); \
    gui.setTheme(&nullTheme, true); \
    gui.setPos(0, 0); \
    gui.setSize(w, h); \
    gui.setDefaultFont(&font);

#define TEST_UPDATE_AND_RENDER \
    gui.update(); \
    gui.render(); \
    gui.poolEvents();
    
// End