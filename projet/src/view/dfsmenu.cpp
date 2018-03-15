#include "dfsmenu.h"
#include "cli.h"
#include "menuview.h"
#include "dotgeneratorview.h"
#include "dfsmetadata.h"
#include "vertexselector.h"

DFSMenu::DFSMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {

    addItem("Afficher le parcours", std::bind(&DFSMenu::onGraphicRepresentationSelected, this));
}

void DFSMenu::onGraphicRepresentationSelected() {
    VertexSelector vs(out(), in(), cli(), "source", true);
    vs.show();

    char componentsChoice;
    out() << "Parcourir toutes les composantes ? (o/n)" << std::endl;
    in() >> componentsChoice;
    DFS dfs(cli()->graph(), componentsChoice == 'o');

    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();
    dfs.begin(vs.selected());
    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    DFSMetaData dmd(&dfs);
    cli()->setView(new DOTGeneratorView(out(), in(), cli(), &dmd));
}
