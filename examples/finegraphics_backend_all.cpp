#include <iostream>
#include <fstream>
#include <ffw/graphics.h>
#include <ffw/gui.h>
#include <ffw/gui/backend/guibackendfinegraphics.h>

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args):GLRenderWindow(args, nullptr) {
        // Create canvas using a GLCanvas::Settings. The canvas will hold the states
        // such as current color, transforms, etc...
        canvas = ffw::GLCanvas(ffw::GLCanvas::Settings());

        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Load fonts
        fontRegular.reset(new ffw::GuiFontFineGraphics(canvas, "FreeSans.ttf", 16.0f));
        fontBold.reset(new ffw::GuiFontFineGraphics(canvas, "FreeSansBold.ttf", 16.0f));
        fontItalic.reset(new ffw::GuiFontFineGraphics(canvas, "FreeSansOblique.ttf", 16.0f));

        // Load image
        // 360x240 RGB (8-bit per channel)
        std::unique_ptr<unsigned char[]> pixels(new unsigned char[360 * 240 * 4]);
        std::ifstream input("owl.raw", std::ios::in | std::ios::binary);
        // Checks needs to be done but none are written,
        // just for the purpose of the example
        input.read((char*)pixels.get(), 360 * 240 * 4);
        imageTexture = ffw::GLTexture2D(360, 240, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
        image.reset(new ffw::GuiImageFineGraphics(canvas, imageTexture));

        gui.reset(new ffw::GuiWindowFineGraphics(canvas));

        gui->setTheme(&theme);
        gui->setPos(0, 0);
        gui->setDefaultFont(fontRegular.get());

        std::ifstream file("all-widgets.xml");
        if (!file) throw std::runtime_error("failed to open xml file");
        const std::string xmlStr(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        ffw::GuiXmlParser::Registry registry;
        registry.addImage("owl", image.get());
        registry.addFont("fontRegular", fontRegular.get());
        registry.addFont("fontBold", fontBold.get());
        registry.addFont("fontItalic", fontItalic.get());

        ffw::GuiXmlParser parser(*gui, registry);
        parser.parse(xmlStr);

        // Find widget by reference (fast lookup through map)
        // gui->findByRef<ffw::GuiButton>("my-button"); // thows std::out_of_range or std::bad_cast
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto size = getSize();

        if (int(gui->getSize().x) != size.x || int(gui->getSize().y) != size.y) {
            gui->setSize(size.x, size.y);
        }
        
        gui->update();
        gui->poolEvents();
        gui->render();

        canvas.beginFrame(size);
        canvas.beginPath();
        const auto img = canvas.imagePattern(ffw::Vec2f(0.0f, 0.0f), getSize(), 0.0f, gui->getFboTextureImage(), 1.0f);
        canvas.rect(ffw::Vec2f(0.0f, 0.0f), getSize());
        canvas.fillPaint(img);
        canvas.fill();
        canvas.endFrame();
    }

    void textInputEvent(const unsigned int c) override {
        gui->injectText(c);
    }

    void keyPressedEvent(const ffw::Key key, const ffw::KeyMode mode) override {
        gui->injectKey(key, mode);
    }

    void mouseMovedEvent(const int mousex, const int mousey) override {
        gui->injectMousePos(mousex, mousey);
    }

    void mouseScrollEvent(const int scroll) override {
        gui->injectScroll(0, scroll);
    }

    void mouseButtonEvent(const ffw::MouseButton button, const ffw::MouseMode mode) override {
        gui->injectMouseButton(button, mode);
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
    }

private:
    ffw::GLCanvas canvas;
    ffw::Vec2f mousePos;
    std::unique_ptr<ffw::GuiWindowFineGraphics> gui;
    std::unique_ptr<ffw::GuiFont> fontRegular;
    std::unique_ptr<ffw::GuiFont> fontBold;
    std::unique_ptr<ffw::GuiFont> fontItalic;
    ffw::GLTexture2D imageTexture;
    std::unique_ptr<ffw::GuiImage> image;
    ffw::GuiThemeSimpleLight theme;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(600, 700);
    args.title = "FineGui Example with FineGraphics";
    args.samples = 4;

    // Instance to our app class
    try {
        App app(args);

        // The main window loop
        while (app.shouldRender()) {
            app.renderFrame();
            app.poolEvents();
        }

        return EXIT_SUCCESS;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
