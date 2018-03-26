#pragma once

#include <algorithm/pcc.h>
#include <algorithm/pccft.h>
#include "menuview.h"

class PCCMenu : public MenuView {
    public:
        PCCMenu(std::ostream& out, std::istream& in, CLI* cli);

    private:
        void onShortestPathSelected(std::vector<std::pair<const Sommet<VertexData>*, int>>*);
        void onShortestPathVisualizationSelected();
        void onShortestPathWindowSelected(std::vector<std::pair<const Sommet<VertexData>*, int>>*);
        void onShortestPathWindowVisualizationSelected();

};