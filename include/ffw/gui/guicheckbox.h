/* This file is part of FineFramework project */
#ifndef FFW_GUI_CHECKBOX
#define FFW_GUI_CHECKBOX
#include "guilabel.h"
namespace ffw {
    /**
     * @ingroup gui
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
