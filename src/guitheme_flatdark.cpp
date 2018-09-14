/*** This file is part of FineFramework project ***/

#include "ffw/gui/guistyle.h"
#include "ffw/gui/guitheme.h"

#define BORDER_RADIUS 0
#define BORDER_SIZE 1

#define WINDOW_COLOR rgb(0x28292E)
#define COLOR_WHITE rgb(0xFFFFFF)
#define COLOR_BLACK rgb(0x000000)
#define COLOR_TRANSPARENT rgba(0xFFFFFF00)

#define TEXT_COLOR_NORMAL rgb(0xC8C8C8)
#define TEXT_COLOR_HOVER rgb(0xC8C8C8)
#define TEXT_COLOR_FOCUS rgb(0x42424A)
#define TEXT_COLOR_DISABLED rgb(0x797979)
#define FUNCTION_COLOR_DEFAULT rgb(0xFFFFFF)

#define BACKGROUND_COLOR_NORMAL rgb(0x42424A)
#define BACKGROUND_COLOR_HOVER rgb(0x585860)
#define BACKGROUND_COLOR_FOCUS rgb(0xD2D2D2)
#define BACKGROUND_COLOR_DISABLED rgb(0x32323A)

#define BORDER_COLOR_NORMAL rgb(0x484850)
#define BORDER_COLOR_HOVER rgb(0x484850)
#define BORDER_COLOR_FOCUS rgb(0xD2D2D2)
#define BORDER_COLOR_DISABLED rgb(0x484850)
#define BORDER_COLOR_BOX rgb(0x18191E)

#define BORDER_P_COLOR_NORMAL rgb(0xA3B2D9)
#define BORDER_P_COLOR_HOVER rgb(0xA3B2D9)
#define BORDER_P_COLOR_FOCUS rgb(0xA3B2D9)
#define BORDER_P_COLOR_DISABLED rgb(0xB4B5B6)

#define TEXT_COLOR_P_NORMAL rgb(0x42424A)
#define TEXT_COLOR_P_HOVER rgb(0x42424A)
#define TEXT_COLOR_P_FOCUS rgb(0xECECEC)
#define TEXT_COLOR_P_DISABLED rgb(0x797979)

#define BACKGROUND_P_COLOR_NORMAL rgb(0xE4B115)
#define BACKGROUND_P_COLOR_HOVER rgb(0xF5C022)
#define BACKGROUND_P_COLOR_FOCUS rgb(0xA57E08)
#define BACKGROUND_P_COLOR_DISABLED rgb(0x32323A)

#define ACTIVITY_COLOR rgb(0xD2D2D2)

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

#define WHITE_PRIMARY_MIX ffw::lerp(BACKGROUND_P_COLOR_HOVER, COLOR_WHITE, 0.5f)

