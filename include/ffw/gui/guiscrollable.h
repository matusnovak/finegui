/* This file is part of FineFramework project */
#ifndef FFW_GUI_SCROLLABLE
#define FFW_GUI_SCROLLABLE
#include "guiwidget.h"
#include "guiscrollbar.h"
#include "guilayout.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create a scrollable widget
    * @details This widget accepts any kind of widgets. If the inner widget
    * exceeds the size of the scrollable widget, the scrollbars will enable.
    * Using the scrollbars, the inner widget is moved up or down, or sideways.
    * You can configure which scrollbars are meant to be shown via the constructor.
    * A class ffw::GuiScrollableLayout is available which uses ffw::GuiScrollable
    * with ffw::GuiLayout as the inner widget.
    * @code
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * // Creates a verticall layout with a scrollbar on the right.
    * // 3rd parameter -> bottom scrollbar
    * // 4th parameter -> right scrollbar
    * auto scrollable = new ffw::GuiScrollableLayout(&gui, ffw::GuiOrientation::VERTICAL, false, true);
    * scrollable->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(100.0f));
    * 
    * // Get the inner widget that will be scrolled.
    * // In this case it's the layout.
    * auto layout = scrollable->getInner();
    * 
    * const auto goDown = new ffw::GuiButton(&gui, "Click to scroll to 50%");
    * goDown->addEventCallback([=](ffw::GuiEvent e) {
    *     // Returns the maximum scroll values.
    *     // Note that the returned type is ffw::Pointf and the x 
    *     // component (minimum scrollbar range) is always going to be zero!
    *     // The y component (maximum scroll range) is what you need.
    *     const auto max = scrollable->getVscroll()->getRange();
    * 
    *     // Scroll down 50%
    *     // This only works after gui.update() has been called
    *     // at least once! The update() function will update 
    *     // the scrollbars.
    *     // Therefore we are putting this in a button callback.
    *     scrollable->getVscroll()->setValue(max.y / 2.0f);
    * }, ffw::GuiEventType::ACTION);
    * 
    * layout->addWidget(goDown);
    * 
    * for (auto i = 0; i < 32; i++) {
    *     const auto button = new ffw::GuiButton(&gui, "Button #" + std::to_string(i));
    *     layout->addWidget(button);
    * }
    * 
    * root->addWidget(scrollable);
    * // Do not free the created widgets! They will be deleted by the gui window!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
    */
    class FFW_API GuiScrollable : public GuiWidget {
    public:
        struct Style {
            GuiScrollBar::Style scrollbarV;
            GuiScrollBar::Style scrollbarH;
            GuiWidget::Style self;
        };

        GuiScrollable(GuiWindow* context, GuiWidget* widget, bool hori, bool vert);
        virtual ~GuiScrollable() = default;
        ffw::Pointf getMinimumWrapSize() override;
        void setScrollbarThickness(float px);
        void setScrollValues(float hori, float vert);
        ffw::Pointf getScrollValues() const;
        inline float getScrollbarThickness() const {
            return thickness;
        }
        inline ffw::GuiScrollBar* getVscroll() {
            return vscroll;
        }
        inline const ffw::GuiScrollBar* getVscroll() const {
            return vscroll;
        }
        inline ffw::GuiScrollBar* getHscroll() {
            return hscroll;
        }
        inline const ffw::GuiScrollBar* getHscroll() const {
            return hscroll;
        }
        inline void setScrollIncrements(const float inc) {
            scrollInc = inc;
        }
        inline float getScrollIncrements() const {
            return scrollInc;
        }
        void setStyle(const GuiScrollable::Style* style, bool defaults = false);
    protected:
        inline ffw::GuiWidget* getInnerAsWidget() {
            return inner;
        }
        inline const ffw::GuiWidget* getInnerAsWidget() const {
            return inner;
        }
    private:
        void widgetEvent(GuiEvent e);
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        bool eventScroll(const ffw::Pointf& scroll) override;
        void eventSize(const ffw::Pointf& size) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        ffw::GuiScrollBar* vscroll;
        ffw::GuiScrollBar* hscroll;
        ffw::GuiWidget* inner;
        float thickness;
        float scrollInc;
    };
    /**
    * @ingroup gui
    */
    class FFW_API GuiScrollableLayout : public GuiScrollable {
    public:
        struct Style {
            GuiScrollable::Style self;
            GuiLayout::Style inner;
        };
        GuiScrollableLayout(GuiWindow* context, GuiOrientation orientation, bool hori, bool vert);
        virtual ~GuiScrollableLayout() = default;
        inline GuiLayout* getInner(){
            return dynamic_cast<ffw::GuiLayout*>(getInnerAsWidget());
        }
        inline const GuiLayout* getInner() const{
            return dynamic_cast<const ffw::GuiLayout*>(getInnerAsWidget());
        }
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        void setStyle(const GuiScrollableLayout::Style* style, bool defaults = false);
    };
}
#endif