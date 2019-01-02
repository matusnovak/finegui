/* This file is part of FineFramework project */
#ifndef FFW_GUI_TABS
#define FFW_GUI_TABS
#include "guiwidget.h"
#include "guilayout.h"
#include "guibuttontoggle.h"
namespace ffw {
    /**
    * @ingroup gui
    * @brief Create tabs widget
    * @details This widget will create one or more tabs. By clicking
    * on the tab at the top will show appropriate widget(s) assigned.
    * For example it is possible to add a layout under each tab, example
    * code below.
    * @code
    * auto gui = ffw::GuiWindowNanoVG(nvg);
    * auto root = gui.getLayout();
    * 
    * auto tabs = new ffw::GuiTabs(&gui);
    * ffw::GuiVerticalLayout* last = nullptr;
    * for (auto i = 1; i <= 3; i++) {
    *     auto layout = new ffw::GuiVerticalLayout(&gui);
    *     auto button = new ffw::GuiButton(&gui, "Button in Tab #" + std::to_string(i));
    *     layout->addWidget(button);
    *     auto tab = tabs->addTab("Tab #" + std::to_string(i), layout);
    *     tab->setSize(ffw::guiPercent(33.33f), tab->getSize().y);
    *     if (i == 3) last = layout;
    * }
    * tabs->showTabByWidget(last);
    * 
    * root->addWidget(tabs);
    * // Do not free the created widgets! They will be deleted by the gui window!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
    */
    class FFW_API GuiTabs : public GuiWidget {
    public:
        class FFW_API Button : public GuiButtonToggle {
        public:
            struct Style {
                GuiButton::Style self;
            };

            Button(GuiWindow* context, const std::string& label, GuiWidget* targetWidget);
            virtual ~Button() = default;
            void setStyle(const Button::Style* style, bool defaults = false);
            inline GuiWidget* getTargetWidget() const {
                return targetWidget;
            }
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
            GuiWidget* targetWidget;
        };
        class FFW_API TopBar : public GuiLayout {
        public:
            struct Style {
                GuiTabs::Button::Style button;
                GuiLayout::Style self;
            };

            TopBar(GuiWindow* context);
            virtual ~TopBar() = default;
            void setStyle(const TopBar::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        };
        class FFW_API Content : public GuiLayout {
        public:
            struct Style {
                GuiLayout::Style self;
            };

            Content(GuiWindow* context);
            virtual ~Content() = default;
            void setStyle(const Content::Style* style, bool defaults = false);
        private:
            void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        };

        struct Style {
            GuiTabs::TopBar::Style topBar;
            GuiTabs::Content::Style content;
            GuiWidget::Style self;
        };

        GuiTabs(GuiWindow* context);
        virtual ~GuiTabs() = default;
        ffw::Pointf getMinimumWrapSize() override;
        GuiTabs::Button* addTab(GuiTabs::Button* button, GuiWidget* widget);
        GuiTabs::Button* addTab(const std::string& label, GuiWidget* widget);
        void showTabByIndex(size_t index);
        void showTabByWidget(const GuiWidget *widget);
        void setStyle(const GuiTabs::Style* style, bool defaults = false);
    private:
        void widgetEvent(GuiEvent e);
        void hideAllExcept(GuiWidget* widget);
        void addWidgetPair(GuiButtonToggle* button, GuiWidget* widget);
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        GuiTabs::TopBar* bar;
        GuiTabs::Content* content;
    };
}
#endif
