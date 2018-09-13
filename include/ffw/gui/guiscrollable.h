/* This file is part of FineFramework project */
#ifndef FFW_GUI_SCROLLABLE
#define FFW_GUI_SCROLLABLE
#include "guiwidget.h"
#include "guiscrollbar.h"
#include "guilayout.h"
namespace ffw {
    /**
    * @ingroup gui
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