/* This file is part of FineFramework project */
#ifndef FFW_GUI_DUMMY
#define FFW_GUI_DUMMY
#include "guiwidget.h"
namespace ffw {
    /**
    * @ingroup gui
    */
    class FFW_API GuiDummy : public GuiWidget {
    public: 
        GuiDummy(GuiWindow* context);
        virtual ~GuiDummy() = default;
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiWidget::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
    };
}
#endif
