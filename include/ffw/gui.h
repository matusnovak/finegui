/**
 * @defgroup gui gui - Graphical User Interface
 * @brief Render engine independent graphic user interface 
 * @details This module allows creation of user interfaces (GUIs). 
 * It takes care of widget layout, automatic spacing when resized, 
 * spacing, callbacks, etc. This module provides several widgets 
 * (buttons, check boxes, text edits, radios, sliders, etc..) however, 
 * has a functionality to add custom widgets as well. All widgets 
 * can be arranged in linear layouts, similarly how HTML works, and can 
 * be also styled. This GUI is not directly linked to the OpenGL, or any 
 * other rendering engine! Instead, it can use any backend with any 
 * renderer you wish to use. However, an OpenGL backend is 
 * provided by default, if the user wishes to use. The entire module is
 * UTF-8 enabled.
 */
#ifndef FFW_GUI_MODULE
#define FFW_GUI_MODULE
#include "gui/guibackend.h"
#include "gui/guibutton.h"
#include "gui/guibox.h"
#include "gui/guibuttontoggle.h"
#include "gui/guicheckbox.h"
#include "gui/guifont.h"
#include "gui/guiimage.h"
#include "gui/guiimageviewer.h"
#include "gui/guilabel.h"
#include "gui/guilayout.h"
#include "gui/guilist.h"
#include "gui/guiprogressbar.h"
#include "gui/guiprogresscircle.h"
#include "gui/guiradio.h"
#include "gui/guitext.h"
#include "gui/guiscrollable.h"
#include "gui/guiscrollbar.h"
#include "gui/guislider.h"
#include "gui/guiswitch.h"
#include "gui/guitab.h"
#include "gui/guitextedit.h"
#include "gui/guiwidget.h"
#include "gui/guiwindow.h"
#include "gui/guitheme.h"
#include "gui/guitextwrapper.h"
#include "gui/guixmlparser.h"
#endif
