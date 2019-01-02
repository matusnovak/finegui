/* This file is part of FineFramework project */
#ifndef FFW_GUI_IMAGE_VIEWER
#define FFW_GUI_IMAGE_VIEWER
#include "guiwidget.h"
#include "rect.h"

namespace ffw {
    class GuiImage;

    /**
    * @ingroup gui
    * @brief Create an image widget with optional label
    * @code
    * auto gui = ffw::GuiWindowNanoVG(nvg); 
    * auto root = gui.getLayout();
    * 
    * // Load pixels
    * std::unique_ptr<unsigned char[]> pixels(new unsigned char[360 * 240 * 4]);
    * std::ifstream input("owl.raw", std::ios::in | std::ios::binary);
    * input.read((char*)pixels.get(), 360 * 240 * 4);
    * 
    * // Create image
    * // Make sure the image is alive while the window is being rendered!
    * // Depending on your backend implementation, you can free the pixels
    * // after creating the image! When using NanoVG or FineGraphics
    * // the pixels are copied into the GPU memory.
    * auto image = ffw::GuiImageNanoVG(nvg, 360, 240, 0, pixels.get());
    * pixels.reset();
    * 
    * auto viewer = new ffw::GuiImageViewer(&gui, &image);
    * viewer->setSize(ffw::guiPercent(50.0f), ffw::guiWrap());
    * viewer->setLabel("Hello World!");
    * viewer->setAlign(ffw::GuiAlign::TOP_LEFT);
    * 
    * root->addWidget(label);
    * // Do not free the created widgets! They will be deleted by the gui window!
    * 
    * while(true){
    *     // Render the gui
    * }
    * @endcode
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
