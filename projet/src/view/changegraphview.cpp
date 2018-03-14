#include "changegraphview.h"
#include <dirent.h>
#include <limits.h>
#include <file/gprparser.h>
#include <fstream>
#include "cli.h"

ChangeGraphView::ChangeGraphView(std::ostream& out, std::istream& in, CLI* cli) :
        View(out, in, cli) {

}

void ChangeGraphView::show() {
    DIR* dir;
    struct dirent* ent;

    do {
        std::vector<std::string> files;

        if ((dir = opendir(".")) == NULL) {
            perror("Erreur");
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
        out() << "Graphes dans le dossier " << buf << ":" << std::endl;

        unsigned long i = 1;
        for(auto file : files) {
            out() << i++ << ": " << file << std::endl;
        }

        if(cli()->graph()) {
            out() << "0: Retour" << std::endl;
        }

        unsigned long choice;
        out() << "Choix: " << std::endl;
        in() >> choice;

        if(choice == 0) {
            if(cli()->graph()) {
                return;
            }
            else {
                out() << "Vous n'avez pas initialisé le graphe";
            }
        }
        else if(choice < files.size()) {
            openGraph(files[choice]);
        }
        else {
            out() << "Mauvais choix" << std::endl;
        }

    } while(!cli()->graph());

    cli()->previousView();
}

bool ChangeGraphView::sameSuffix(const std::string& fileName, const std::string& suffix) const {
    return (fileName.length() >= suffix.length() && std::equal(suffix.rbegin(), suffix.rend(), fileName.rbegin()));
}

void ChangeGraphView::openGraph(const std::string& path) {
    out() << "Ouverture du graphe " << path << std::endl;

    const clock_t begin_time = clock();

    std::ifstream ifs(path);
    GPRParser gprp(ifs);
    gprp.load();

    out() << "Graphe ouvert en " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " secondes.";

    cli()->setGraph(new ModelingGraph(gprp.graphe()));
}

