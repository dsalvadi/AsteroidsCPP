#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace sf;

#define Main_Menu_Max 3

class MainMenu
{
    public:
    MainMenu(int width, int height);
    void draw(RenderWindow& window, int lastScore);
    void MoveUp();
    void MoveDown();
    int stateInfo = -1;

    int MainMenuPressed(){
        return MainMenuSelected;
    }
    ~MainMenu();


    // Score Manipulation
    int ScoreParse();
    fstream scoreFile;
    void ResetScore();
    void CheckHigh(int lastScore);

    // Font and Text
    protected:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Main_Menu_Max];
    Text title;
    Text endScore;
    Text highScore;
    Text about;
};