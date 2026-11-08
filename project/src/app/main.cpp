#include "dnf/app/game_application.hpp"
#include "dnf/entry.hpp"

static int run(int argc, char** argv) {
    dnf::app::GameApplication application;
    return application.run(argc, argv);
}

DNF_ENTRY(run)
