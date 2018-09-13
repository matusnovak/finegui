/* This file is part of FineFramework project */
#ifndef FFW_GUI_WIDGET
#define FFW_GUI_WIDGET

#include <functional>
#include <vector>
#include "constants.h"
#include "guifont.h"
#include "guistyle.h"

namespace ffw {
    class GuiWindow;
    class GuiWidget;
    class GuiTheme;
    /**
     * @ingroup gui
     */
    enum class GuiEventType {
        ACTION = 0x1,
        //SELECTED = 0x2,
        //CHANGED = 0x4,
        //SLIDED = 0x8,
        SIZE = 0x10,
        INNER = 0x20,
        POSITION = 0x40,
        HOVER = 0x80,
        FOCUS = 0x100,
        STATE = 0x200,
        INPUT = 0x400,
        KEY = 0x800,
        MOUSEBTN = 0x1000,
        ALL = 0x7FFFFFFF,
    };

    enum class GuiFocusType {
        DEFAULT = 0,
        STICKY,
        DROP,
        TOGGLE,
    };

    enum class GuiOrientation {
        FIXED,
        VERTICAL,
        HORIZONTAL
    };

    class GuiEvent {
    public:
        union Data {
            struct ActionData {
                int value;
            } action;

            struct SizeData {
                float width;
                float height;
            } size;

            struct InnerData {
                float width;
                float height;
            } inner;

            struct PosData {
                float x;
                float y;
            } pos;

            struct HoverData {
                bool gained;
            } hover;

            struct FocusData {
                bool gained;
            } focus;

            struct StateData {
                bool disabled;
            } state;

            struct InputData {
                unsigned int chr;
            } input;

            struct InputKey {
                ffw::Key key;
                ffw::KeyMode mode;
            } key;

            struct MousebtnData {
                ffw::MouseButton button;
                ffw::MouseMode mode;
            } mousebtn;
        };

        GuiEvent(GuiWidget* widget, GuiEventType type, Data data):widget(widget),type(type),data(data) {
        }

        GuiWidget* widget = nullptr;
        GuiEventType type = GuiEventType::ACTION;
        Data data;
    };
    /**
    * @ingroup gui
    */
    struct GuiCallback {
        std::function<void(GuiEvent)> func = nullptr;
        bool now = false;
        GuiEventType type = GuiEventType::ALL;

