/* This file is part of FineFramework project */
#ifndef FFW_GUI_PROGRESSBAR
#define FFW_GUI_PROGRESSBAR
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    */
    class FFW_API GuiProgressBar : public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style inner;
            GuiWidget::Style self;
        };
        
        GuiProgressBar(GuiWindow* context);
        virtual ~GuiProgressBar() = default;
        ffw::Pointf getMinimumWrapSize() override;
        void setValue(const float value);
        inline float getValue() const {
            return percent;
        }
        void setInnerStyleGroup(const GuiWidget::Style* style);
        const GuiWidget::Style* getInnerStyleGroup() const  {
            return innerStyle;
        }
        void setStyle(const GuiProgressBar::Style* style, bool defaults = false);
    protected:
        const GuiWidget::Style* innerStyle;
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        float percent;
    };
}
#endif
