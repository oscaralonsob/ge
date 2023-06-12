#include "./Game/Game.h"

#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int opt;
    bool debug = false;

    while ((opt = getopt(argc, argv, "d")) != -1) {
        if (opt == 'd') {
            debug = true;
        }
    }

    Game game;

    game.Initialize(debug);
    game.Run();
    game.Destroy();

    return 0;
}
