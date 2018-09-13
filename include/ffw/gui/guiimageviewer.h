/* This file is part of FineFramework project */
#ifndef FFW_GUI_IMAGE_VIEWER
#define FFW_GUI_IMAGE_VIEWER
#include "guiwidget.h"
#include "rect.h"

namespace ffw {
    class GuiImage;

    /**
    * @ingroup gui
    */
    class FFW_API GuiImageViewer : public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        GuiImageViewer(GuiWindow* context, const GuiImage* image);
        virtual ~GuiImageViewer() = default;
        void setImage(const GuiImage* image);
        void setSubsection(int posx, int posy, int width, int height);
        void setMirror(bool mirrorX, bool mirrorY);
        inline const GuiImage* getImage() const {
            return img;
        }
        inline const Recti getSubsection() const {
            return sub;
        }
        inline const Point<bool> getMirror() const {
            return mirror;
        }
        void setLabel(const std::string& label);
        const std::string& getLabel() const;
        ffw::Pointf getMinimumWrapSize() override;
        void setStyle(const GuiImageViewer::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventHover(bool gained) override;
        void eventFocus(bool gained) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        const GuiImage* img;
        ffw::Recti sub;
        Point<bool> mirror;
        std::string label;
    };
}
#endif
