/* This file is part of FineFramework project */
#ifndef FFW_GUI_PROGRESSCIRCLE
#define FFW_GUI_PROGRESSCIRCLE
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create a progress circle widget
    * @code
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * auto progress = new ffw::GuiProgressCircle(&gui);
    * progress->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(100.0f));
    * progress->setValue(75.0f);
    * auto percent = progress->getValue(); // Programatically get value
    * 
    * root->addWidget(progress);
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
    * @note The height or width of the circle will be adjusted based on
    * the available size. For example if you call setSize() with 100%
    * width and 100px height, the circle will be 100x100 pixels.
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
