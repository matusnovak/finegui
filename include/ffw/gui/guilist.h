/* This file is part of FineFramework project */
#ifndef FFW_GUI_LIST
#define FFW_GUI_LIST
#include "guiscrollable.h"
namespace ffw {
    /**
    * @ingroup gui
    */
    class FFW_API GuiList : public GuiScrollableLayout {
    public:
        class Item;
        class FFW_API Value {
        public:
            Value(GuiList* list);
            ~Value() = default;
            void setValue(int value);
            int getValue() const;
            void assign(GuiList::Item* item);
            void remove(GuiList::Item* item);
            void clearAllExcept(const GuiList::Item* item);
            void reset();
            inline size_t getNumOfassigned() const {
                return items.size();
            }
        private:
            std::vector<GuiList::Item*> items;
            int value;
            GuiList* parent;
        };

        class FFW_API Item : public GuiWidget {
        public:
            struct Style {
                GuiWidget::Style self;
            };

            Item(GuiWindow* context, const std::string& label, int base, GuiList::Value* group);
            virtual ~Item();
            void setLabel(const std::string& label);
            const std::string& getLabel() const;
            void setGroup(GuiList::Value* group);
            inline int getBaseValue() const {
                return base;
            }
            void setBaseValue(int base);
            bool isSelected() const;
            void assignValue(bool value);
            ffw::Pointf getMinimumWrapSize() override;
            void setStyle(const Item::Style* style, bool defaults = false);
        private:
            void eventRender(const ffw::Pointf& contentoffset, const ffw::Pointf& contentsize) override;
            void eventHover(bool gained) override;
            void eventFocus(bool gained) override;
            virtual void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
            std::string label;
            int base;
            GuiList::Value* group;
        };

        struct Style {
            GuiList::Item::Style item;
            GuiScrollable::Style self;
        };
        GuiList(GuiWindow* context);
        virtual ~GuiList() = default;
        GuiList::Item* addItem(const std::string& label);
        GuiList::Item* addItem(GuiList::Item* item);
        void deleteAllItems();
        bool deleteItem(const GuiList::Item* item);
        void setSelectedIndex(int index);
        void resetSelected();
        void setSelected(const GuiList::Item* item);
        GuiList::Item* getSelectedItem() const;
        int getSelectedIndex() const;
        void setStyle(const GuiList::Style* style, bool defaults = false);
        inline GuiList::Value* getGroup() {
            return &group;
        }
        inline const GuiList::Value* getGroup() const {
            return &group;
        }
    private:
        void eventHover(bool gained) override;
        void eventFocus(bool gained) override;
        void eventThemeChanged(const GuiTheme* theme, bool defaults) override;
        GuiList::Value group;
        int counter;
        const GuiList::Style* style;
    };
}
#endif
