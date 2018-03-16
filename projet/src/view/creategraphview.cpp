#include "creategraphview.h"
#include "vertexselector.h"
#include <iostream>
#include <limits>
#include <modeling/vertexnotfound.h>

CreateGraphView::CreateGraphView(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli, true) {
    addItem("Créer un sommet", std::bind(&CreateGraphView::onCreateVertexSelected, this));
    addItem("Créer une arête", std::bind(&CreateGraphView::onCreateEdgeSelected, this));
    addItem("Quitter sans sauvegardeer", std::bind(&CreateGraphView::onDiscardSelected, this));
}

void CreateGraphView::onCreateVertexSelected() {
    std::string vertexName;

    out() << "Entrez le nom du sommet:";
    in() >> vertexName;
    in().clear();
    in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        _graph.vertex(vertexName);
        out() << "Le sommet existe déjà" << std::endl;
        return;

    }
    catch (VertexNotFound& e) {
        unsigned int inf;
        unsigned int sup;
        bool ok;

        do {
            out() << "Entrez la borne inférieure de la fenêtre" << std::endl;
            in() >> inf;

            if(!in()) {
                out() << "Erreur de format" << std::endl;
                ok = false;
            }
            else {
                ok = true;
            }

            in().clear();
            in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (!ok);

        do {
            out() << "Entrez la borne supérieure de la fenêtre" << std::endl;
            in() >> sup;

            if(!in()) {
                out() << "Erreur de format" << std::endl;
                ok = false;
            }
            else if(sup < inf) {
                out() << "La borne doit être supérieure ou égale à " << inf << std::endl;
                ok = false;
            }
            else {
                ok = true;
            }

            in().clear();
            in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (!ok);

        _graph.creerSommet(vertexName, VertexData(inf, sup));
    }
}

void CreateGraphView::onCreateEdgeSelected() {
    std::string id;
    int cost;
    int time;
    bool ok;

    out() << "Entrez l'identifiant:";
    in() >> id;
    in().clear();
    in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    VertexSelector vs(out(), in(), cli(), "début", false, &_graph);
    VertexSelector vs2(out(), in(), cli(), "fin", false, &_graph);

    vs.show();
    vs2.show();

    do {
        out() << "Entrez le coût:";
        in() >> cost;
        if(!in()) {
            out() << "Coût invalide" << std::endl;
            ok = false;
        }
        else if(cost < 0) {
            out() << "Le coût doit être positif" << std::endl;
            ok = false;
        }
        else {
            ok = true;
        }
        in().clear();
        in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while(!ok);

    do {
        out() << "Entrez le temps:";
        in() >> time;
        if(!in()) {
            out() << "Temps invalide" << std::endl;
            ok = false;
        }
        else if(time < 0) {
            out() << "Le temps doit être positif" << std::endl;
            ok = false;
        }
        else {
            ok = true;
        }
        in().clear();
        in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while(!ok);

    _graph.creeArete(id, EdgeData(cost, time), _graph.vertex(vs.selected()->cle()), _graph.vertex(vs2.selected()->cle()));
}

void CreateGraphView::onDiscardSelected() {
    _discard = true;
    quitMenu();
}
