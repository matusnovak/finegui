/* This file is part of FineFramework project */
#ifndef FFW_GUI_LAYOUT
#define FFW_GUI_LAYOUT
#include "guiwidget.h"
namespace ffw {
    /**
     * @ingroup gui
     * @brief Create a linear layout widget
     * @details This widget is able to hold any number of child widgets.
     * The widgets will be displayed in the order inserted via addWidget() 
     * method. Based on the orientation, the widgets will be ordered
     * vertically or horizontally. It is possible to order the widgets with
     * a fixed [X, Y] position by using ffw::GuiOrientation::FIXED and setting
     * position for each inserted child via setPos() method. If the available
     * area is not big enough to contain all widgets, they will be cut off. 
     * However, you can force wrapping the widgets (for example adding 4
     * widgets with width of 50% will create two rows) by calling
     * setWrap(true)
     * @code
     * auto gui = ffw::GuiWindowNanoVG(nvg);
     * auto root = gui.getLayout();
     *     
     * // Create two columns with 47.5% width each and 5% margin between...
     * auto left = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
     * left->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(100.0));
     * left->setMarginRight(ffw::guiPercent(2.5f)); // 2.5% margin on right
     * 
     * auto right = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
     * right->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(100.0));
     * right->setMarginLeft(ffw::guiPercent(2.5f)); // 2.5% margin on left
     * 
     * auto button1 = new ffw::GuiButton(&gui, "I am on the left!");
     * left->addWidget(button1);
     * auto button2 = new ffw::GuiButton(&gui, "I am on the right!");
     * right->addWidget(button2);
     * 
     * root->setOrientation(ffw::GuiOrientation::HORIZONTAL);
     * root->addWidget(left);
     * root->addWidget(right);
     * // Do not free the created widgets! They will be deleted by the gui window!
     * 
     * while(true){
     *     // Render the gui
     * }
     * @endcode
     * @bug Sometimes when layout changes its size by adding new 
     * widgets programatically, it will not properly redraw, and some
     * artifacts may appear. To fix this, simply call redraw() function
     * on the parent widget.
     */
    class FFW_API GuiLayout: public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        GuiLayout(GuiWindow* context, GuiOrientation orientation);
        virtual ~GuiLayout();
        GuiWidget* addWidget(GuiWidget* widget);
        GuiWidget* addWidgetAfter(const GuiWidget* previous, GuiWidget* widget);
        GuiWidget* addWidgetBefore(const GuiWidget* next, GuiWidget* widget);
        void deleteWidgets();
        bool deleteSingleWidget(const GuiWidget* widget);
        void setOrientation(GuiOrientation orient);
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiLayout::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
    };
    /**
     * @ingroup gui
     * @note This is same as creating ffw::GuiLayout with ffw::GuiOrientation::VERTICAL
     * @see ffw::GuiLayout
     */
    class GuiVerticalLayout: public GuiLayout {
    public:
        GuiVerticalLayout(GuiWindow* context):
        GuiLayout(context, GuiOrientation::VERTICAL) {
            
        }
        virtual ~GuiVerticalLayout(){}
    };
    /**
     * @ingroup gui
     * @note This is same as creating ffw::GuiLayout with ffw::GuiOrientation::HORIZONTAL
     * @see ffw::GuiLayout
     */
    class GuiHorizontalLayout: public GuiLayout {
    public:
        GuiHorizontalLayout(GuiWindow* context):
        GuiLayout(context, GuiOrientation::HORIZONTAL) {
            
        }
        virtual ~GuiHorizontalLayout(){}
    };
    /**
     * @ingroup gui
     * @note This is same as creating ffw::GuiLayout with ffw::GuiOrientation::FIXED
     * @see ffw::GuiLayout
     */
    class GuiFixedLayout: public GuiLayout {
    public:
        GuiFixedLayout(GuiWindow* context):
        GuiLayout(context, GuiOrientation::FIXED) {
            
        }
        virtual ~GuiFixedLayout(){}
    };
}
#endif
