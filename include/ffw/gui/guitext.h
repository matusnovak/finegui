/* This file is part of FineFramework project */
#ifndef FFW_GUI_RICH_TEXT
#define FFW_GUI_RICH_TEXT
#include <list>
#include "guiwidget.h"

namespace ffw {
    /**
    * @ingroup gui
    */
    class FFW_API GuiText: public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        struct Paragraph {
            Paragraph(const GuiFont* font, const Color& color, const std::string& str):font(font),color(color),str(str){

            }

            void recalculate(float width, const GuiFont* fallback, float lineHeight);

            const GuiFont* font;
            const Color color;
            const std::string str;
            ffw::Pointf size;

            std::vector<GuiFont::Chunk> chunks;
        };

        GuiText(GuiWindow* context);
        virtual ~GuiText() = default;

        Paragraph* addParagraph(const std::string& text);
        Paragraph* addParagraph(const std::string& text, const Color& color, const GuiFont* font);
        const std::list<Paragraph>& getParagraphs() const {
            return paragraphs;
        }

        void setStyle(const GuiText::Style* style, bool defaults = false);
        ffw::Pointf getMinimumWrapSize() override;
    private:
        void recalculateSize(float width);
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventSize(const ffw::Pointf& size) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        float lastCalculatedWidth;
        std::list<Paragraph> paragraphs;
    };
    /**
    * @ingroup gui
    */
    /*class FFW_API GuiRichText : public GuiWidget {
    public:
        struct Style {
            GuiWidget::Style self;
        };

        GuiRichText(GuiWindow* context);
        virtual ~GuiRichText() = default;
        void setText(const std::wstring& str);
        const std::wstring getText() const;
        ffw::Pointf getMinimumWrapSize() override;
        void addParagraph();
        void addSection(const ffw::Color& color, ffw::GuiFont* font = nullptr);
        void addSection(ffw::GuiFont* font);
        void addSectionDefault();
        void addText(const std::wstring& str);
        void setStyle(const GuiRichText::Style* style, bool defaults = false);
    private:
        void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
        void eventSize(const ffw::Pointf& size) override;
        virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        GuiTextWrapper text;
        float lastCalculatedWidth;
    };*/
}
#endif
