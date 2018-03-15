#pragma once

#include "menuview.h"

class MainMenu : public MenuView {
    public:
        MainMenu(std::ostream& out, std::istream& in, CLI* cli);

    private:
        void onChangeGraphSelected();
};