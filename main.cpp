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
    int lastScore = 0;

    /////main loop/////
    while (app.isOpen())
    {
        // Main Menu State
        if (state == -1)
        {
            mainMenu.draw(app, lastScore);
            state = mainMenu.stateInfo;
        }
        // Game State
        else if (state == 0)
        {
            app.clear();
            state = game.draw_game(app);
        }
        // High Score Reset Functionality
        else if (state == 1)
        {
            mainMenu.ResetScore();
            mainMenu.stateInfo = -1;
            state = -1;
        }
        // Post Game Over State, Returns to Menu State post reset.
        else if (state == 3)
        {
            lastScore = game.score;
            mainMenu.CheckHigh(lastScore);  // Compare last score and recorded high score. Update.
            game.reset_game();              // Reset Game State
            mainMenu.stateInfo = -1;        // Return to Menu State
            state = -1;
            // mainMenu.draw(app);
        }
        // Any other option closes the window
        else
        {
            app.close();
        }
        //cout << state;    // Debug Current State
    }

    return 0;
}
