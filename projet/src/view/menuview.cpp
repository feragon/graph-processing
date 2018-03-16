#include <iostream>
#include <limits>
#include "menuview.h"

MenuView::MenuView(std::ostream& out, std::istream& in, CLI* cli, bool canQuit) :
        View(out, in, cli) {
    _showMenu = true;
    _canQuit = canQuit;
}

void MenuView::show() {
    while (_showMenu) {
        if(_canQuit) {
            out() << "0: Quitter" << std::endl;
        }
        for (unsigned long i = 1; i <= _items.size(); i++) {
            out() << i << ": " << _items[i-1].first << std::endl;
        }

        out() << "Choix [";
        if(_canQuit) {
            out() << "0";
        }
        else {
            out() << "1";
        }
        out() << "-" << _items.size() << "]: ";

        unsigned long choice;
        in() >> choice;
        in().clear();
        in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(choice == 0 && _canQuit) {
            quitMenu();
        }
        else if(choice >= 1 && choice <= _items.size()) {
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
