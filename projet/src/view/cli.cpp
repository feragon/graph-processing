#include <iostream>
#include "cli.h"
#include "changegraphview.h"
#include <fstream>

CLI::CLI(std::ostream& out, std::istream& in) :
    _out(out),
    _in(in) {

    _graph = nullptr;
    _views = nullptr;
}

void CLI::start() {
    _out << "Projet de modelisation" << std::endl;
    _out << "Par ROMEO Florian et WEBERT Chris" << std::endl;
    _out << "Choix du graphe:" << std::endl;

    setView(new ChangeGraphView(_out, _in, this));
}

CLI::~CLI() {
    if(_graph) {
        delete _graph;
    }

    Liste<View>::efface2(_views);
}


void CLI::previousView() {
    if(_currentView == nullptr) {
        return;
    }

    try {
        View* v = Liste<View>::depiler(_views);
        delete _currentView;
        _currentView = v;
    }
    catch(std::invalid_argument& e) {
        return;
    }
}

void CLI::setView(View* view) {
    if(_currentView == nullptr) {
        _currentView = view;
    }
    else {
        _views = new Liste<View>(_currentView, _views);
        _currentView = view;
    }

    _currentView->show();
}
