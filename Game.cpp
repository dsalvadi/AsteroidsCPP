#include "Game.hpp"
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>

// Window size
const int W = 1200;
const int H = 800;

// For conversion from degrees to radians
float DEGTORAD = 0.017453f;

// Animation Class Method Definitions
Animation::Animation() {}

// Animation::Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
// {
//     Frame = 0;
//     speed = Speed;

//     for (int i = 0; i < count; i++)
//         frames.push_back(IntRect(x + i * w, y, w, h));

//     sprite.setTexture(t);
//     sprite.setOrigin(w / 2, h / 2);
//     sprite.setTextureRect(frames[0]);
// }

// Creating method to set params for pre-declared animations
void Animation::init_anim(Texture &t, int x, int y, int w, int h, int count, float Speed)
{
    Frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
        frames.push_back(IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    sprite.setTextureRect(frames[0]);
}

void Animation::update()
{
    Frame += speed;
    int n = frames.size();
    if (Frame >= n)
        Frame -= n;
    if (n > 0)
        sprite.setTextureRect(frames[int(Frame)]);
}

bool Animation::isEnd()
{
    return Frame + speed >= frames.size();
}

// Entity Class Method Definitions
Entity::Entity()
{
    life = 1;
}

Entity::~Entity() {}

void Entity::update() {}

void Entity::settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1)
{
    anim = a;
    x = X;
    y = Y;
    angle = Angle;
    R = radius;
}

void Entity::draw(RenderWindow &app)
{
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90);
    app.draw(anim.sprite);

    // CircleShape circle(R);
    // circle.setFillColor(Color(255,0,0,170));
    // circle.setPosition(x,y);
    // circle.setOrigin(R,R);
    //app.draw(circle);
}

// Asteroid Class Method Definitions
asteroid::asteroid()
{
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
    name = "asteroid";
}

void asteroid::update()
{
    x += dx;
    y += dy;

    if (x > W)
        x = 0;
    if (x < 0)
        x = W;
    if (y > H)
        y = 0;
    if (y < 0)
        y = H;
}

// Bullet Class Method Definitions
bullet::bullet()
{
    name = "bullet";
}
void bullet::update()
{
    dx = cos(angle * DEGTORAD) * 6;
    dy = sin(angle * DEGTORAD) * 6;
    // angle+=rand()%7-3;  /*try this*/
    x += dx;
    y += dy;

    // despawn bullet if it crosses window boundaries
    if (x > W || x < 0 || y > H || y < 0)
        life = 0;
}

// Player Class Method Definitions
player::player()
{
    name = "player";
}

void player::update()
{
    if (thrust)
    {
        dx += cos(angle * DEGTORAD) * 0.2;
        dy += sin(angle * DEGTORAD) * 0.2;
    }
    else
    {
        dx *= 0.99;
        dy *= 0.99;
    }

    maxSpeed = 15;
    speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W)
        x = 0;
    if (x < 0)
        x = W;
    if (y > H)
        y = 0;
    if (y < 0)
        y = H;
}

// Game Class Method Definitions
Game::Game()
{
    srand(time(0));

    if (!t1.loadFromFile("images/spaceship.png"))
        std::cout << "Error in t1" << std::endl;
    if (!t2.loadFromFile("images/background.jpg"))
        std::cout << "Error in t2" << std::endl;
    if (!t3.loadFromFile("images/explosions/type_C.png"))
        std::cout << "Error in t3" << std::endl;
    if (!t4.loadFromFile("images/rock.png"))
        std::cout << "Error in t4" << std::endl;
    if (!t5.loadFromFile("images/fire_blue.png"))
        std::cout << "Error in t5" << std::endl;
    if (!t6.loadFromFile("images/rock_small.png"))
        std::cout << "Error in t6" << std::endl;
    if (!t7.loadFromFile("images/explosions/type_B.png"))
        std::cout << "Error in t7" << std::endl;

    t1.setSmooth(true);
    t2.setSmooth(true);

    background.setTexture(t2);

    // Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    // Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    // Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    // Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    // Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    // Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    // Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);

    sExplosion.init_anim(t3, 0, 0, 256, 256, 48, 0.5);
    sRock.init_anim(t4, 0, 0, 64, 64, 16, 0.2);
    sRock_small.init_anim(t6, 0, 0, 64, 64, 16, 0.2);
    sBullet.init_anim(t5, 0, 0, 32, 64, 16, 0.8);
    sPlayer.init_anim(t1, 40, 0, 40, 40, 1, 0);
    sPlayer_go.init_anim(t1, 40, 40, 40, 40, 1, 0);
    sExplosion_ship.init_anim(t7, 0, 0, 192, 192, 64, 0.5);

    // // spawn in 15 asteroids in the window
    // for (int i = 0; i < 15; i++)
    // {
    //     asteroid *a = new asteroid();
    //     a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
    //     entities.push_back(a);
    // }

    // // spawn the player
    // p = new player();
    // p->settings(sPlayer, 200, 200, 0, 20);
    // //std::cout << p->x << " " << p->y << std::endl;
    // entities.push_back(p);

    reset_game();
    
    if (!scoreFont.loadFromFile("fonts/Montserrat-Medium.ttf"))
    {
        std::cout << "No Font Found";
    }    
    scoreText.setFont(scoreFont);
    scoreText.setFillColor(Color::White);
    scoreText.setString(std::to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setPosition(0, 0);
    //std::cout<<score;
}

// Function to check for collisions between entities
bool isCollide(Entity *a, Entity *b)
{
    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) < (a->R + b->R) * (a->R + b->R);
}

