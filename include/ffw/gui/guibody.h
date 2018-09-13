/* This file is part of FineFramework project */
#ifndef FFW_GUI_BODY
#define FFW_GUI_BODY
#include "guilayout.h"

namespace ffw {
    /**
     * @ingroup gui
     */
    class FFW_API GuiBody: public GuiLayout {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        GuiBody(GuiWindow* context, GuiOrientation orient);
        virtual ~GuiBody() = default;
        void setStyle(const GuiBody::Style* style, bool defaults = false);
    private:
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
    };
}

#endif