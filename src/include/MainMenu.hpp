#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define Main_Menu_Max 4

class MainMenu
{
    public:
    MainMenu(int width, int height);
    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int stateInfo = -1;

    int MainMenuPressed(){
        return MainMenuSelected;
    }
    ~MainMenu();

    protected:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Main_Menu_Max];
};