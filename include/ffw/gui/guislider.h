/* This file is part of FineFramework project */
#ifndef FFW_GUI_SLIDER
#define FFW_GUI_SLIDER
#include "guiwidget.h"
namespace ffw {
    /**
     * @ingroup gui
     */
    class FFW_API GuiSlider: public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style button;
            GuiWidget::Style bar;
            GuiWidget::Style self;
        };
        GuiSlider(GuiWindow* context, bool vertical);
        virtual ~GuiSlider() = default;
        bool isVertical() const;
        void setValue(float val);
        float getValue() const;
        void setBarSize(const Point<GuiUnits>& s);
        inline const Point<GuiUnits>& getBarSize() const {
            return barSize;
        }
        const ffw::Pointf& getRange() const;
        void setRange(float min, float max);
        void setButtonSize(const Point<GuiUnits>& s);
        inline const Point<GuiUnits>& getButtonSize() const {
            return buttonSize;
        }
        void setInversed(bool inversed);
        bool getInversed() const;
        ffw::Pointf getMinimumWrapSize() override;
        void setBarStyleGroup(const GuiWidget::Style* style);
        inline const GuiWidget::Style* getBarStyleGroup() const {
            return styleBar;
        }
        void setButtonStyleGroup(const GuiWidget::Style* style);
        inline const GuiWidget::Style* getButtonStyleGroup() const {
            return styleButton;
        }
        void setStyle(const GuiSlider::Style* style, bool defaults = false);
    protected:
        const GuiWidget::Style* styleButton;
        const GuiWidget::Style* styleBar;
        Point<GuiUnits> buttonSize;
        Point<GuiUnits> barSize;
    private:
        void calculateButtonSize(ffw::Pointf& pos, ffw::Pointf& size) const;
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventHover(bool gained) override;
        void eventFocus(bool gained) override;
        void eventMouse(const ffw::Pointf& pos) override;
        void eventMouseButton(ffw::MouseButton button, ffw::MouseMode mode) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        bool vertical;
        ffw::Pointf range;
        float value;
        bool inverse;
        Pointi clickedOffset;
    };
}
#endif
