/* This file is part of FineFramework project */
#ifndef FFW_GUI_SWITCH
#define FFW_GUI_SWITCH
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create a switch widget
    * @details This widget acts exactly as the ffw::GuiButtonToggle
    * @code
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * auto button = new ffw::GuiSwitch(&gui);
    * button->setSize(ffw::guiPixels(50.0f), ffw::guiPixels(25.0f));
    * button->addEventCallback([](ffw::GuiEvent e) {
    *     std::cout << "Clicked! Status: " << e.data.action.value << std::endl;
    * }, ffw::GuiEventType::ACTION);
    * auto isPressed = button->getValue(); // Programatically get on/off state
    * button->setValue(true); // Programatically set on/off state
    * 
    * root->addWidget(button);
    * // Do not free the created widgets! They will be deleted by the gui window!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
    */
    class FFW_API GuiSwitch : public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style button;
            GuiWidget::Style self;
        };
        GuiSwitch(GuiWindow* context);
        virtual ~GuiSwitch() = default;
        void setValue(bool value);
        bool getValue() const;
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiSwitch::Style* style, bool defaults = false);
    protected:
        const GuiWidget::Style* styleButton;
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventHover(bool gained) override;
        void eventFocus(bool gained) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
    };
}
#endif
