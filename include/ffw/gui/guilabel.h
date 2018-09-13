/* This file is part of FineFramework project */
#ifndef FFW_GUI_LABEL
#define FFW_GUI_LABEL
#include "guiwidget.h"
namespace ffw {
    /**
     * @ingroup gui
     */
    class FFW_API GuiLabel: public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        GuiLabel(GuiWindow* context, const std::string& label);
        virtual ~GuiLabel() = default;
        void setLabel(const std::string& label);
        const std::string& getLabel() const;
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiLabel::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        std::string label;
    };
}
#endif
