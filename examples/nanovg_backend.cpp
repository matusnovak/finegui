#include <iostream>

#include "glad.h"
#include <GLFW/glfw3.h>

#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

#include <ffw/gui.h>
#include <ffw/gui/backend/guibackendnanovg.h>

extern "C" {
    // Uncommenting this causes freetype library not to compile?!
    // Why?!
    void FT_Trace_Disable(void) {

    }

    void FT_Trace_Enable(void) {

    }
}

#define FONS_USE_FREETYPE
#include <nanovg.c>
#include "glad.c"

static ffw::GuiWindow* currentWindow = nullptr;

///=============================================================================
void errorcb(const int error, const char* desc){
    std::cerr << "GLFW error: " << error << ": " << desc << std::endl;
}

///=============================================================================
static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if (currentWindow) {
        currentWindow->injectKey(static_cast<ffw::Key>(key), static_cast<ffw::KeyMode>(action));
    }
}

///=============================================================================
static void textCallback(GLFWwindow * window, unsigned int key) {
    if (currentWindow) {
        currentWindow->injectText(key);
    }
}


///=============================================================================
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (currentWindow) {
        currentWindow->injectMouseButton(static_cast<ffw::MouseButton>(button), static_cast<ffw::MouseMode>(action));
    }
}

///=============================================================================
void render(GLFWwindow* window, NVGcontext* nvg) {
    ffw::Pointi viewport;
    glfwGetWindowSize(window, &viewport.x, &viewport.y);

    // ffw::GuiWindowNanoVG is an instance of ffw::GuiWindow
    // and contains the overrides for the abstract ffw::GuiBackend specific to NanoVG.
    // It will be destroyed once this function ends.
    // This is defined in <ffw/gui/backend/guibackendnanovg.h>
    auto gui = ffw::GuiWindowNanoVG(nvg);
    auto theme = ffw::GuiThemeSimpleLight();
    currentWindow = &gui;

    // Load fonts
    auto fontRegular = ffw::GuiFontNanoVG(nvg, "FreeSans.ttf", 16.0f);
    auto fontBold = ffw::GuiFontNanoVG(nvg, "FreeSansBold.ttf", 16.0f);
    auto fontItalic = ffw::GuiFontNanoVG(nvg, "FreeSansOblique.ttf", 16.0f);

    // Load image
    // 360x240 RGB (8-bit per channel)
    std::unique_ptr<unsigned char[]> pixels(new unsigned char[360 * 240 * 4]);
    std::ifstream input("owl.raw", std::ios::in | std::ios::binary);
    // Checks needs to be done but none are written,
    // just for the purpose of the example
    input.read((char*)pixels.get(), 360 * 240 * 4);

    auto image = ffw::GuiImageNanoVG(nvg, 360, 240, 0, pixels.get());

    gui.setTheme(&theme);
    gui.setPos(0, 0);
    gui.setDefaultFont(&fontRegular);

    try {
        std::ifstream file("all-widgets.xml");
        if (!file) throw std::runtime_error("failed to open xml file");
        const std::string xmlStr (
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        ffw::GuiXmlParser::Registry registry;
        registry.addImage("owl", &image);
        registry.addFont("fontRegular", &fontRegular);
        registry.addFont("fontBold", &fontBold);
        registry.addFont("fontItalic", &fontItalic);

        ffw::GuiXmlParser parser(gui, registry);
        parser.parse(xmlStr);

        // Find widget by reference (fast lookup through map)
        // gui.findByRef<ffw::GuiButton>("my-button"); // thows std::out_of_range or std::bad_cast
    } catch (std::exception& e) {
        std::cerr << "Failed to parse xml document: " << e.what() << std::endl;
    }

    // Set user input callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCharCallback(window, &textCallback);
    
    while (!glfwWindowShouldClose(window)) {
        ffw::Pointd mouse;

        glfwGetCursorPos(window, &mouse.x, &mouse.y);
        glfwGetWindowSize(window, &viewport.x, &viewport.y);

        // Update and render
        glViewport(0, 0, viewport.x, viewport.y);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        if (viewport.x != int(gui.getSize().x) || viewport.y != int(gui.getSize().y)) {
            gui.setSize(float(viewport.x), float(viewport.y));
        }

        gui.injectMousePos(float(mouse.x), float(mouse.y));

        gui.update();
        gui.poolEvents();
        gui.render();

        // Render the framebuffer from the GuiWindow
        nvgBeginFrame(nvg, viewport.x, viewport.y, 1.0f);
        const auto img = nvgImagePattern(nvg, 0, 0, viewport.x, viewport.y, 0, /* ---> */ gui.getFbo()->image, 1.0f);
        nvgBeginPath(nvg);
        nvgRect(nvg, 0.0f, 0.0f, viewport.x, viewport.y);
        nvgFillPaint(nvg, img);
        nvgFill(nvg);
        nvgEndFrame(nvg);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

///=============================================================================
int main(int argc, char *argv[]) {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW." << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(errorcb);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 4);

    auto* window = glfwCreateWindow(600, 700, "FineGui Example with NanoVG", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    //glfwSetKeyCallback(window, key);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    auto* nvg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);

    if (nvg == nullptr) {
        std::cerr << "Failed to initialize NanovVG" << std::endl;
        return EXIT_FAILURE;
    }

    render(window, nvg);

    nvgDeleteGL3(nvg);
    glfwTerminate();
    return 0;
}
