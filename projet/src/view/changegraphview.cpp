#include "changegraphview.h"
#include <dirent.h>
#include <limits.h>
#include <file/gprparser.h>
#include <fstream>
#include "cli.h"

ChangeGraphView::ChangeGraphView(std::ostream& out, std::istream& in, CLI* cli) :
        MenuView(out, in, cli) {
    DIR* dir;
    struct dirent* ent;

    std::vector<std::string> files;

    if ((dir = opendir(".")) == NULL) {
        perror("Erreur");
    }
    else {
        while ((ent = readdir(dir)) != NULL) {
            if(sameSuffix(ent->d_name, ".gpr")) {
                addItem(ent->d_name, std::bind(&ChangeGraphView::openGraph, this, std::string(ent->d_name)));
            }
        }
        closedir(dir);
    }
}

void ChangeGraphView::show() {
    char buf[PATH_MAX + 1];
    realpath(".", buf);
    out() << "Graphes dans le dossier " << buf << ":" << std::endl;

    MenuView::show();
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

    out() << "Graphe ouvert en " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " secondes." << std::endl;

    cli()->setGraph(new ModelingGraph(gprp.graphe()));

    quitMenu();
}

