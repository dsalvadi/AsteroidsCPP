#include "MainMenu.hpp"

MainMenu::MainMenu(int W, int H)
{
    if (!font.loadFromFile("fonts/Montserrat-Regular.ttf"))
    {
        cout << "No Font Found";
    }

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(W/2, H/5);

    //Options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(W/2, 2*H/5);

    //Options
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("About");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(W/2, 3*H/5);

    //Options
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(W/2, 4*H/5);

    MainMenuSelected = -1;
}

MainMenu ::~MainMenu()
{
}


void MainMenu::MoveUp()
{
    if (MainMenuSelected - 1 >= 0)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);

        MainMenuSelected--;
        if (MainMenuSelected == -1)
        {
            MainMenuSelected = 2;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

void MainMenu::MoveDown()
{
    if (MainMenuSelected + 1 <= Main_Menu_Max)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;
        if (MainMenuSelected == Main_Menu_Max)
            MainMenuSelected = 0;
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}

//Draw MainMenu
void MainMenu::draw(RenderWindow &app)
{
    Event event;
    app.clear();
    for (int i = 0; i < Main_Menu_Max; ++i)
    {
        app.draw(mainMenu[i]);
    }

    // while(app.isOpen())
    // {
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return || event.key.code == Keyboard::Space)
                {
                    stateInfo = MainMenuPressed();
                    break;
                }
            }
        }
        if (stateInfo != -1) return;
        
        app.display();
    //}
    
}