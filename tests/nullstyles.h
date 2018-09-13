#include <ffw/gui.h>

class GuiThemeDummy: public ffw::GuiTheme {
public:
    GuiThemeDummy();
};

#define NO_STYLE ffw::GuiStyle(ffw::GuiStyle::Background(), ffw::GuiStyle::Border(), ffw::GuiStyle::Outline(), ffw::GuiStyle::Text(), ffw::GuiStyle::Function())
#define NO_PADDING ffw::GuiStyle::Padding()
#define NO_MARGIN ffw::GuiStyle::Margin()

GuiThemeDummy::GuiThemeDummy() {
    body = ffw::GuiBody::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiPercent(100)))
        }
    };

    box = ffw::GuiBox::Style {
        // Label
        ffw::GuiLabel::Style {
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
            }
        },

        // Layout
        ffw::GuiLayout::Style {
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
            }
        },

        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    button = ffw::GuiButton::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    buttonPrimary = ffw::GuiButtonPrimary::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    radio = ffw::GuiRadio::Style {
        // Button
        ffw::GuiRadio::Button::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, ffw::GuiStyle::Padding(ffw::guiPercent(30)), ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPixels(16), ffw::guiPixels(16)))
            }
        },
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    checkbox = ffw::GuiCheckbox::Style {
        // Button
        ffw::GuiCheckbox::Button::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, ffw::GuiStyle::Padding(ffw::guiPercent(20)), ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPixels(16), ffw::guiPixels(16)))
            }
        },
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    imageViewer = ffw::GuiImageViewer::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    label = ffw::GuiLabel::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    layout = ffw::GuiLayout::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    progressBar = ffw::GuiProgressBar::Style {
        // Inner
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults()
        },
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiPixels(16)))
        }
    };

    progressCircle = ffw::GuiProgressCircle::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE ,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    richText = ffw::GuiText::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    scrollbar = ffw::GuiScrollBar::Style {
        // Left button
        ffw::GuiScrollBar::ButtonLeft::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiWrap(), ffw::guiWrap()))
            }
        },
        // Right button
        ffw::GuiScrollBar::ButtonRight::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiWrap(), ffw::guiWrap()))
            }
        },
        // Top button
        ffw::GuiScrollBar::ButtonTop::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiWrap(), ffw::guiWrap()))
            }
        },
        // Bottom button
        ffw::GuiScrollBar::ButtonBottom::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiWrap(), ffw::guiWrap()))
            }
        },
        // Scroll
        ffw::GuiSlider::Style {
            // Button
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(25), ffw::guiPixels(12)))
            },
            // Bar
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiPercent(100)))
            },
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(ffw::GuiStyle::Margin(), NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D())
            }
        },
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        },
    };

    scrollable = ffw::GuiScrollable::Style {
        // Vertical scrollbar
        scrollbar,

        // Horizontal scrollbar
        scrollbar,

        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    list = ffw::GuiList::Style {
        // item
        ffw::GuiList::Item::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
            }
        },
        // Self
        scrollable
    };

    scrollableLayout = ffw::GuiScrollableLayout::Style {
        // Scrollable
        scrollable,

        // Inner
        ffw::GuiLayout::Style {
            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
            }
        }
    };

    slider = ffw::GuiSlider::Style {
        // Button
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPixels(8), ffw::guiPixels(16)))
        },
        // Bar
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiPixels(4)))
        },
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    swtch = ffw::GuiSwitch::Style {
        // Button
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults()
        },

        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiPixels(32), ffw::guiPixels(16)))
        }
    };

    tabs = ffw::GuiTabs::Style {
        // Top Bar
        ffw::GuiTabs::TopBar::Style {
            ffw::GuiTabs::Button::Style {
                // Self
                ffw::GuiWidget::Style {
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::CENTER, ffw::GuiUnits2D(ffw::guiWrap(), ffw::guiWrap()))
                }
            },
            ffw::GuiLayout::Style {
                // Self
                ffw::GuiWidget::Style {
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
                }
            }
        },

        // Content
        ffw::GuiTabs::Content::Style {
            ffw::GuiLayout::Style {
                // Self
                ffw::GuiWidget::Style {
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
                }
            }
        },

        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };

    textArea = ffw::GuiScrollableTextInput::Style {
        // Scrollable
        ffw::GuiScrollable::Style {
            // Vertical scrollbar
            scrollbar,

            // Horizontal scrollbar
            scrollbar,

            // Self
            ffw::GuiWidget::Style {
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                NO_STYLE,
                ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
            }
        },

        // Text area
        ffw::GuiScrollableTextInput::Inner::Style {
            ffw::GuiTextInput::Style {
                // Self
                ffw::GuiWidget::Style {
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    NO_STYLE,
                    ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
                }
            }
        }
    };

    textInput = ffw::GuiTextInput::Style {
        // Self
        ffw::GuiWidget::Style {
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            NO_STYLE,
            ffw::GuiDefaults(NO_MARGIN, NO_PADDING, ffw::GuiAlign::TOP_LEFT, ffw::GuiUnits2D(ffw::guiPercent(100), ffw::guiWrap()))
        }
    };
}

GuiThemeDummy nullTheme;
