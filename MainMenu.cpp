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
    mainMenu[0].setPosition(W / 4, 2 * H / 5);

    //Options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Reset High Score");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(W / 4, 2 * H / 5 + 125);

    //Options
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Exit");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(W / 4, 2 * H / 5 + 250);

    // Score
    endScore.setFont(font);
    endScore.setFillColor(Color::White);
    //endScore.setString("Ending Score: 0");
    endScore.setCharacterSize(30);
    endScore.setPosition(W / 4, H / 5);

    // Title
    title.setFont(font);
    title.setFillColor(Color::Green);
    title.setString("Asteroids!!!");
    title.setCharacterSize(100);
    title.setPosition(W / 4, H / 20);

    // High Score
    highScore.setFont(font);
    highScore.setFillColor(Color::Red);
    highScore.setCharacterSize(40);
    highScore.setPosition(W / 4, H / 5 + 40);

    // About
    about.setFont(font);
    about.setFillColor(Color::White);
    about.setString("Mini-Project by Dhruv, Shreyas, Raka and Pranav");
    about.setCharacterSize(15);
    about.setPosition(W / 4, 9 * H / 10);

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
void MainMenu::draw(RenderWindow &app, int lastScore)
{
    Event event;
    app.clear();
    for (int i = 0; i < Main_Menu_Max; ++i)
    {
        app.draw(mainMenu[i]);
    }

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

    // Check and update High Score
    // CheckHigh(lastScore);
    // Set the strings for the scores
    highScore.setString("High Score: " + to_string(ScoreParse()));
    endScore.setString("Previous Score: " + to_string(lastScore));
    
    app.draw(title);
    app.draw(highScore);
    app.draw(endScore);
    app.draw(about);

    if (stateInfo != -1)
        return;

    app.display();
}

// Method to read score in highscore.txt and return it as an integer
int MainMenu::ScoreParse()
{
    scoreFile.open("highscore.txt", ios::in); //open a file to perform read operation using file object

    //checking whether the file is open
    if (scoreFile.is_open())
    {
        string sc;
        getline(scoreFile, sc);
        scoreFile.close(); //close the file object.
        return stoi(sc);
    }
    return 0;
}

// Method to reset high score to zero
void MainMenu::ResetScore()
{
    remove("highscore.txt");

    scoreFile.open("highscore.txt", ios::out); // open a file to perform write operation using file object
    if (scoreFile.is_open())                   // checking whether the file is open {
        scoreFile << "0";                      // inserting text
    scoreFile.close();                         // close the file object
}

// Method to check if last score is higher than the recorded high score. If so, update recorded high score.
void MainMenu::CheckHigh(int lastScore)
{
    int hScore = ScoreParse();

    // Updating file if the previous score is greater than recorded high score
    if (lastScore > hScore)
    {
        remove("highscore.txt");

        scoreFile.open("highscore.txt", ios::out);
        if (scoreFile.is_open())                   
            scoreFile << to_string(lastScore);   
        scoreFile.close();                        
    }
}