//#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "Game.hpp"
using namespace sf;

// Window size
const int W = 1200;
const int H = 800;

int state = -1;

int main()
{   
    RenderWindow app(VideoMode(W, H), "Asteroids!");
    Game game;
    app.setFramerateLimit(60);
    MainMenu mainMenu(W, H);

    /////main loop/////
    while (app.isOpen())
    {
        if (state == -1)
        {
            mainMenu.draw(app);
            state = mainMenu.stateInfo;
        }
        else if (state == 0)
        {
            game.draw_game(app);
        }
        else
        {
            app.close();
        }
    }

    return 0;
}
