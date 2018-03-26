#include "pccmenu.h"
#include "cli.h"
#include "vertexselector.h"
#include "pccmetadata.h"
#include "dotgeneratorview.h"
#include <ctime>

PCCMenu::PCCMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {
    addItem("PCC (Dijkstra)", std::bind(&PCCMenu::onShortestPathSelected, this, nullptr));
    addItem("PCC (Visualisation)", std::bind(&PCCMenu::onShortestPathVisualizationSelected, this));
    addItem("PCC avec fenêtre (Correction d'étiquette)", std::bind(&PCCMenu::onShortestPathWindowSelected, this, nullptr));
    addItem("PCC avec fenêtre (Visualisation)", std::bind(&PCCMenu::onShortestPathWindowVisualizationSelected, this));
}

void PCCMenu::onShortestPathSelected(std::vector<std::pair<const Sommet<VertexData>*, int>> *chemin) {
    VertexSelector vs_source(out(), in(), cli(), "source", false);
    VertexSelector vs_puit(out(), in(), cli(), "puit", false);
    vs_source.show();
    vs_puit.show();

    char functChoice;
    do {
        out() << "Optimiser le cout ou le temps ? (c/t) : ";
        in() >> functChoice;
        in().clear();
        in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while(functChoice != 'c' && functChoice != 't');

    PCC pcc(cli()->graph());
    if(chemin == nullptr)
        chemin = new std::vector<std::pair<const Sommet<VertexData>*, int>>();

    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();

    try {
        if(functChoice == 'c')
            pcc.begin(vs_source.selected(), PCC::cout);
        else
            pcc.begin(vs_source.selected(), PCC::temps);

        out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;
    }
    catch (std::exception& e) {
        out() << "Erreur: " << e.what() << std::endl;
    }


    int valeur;
    *chemin = pcc.plusCourtChemin((Sommet<VertexData>*)vs_puit.selected(), &valeur);

    out() << "Chemin";
    for(auto sommet : *chemin) {
        out() << " -> " << sommet.first->cle();
    }
    if(chemin->empty()) {
        out() << " non trouvé";
    }
    else {
        out() << std::endl;
        out() << "Valeur: " << valeur;
    }
    out() << std::endl;
}

void PCCMenu::onShortestPathVisualizationSelected() {

    std::vector<std::pair<const Sommet<VertexData>*, int>> chemin;
    onShortestPathSelected(&chemin);

    PCCMetaData<PCC> pmd(chemin);
    DOTGeneratorView dgv(out(), in(), cli(), &pmd);
    dgv.show();
}

void PCCMenu::onShortestPathWindowSelected(std::vector<std::pair<const Sommet<VertexData>*, int>> *chemin) {
    VertexSelector vs_source(out(), in(), cli(), "source", false);
    VertexSelector vs_puit(out(), in(), cli(), "puit", false);
    vs_source.show();
    vs_puit.show();

    PCCFT pccft(cli()->graph());
    if(chemin == nullptr)
        chemin = new std::vector<std::pair<const Sommet<VertexData>*, int>>();

    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();
    pccft.begin(vs_source.selected());
    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    char functChoice;
    do {
        out() << "Optimiser le cout ou le temps ? (c/t) : ";
        in() >> functChoice;
        in().clear();
        in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while(functChoice != 'c' && functChoice != 't');

    int a = 0;
    int b = std::numeric_limits<int>::max();
    std::string input;

    out() << "Borne inférieure de la fenêtre (vide pour 0) : ";
    std::getline(in(), input);
    if (!input.empty()) {
        std::istringstream stream(input);
        stream >> a;
    }

    out() << "Borne supérieure de la fenêtre (vide pour +inf) : ";
    std::getline(in(), input);
    if (!input.empty()) {
        std::istringstream stream(input);
        stream >> b;
    }

    Etiquette e(nullptr, nullptr, 0, 0);
    if(functChoice == 'c') {
        *chemin = pccft.meilleurChemin((Sommet<VertexData>*) vs_puit.selected(), PCCFT::cout, a, b, &e);
    }
    else {
        *chemin = pccft.meilleurChemin((Sommet<VertexData>*) vs_puit.selected(), PCCFT::temps, a, b, &e);
    }

    out() << "Chemin";
    for(auto sommet : *chemin) {
        out() << " -> " << sommet.first->cle();
    }
    if(chemin->empty()) {
        out() << " non trouvé";
    }
    else {
        out() << std::endl;
        out() << "Coût: " << e.cost() << ", Temps: " << e.time() << std::endl;
    }
    out() << std::endl;
}

void PCCMenu::onShortestPathWindowVisualizationSelected() {

    std::vector<std::pair<const Sommet<VertexData>*, int>> chemin;
    onShortestPathWindowSelected(&chemin);

    PCCMetaData<PCCFT> pmd(chemin);
    DOTGeneratorView dgv(out(), in(), cli(), &pmd);
    dgv.show();
}