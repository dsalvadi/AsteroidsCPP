#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
using namespace sf;

// Class to contain animation information
class Animation
{
    public:
    float Frame, speed;
    Sprite sprite;
    std::vector<IntRect> frames;

    Animation();
    //Animation (Texture &t, int x, int y, int w, int h, int count, float Speed);
    void init_anim(Texture &t, int x, int y, int w, int h, int count, float Speed);
    //~Animation(){};
    void update();
    bool isEnd();
};

// Class to contain details of entities/sprites
class Entity
{
    public:
    float x,y,dx,dy,R,angle;
    bool life;
    std::string name;
    Animation anim;

    Entity();

    void settings(Animation &a,int X,int Y,float Angle,int radius);
    virtual void update();
    void draw(RenderWindow &app);
    virtual ~Entity();
};

// Derived child class for asteroid sprites
class asteroid: public Entity
{
    public:
    asteroid();

    void update();
};

// Derived child class for bullet sprites
class bullet: public Entity
{
    public:
    bullet();

    void update();
};

// Derived child class for player sprite
class player: public Entity
{
    public:
    bool thrust;
    int maxSpeed;
    float speed;

    player();
    void update();
};

class Game
{
    public:
    Texture t1,t2,t3,t4,t5,t6,t7;
    Animation sExplosion, sRock, sRock_small, sBullet, sPlayer, sPlayer_go, sExplosion_ship; 
    Sprite background;
    // create a list containing all of the entities currently in use
    std::list<Entity*> entities;

    int score;
    Font scoreFont;
    Text scoreText; 
    
    // pointer for player
    player *p;
    bool endGame;
    void spawn_asteroid();

    Game();
    int draw_game(RenderWindow& app);
    void reset_game();
};

// detecting collisions using distance between centers of sprites and radii of their bounding circles 
bool isCollide(Entity *a, Entity *b);

// void drawGame(Animation sExplosion, Animation sRock, Animation sRock_small, 
//             Animation sBullet, Animation sPlayer, Animation sPlayer_go, 
//             Animation sExplosion_ship, std::list<Entity*> entities);