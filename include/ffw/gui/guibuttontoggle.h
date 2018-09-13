/* This file is part of FineFramework project */
#ifndef FFW_GUI_BUTTON_TOGGLE
#define FFW_GUI_BUTTON_TOGGLE
#include "guibutton.h"
namespace ffw {
    /**
    * @ingroup gui
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
