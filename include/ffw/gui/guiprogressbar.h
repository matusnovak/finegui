/* This file is part of FineFramework project */
#ifndef FFW_GUI_PROGRESSBAR
#define FFW_GUI_PROGRESSBAR
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create a progress bar widget
    * @code
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * auto progress = new ffw::GuiProgressBar(&gui);
    * progress->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
    * progress->setValue(75.0f);
    * auto percent = progress->getValue(); // Programatically get value
    * 
    * root->addWidget(progress);
    * // Do not free the created widgets! They will be deleted by the gui window!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
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
