#include <iostream>
#include <fstream>
#include <ffw/graphics.h>
#include <ffw/gui.h>
#include <ffw/gui/backend/guibackendfinegraphics.h>

///=============================================================================
class App : public ffw::GLRenderWindow {
public:
    App(const ffw::RenderWindowArgs& args):GLRenderWindow(args, nullptr),
    canvas(ffw::GLCanvas::Settings()),gui(canvas) {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		fontRegular.reset(new ffw::GuiFontFineGraphics(canvas, "FreeSans.ttf", 16.0f));
		fontBold.reset(new ffw::GuiFontFineGraphics(canvas, "FreeSansBold.ttf", 32.0f));
		fontItalic.reset(new ffw::GuiFontFineGraphics(canvas, "FreeSansOblique.ttf", 16.0f));

        gui.setTheme(&theme);
        gui.setPos(0, 0);
        gui.setDefaultFont(fontRegular.get());

		auto root = gui.getLayout();
		root->setWrap(true);

		// Create two columns with 47.5% width each and 5% margin between...
		auto left = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
		left->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(50.0f));
		left->setMarginRight(ffw::guiPercent(2.5f)); // 2.5% margin on right

		auto right = new ffw::GuiLayout(&gui, ffw::GuiOrientation::VERTICAL);
		right->setSize(ffw::guiPercent(47.5f), ffw::guiPercent(50.0f));
		right->setMarginLeft(ffw::guiPercent(2.5f)); // 2.5% margin on left

		auto bottom = new ffw::GuiHorizontalLayout(&gui);
		bottom->setSize(ffw::guiPercent(100.0f), ffw::guiPercent(45.0f));
		bottom->setMarginTop(ffw::guiPercent(5.0f));
		bottom->setAlign(ffw::GuiAlign::CENTER);
		bottom->setWrap(true);

		// Start of left column
		auto label1 = new ffw::GuiLabel(&gui, "Left column 50% width:");
		left->addWidget(label1);

		auto button1 = new ffw::GuiButton(&gui, "I am on the left!");
		button1->addEventCallback([](const ffw::GuiEvent e) {
			const auto btn = dynamic_cast<const ffw::GuiButton*>(e.widget);
			std::cout << "Button with label: " << btn->getLabel() << " clicked!" << std::endl;
		}, ffw::GuiEventType::ACTION);
		left->addWidget(button1);

		auto checkbox1 = new ffw::GuiCheckbox(&gui, "Hello World");
		checkbox1->setValue(true);
		left->addWidget(checkbox1);

		auto radio1 = new ffw::GuiRadio(&gui, "Radio A", 100);
		auto radio2 = new ffw::GuiRadio(&gui, "Radio A", 200, radio1);
		auto radio3 = new ffw::GuiRadio(&gui, "Radio A", 300, radio1);
		radio1->setValue(300);
		left->addWidget(radio1);
		left->addWidget(radio2);
		left->addWidget(radio3);

		// Start of right column
		auto label2 = new ffw::GuiLabel(&gui, "Right column 50% width:");
		right->addWidget(label2);

		auto button2 = new ffw::GuiButton(&gui, "I am on the right!");
		right->addWidget(button2);

		auto input = new ffw::GuiScrollableTextInput(&gui);
		input->setSize(ffw::guiPercent(100.0f), ffw::guiPixels(100.0f));
		input->setValue(
			"Lorem ipsum dolor sit amet, consectetur adipiscing elit"
			"\n"
			"\n"
			"sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
		);
		right->addWidget(input);

		// Start of bottom column
		auto label3 = new ffw::GuiLabel(&gui, "Another column 100% width with align \"CENTER\"");
		label3->setSize(ffw::guiWrap(), ffw::guiWrap());
		bottom->addWidget(label3);

		for (auto i = 0; i < 3; i++) {
			auto button = new ffw::GuiButtonToggle(&gui, "Button #" + std::to_string(i));
			button->setSize(ffw::guiPercent(30.0f), ffw::guiWrap());
			if (i != 2) button->setMarginRight(ffw::guiPercent(5.0f));
			bottom->addWidget(button);
		}

		// Add everything together
		root->setOrientation(ffw::GuiOrientation::HORIZONTAL);
		root->addWidget(left);
		root->addWidget(right);
		root->addWidget(bottom);
    }

    ~App() {
    }

    void render() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto size = getSize();

        if (int(gui.getSize().x) != size.x || int(gui.getSize().y) != size.y) {
            gui.setSize(size.x, size.y);
        }
        
        gui.update();
        gui.poolEvents();
        gui.render();

        canvas.beginFrame(size);
        canvas.beginPath();
        const auto img = canvas.imagePattern(ffw::Vec2f(0.0f, 0.0f), getSize(), 0.0f, gui.getFboTextureImage(), 1.0f);
        canvas.rect(ffw::Vec2f(0.0f, 0.0f), getSize());
        canvas.fillPaint(img);
        canvas.fill();
        canvas.endFrame();
    }

    void textInputEvent(const unsigned int c) override {
        gui.injectText(c);
    }

    void keyPressedEvent(const ffw::Key key, const ffw::KeyMode mode) override {
        gui.injectKey(key, mode);
    }

    void mouseMovedEvent(const int mousex, const int mousey) override {
        gui.injectMousePos(mousex, mousey);
    }

    void mouseScrollEvent(const int scroll) override {
        gui.injectScroll(0, scroll);
    }

    void mouseButtonEvent(const ffw::MouseButton button, const ffw::MouseMode mode) override {
        gui.injectMouseButton(button, mode);
    }

    void windowCloseEvent() override {
        this->shouldClose(true);
    }

private:
    ffw::GLCanvas canvas;
    ffw::GuiWindowFineGraphics gui;
	std::unique_ptr<ffw::GuiFont> fontRegular;
	std::unique_ptr<ffw::GuiFont> fontBold;
	std::unique_ptr<ffw::GuiFont> fontItalic;
    ffw::GuiThemeFlatDark theme;
	ffw::GLTexture2D imageTexture;
	std::unique_ptr<ffw::GuiImage> image;
};

///=============================================================================
int main(int argc, char *argv[]) {

    // set arguments
    ffw::RenderWindowArgs args;
    args.size = ffw::Vec2<int>(400, 400);
    args.title = "FineGui Example";
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
