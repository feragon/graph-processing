#include "pccmenu.h"

PCCMenu::PCCMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {
    addItem("PCC coût", std::bind(&PCCMenu::onLowestCostSelected, this));
    addItem("PCC coût (visualisation)", std::bind(&PCCMenu::onLowestCostVisualizationSelected, this));
    addItem("PCC distance", std::bind(&PCCMenu::onLowestDistanceSelected, this));
    addItem("PCC distance (visualisation)", std::bind(&PCCMenu::onLowestDistanceVisualizationSelected, this));
}

void PCCMenu::onLowestCostSelected() {

}

void PCCMenu::onLowestDistanceSelected() {

}

void PCCMenu::onLowestCostVisualizationSelected() {

}

void PCCMenu::onLowestDistanceVisualizationSelected() {

}
