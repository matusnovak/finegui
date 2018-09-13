/*** This file is part of FineFramework project ***/

#include "ffw/gui/guistyle.h"
#include "ffw/gui/guitheme.h"

#define BORDER_RADIUS 4
#define BORDER_SIZE 1

#define WINDOW_COLOR rgb(0xF5F6F7).inverted()
#define COLOR_WHITE rgb(0xFFFFFF).inverted()
#define COLOR_BLACK rgb(0x000000).inverted()
#define COLOR_TRANSPARENT rgba(0xFFFFFF00)

#define TEXT_COLOR_NORMAL rgb(0x2E2E2E).inverted()
#define TEXT_COLOR_HOVER rgb(0x2E2E2E).inverted()
#define TEXT_COLOR_FOCUS rgb(0x2E2E2E).inverted()
#define TEXT_COLOR_DISABLED rgb(0x989898).inverted()
#define FUNCTION_COLOR_DEFAULT rgb(0xFFFFFF)

#define BACKGROUND_COLOR_NORMAL rgb(0xF4F5F6).inverted()
#define BACKGROUND_COLOR_HOVER rgb(0xDEDFE0).inverted()
#define BACKGROUND_COLOR_FOCUS rgb(0xDEDFE0).inverted()
#define BACKGROUND_COLOR_DISABLED rgb(0xEFF0F1).inverted()

#define BORDER_COLOR_NORMAL rgb(0xB4B5B6).inverted()
#define BORDER_COLOR_HOVER rgb(0xB4B5B6).inverted()
#define BORDER_COLOR_FOCUS rgb(0x3497FD).inverted()
#define BORDER_COLOR_DISABLED rgb(0xC9C9C9).inverted()
#define BORDER_COLOR_BOX rgb(0xDDDEDF).inverted()

#define BORDER_P_COLOR_NORMAL rgb(0xA3B2D9).inverted()
#define BORDER_P_COLOR_HOVER rgb(0xA3B2D9).inverted()
#define BORDER_P_COLOR_FOCUS rgb(0xA3B2D9).inverted()
#define BORDER_P_COLOR_DISABLED rgb(0xB4B5B6).inverted()

#define TEXT_COLOR_P_NORMAL rgb(0xF8FCFB).inverted()
#define TEXT_COLOR_P_HOVER rgb(0xF8FCFB).inverted()
#define TEXT_COLOR_P_FOCUS rgb(0xF8FCFB).inverted()
#define TEXT_COLOR_P_DISABLED rgb(0x989898).inverted()

#define BACKGROUND_P_COLOR_NORMAL rgb(0x2C84DD).inverted()
#define BACKGROUND_P_COLOR_HOVER rgb(0x3497FD).inverted()
#define BACKGROUND_P_COLOR_FOCUS rgb(0x1E5995).inverted()
#define BACKGROUND_P_COLOR_DISABLED rgb(0xEFF0F1).inverted()

#define BACKGROUND_NORMAL GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_NORMAL)
#define BACKGROUND_HOVER GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_HOVER)
#define BACKGROUND_FOCUS GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_FOCUS)
#define BACKGROUND_DISABLED GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_DISABLED)

#define BORDER_NORMAL GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_NORMAL)
#define BORDER_HOVER GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_HOVER)
#define BORDER_FOCUS GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_FOCUS)
#define BORDER_DISABLED GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_DISABLED)
#define BORDER_BOX GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_BOX)

#define BACKGROUND_P_NORMAL GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_NORMAL)
#define BACKGROUND_P_HOVER GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_HOVER)
#define BACKGROUND_P_FOCUS GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_FOCUS)
#define BACKGROUND_P_DISABLED GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_DISABLED)

#define BORDER_P_NORMAL GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_P_COLOR_NORMAL)
#define BORDER_P_HOVER GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_P_COLOR_HOVER)
#define BORDER_P_FOCUS GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_P_COLOR_FOCUS)
#define BORDER_P_DISABLED GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_P_COLOR_DISABLED)

#define NO_BORDER GuiStyle::Border()
#define NO_OUTLINE GuiStyle::Outline()
#define NO_BACKGROUND GuiStyle::Background()
#define NO_STYLE GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT)
#define NO_STYLE_DISABLED GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT)

#define WHITE_PRIMARY_MIX _LERP(BACKGROUND_P_COLOR_HOVER, COLOR_WHITE, 0.5f)

