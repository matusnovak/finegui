/* This file is part of FineFramework project */
#ifndef FFW_GUI_BUTTON
#define FFW_GUI_BUTTON
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create a basic button with a label
    * @details Creates a basic button with a label. A click callback
    * can be added, see example below.
    * @code
    * // Example creating a button
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * auto button = new ffw::GuiButton(&gui, "Button");
    * button->setLabel("Button #1"); // Overwrites "Button"
    * button->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
    * button->addEventCallback([](ffw::GuiEvent e) {
    *     std::cout << "Clicked!" << std::endl;
    * }, ffw::GuiEventType::ACTION);
    * 
    * root->addWidget(button);
    * // Do not free the created widgets! They will be deleted by window itself!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
    */
    class FFW_API GuiButton : public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };
        
        GuiButton(GuiWindow* context, const std::string& label);
        virtual ~GuiButton() = default;
        void setLabel(const std::string& label);
        const std::string& getLabel() const;
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiButton::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventHover(bool gained) override;
        void eventFocus(bool gained) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        std::string label;
    };
    /**
    * @ingroup gui
    */
    class FFW_API GuiButtonPrimary : public GuiButton {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        GuiButtonPrimary(GuiWindow* context, const std::string& label);
        virtual ~GuiButtonPrimary() = default;
        void setStyle(const GuiButtonPrimary::Style* style, bool defaults = false);
    private:
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
    };
}
#endif
