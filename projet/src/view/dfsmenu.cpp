#include "dfsmenu.h"
#include "cli.h"
#include "menuview.h"

DFSMenu::DFSMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {

    addItem("Afficher le parcours", std::bind(&DFSMenu::onGraphicRepresentationSelected, this));
    addItem("Detection de circuits", std::bind(&DFSMenu::onCycleDetectionSelected, this));
}

void DFSMenu::onGraphicRepresentationSelected() {

}

void DFSMenu::onCycleDetectionSelected() {

}
