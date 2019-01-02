/* This file is part of FineFramework project */
#ifndef FFW_GUI_CHECKBOX
#define FFW_GUI_CHECKBOX
#include "guilabel.h"
namespace ffw {
    /**
     * @ingroup gui
     * @brief Create a checkbox widget with on/off status and a label
     * @code
     * // Example creating a checkbox
     * auto gui = ffw::GuiWindowNanoVG(nvg);
     * auto root = gui.getLayout();
     * 
     * auto checkbox = new ffw::GuiCheckbox(&gui, "I am a checkbox");
     * checkbox->setLabel("I am a new label");
     * checkbox->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(25.0f));
     * checkbox->addEventCallback([](ffw::GuiEvent e) {
     *     std::cout << "Clicked! Status: " << e.data.action.value << std::endl;
     * }, ffw::GuiEventType::ACTION);
     * auto isPressed = checkbox->getValue(); // Programatically get on/off state
     * checkbox->setValue(true); // Programatically set on/off state
     * 
     * root->addWidget(checkbox);
     * // Do not free the created widgets! They will be deleted by window itself!
     * 
     * while(true){
     *     // Render the gui
     * }
     * @endcode
     */
    class FFW_API GuiCheckbox: public GuiWidget {
    public:
        class FFW_API Button : public GuiWidget {
        public:
            struct Style {
                GuiWidget::Style self;
            };
            Button(GuiWindow* context);
            virtual ~Button() = default;
            ffw::Pointf getMinimumWrapSize() override;
            void setStyle(const Button::Style* style, bool defaults = false);
        private:
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
            void eventHover(bool gained) override;
            void eventFocus(bool gained) override;
            virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        };

        struct Style {
            GuiCheckbox::Button::Style button;
            GuiWidget::Style self;
        };

        GuiCheckbox(GuiWindow* context, const std::string& label);
        virtual ~GuiCheckbox() = default;
        void setLabel(const std::string& label);
        const std::string& getLabel() const;
        void setValue(bool value);
        bool getValue() const;
        inline const GuiCheckbox::Button* getButton() const {
            return widgetbutton;
        }
        inline GuiCheckbox::Button* getButton(){
            return widgetbutton;
        }
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiCheckbox::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        GuiCheckbox::Button* widgetbutton;
        std::string label;
    };
}
#endif
