#include <iostream>
#include "cli.h"
#include <dirent.h>
#include <limits.h>
#include <fstream>
#include <file/gprparser.h>

CLI::CLI(std::ostream& out, std::istream& in) :
    _out(out),
    _in(in) {

    _graph = nullptr;
}

void CLI::start() {
    _out << "Projet de modelisation" << std::endl;
    _out << "Par ROMEO Florian et WEBERT Chris" << std::endl;
    _out << "Choix du graphe:" << std::endl;

    chooseGraph();
}

CLI::~CLI() {
    if(_graph) {
        delete _graph;
    }
}

void CLI::chooseGraph() {
    if(_graph) {
        delete _graph;
    }

    DIR* dir;
    struct dirent* ent;

    do {
        std::vector<std::string> files;

        if ((dir = opendir(".")) == NULL) {
            perror("Erreur");
            _graph = nullptr;
        }
        else {
            while ((ent = readdir(dir)) != NULL) {
                if(sameSuffix(ent->d_name, ".gpr")) {
                    files.emplace_back(ent->d_name);
                }
            }
            closedir(dir);
        }

        char buf[PATH_MAX + 1];
        realpath(".", buf);
        _out << "Graphes dans le dossier " << buf << ":" << std::endl;

        unsigned long i = 1;
        for(auto file : files) {
            _out << i++ << ": " << file << std::endl;
        }

        //_out << "0: Créer un graphe" << std::endl;

        unsigned long choice;
        _out << "Choix: " << std::endl;
        _in >> choice;

        if(choice == 0) {

        }
        else if(choice < files.size()) {
            openGraph(files[choice]);
        }
        else {
            _out << "Mauvais choix" << std::endl;
        }

    } while(!_graph);
}

bool CLI::sameSuffix(const std::string& fileName, const std::string& suffix) const {
    return (fileName.length() >= suffix.length() && std::equal(suffix.rbegin(), suffix.rend(), fileName.rbegin()));
}

void CLI::openGraph(const std::string& path) {
    _out << "Ouverture du graphe " << path << std::endl;

    const clock_t begin_time = clock();

    std::ifstream ifs(path);
    GPRParser gprp(ifs);
    gprp.load();

    std::cout << "Graphe ouvert en " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " secondes.";

    _graph = new ModelingGraph(gprp.graphe());
}