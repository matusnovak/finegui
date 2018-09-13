/* This file is part of FineFramework project */
#ifndef FFW_GUI_SWITCH
#define FFW_GUI_SWITCH
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
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