int Game::draw_game(RenderWindow &app)
{
    endGame = false; // For hit detection

    Event event;

    while (app.pollEvent(event))
    {
        if (event.type == Event::Closed)
            app.close();
        // check for spacebar trigger. spawn bullet if spacebar has been tapped
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Space)
            {
                bullet *b = new bullet();
                b->settings(sBullet, p->x, p->y, p->angle, 10);
                entities.push_back(b);
            }
        }
        // check for escape trigger, go to main menu if tapped
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                return 3;
            }
        }
    }

    // Rotate ship by 3 deg. based on direction
    if (Keyboard::isKeyPressed(Keyboard::Right))
        p->angle += 3;
    if (Keyboard::isKeyPressed(Keyboard::Left))
        p->angle -= 3;
    if (Keyboard::isKeyPressed(Keyboard::Up))
        p->thrust = true;
    else
        p->thrust = false;

    // iterate through every entity and check for collisions between two types of objects
    for (auto a : entities)
    {
        for (auto b : entities)
        {

            if (a->name == "asteroid" && b->name == "bullet")
            {
                if (isCollide(a, b))
                {
                    a->life = false;
                    b->life = false;

                    Entity *e = new Entity();
                    e->settings(sExplosion, a->x, a->y);
                    e->name = "explosion";
                    entities.push_back(e);

                    // Update Score, +10 per collision
                    score = score + 10;

                    for (int i = 0; i < 2; i++)
                    {
                        if (a->R == 15)
                            continue;
                        Entity *e = new asteroid();
                        e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                        entities.push_back(e);
                    }
                }
            }
            if (a->name == "player" && b->name == "asteroid")
            {
                if (isCollide(a, b))
                {
                    b->life = false;

                    Entity *e = new Entity();
                    e->settings(sExplosion_ship, a->x, a->y);
                    e->name = "explosion";
                    entities.push_back(e);

                    p->settings(sPlayer, W / 2, H / 2, 0, 20);
                    p->dx = 0;
                    p->dy = 0;

                    endGame = true;
                }
            }
        }
    }

    // set ship animation based on thrust
    if (p->thrust)
        p->anim = sPlayer_go;
    else
        p->anim = sPlayer;

    // delete explosion entity if animation has ended
    for (auto e : entities)
        if (e->name == "explosion")
            if (e->anim.isEnd())
                e->life = 0;

    // spawn an asteroid randomly
    if (rand() % 300 == 0)
    {
        asteroid *a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    // check life of entities. Despawn them if their life has ended
    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity *e = *i;
        e->update();
        e->anim.update();
        //if (e->name != "asteroid")
        //std::cout<< e->name << " " << e->x << "," << e->y << " " << e->life << std::endl;
        if (e->life == false)
        {  
            i = entities.erase(i);
            delete e;
        }
        else
            i++;
    }

    // Update Score
    scoreText.setString("Score: " + std::to_string(score));

    //////draw//////
    //app.clear();
    // Draw Background
    app.draw(background);
    // Draw Entities
    for (auto i : entities)
    {
        i->draw(app);
    }
    // Draw Score
    app.draw(scoreText);
    
    // Display frame
    app.display();
    
    // Goto state 3 if end, else keep at state 1
    if (endGame)
        return 3;
    else
        return 0;
}

void Game::spawn_asteroid()
{
    asteroid *a = new asteroid();
    a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
    entities.push_back(a);
}

void Game::reset_game()
{
    //// Delete existing entities from list and memory

    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity *e = *i;
        i = entities.erase(i);
        delete e;
    }
 
    //// Respawn Asteroids and Player

    // spawn in 15 asteroids in the window
    for (int i = 0; i < 15; i++)
    {
        asteroid *a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    // spawn the player
    p = new player();
    p->settings(sPlayer, W/2, H/2, 0, 20);
    entities.push_back(p);

    //// Reset Score to 0
    score = 0;
    endGame = false;

}