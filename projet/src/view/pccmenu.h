#pragma once

#include "menuview.h"

class PCCMenu : public MenuView {
    public:
        PCCMenu(std::ostream& out, std::istream& in, CLI* cli);

    private:
        void onShortestPathSelected();
        void onShortestPathVisualizationSelected();
        void onShortestPathWindowSelected();
        void onShortestPathWindowVisualizationSelected();

};