        template<class T>
        static GuiCallback make(void (T::*memfuncptr)(GuiEvent), T* instance, GuiEventType type = GuiEventType::ALL, bool instant = false) {
            GuiCallback callback = GuiCallback();
            callback.func = std::bind(memfuncptr, instance, std::placeholders::_1);
            callback.now = instant;
            callback.type = type;
            return callback;
        }
        static GuiCallback make(const std::function<void(GuiEvent)>& function, GuiEventType type = GuiEventType::ALL, bool instant = false) {
            GuiCallback callback = GuiCallback();
            callback.func = function;
            callback.now = instant;
            callback.type = type;
            return callback;
        }
        template<typename F>
        static GuiCallback make(const F& lambda, GuiEventType type = GuiEventType::ALL, bool instant = false) {
            GuiCallback callback = GuiCallback();
            callback.func = std::function<void(GuiEvent)>(lambda);
            callback.now = instant;
            callback.type = type;
            return callback;
        }
    };
    /**
     * @ingroup gui
     */
    class GuiUserInput {
    public:
        ffw::MouseButton mousebtn;
        ffw::MouseMode mousemode;
        unsigned int chr;
        ffw::Key key;
        ffw::KeyMode keymode;
        mutable ffw::Pointf scroll;
    };
    /**
     * @ingroup gui
     */
    class FFW_API GuiWidget {
    public:
        struct Style {
            GuiStyle normal;
            GuiStyle hover;
            GuiStyle active;
            GuiStyle disabled;
            GuiDefaults defaults;
        };
        struct Flags {
            unsigned int hover: 1;
            unsigned int focus: 1;
            unsigned int disabled: 1;
            unsigned int hidden: 1;
            unsigned int wrap: 1;
            unsigned int render: 1;
            unsigned int invalidate: 1;
            unsigned int ignore: 1;
            unsigned int rearrange: 1;
            unsigned int first: 1;
            unsigned int eventpos: 1;
            unsigned int eventsize: 1;
            unsigned int eventinner: 1;
            unsigned int eventdisabled: 1;
            unsigned int eventfocus: 1;
            unsigned int eventhover: 1;
        };
        GuiWidget(GuiWindow* context);
        GuiWidget(const GuiWidget& other) = delete;
        GuiWidget(GuiWidget&& other);
        void swap(GuiWidget& other);
        virtual ~GuiWidget();
        inline void setSize(GuiUnits width, GuiUnits height) {
            setSize(Point<GuiUnits>(width, height));
        }
        void setSize(const Point<GuiUnits>& s);
        void setPos(const Point<GuiUnits>& pos) {
            setPos(pos.x, pos.y);
        }
        void setPos(GuiUnits posx, GuiUnits posy);
        const Point<GuiUnits>& getPos() const;
        const Point<GuiUnits>& getSize() const;
        ffw::Pointf getVisibleContentSize() const;
        ffw::Pointf getVisibleContentPos() const;
        inline ffw::Pointf getInnerContentSize() const {
            return totalSize;
        }
        inline ffw::Pointf getInnerContentPos() const {
            return getVisibleContentPos() + offset;
        }
        ffw::Pointf getAbsolutePos() const;
        void setOffset(const ffw::Pointf off);
        const ffw::Pointf& getOffset() const;
        void setPadding(GuiUnits top, GuiUnits right, GuiUnits bottom, GuiUnits left);
        inline void setPadding(GuiUnits all) {
            setPadding(all, all, all, all);
        }
        inline void setPadding(const GuiStyle::Padding& pad) {
            setPadding(pad[0], pad[1], pad[2], pad[3]);
        }
        void setMargin(GuiUnits top, GuiUnits right, GuiUnits bottom, GuiUnits left);
        inline void setMargin(GuiUnits all) {
            setMargin(all, all, all, all);
        }
        inline void setMargin(const GuiStyle::Margin& mar) {
            setMargin(mar[0], mar[1], mar[2], mar[3]);
        }
        inline const GuiStyle::Padding& getPadding() const {
            return padding;
        }
        inline const GuiStyle::Margin& getMargin() const {
            return margin;
        }
        inline GuiUnits getPadding(int side) const {
            return padding[side];
        }
        inline GuiUnits getMargin(int side) const {
            return margin[side];
        }
        inline void setMarginTop(GuiUnits val) {
            setMargin(val, margin[1], margin[2], margin[3]);
        }
        inline void setMarginRight(GuiUnits val) {
            setMargin(margin[0], val, margin[2], margin[3]);
        }
        inline void setMarginBottom(GuiUnits val) {
            setMargin(margin[0], margin[1], val, margin[3]);
        }
        inline void setMarginLeft(GuiUnits val) {
            setMargin(margin[0], margin[1], margin[2], val);
        }
        inline void setPaddingTop(GuiUnits val) {
            setPadding(val, padding[1], padding[2], padding[3]);
        }
        inline void setPaddingRight(GuiUnits val) {
            setPadding(padding[0], val, padding[2], padding[3]);
        }
        inline void setPaddingBottom(GuiUnits val) {
            setPadding(padding[0], padding[1], val, padding[3]);
        }
        inline void setPaddingLeft(GuiUnits val) {
            setPadding(padding[0], padding[1], padding[2], val);
        }
        float getPaddingInPixels(int side) const;
        float getMarginInPixels(int side) const;
        void setAlign(GuiAlign align);
        GuiAlign getAlign() const;
        void setWrap(bool wrap);
        inline bool getWrap() const {
            return flags.wrap;
        }
        void setID(unsigned long id);
        void setRef(std::string ref);
        unsigned long getID() const;
        inline const std::string& getRef() const {
            return ref;
        }
        void update(const ffw::Pointf& parentpos, const ffw::Pointf& parentsize, const GuiUserInput& input, ffw::Pointf mousepos, bool mouseout);
        void render(const ffw::Pointf& clippos, const ffw::Pointf& clipsize, const ffw::Pointf& off, bool clear);
        bool shouldRedraw() const;
        void redraw();
        void invalidate();
        void setParent(GuiWidget* parent);
        const GuiWidget* getParent() const;
        inline bool hasHover() const {
            return flags.hover;
        }
        inline bool hasFocus() const {
            return flags.focus;
        }
        void setFocus(bool f);
        void setHover(bool h);
        void setDisabled(bool d);
        void setHidden(bool h);
        void setIgnoreUserInput(bool d);
        inline void hide() {
            setHidden(true);
        }
        inline void show() {
            setHidden(false);
        }
        inline bool isHidden() const {
            return flags.hidden;
        }
        inline bool isDisabled() const {
            return flags.disabled;
        }
        void setFont(const GuiFont* font);
        const GuiFont* getFont() const;
        const GuiFont* getCurrentFont() const;
        inline const Pointi getMousePos() const {
            return mouseOld;
        }
        virtual ffw::Pointf getMinimumWrapSize() = 0;
        ffw::Pointf getOuterWrapSize() {
            auto s = getMinimumWrapSize();
            s.x += getPaddingInPixels(1) + getPaddingInPixels(3) + getMarginInPixels(1) + getMarginInPixels(3);
            s.y += getPaddingInPixels(0) + getPaddingInPixels(2) + getMarginInPixels(0) + getMarginInPixels(2);
            return s;
        }
        template<class T>
        T* findByID(unsigned long id_){
            if(typeid(*this).hash_code() == typeid(T).hash_code() && id == id_)return dynamic_cast<T*>(this);
            else if(widgets.size() > 0){
                for(auto& w : widgets){
                    T* test = w->findByID<T>(id_);
                    if(test != NULL)return test;
                }
            }
            return NULL;
        }
        template<class T>
        void addEventCallback(void (T::*memfuncptr)(GuiEvent), T* instance, GuiEventType type = GuiEventType::ALL, bool now = false){
            eventCallbacks.push_back(GuiCallback::make(memfuncptr, instance, type, now));
        }
        void addEventCallback(const std::function<void(GuiEvent)>& function, GuiEventType type = GuiEventType::ALL, bool now = false) {
            eventCallbacks.push_back(GuiCallback::make(function, type, now));
        }
        template<typename F>
        void addEventCallback(const F& lambda, GuiEventType type = GuiEventType::ALL, bool now = false) {
            eventCallbacks.push_back(GuiCallback::make(lambda, type, now));
        }
        void setTheme(const GuiTheme* theme, bool defaults = false);
        void setStyleGroup(const GuiWidget::Style* style);
        inline const GuiWidget::Style* getStyleGroup() {
            return widgetStyle;
        }
        inline const ffw::GuiStyle* getCurrentStyle() const {
            return getCurrentStyle(widgetStyle);
        }
        const ffw::GuiStyle* getCurrentStyle(const GuiWidget::Style* group) const;
        inline const ffw::Pointf& getRealSize() const {
            return sizeReal;
        }
        inline ffw::Pointf getRealSizeWithMargin() const {
            return ffw::Pointf(
                sizeReal.x + getMarginInPixels(1) + getMarginInPixels(3),
                sizeReal.y + getMarginInPixels(0) + getMarginInPixels(2)
            );
        }
        inline const ffw::Pointf& getRealPos() const {
            return posReal;
        }
        inline void setLineHeight(float height) {
            lineHeight = height;
            redraw();
        }
        inline float getLineHeight() const {
            return lineHeight;
        }
        inline void setDefaults(const ffw::GuiDefaults* def) {
            if (def != NULL) {
                size.set(def->size.x, def->size.y);
                padding = def->padding;
                margin = def->margin;
                align = def->align;
            }
        }
        inline GuiWindow* getWindow() {
            return context;
        }
        inline const GuiWindow* getWindow() const  {
            return context;
        }
        inline void setToggleFocus() {
            focusType = GuiFocusType::TOGGLE;
        }
        inline void setStickyFocus() {
            focusType = GuiFocusType::STICKY;
        }
        inline void setDropFocus() {
            focusType = GuiFocusType::DROP;
        }
        inline void setDefaultFocus() {
            focusType = GuiFocusType::DEFAULT;
        }
        inline GuiFocusType getFocusType() const {
            return focusType;
        }
        inline const std::vector<GuiWidget*>& getAllWidgets() const {
            return widgets;
        }
        void pushEvent(GuiEventType type, GuiEvent::Data data);
        GuiWidget& operator = (const GuiWidget& other) = delete;
        GuiWidget& operator = (GuiWidget&& other);
    protected:
        void traverseBackground(const ffw::Pointf& pos, const ffw::Pointf& size);
        GuiWidget* addWidgetInternal(GuiWidget* widget);
        GuiWidget* addWidgetAfterInternal(const GuiWidget* previous, GuiWidget* widget);
        GuiWidget* addWidgetBeforeInternal(const GuiWidget* next, GuiWidget* widget);
        void deleteWidgetsInternal();
        bool deleteSingleWidgetInternal(const GuiWidget* widget);
        void setOrientationInternal(GuiOrientation orientation);
        void recalculatePos();
        void recalculateSize(GuiWidget* ptr = NULL);
        void renderComponent(const ffw::Pointf& pos, const ffw::Pointf& size, const ffw::GuiStyle* group);
        virtual void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) = 0;
        virtual void eventPos(const ffw::Pointf& pos);
        virtual void eventSize(const ffw::Pointf& size);
        virtual void eventHover(bool gained);
        virtual void eventFocus(bool gained);
        virtual void eventMouse(const ffw::Pointf& mousePos);
        virtual bool eventScroll(const ffw::Pointf& scroll);
        virtual void eventMouseButton(ffw::MouseButton button, ffw::MouseMode mode);
        virtual void eventText(uint32_t chr);
        virtual void eventKey(ffw::Key key, ffw::KeyMode mode);
        virtual void eventDisabled(bool disabled);
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults = false) = 0;
        GuiWindow* context;
        const GuiWidget::Style* widgetStyle;
        inline const Flags& getFlags() const {
            return flags;
        }
    private:
        void checkEvents();
        void arrangeWidgetsVertical(GuiWidget* ptr = nullptr);
        void arrangeWidgetsHorizontal(GuiWidget* ptr = nullptr);
        void arrangeWidgetsFixed(GuiWidget* ptr = nullptr);
        void realignWidgetsHorizontally(size_t start, size_t end, const ffw::Pointf& contentSize);
        void realignWidgetsHorizontallyEnd(size_t start, size_t end, const ffw::Pointf& contentSize, const ffw::Pointf& totalSize);
        void realignWidgetsVertically(size_t start, size_t end, const ffw::Pointf& contentSize);
        void realignWidgetsVerticallyEnd(size_t start, size_t end, const ffw::Pointf& contentSize, const ffw::Pointf& totalSize);
        ffw::Pointf sizeReal;
        ffw::Pointf posReal;
        ffw::GuiUnits2D size;
        ffw::GuiUnits2D pos;
        ffw::Pointf mouseOld;
        ffw::Pointf offset;
        ffw::Pointf totalSize;
        GuiOrientation orientation;
        GuiAlign align;
        std::vector<GuiWidget*> widgets;
        GuiStyle::Margin margin;
        GuiStyle::Padding padding;
        GuiFocusType focusType;
        float lineHeight;
        const GuiFont* widgetfont;
        unsigned long id;
        std::string ref;
        GuiWidget* parent;
        std::vector<GuiCallback> eventCallbacks;
        Flags flags;
    };
}

#endif
