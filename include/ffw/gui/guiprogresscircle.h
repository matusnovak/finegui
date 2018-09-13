/* This file is part of FineFramework project */
#ifndef FFW_GUI_PROGRESSCIRCLE
#define FFW_GUI_PROGRESSCIRCLE
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    */
    class FFW_API GuiProgressCircle : public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };
        GuiProgressCircle(GuiWindow* context);
        virtual ~GuiProgressCircle() = default;
        ffw::Pointf getMinimumWrapSize() override;
        void setValue(float value);
        inline float getValue() const {
            return percent;
        }
        void setThickness(float val);
        inline float getThickness() const {
            return thickness;
        }
        void setStyle(const GuiProgressCircle::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        std::string label;
        float percent;
        float thickness;
    };
}
#endif
