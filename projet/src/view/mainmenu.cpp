#include <file/dotmetadata.h>
#include "mainmenu.h"
#include "cli.h"
#include "changegraphview.h"
#include "dfsmenu.h"
#include "dotgeneratorview.h"

MainMenu::MainMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {

    addItem("Changer de graphe", std::bind(&MainMenu::onChangeGraphSelected, this));
    addItem("Visualiser graphe", std::bind(&MainMenu::onVisualizeGraphSelected, this));
    addItem("DFS", std::bind(&MainMenu::onDFSSelected, this));
}

void MainMenu::onChangeGraphSelected() {
    cli()->setView(new ChangeGraphView(out(), in(), cli()));
}

void MainMenu::onDFSSelected() {
    cli()->setView(new DFSMenu(out(), in(), cli()));
}

void MainMenu::onVisualizeGraphSelected() {
    DotMetaData dmd;
    cli()->setView(new DOTGeneratorView(out(), in(), cli(), &dmd));
}