ffw::GuiThemeFlatDark::GuiThemeFlatDark() {
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
            GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(4), GuiAlign::CENTER, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };

    buttonPrimary = GuiButtonPrimary::Style{
        // Self
        GuiWidget::Style{
            GuiStyle(BACKGROUND_P_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_P_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_P_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_P_HOVER, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_P_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_P_FOCUS, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_P_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_P_DISABLED, FUNCTION_COLOR_DEFAULT),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(4), GuiAlign::CENTER, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };

    radio = GuiRadio::Style{
        // Button
        GuiRadio::Button::Style{
        // Self
        GuiWidget::Style{
            GuiStyle(GuiStyle::Background(8, BACKGROUND_COLOR_NORMAL), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), COLOR_TRANSPARENT),
            GuiStyle(GuiStyle::Background(8, BACKGROUND_COLOR_NORMAL), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), TEXT_COLOR_HOVER),
            GuiStyle(GuiStyle::Background(8, BACKGROUND_COLOR_HOVER), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), BACKGROUND_COLOR_FOCUS),
            GuiStyle(GuiStyle::Background(8, BACKGROUND_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), COLOR_TRANSPARENT),
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
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_NORMAL), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_TRANSPARENT)),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_NORMAL), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(TEXT_COLOR_HOVER)),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_HOVER), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(BACKGROUND_COLOR_FOCUS)),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, GuiStyle::Text(COLOR_BLACK), GuiStyle::Function(COLOR_TRANSPARENT)),
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
            GuiStyle(BACKGROUND_P_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_P_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_P_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_P_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiDefaults()
        },
        // Self
        GuiWidget::Style{
            GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiPixels(16)))
        }
    };

    progressCircle = GuiProgressCircle::Style{
        // Self
        GuiWidget::Style{
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, GuiStyle::Function(BACKGROUND_P_COLOR_HOVER, BACKGROUND_COLOR_NORMAL)) ,
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, GuiStyle::Function(BACKGROUND_P_COLOR_HOVER, BACKGROUND_COLOR_NORMAL)),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, GuiStyle::Function(BACKGROUND_P_COLOR_HOVER, BACKGROUND_COLOR_NORMAL)),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, GuiStyle::Function(BACKGROUND_COLOR_HOVER, BACKGROUND_COLOR_NORMAL)),
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
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
            }
        },
        // Right button
        GuiScrollBar::ButtonRight::Style{
            // Self
            GuiWidget::Style{
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
            }
        },
        // Top button
        GuiScrollBar::ButtonTop::Style{
            // Self
            GuiWidget::Style{
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
            }
        },
        // Bottom button
        GuiScrollBar::ButtonBottom::Style{
            // Self
            GuiWidget::Style{
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::CENTER, GuiUnits2D(guiWrap(), guiWrap()))
            }
        },
        // Scroll
        GuiSlider::Style{
            // Button
            GuiWidget::Style{
                GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
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
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
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
            GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };

    list = GuiList::Style{
        // item
        GuiList::Item::Style{
            // Self
            GuiWidget::Style{
                GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_COLOR_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(BACKGROUND_COLOR_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
            }
        },
        // Self
        GuiScrollable::Style{
            // Vertical scrollbar
            scrollbar,

            // Horizontal scrollbar
            scrollbar,

            // Self
            GuiWidget::Style{
                GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, BORDER_DISABLED, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
            }
        }
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
                GuiDefaults(0, 2, GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
            }
        }
    };

    slider = GuiSlider::Style{
        // Button
        GuiWidget::Style{
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE_DISABLED,
            GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPixels(8), guiPixels(16)))
        },
        // Bar
        GuiWidget::Style{
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, COLOR_BLACK, ACTIVITY_COLOR),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, COLOR_BLACK, ACTIVITY_COLOR),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, COLOR_BLACK, ACTIVITY_COLOR),
            GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, COLOR_BLACK, ACTIVITY_COLOR),
            GuiDefaults(0, 0, GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiPercent(100)))
        },
        // Self
        GuiWidget::Style{
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_NORMAL), NO_BORDER, NO_OUTLINE, COLOR_BLACK, FUNCTION_COLOR_DEFAULT),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_HOVER), NO_BORDER, NO_OUTLINE, COLOR_BLACK, FUNCTION_COLOR_DEFAULT),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_HOVER), NO_BORDER, NO_OUTLINE, COLOR_BLACK, FUNCTION_COLOR_DEFAULT),
            GuiStyle(GuiStyle::Background(BACKGROUND_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, COLOR_BLACK, FUNCTION_COLOR_DEFAULT),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };

    swtch = GuiSwitch::Style{
        // Button
        GuiWidget::Style{
            GuiStyle(GuiStyle::Background(TEXT_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(GuiStyle::Background(TEXT_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(GuiStyle::Background(TEXT_COLOR_FOCUS), NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(GuiStyle::Background(TEXT_COLOR_DISABLED), NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
            GuiDefaults()
        },

        // Self
        GuiWidget::Style{
            GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
            GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::CENTER, GuiUnits2D(guiPixels(32), guiPixels(16)))
        }
    };

    tabs = GuiTabs::Style{
        // Top Bar
        GuiTabs::TopBar::Style{
            GuiTabs::Button::Style{
                // Self
                GuiWidget::Style{
                    GuiStyle(BACKGROUND_NORMAL, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                    GuiStyle(BACKGROUND_HOVER, NO_BORDER, NO_OUTLINE, TEXT_COLOR_HOVER, FUNCTION_COLOR_DEFAULT),
                    GuiStyle(BACKGROUND_FOCUS, NO_BORDER, NO_OUTLINE, TEXT_COLOR_FOCUS, FUNCTION_COLOR_DEFAULT),
                    GuiStyle(BACKGROUND_DISABLED, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
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
                GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_NORMAL, FUNCTION_COLOR_DEFAULT),
                GuiStyle(NO_BACKGROUND, BORDER_DISABLED, NO_OUTLINE, TEXT_COLOR_DISABLED, FUNCTION_COLOR_DEFAULT),
                GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
            }
        },

        // Text area
        GuiScrollableTextInput::Inner::Style{
            GuiTextInput::Style{
                // Self
                GuiWidget::Style{
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
                    GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, BACKGROUND_COLOR_HOVER),
                    GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(2), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
                }
            }
        }
    };

    textInput = GuiTextInput::Style{
        // Self
        GuiWidget::Style{
            GuiStyle(NO_BACKGROUND, BORDER_NORMAL, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
            GuiStyle(NO_BACKGROUND, BORDER_HOVER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
            GuiStyle(NO_BACKGROUND, BORDER_FOCUS, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
            GuiStyle(NO_BACKGROUND, BORDER_DISABLED, NO_OUTLINE, TEXT_COLOR_DISABLED, BACKGROUND_COLOR_HOVER),
            GuiDefaults(GuiStyle::Margin(0, 0, 5, 0), GuiStyle::Padding(4), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
        }
    };

    dummy = GuiWidget::Style{
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_NORMAL, BACKGROUND_COLOR_HOVER),
        GuiStyle(NO_BACKGROUND, NO_BORDER, NO_OUTLINE, TEXT_COLOR_DISABLED, BACKGROUND_COLOR_HOVER),
        GuiDefaults(GuiStyle::Margin(0), GuiStyle::Padding(0), GuiAlign::TOP_LEFT, GuiUnits2D(guiPercent(100), guiWrap()))
    };
}

ffw::GuiThemeFlatDark ffw::GuiThemeFlatDark::singleton;
