/* This file is part of FineFramework project */
#ifndef FFW_GUI_RADIO
#define FFW_GUI_RADIO
#include "guilabel.h"

namespace ffw {
    /**
     * @ingroup gui
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
