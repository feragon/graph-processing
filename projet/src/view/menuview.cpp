#include <iostream>
#include "menuview.h"

MenuView::MenuView(std::ostream& out, std::istream& in, CLI* cli) :
        View(out, in, cli) {
    _showMenu = true;
}

void MenuView::show() {
    while (_showMenu) {
        for (unsigned long i = 1; i <= _items.size(); i++) {
            out() << i << ": " << _items[i-1].first << std::endl;
        }

        out() << "Choix [1-" << _items.size() << "]: ";

        unsigned long choice;
        in() >> choice;

        if(choice >= 1 && choice <= _items.size()) {
            _items[choice-1].second();
        }
        else {
            out() << "Choix incorrect" << std::endl;
        }
    }
}

void MenuView::addItem(const std::string& name, const std::function<void(void)>& callback) {
    _items.emplace_back(std::pair<std::string, std::function<void(void)>>(name, callback));
}

void MenuView::quitMenu() {
    _showMenu = false;
}
