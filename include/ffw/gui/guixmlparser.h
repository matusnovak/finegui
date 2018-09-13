/* This file is part of FineFramework project */
#ifndef FFW_GUI_XML_PARSER
#define FFW_GUI_XML_PARSER

#include <string>
#include <exception>
#include <unordered_map>
#include "./config.h"
#include "guistyle.h"
#include "guiwidget.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace tinyxml2 {
    class XMLElement;
}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace ffw {
    class GuiLayout;
    class GuiWidget;
    class GuiWindow;
    class GuiImage;

    class GuiXmlException: public std::runtime_error {
    public:
        GuiXmlException(const std::string& msg):std::runtime_error(msg) {
            
        }
    };

    class GuiXmlNotFound : public GuiXmlException {
    public:
        GuiXmlNotFound(const std::string& msg) :GuiXmlException(msg) {

        }
    };

    class FFW_API GuiXmlParser {
    public:
        class Token {
        public:
            Token() = default;
            virtual ~Token() = default;

            virtual bool hasAttribute(const char* key) const = 0;
            virtual std::string getAttributeString(const char* key) const = 0;
            virtual int getAttributeInt(const char* key) const = 0;
            virtual float getAttributeFloat(const char* key) const = 0;
            virtual std::string getContent() const = 0;

            GuiUnits getAttributeUnits(const char* key) const;
            float getAttributePixels(const char* key) const;
            GuiUnits2D getAttributeUnits2D(const char* keyW, const char* keyH) const;
            GuiStyle::Attribute<GuiUnits> getAttributeUnitsAttribute(const char* key) const;
            GuiAlign getAttributeAlign(const char* key) const;
            GuiOrientation getAttributeOrientation(const char* key) const;
            bool getAttributeBool(const char* key) const;
        };

        class Registry {
        public:
            Registry() = default;
            virtual ~Registry() = default;

            virtual const GuiImage* getImage(const std::string& key) const {
                auto it = images.find(key);
                if (it == images.end()) throw GuiXmlNotFound("image id: \"" + key + "\" not found");
                return it->second;
            }
            virtual const GuiFont* getFont(const std::string& key) const {
                auto it = fonts.find(key);
                if (it == fonts.end()) throw GuiXmlNotFound("font id: \"" + key + "\" not found");
                return it->second;
            }
            void addImage(const std::string& key, const GuiImage* image) {
                images.insert(std::make_pair(key, image));
            }
            void addFont(const std::string& key, const GuiFont* font) {
                fonts.insert(std::make_pair(key, font));
            }
        private:
            std::unordered_map<std::string, const GuiImage*> images;
            std::unordered_map<std::string, const GuiFont*> fonts;
        };

        class XmlToken; // Public Token

        class Visitor {
        public:
            Visitor(const std::string& key):key(key) {
                
            }
            virtual ~Visitor() = default;

            virtual void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const;
            virtual GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const = 0;

            inline const std::string& getKey() const {
                return key;
            }
        private:
            std::string key;
        };

        class VisitorGuiWidget: public Visitor {
        public:
            VisitorGuiWidget(const std::string& key):Visitor(key) {
            }
            virtual ~VisitorGuiWidget() = default;

            void defaults(const Token& token, GuiWidget* instance, const Registry* registry, bool padding = true, bool margin = true) const;
        };

        class VisitorGuiButton : public VisitorGuiWidget {
        public:
            VisitorGuiButton():VisitorGuiWidget("button") {
            }
            virtual ~VisitorGuiButton() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiButtonToggle : public VisitorGuiWidget {
        public:
            VisitorGuiButtonToggle() :VisitorGuiWidget("button-toggle") {
            }
            virtual ~VisitorGuiButtonToggle() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiButtonPrimary : public VisitorGuiWidget {
        public:
            VisitorGuiButtonPrimary() :VisitorGuiWidget("button-primary") {
            }
            virtual ~VisitorGuiButtonPrimary() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiBox : public VisitorGuiWidget {
        public:
            VisitorGuiBox():VisitorGuiWidget("box") {
            }
            virtual ~VisitorGuiBox() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiLayout : public VisitorGuiWidget {
        public:
            VisitorGuiLayout() :VisitorGuiWidget("layout") {
            }
            virtual ~VisitorGuiLayout() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiVerticalLayout : public VisitorGuiWidget {
        public:
            VisitorGuiVerticalLayout() :VisitorGuiWidget("vertial-layout") {
            }
            virtual ~VisitorGuiVerticalLayout() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiHorizontalLayout : public VisitorGuiWidget {
        public:
            VisitorGuiHorizontalLayout() :VisitorGuiWidget("horizontal-layout") {
            }
            virtual ~VisitorGuiHorizontalLayout() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiScrollableLayout : public VisitorGuiWidget {
        public:
            VisitorGuiScrollableLayout() :VisitorGuiWidget("scrollable-layout") {
            }
            virtual ~VisitorGuiScrollableLayout() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiLabel : public VisitorGuiWidget {
        public:
            VisitorGuiLabel() :VisitorGuiWidget("label") {
            }
            virtual ~VisitorGuiLabel() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiRadio: public VisitorGuiWidget {
        public:
            VisitorGuiRadio() :VisitorGuiWidget("radio") {
            }
            virtual ~VisitorGuiRadio() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiCheckbox : public VisitorGuiWidget {
        public:
            VisitorGuiCheckbox() :VisitorGuiWidget("checkbox") {
            }
            virtual ~VisitorGuiCheckbox() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiSlider : public VisitorGuiWidget {
        public:
            VisitorGuiSlider() :VisitorGuiWidget("slider") {
            }
            virtual ~VisitorGuiSlider() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiScrollBar : public VisitorGuiWidget {
        public:
            VisitorGuiScrollBar() :VisitorGuiWidget("scrollbar") {
            }
            virtual ~VisitorGuiScrollBar() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiImageViewer : public VisitorGuiWidget {
        public:
            VisitorGuiImageViewer() :VisitorGuiWidget("image-viewer") {
            }
            virtual ~VisitorGuiImageViewer() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiTextInput : public VisitorGuiWidget {
        public:
            VisitorGuiTextInput() :VisitorGuiWidget("text-input") {
            }
            virtual ~VisitorGuiTextInput() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiScrollableTextInput : public VisitorGuiWidget {
        public:
            VisitorGuiScrollableTextInput() :VisitorGuiWidget("text-area") {
            }
            virtual ~VisitorGuiScrollableTextInput() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiWindow : public Visitor {
        public:
            VisitorGuiWindow() :Visitor("window") {
            }
            virtual ~VisitorGuiWindow() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiList : public VisitorGuiWidget {
        public:
            VisitorGuiList() :VisitorGuiWidget("list") {
            }
            virtual ~VisitorGuiList() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiListItem : public VisitorGuiWidget {
        public:
            VisitorGuiListItem() :VisitorGuiWidget("list-item") {
            }
            virtual ~VisitorGuiListItem() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiSwitch : public VisitorGuiWidget {
        public:
            VisitorGuiSwitch() :VisitorGuiWidget("switch") {
            }
            virtual ~VisitorGuiSwitch() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiProgressBar : public VisitorGuiWidget {
        public:
            VisitorGuiProgressBar() :VisitorGuiWidget("progress-bar") {
            }
            virtual ~VisitorGuiProgressBar() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiProgressCircle : public VisitorGuiWidget {
        public:
            VisitorGuiProgressCircle() :VisitorGuiWidget("progress-circle") {
            }
            virtual ~VisitorGuiProgressCircle() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiTabs : public VisitorGuiWidget {
        public:
            VisitorGuiTabs() :VisitorGuiWidget("tabs") {
            }
            virtual ~VisitorGuiTabs() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiTabLayout : public VisitorGuiWidget {
        public:
            VisitorGuiTabLayout() :VisitorGuiWidget("tab-layout") {
            }
            virtual ~VisitorGuiTabLayout() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiText : public VisitorGuiWidget {
        public:
            VisitorGuiText() :VisitorGuiWidget("text") {
            }
            virtual ~VisitorGuiText() = default;

            void addWidget(GuiWidget* acceptor, GuiWindow* window, GuiWidget* child) const override;
            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        class VisitorGuiTextPara : public VisitorGuiWidget {
        public:
            VisitorGuiTextPara() :VisitorGuiWidget("para") {
            }
            virtual ~VisitorGuiTextPara() = default;

            GuiWidget* accept(GuiWidget* acceptor, GuiWindow* window, const Token& token, const Registry* registry) const override;
        };

        GuiXmlParser(GuiWindow& window, const Registry& registry);
        virtual ~GuiXmlParser() = default;
        void parse(const std::string& str) {
            parse(str.c_str(), str.size());
        }
        void parse(const char* src, size_t len);
        void addVisitor(const Visitor* visitor) {
            visitors.insert(std::make_pair(visitor->getKey(), visitor));
        }
    private:
        GuiWidget* recursive(tinyxml2::XMLElement* elem, GuiWidget* parent);
        const Visitor* getVisitor(const std::string& key);

        GuiWindow& window;
        const Registry& registry;
        std::unordered_map<std::string, const Visitor*> visitors;
    };
}

#endif
