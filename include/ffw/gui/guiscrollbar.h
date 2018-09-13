/* This file is part of FineFramework project */
#ifndef FFW_GUI_SCROLLBAR
#define FFW_GUI_SCROLLBAR
#include "guiwidget.h"
#include "guibutton.h"
#include "guislider.h"
namespace ffw {
    /**
    * @ingroup gui
    */
    class FFW_API GuiScrollBar : public GuiWidget {
    public:
        class ButtonLeft: public GuiButton {
        public:
            struct Style {
                GuiButton::Style self;
            };
            ButtonLeft(GuiWindow* context);
            virtual ~ButtonLeft() = default;
            void setStyle(const ButtonLeft::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        };

        class ButtonRight : public GuiButton {
        public:
            struct Style {
                GuiButton::Style self;
            };
            ButtonRight(GuiWindow* context);
            virtual ~ButtonRight() = default;
            void setStyle(const ButtonRight::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        };

        class ButtonTop: public GuiButton {
        public:
            struct Style {
                GuiButton::Style self;
            };
            ButtonTop(GuiWindow* context);
            virtual ~ButtonTop() = default;
            void setStyle(const ButtonTop::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        };

        class ButtonBottom : public GuiButton {
        public:
            struct Style {
                GuiButton::Style self;
            };
            ButtonBottom(GuiWindow* context);
            virtual ~ButtonBottom() = default;
            void setStyle(const ButtonBottom::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        };

        class Scroll : public GuiSlider {
        public:
            struct Style {
                GuiSlider::Style self;
            };
            Scroll(GuiWindow* context, bool vertical);
            virtual ~Scroll() = default;
            void setStyle(const Scroll::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        };

        struct Style {
            GuiScrollBar::ButtonLeft::Style buttonLeft;
            GuiScrollBar::ButtonRight::Style buttonRight;
            GuiScrollBar::ButtonTop::Style buttonTop;
            GuiScrollBar::ButtonBottom::Style buttonBottom;
            GuiScrollBar::Scroll::Style scroll;
            GuiWidget::Style self;
        };

        GuiScrollBar(GuiWindow* context, bool vertical);
        virtual ~GuiScrollBar() = default;
        inline bool isVertical() const {
            return slider->isVertical();
        }
        inline GuiButton* getButtonFirst() {
            return left;
        }
        inline const GuiButton* getButtonFirst() const {
            return left;
        }
        inline GuiButton* getButtonSecond() {
            return right;
        }
        inline const GuiButton* getButtonSecond() const {
            return right;
        }
        inline GuiSlider* getSlider() {
            return slider;
        }
        inline const GuiSlider* getSlider() const {
            return slider;
        }
        inline void setValue(const float val) {
            slider->setValue(val);
        }
        inline float getValue() const {
            return slider->getValue();
        }
        inline const ffw::Pointf& getRange() const {
            return slider->getRange();
        }
        inline void setRange(const float min, const float max) {
            slider->setRange(min, max);
        }
        inline void setInversed(const bool inversed) {
            slider->setInversed(inversed);
        }
        inline bool getInversed() const {
            return slider->getInversed();
        }
        inline void setIncrements(float inc) {
            increments = inc;
        }
        inline float getIncrements() const {
            return increments;
        }
        void setButtonLength(GuiUnits length);
        inline GuiUnits getButtonLength() const {
            if (slider->isVertical())return slider->getButtonSize().y;
            else return slider->getButtonSize().x;
        }
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiScrollBar::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventSize(const ffw::Pointf& size) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        void recalculate(const ffw::Pointf& size);
        void buttonCallback(ffw::GuiEvent e);
        GuiButton* left;
        GuiButton* right;
        Scroll* slider;
        float increments;
    };
}
#endif
