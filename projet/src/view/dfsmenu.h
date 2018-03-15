#pragma once

#include <sndfile.hh>
#include "menuview.h"

class DFSMenu : public MenuView {
    public:
        DFSMenu(std::ostream& out, std::istream& in, CLI* cli);

    private:
        void onGraphicRepresentationSelected();
        void onCycleDetectionSelected();
        void onNumberingSelected();
        void onPathFindingSelected();
};