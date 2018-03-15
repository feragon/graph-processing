#include "mainmenu.h"
#include "cli.h"
#include "changegraphview.h"
#include "dfsmenu.h"

MainMenu::MainMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {

    addItem("Changer de graphe", std::bind(&MainMenu::onChangeGraphSelected, this));
    addItem("DFS", std::bind(&MainMenu::onDFSSelected, this));
}

void MainMenu::onChangeGraphSelected() {
    cli()->setView(new ChangeGraphView(out(), in(), cli()));
}

void MainMenu::onDFSSelected() {
    cli()->setView(new DFSMenu(out(), in(), cli()));
}