ffw::GuiThemeSimpleDark::GuiThemeSimpleDark() {
    body = GuiBody::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(WINDOW_COLOR), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(WINDOW_COLOR), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(WINDOW_COLOR), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(WINDOW_COLOR), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(10), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiPercent(100)))
    }
    };

    box = GuiBox::Style{
        // Label
        GuiLabel::Style{
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 2, 0), GuiStyle::Padding(0, 0, 0, 5), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    },

        // Layout
        GuiLayout::Style{
        GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, BORDER_BOX, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, BORDER_BOX, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, BORDER_BOX, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, BORDER_BOX, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(5), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    },

        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    button = GuiButton::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, BORDER_DISABLED, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(4), GuiAlign::CENTER, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    buttonPrimary = GuiButtonPrimary::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_P_NORMAL, BORDER_P_NORMAL, NO_OUTLINE, TEXT_COLOR_P_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_P_HOVER, BORDER_P_HOVER, NO_OUTLINE, TEXT_COLOR_P_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_P_FOCUS, BORDER_P_FOCUS, NO_OUTLINE, TEXT_COLOR_P_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_P_DISABLED, BORDER_P_DISABLED, NO_OUTLINE, TEXT_COLOR_P_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(4), GuiAlign::CENTER, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    radio = GuiRadio::Style{
        // Button
        GuiRadio::Button::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(8, COLOR_WHITE), GuiStyle::Border(BORDER_SIZE, 8, BORDER_COLOR_NORMAL), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_WHITE)),
        GuiStyle(GuiStyle::Background(8, WHITE_PRIMARY_MIX), GuiStyle::Border(BORDER_SIZE, 8, BORDER_COLOR_HOVER), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_WHITE)),
        GuiStyle(GuiStyle::Background(8, BACKGROUND_P_COLOR_HOVER), GuiStyle::Border(BORDER_SIZE, 8, BORDER_COLOR_FOCUS), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_WHITE)),
        GuiStyle(GuiStyle::Background(8, BACKGROUND_COLOR_DISABLED), GuiStyle::Border(BORDER_SIZE, 8, BORDER_COLOR_DISABLED), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(BACKGROUND_COLOR_DISABLED)),
        GuiDefaults(GuiStyle::Margin(0, 5, 0, 0), GuiStyle::Padding(guiPercent(30)), GuiAlign::TOP_LEFT, GuiUnits2D(guiPixels(16), guiPixels(16)))
    }
    },
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    checkbox = GuiCheckbox::Style{
        // Button
        GuiCheckbox::Button::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, COLOR_WHITE), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_NORMAL), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_WHITE)),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, WHITE_PRIMARY_MIX), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_HOVER), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_WHITE)),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_HOVER), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_FOCUS), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_WHITE)),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_DISABLED), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_DISABLED), NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(BACKGROUND_COLOR_DISABLED)),
        GuiDefaults(GuiStyle::Margin(0, 5, 0, 0), GuiStyle::Padding(guiPercent(20)), GuiAlign::TOP_LEFT, GuiUnits2D(guiPixels(16), guiPixels(16)))
    }
    },
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    imageViewer = GuiImageViewer::Style{
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    label = GuiLabel::Style{
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    layout = GuiLayout::Style{
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    progressBar = GuiProgressBar::Style{
        // Inner
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_HOVER), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_HOVER), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_P_COLOR_HOVER), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BORDER_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiDefaults()
    },
        // Self
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BORDER_RADIUS, BACKGROUND_COLOR_DISABLED), GuiStyle::Border(BORDER_SIZE, BORDER_RADIUS, BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiPixels(16)))
    }
    };

    progressCircle = GuiProgressCircle::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, GuiStyle::Function(BACKGROUND_P_COLOR_HOVER, BACKGROUND_COLOR_FOCUS)) ,
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, GuiStyle::Function(BACKGROUND_P_COLOR_HOVER, BACKGROUND_COLOR_FOCUS)),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, GuiStyle::Function(BACKGROUND_P_COLOR_HOVER, BACKGROUND_COLOR_FOCUS)),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, GuiStyle::Function(BORDER_COLOR_DISABLED, BACKGROUND_COLOR_FOCUS)),
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::CENTER, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    richText = GuiText::Style{
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    scrollbar = GuiScrollBar::Style{
        // Left button
        GuiScrollBar::ButtonLeft::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 0, 0, 4), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 0, 0, 4), BORDER_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 0, 0, 4), BORDER_COLOR_FOCUS), NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 0, 0, 4), BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(3), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
    }
    },
        // Right button
        GuiScrollBar::ButtonRight::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 4, 4, 0), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 4, 4, 0), BORDER_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 4, 4, 0), BORDER_COLOR_FOCUS), NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 4, 4, 0), BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(3), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
    }
    },
        // Top button
        GuiScrollBar::ButtonTop::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 4, 0, 0), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 4, 0, 0), BORDER_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 4, 0, 0), BORDER_COLOR_FOCUS), NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, GuiStyle::Border(1, GuiStyle::Attribute<float>(4, 4, 0, 0), BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(3), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
    }
    },
        // Bottom button
        GuiScrollBar::ButtonBottom::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 0, 4, 4), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 0, 4, 4), BORDER_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 0, 4, 4), BORDER_COLOR_FOCUS), NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, GuiStyle::Border(1, GuiStyle::Attribute<float>(0, 0, 4, 4), BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(3), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
    }
    },
        // Scroll
        GuiSlider::Style{
        // Button
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(25), guiPixels(12)))
    },
        // Bar
        GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, COLOR_TRANSPARENT),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, COLOR_TRANSPARENT),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, COLOR_TRANSPARENT),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, COLOR_TRANSPARENT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiPercent(100)))
    },
        // Self
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_FOCUS), GuiStyle::Border(1, 0, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_FOCUS), GuiStyle::Border(1, 0, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_FOCUS), GuiStyle::Border(1, 0, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_FOCUS), GuiStyle::Border(1, 0, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(), GuiStyle::Padding(), GuiAlign::TOP_LEFT, GuiUnits2D())
    }
    },
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(1), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    },
    };

    scrollable = GuiScrollable::Style{
        // Vertical scrollbar
        scrollbar,

        // Horizontal scrollbar
        scrollbar,

        // Self
        GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    list = GuiList::Style{
        // item
        GuiList::Item::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(WHITE_PRIMARY_MIX), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(BACKGROUND_P_COLOR_HOVER), NO_BORDER, NO_OUTLINE, COLOR_WHITE, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    },
        // Self
        scrollable
    };

    scrollableLayout = GuiScrollableLayout::Style{
        // Scrollable
        scrollable,

        // Inner
        GuiLayout::Style{
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    }
    };

    slider = GuiSlider::Style{
        // Button
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, BORDER_DISABLED, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPixels(8), guiPixels(16)))
    },
        // Bar
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(2, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, 2, BORDER_COLOR_NORMAL), NO_OUTLINE, COLOR_BLACK, BACKGROUND_P_COLOR_HOVER),
        GuiStyle(GuiStyle::Background(2, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, 2, BORDER_COLOR_NORMAL), NO_OUTLINE, COLOR_BLACK, BACKGROUND_P_COLOR_HOVER),
        GuiStyle(GuiStyle::Background(2, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, 2, BORDER_COLOR_NORMAL), NO_OUTLINE, COLOR_BLACK, BACKGROUND_P_COLOR_HOVER),
        GuiStyle(GuiStyle::Background(2, BACKGROUND_COLOR_DISABLED), GuiStyle::Border(BORDER_SIZE, 2, BORDER_COLOR_DISABLED), NO_OUTLINE, COLOR_BLACK, BACKGROUND_P_COLOR_DISABLED),
        GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiPixels(4)))
    },
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 0, 0), GuiStyle::Padding(2, 4, 2, 4), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    swtch = GuiSwitch::Style{
        // Button
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(8, BORDER_COLOR_NORMAL), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(8, COLOR_WHITE), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(8, COLOR_WHITE), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(8, BORDER_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults()
    },

        // Self
        GuiWidget::Style{
        GuiStyle(GuiStyle::Background(10, BACKGROUND_COLOR_NORMAL), GuiStyle::Border(BORDER_SIZE, 10, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(10, WHITE_PRIMARY_MIX), GuiStyle::Border(BORDER_SIZE, 10, BORDER_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(10, BACKGROUND_P_COLOR_HOVER), GuiStyle::Border(BORDER_SIZE, 10, BORDER_P_COLOR_FOCUS), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(GuiStyle::Background(10, BACKGROUND_COLOR_DISABLED), GuiStyle::Border(BORDER_SIZE, 10, BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::CENTER, GuiUnits2D(guiPixels(42), guiPixels(20)))
    }
    };

    tabs = GuiTabs::Style{
        // Top Bar
        GuiTabs::TopBar::Style{
        GuiTabs::Button::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(BACKGROUND_NORMAL, GuiStyle::Border(GuiStyle::Attribute<float>(BORDER_SIZE, BORDER_SIZE, 0, BORDER_SIZE), GuiStyle::Attribute<float>(BORDER_RADIUS, BORDER_RADIUS, 0, 0), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_HOVER, GuiStyle::Border(GuiStyle::Attribute<float>(BORDER_SIZE, BORDER_SIZE, 0, BORDER_SIZE), GuiStyle::Attribute<float>(BORDER_RADIUS, BORDER_RADIUS, 0, 0), BORDER_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_FOCUS, GuiStyle::Border(GuiStyle::Attribute<float>(BORDER_SIZE, BORDER_SIZE, 0, BORDER_SIZE), GuiStyle::Attribute<float>(BORDER_RADIUS, BORDER_RADIUS, 0, 0), BORDER_COLOR_FOCUS), NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
        GuiStyle(BACKGROUND_DISABLED, GuiStyle::Border(GuiStyle::Attribute<float>(BORDER_SIZE, BORDER_SIZE, 0, BORDER_SIZE), GuiStyle::Attribute<float>(BORDER_RADIUS, BORDER_RADIUS, 0, 0), BORDER_COLOR_DISABLED), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0, 3, 0, 0), GuiStyle::Padding(4), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
    }
    },
        GuiLayout::Style{
        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    }
    },

        // Content
        GuiTabs::Content::Style{
        GuiLayout::Style{
        // Self
        GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(BORDER_SIZE, GuiStyle::Attribute<float>(0, 0, BORDER_RADIUS, BORDER_RADIUS), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(BORDER_SIZE, GuiStyle::Attribute<float>(0, 0, BORDER_RADIUS, BORDER_RADIUS), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(BORDER_SIZE, GuiStyle::Attribute<float>(0, 0, BORDER_RADIUS, BORDER_RADIUS), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiStyle(NO_BACKGROUND, GuiStyle::Border(BORDER_SIZE, GuiStyle::Attribute<float>(0, 0, BORDER_RADIUS, BORDER_RADIUS), BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(5), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    }
    },

        // Self
        GuiWidget::Style{
        NO_STYLE,
        NO_STYLE,
        NO_STYLE,
        NO_STYLE_DISABLED,
        GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    }
    };

    textArea = GuiScrollableTextInput::Style{
        // Scrollable
        GuiScrollable::Style{
            // Vertical scrollbar
            scrollbar,

            // Horizontal scrollbar
            scrollbar,

            // Self
            GuiWidget::Style{
                GuiStyle(GuiStyle::Background(COLOR_WHITE), GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(GuiStyle::Background(COLOR_WHITE), GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(GuiStyle::Background(COLOR_WHITE), GuiStyle::Border(1, 4, BACKGROUND_P_COLOR_HOVER), NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_DISABLED), GuiStyle::Border(1, 4, BORDER_COLOR_NORMAL), NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
            }
        },

        // Text area
        GuiScrollableTextInput::Inner::Style{
            GuiTextInput::Style{
                // Self
                GuiWidget::Style{
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, WHITE_PRIMARY_MIX),
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, WHITE_PRIMARY_MIX),
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, WHITE_PRIMARY_MIX),
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, WHITE_PRIMARY_MIX),
                    GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
                }
            }
        }
    };

    textInput = GuiTextInput::Style{
        // Self
        GuiWidget::Style{
            GuiStyle(GuiStyle::Background(COLOR_WHITE), BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, WHITE_PRIMARY_MIX),
            GuiStyle(GuiStyle::Background(COLOR_WHITE), BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_HOVER, WHITE_PRIMARY_MIX),
            GuiStyle(GuiStyle::Background(COLOR_WHITE), BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_FOCUS, WHITE_PRIMARY_MIX),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_DISABLED), BORDER_DISABLED, NO_OUTLINE, TEXT_COLOR_DISABLED, WHITE_PRIMARY_MIX),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(4), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };

    dummy = GuiDummy::Style{
        // Self
        GuiWidget::Style{
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, BACKGROUND_COLOR_HOVER),
            GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };
}

ffw::GuiThemeSimpleDark ffw::GuiThemeSimpleDark::singleton;
