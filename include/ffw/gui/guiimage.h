/* This file is part of FineFramework project */
#ifndef FFW_GUI_IMAGE
#define FFW_GUI_IMAGE
#include "./config.h"
namespace ffw {
    /**
    * @ingroup gui
    */
    class GuiImage {
    public:
        virtual bool isCreated() const = 0;
        virtual void destroy() = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
    };
}
#endif
