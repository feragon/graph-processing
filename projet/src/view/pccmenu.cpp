#include "pccmenu.h"
#include "cli.h"
#include "vertexselector.h"
#include "pccmetadata.h"
#include "dotgeneratorview.h"
#include <ctime>
#include <limits>
#include <algorithm/pccft.h>

PCCMenu::PCCMenu(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {
    addItem("PCC (Dijkstra)", std::bind(&PCCMenu::onShortestPathSelected, this));
    addItem("PCC (Visualisation)", std::bind(&PCCMenu::onShortestPathVisualizationSelected, this));
    addItem("PCC avec fenêtre (Correction d'étiquette)", std::bind(&PCCMenu::onShortestPathWindowSelected, this));
    addItem("PCC avec fenêtre (Visualisation)", std::bind(&PCCMenu::onShortestPathWindowVisualizationSelected, this));
}

void PCCMenu::onShortestPathSelected() {
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

    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();

    if(functChoice == 'c')
        pcc.begin(vs_source.selected(), PCC::cout);
    else
        pcc.begin(vs_source.selected(), PCC::temps);

    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;

    int valeur;
    auto chemin = pcc.plusCourtChemin((Sommet<VertexData>*)vs_puit.selected(), &valeur);
    
    out() << "Chemin";
    for(auto sommet : chemin) {
        out() << " -> " << sommet->cle();
    }
    if(chemin.empty()) {
        out() << " non trouvé";
    }
    else {
        out() << std::endl;
        out() << "Valeur: " << valeur;
    }
    out() << std::endl;
}

void PCCMenu::onShortestPathVisualizationSelected() {
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

    out() << "Début du parcours" << std::endl;
    clock_t begin_time = clock();

    if(functChoice == 'c')
        pcc.begin(vs_source.selected(), PCC::cout);
    else
        pcc.begin(vs_source.selected(), PCC::temps);

    out() << "Graphe parcouru en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;


    PCCMetaData<PCC> pmd(&pcc, pcc.plusCourtChemin((Sommet<VertexData>*)vs_puit.selected()));
    DOTGeneratorView dgv(out(), in(), cli(), &pmd);
    dgv.show();
}

void PCCMenu::onShortestPathWindowSelected() {
    VertexSelector vs_source(out(), in(), cli(), "source", false);
    VertexSelector vs_puit(out(), in(), cli(), "puit", false);
    vs_source.show();
    vs_puit.show();

    PCCFT pccft(cli()->graph());

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
    std::vector<const Sommet<VertexData>*> chemin;
    if(functChoice == 'c') {
        chemin = pccft.meilleurChemin((Sommet<VertexData>*) vs_puit.selected(), PCCFT::cout, a, b, &e);
    }
    else {
        chemin = pccft.meilleurChemin((Sommet<VertexData>*) vs_puit.selected(), PCCFT::temps, a, b, &e);
    }

    out() << "Chemin";
    for(auto sommet : chemin) {
        out() << " -> " << sommet->cle();
    }
    if(chemin.empty()) {
        out() << " non trouvé";
    }
    else {
        out() << std::endl;
        out() << "Coût: " << e.cost() << " temps:" << e.time() << std::endl;
    }
    out() << std::endl;
}

void PCCMenu::onShortestPathWindowVisualizationSelected() {
    VertexSelector vs_source(out(), in(), cli(), "source", false);
    VertexSelector vs_puit(out(), in(), cli(), "puit", false);
    vs_source.show();
    vs_puit.show();

    PCCFT pccft(cli()->graph());

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


    PCCMetaData<PCCFT> *pmd;
    if(functChoice == 'c') {
        pmd = new PCCMetaData<PCCFT>(&pccft, pccft.meilleurChemin((Sommet<VertexData>*) vs_puit.selected(), PCCFT::cout, a, b));
    }
    else {
        pmd = new PCCMetaData<PCCFT>(&pccft, pccft.meilleurChemin((Sommet<VertexData>*) vs_puit.selected(), PCCFT::temps, a, b));
    }

    DOTGeneratorView dgv(out(), in(), cli(), pmd);
    dgv.show();

    delete pmd;
}