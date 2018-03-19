#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#include <file/dotwriter.h>
#include <limits>
#include "dotgeneratorview.h"
#include "cli.h"
#include <ctime>

#ifndef PATH_MAX
#define PATH_MAX _MAX_PATH
#endif

#ifdef _WIN32
#define NOMINMAX
#include "windows.h"
#endif

DOTGeneratorView::DOTGeneratorView(std::ostream& out, std::istream& in, CLI* cli, DotMetaData* dmd) :
        View(out, in, cli) {
    _dmd = dmd;
}

void DOTGeneratorView::show() {
    bool ok;
    std::string outputFile;

    do {
        char buf[PATH_MAX + 1];

        #ifdef _WIN32
            GetFullPathName(".", PATH_MAX, buf, NULL);
        #else
            realpath(".", buf);
        #endif

        out() << "Dossier actuel: " << buf << std::endl;
        out() << "Entrez le nom du fichier à créer: ";

        in() >> outputFile;
        in().clear();
        in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (FILE* file = fopen(outputFile.c_str(), "r")) {
            fclose(file);
            char choice;

            do {
                out() << "Le fichier existe déjà, l'écraser ? (o/n)";
                in() >> choice;
                in().clear();
                in().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
