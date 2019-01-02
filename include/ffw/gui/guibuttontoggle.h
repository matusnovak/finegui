/* This file is part of FineFramework project */
#ifndef FFW_GUI_BUTTON_TOGGLE
#define FFW_GUI_BUTTON_TOGGLE
#include "guibutton.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create a basic on/off toggle button with a label
    * @details Creates a basic toggle button with a label. A click callback
    * can be added, see example below.
    * @code
    * // Example creating a toggle button
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * auto button = new ffw::GuiButtonToggle(&gui, "Button");
    * button->setLabel("Button #1"); // Overwrites "Button"
    * button->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
    * button->addEventCallback([](ffw::GuiEvent e) {
    *     std::cout << "Clicked! Status: " << e.data.action.value << std::endl;
    * }, ffw::GuiEventType::ACTION);
    * auto isPressed = button->getValue(); // Programatically get on/off state
    * button->setValue(true); // Programatically set on/off state
    * 
    * root->addWidget(button);
    * // Do not free the created widgets! They will be deleted by window itself!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
    */
    class FFW_API GuiButtonToggle : public GuiButton {
    public:
        GuiButtonToggle(GuiWindow* context, const std::string& label);
        virtual ~GuiButtonToggle() = default;
        void setValue(bool value);
        bool getValue() const;
    private:
        void eventFocus(bool gained) override;
    };
    /**
    * @ingroup gui
    */
    class FFW_API GuiButtonTogglePrimary : public GuiButtonPrimary {
    public:
        GuiButtonTogglePrimary(GuiWindow* context, const std::string& label);
        virtual ~GuiButtonTogglePrimary() = default;
        void setValue(bool value);
        bool getValue() const;
    private:
        void eventFocus(bool gained) override;
    };
}
#endif
