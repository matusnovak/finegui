/* This file is part of FineFramework project */
#ifndef FFW_GUI_RADIO
#define FFW_GUI_RADIO
#include "guilabel.h"

namespace ffw {
    /**
     * @ingroup gui
     * @brief Create a radio widgets
     * @details It is possible to group together multiple
     * radio widgets together (when you click one, it will turn off
     * other radios). The setValue() and getValue() operates on integers
     * and the value is based on the base value set in the constructor.
     * In the example below we are creating widgets with base values of 
     * 100, 200, and 300.
     * @code
     * auto gui = ffw::GuiWindowNanoVG(nvg);
     * auto root = gui.getLayout();
     * 
     * // Create three radios that will belong to the same group.
     * // To group radios, simply add first of the group member as
     * // the 4th parameter. The base value is the 3rd parameter.
     * // This is similar as in HTML: <input type="radio" value="100" .../>
     * auto radio1 = new ffw::GuiRadio(&gui, "Radio #1", 100);
     * auto radio2 = new ffw::GuiRadio(&gui, "Radio #2", 200, radio1);
     * auto radio3 = new ffw::GuiRadio(&gui, "Radio #3", 300, radio1);
     * 
     * radio1->addEventCallback([](ffw::GuiEvent e) {
     *     // The "e.data.action.value" will be
     *     // the base value, either 100, 200, or 300
     *     std::cout << "Radio selected value: " << e.data.action.value << std::endl;
     * }, ffw::GuiEventType::ACTION);
     * 
     * // To change which radio is set, simply call setValue()
     * // on any of the grouped radios. This also works on
     * // getting the value via getValue().
     * radio1->setValue(200);
     * 
     * root->addWidget(radio1);
     * root->addWidget(radio2);
     * root->addWidget(radio3);
     * // Do not free the created widgets! They will be deleted by the gui window!
     * 
     * while(true){
     *     // Render the gui
     * }
     * @endcode
     */
    class FFW_API GuiRadio: public GuiWidget {
    public:
        class FFW_API Value {
        public:
            Value();
            virtual ~Value() = default;
            void setValue(int value);
            int getValue() const;
            void assign(GuiRadio* radio);
            void remove(GuiRadio* radio);
            void clearAllExcept(const GuiRadio* radio);
            size_t getNumOfAssigned() const;
        private:
            std::vector<GuiRadio*> radios;
            int value;
        };
        
        class FFW_API Button : public GuiWidget {
        public:
            struct Style {
                GuiWidget::Style self;
            };

            Button(GuiWindow* context);
            virtual ~Button() = default;
            ffw::Pointf getMinimumWrapSize() override;
            GuiRadio::Value* group;
            GuiRadio* parentradio;
            void setStyle(const Button::Style* style, bool defaults = false);
        private:
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
            void eventHover(bool gained) override;
            void eventFocus(bool gained) override;
            virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        };
        
        struct Style {
            GuiRadio::Button::Style button;
            GuiWidget::Style self;
        };
        GuiRadio(GuiWindow* context, const std::string& label, int base, GuiRadio* other = nullptr);
        virtual ~GuiRadio();
        void setLabel(const std::string& label);
        const std::string& getLabel() const;
        int getBaseValue() const;
        void setValue(int value);
        int getValue() const;
        void resetValue();
        void assignValue(bool value);
        void setButtonSize(float width);
        inline const GuiRadio::Button* getButton() const {
            return widgetbutton;
        }
        inline GuiRadio::Button* getButton(){
            return widgetbutton;
        }
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiRadio::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        GuiRadio::Button* widgetbutton;
        std::string label;
        int basevalue;
        GuiRadio::Value* group;
    };
}
#endif
