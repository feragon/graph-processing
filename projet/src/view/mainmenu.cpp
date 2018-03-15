#include "mainmenu.h"
#include "cli.h"
#include "changegraphview.h"

MainMenu::MainMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli) {

    addItem("Changer de graphe", std::bind(&MainMenu::onChangeGraphSelected, this));
}

void MainMenu::onChangeGraphSelected() {
    cli()->setView(new ChangeGraphView(out(), in(), cli()));
}
