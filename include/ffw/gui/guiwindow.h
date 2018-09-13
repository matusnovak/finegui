/* This file is part of FineFramework project */
#ifndef FFW_GUI_WINDOW
#define FFW_GUI_WINDOW
#include "guibackend.h"
#include "guilayout.h"
#include "guifont.h"
#include "guibody.h"
#include <queue>
#include <functional>
#include <unordered_map>

namespace ffw {
    class GuiBody;
    /**
     * @ingroup gui
     */
    class FFW_API GuiWindow: public GuiBackend {
    public:
        GuiWindow();
        virtual ~GuiWindow();
        void setSize(float width, float height);
        void setPos(float posx, float posy);
        const ffw::Pointf& getSize() const;
        const ffw::Pointf& getPos() const;
        void setDefaultFont(const GuiFont* font);
        const GuiFont* getDefaultFont() const;
        void injectMousePos(float posx, float posy);
        void injectScroll(float posx, float posy);
        void injectMouseButton(ffw::MouseButton button, ffw::MouseMode mode);
        void injectText(unsigned int chr);
        void injectKey(ffw::Key key, ffw::KeyMode mode);
        void update();
        void poolEvents();
        void render();
        void redraw();
        void invalidate();
        GuiBody* getLayout() {
            return body;
        }
        const GuiBody* getLayout() const {
            return body;
        }
        void pushEvent(std::vector<GuiCallback>& callbacks, GuiEvent e);
        void setTheme(const GuiTheme* thm, bool defaults = false);
        const GuiTheme* getTheme() const;
        template<class T>
        T* findByID(unsigned long id){
            return body->findByID<T>(id);
        }
        template<class T>
        T* findByRef(const std::string& ref) {
            auto test = dynamic_cast<T*>(refs.at(ref));
            if (!test) throw std::bad_cast();
            return test;
        }
        void addRef(GuiWidget* widget) {
            refs.insert(std::make_pair(widget->getRef(), widget));
        }
    private:
        GuiBody* body;
        const GuiTheme* theme;
        ffw::Pointf size;
        ffw::Pointf pos;
        GuiUserInput input;
        const GuiFont* defaultfont;
        std::queue<std::pair<std::function<void(GuiEvent)>, GuiEvent>> eventqueue;
        ffw::Pointf mousepos;
        std::unordered_map<std::string, GuiWidget*> refs;
    };
}
#endif
