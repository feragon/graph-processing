#include <iomanip>
#include <limits>
#include "dfsmenu.h"
#include "cli.h"
#include "menuview.h"
#include "dotgeneratorview.h"
#include "dfsmetadata.h"
#include "vertexselector.h"
#include "sccmetadata.h"

DFSMenu::DFSMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {

    addItem("Afficher le parcours", std::bind(&DFSMenu::onGraphicRepresentationSelected, this));
    addItem("Detection de circuits", std::bind(&DFSMenu::onCycleDetectionSelected, this));
    addItem("Numérotation (suffixe/prefixe/topologique)", std::bind(&DFSMenu::onNumberingSelected, this));
    addItem("Existence chemin", std::bind(&DFSMenu::onPathFindingSelected, this));
    addItem("Affichage CFC", std::bind(&DFSMenu::onSCCSelected, this));
}

void DFSMenu::onGraphicRepresentationSelected() {
    VertexSelector vs(out(), in(), cli(), "source", true);
    vs.show();

    char componentsChoice;
    out() << "Parcourir toutes les composantes ? (o/n)" << std::endl;
    in() >> componentsChoice;
    in().clear();
    in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DFS dfs(cli()->graph(), componentsChoice == 'o');

    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();
    dfs.begin(vs.selected());
    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    DFSMetaData dmd(&dfs);
    cli()->setView(new DOTGeneratorView(out(), in(), cli(), &dmd));
}

void DFSMenu::onCycleDetectionSelected() {
    DFS dfs(cli()->graph());
    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();
    dfs.begin();
    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    out() << "Existence de cycle: ";

    if(dfs.hasCycle()) {
        out() << "oui";
    }
    else {
        out() << "non";
    }
    out() << std::endl;
}

void DFSMenu::onNumberingSelected() {
    DFS dfs(cli()->graph());
    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();
    dfs.begin();
    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    if(dfs.hasCycle()) {
        out() << "Pas d'ordre topologique" << std::endl;
    }

    out() << std::setw(10) << "Sommet" << std::setw(10) << "Prefixe" << std::setw(10) << "Suffixe";
    if(!dfs.hasCycle()) {
        out() << std::setw(10) << "Topologique";
    }
    out() << std::endl;

    for(auto vertex = cli()->graph()->sommets(); vertex; vertex = vertex->next) {
        out() << std::setw(10) << vertex->value->cle()
              << std::setw(10) << dfs.prefixNumber(vertex->value)
              << std::setw(10) << dfs.suffixNumber(vertex->value);

        if(!dfs.hasCycle()) {
            out() << std::setw(10) << dfs.topologicalNumber(vertex->value);
        }

        out() << std::endl;
    }
}

void DFSMenu::onPathFindingSelected() {
    VertexSelector beginVs(out(), in(), cli(), "début", false);
    VertexSelector endVs(out(), in(), cli(), "fin", false);

    beginVs.show();
    endVs.show();

    out() << "Existence d'un chemin: ";

    if(DFS::pathExists(cli()->graph(), beginVs.selected(), endVs.selected())) {
        out() << "oui";
    }
    else {
        out() << "non";
    }
    out() << "\n";
}

void DFSMenu::onSCCSelected() {
    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();
    auto scc = DFS::stronglyConnectedComponents(cli()->graph());
    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    for(auto l = cli()->graph()->sommets(); l ; l = l->next) {
        scc.at(l->value);
    }

    SCCMetaData sccMetaData(scc);
    cli()->setView(new DOTGeneratorView(out(), in(), cli(), &sccMetaData));
}
