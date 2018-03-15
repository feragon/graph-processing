#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <file/dotwriter.h>
#include "dotgeneratorview.h"
#include "cli.h"

DOTGeneratorView::DOTGeneratorView(std::ostream& out, std::istream& in, CLI* cli, DotMetaData* dmd) :
        View(out, in, cli) {
    _dmd = dmd;
}

void DOTGeneratorView::show() {
    bool ok;
    std::string outputFile;

    do {
        char buf[PATH_MAX + 1];
        realpath(".", buf);
        out() << "Dossier actuel: " << buf << std::endl;
        out() << "Entrez le nom du fichier à créer: ";

        in() >> outputFile;

        if (FILE* file = fopen(outputFile.c_str(), "r")) {
            fclose(file);
            char choice;

            do {
                out() << "Le fichier existe déjà, l'écraser ? (o/n)";
                in() >> choice;
            } while (choice != 'o' && choice != 'n');

            ok = (choice == 'o');
        }
        else {
            ok = true;
        }
    } while (!ok);

    const clock_t begin_time = clock();

    std::ofstream ofs(outputFile);
    DotWriter dotw(ofs);
    dotw.writeGraph("output", *(cli()->graph()), _dmd);

    out() << "Fichier écrit en " << float(clock() - begin_time) / CLOCKS_PER_SEC << " secondes." << std::endl;
}
