#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;


//vector < pair<float, float> > eMagazine;

/*
class player
{
public:
    Sprite sprite;
    int HP, maxHP;

    player(Texture* texture)
    {
        this->maxHP = 100;
        this->HP = this->maxHP;
        this->sprite.setTexture(*texture);
        this->setPosition()
    }
};
*/

class enemy
{

public:
    Sprite sprite;
    int HP, maxHP;
    int eBulletLoad;

    enemy(Texture* texture)
    {
        this-> maxHP = 3;
        this->HP = this->maxHP;
        this->eBulletLoad = 0;

        this->sprite.setTexture(*texture);
        this->sprite.setScale(0.5, 0.5);

        this->sprite.setPosition(1100, rand() % (int)(800 - this->sprite.getGlobalBounds().height));

    }
};

class sat
{
public:
    Sprite sprite;
    int HP, maxHP;

    sat(Texture* texture)
    {
        this->maxHP = 3;
        this->HP = this->maxHP;

        this->sprite.setTexture(*texture);
        this->sprite.setScale(0.2, 0.2);

        this->sprite.setPosition(1100, rand() % (int)800 );
    }
};

class magazine
{
public:
    Sprite sprite;

    magazine(Texture* texture, Vector2f position)
    {
        this->sprite.setTexture(*texture);
        this->sprite.setScale(1.f, 0.5f);
        this->sprite.setPosition(position.x+100.f, position.y+25.f);
    }
};
class emagazine
{
public:
    Sprite sprite;
   
    emagazine(Texture* texture, Vector2f position)
    {
        this->sprite.setTexture(*texture);
        this->sprite.setScale(0.5f, 1.f);
        this->sprite.setPosition(position.x , position.y + 25.f);
    }
};

class mateor
{
public:
    Sprite sprite;

    mateor(Texture* texture)
    {
        this->sprite.setTexture(*texture);
        this->sprite.setPosition( rand() % (int)(1100 - this->sprite.getGlobalBounds().width), 0.f);
        this->sprite.setScale(0.5, 0.5);
       
    }
};

int main()                                                           //main function 
{
    //srand(time(NULL));

    RenderWindow window(VideoMode(1100, 800), "MISSION HORIZON");   //making window
    window.setFramerateLimit(60);

    int point = 0;
    
    Texture bgtexture;                                              //making background
    if (!bgtexture.loadFromFile("background.jpg"))
    {
        cout << "Failed to load background";
        exit(-1);
    }
    RectangleShape background(Vector2f(1100.f, 800.f));             //background 1
    background.setTexture(&bgtexture);
    background.setPosition(0.f, 0.f);

    Texture bg;                                                     //background 2
    bg.loadFromFile("image/bg2.jpg");
    RectangleShape bg2(Vector2f(1100.f, 800.f));
    bg2.setTexture(&bg);
    bg2.setPosition(1100.f , 0.f);

    
    Texture playerTexture;                                          //player loading
    if (!playerTexture.loadFromFile("image/player.jpg"))
    {
        cout << "Failed to load player";
    }
    RectangleShape player(Vector2f(100.f, 50.f));
    player.setTexture(&playerTexture);
    player.setPosition(0.f , 400.f);


    sf::Texture bulletTexture;                                      //Loading bullet
    bulletTexture.loadFromFile("image/laser.png");
   // RectangleShape bullet(Vector2f(80.f, 20.f));
    //bullet.setTexture(&bulletTexture);
    Texture ebulletTexture;                                   
    ebulletTexture.loadFromFile("image/bullet1.png");

    Texture mateorTexture;                                          //Loading mateor
    if (!mateorTexture.loadFromFile("mateor1.png")) exit(-1);


    
    SoundBuffer shotBuffer;                                         //sound and music effect
    shotBuffer.loadFromFile("sound/laser.ogg");
    Sound shot;          
    shot.setBuffer(shotBuffer);
    shot.setVolume(5);

    Music bgmusic;                                                  
    if (!bgmusic.openFromFile("sound/space.wav"))
    {
        cout << "Failed to load music";
        exit(-1);
    }
    bgmusic.play();
    bgmusic.setLoop(true);
    bgmusic.setVolume(10);

    
    Texture enemyTex;                                               // Enemy loading 
    Texture enemyTex1;
    Texture enemyTex2;
    //Texture enemyTex3;
    //Texture enemyTex4;
    //Texture enemyTex5;
    enemyTex.loadFromFile("image/alien.png");
    enemyTex1.loadFromFile("image/alien1.png");
    enemyTex2.loadFromFile("image/alien2.png");
    //enemyTex3.loadFromFile("image/alien3.png");
    //enemyTex4.loadFromFile("image/alien4.png");
    //enemyTex5.loadFromFile("image/alien5.png");

    Texture satelliteTex1;
    Texture satelliteTex2;
    Texture satelliteTex3;
    Texture spacestationTex;
    satelliteTex1.loadFromFile("image/satellite.png");
    satelliteTex2.loadFromFile("image/satellite1.png");
    satelliteTex3.loadFromFile("image/satellite2.png");
    spacestationTex.loadFromFile("international-space-station.png");
    

    Font font;                                                      //Font loading
    font.loadFromFile("fonts/space.otf");
    Text end;
    end.setString("Game Over");
    end.setPosition(1000.f, 400.f);
    end.setScale(2.f, 2.f);

    Text score;                                                     //score loading
    score.setFont(font);
    score.setString("SCORE : ");
    score.setPosition(10.f, 10.f);
    Text pnt;
    pnt.setFont(font);
    pnt.setPosition(score.getGlobalBounds().width , 10);

    RectangleShape HP(Vector2f(200.f, 30.f ) );                     //health display
    HP.setFillColor(Color::Green);
    HP.setPosition(window.getSize().x/2 -100.f,10.f );

    RectangleShape HPbox(HP.getSize());
    HPbox.setOutlineColor(Color::White);
    HPbox.setOutlineThickness(3.f);
    HPbox.setFillColor(Color::Transparent);
    HPbox.setPosition(HP.getPosition() );

    Text health;                     //health percentage text
    health.setFont(font);
    health.setPosition(HP.getPosition().x +80.f, HP.getPosition().y + 0.f);
    health.setFillColor(Color::White);

    


    
    

    RectangleShape ebullet(Vector2f(80.f, 20.f));
    ebullet.setTexture(&ebulletTexture);
       
                                               //varibale initialization
    int enemyloadTime = 250;
    int shootTimer = 21;  //player bullet loading time
    int mateorTimer = 200;
    int time = 0;
    

    int playerHP = 50;
    vector <magazine> bullet; // player bullet vector
    vector < enemy > alien1; // Enemy vector
    vector <mateor> mateor1;
    vector <sat> satellite;
    vector <emagazine> eBullet;

    


    while (window.isOpen())                                                                        // GAME LOOP STARTS
    {
        Event event;

        while (window.pollEvent(event))                             //event loop
        {
            if(event.type == Event::Closed)
                window.close();

            if ( (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space))               //Bullet pressed tracking
            {
                if (shootTimer > 20)
                {
                    bullet.push_back(magazine(&bulletTexture, player.getPosition()));
                    shot.play();
                    shootTimer = 1;
                }
            }

           

        }

       
  
                                                                                              //moving background effect
        background.move(-1.f, 0.f);
        bg2.move(-1.f, 0.f);
        
        if (background.getPosition().x == 0)
            bg2.setPosition(1100.f , 0.f);
        if(bg2.getPosition().x == 0)
            background.setPosition( 1100.f , 0.f);


        if (Keyboard::isKeyPressed(Keyboard::Key::A ))                                         //control setup
        {
            if(player.getPosition().x>0)
            player.move(-5.f, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S ))
        {
            if(player.getPosition().y+ player.getSize().y < window.getSize().y)
            player.move(0, 5.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            if(player.getPosition().x+player.getSize().x < window.getSize().x)
            player.move(5.f, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            if(player.getPosition().y >0)
            player.move(0, -5.f);
        }               

                                                                                                 // all variable laoding time increment
        shootTimer++;
        enemyloadTime++;
        mateorTimer++;
        time++;

        HP.setSize(Vector2f( (playerHP * 200) / 50.f , 30.f)); //Health dynamic display

        


        

        if (mateorTimer > 300)                                                                  //Mateor generating factory
        {
            mateor1.push_back(&mateorTexture);
            mateorTimer = 0;
        }
                                                                                                 //Enemy generating factory
        if (time % 300 == 0)
        {
            if (time % 300 == 0)        alien1.push_back(&enemyTex);
            else if (time % 800 == 0)        alien1.push_back(&enemyTex1);
            else if (time % 1400 == 0)        alien1.push_back(&enemyTex2);
            //else if (time % 1100 == 0)        alien1.push_back(&enemyTex3);
            //else if (time % 1400 == 0)        alien1.push_back(&enemyTex4);
           // else if (time % 1700 == 0)        alien1.push_back(&enemyTex5);
        }
        
        
        if (time % 200 == 0)                                                                    //satellite generating factory
        {
            if (time % 400 == 0)       satellite.push_back(&satelliteTex1);
            else if (time % 700 == 0)  satellite.push_back(&satelliteTex2);
            else if (time % 1100 == 0) satellite.push_back(&spacestationTex);
            else                       satellite.push_back(&satelliteTex3);
            
        }

        

                                                                                               //player bullet collision check
        if (!bullet.empty())
        {                                                                                
            for (size_t i = 0; i < bullet.size(); i++) //for bullet
            {
                bool alreadyCollided = false;

                for (size_t j = 0; j < alien1.size(); j++) //for allien
                {
                    
                    if (bullet[i].sprite.getGlobalBounds().intersects(alien1[j].sprite.getGlobalBounds()) ) // is collided with alien?
                    {
                        alien1[j].HP--;
                        
                        bullet.erase(bullet.begin() + i);
                        alreadyCollided = true;
                        break;
                    }
                
                    if (alien1[j].HP <= 0)
                    {
                        point += 3;
                        alien1.erase(alien1.begin() + j);
                    }
                    
                    
                }

                if (alreadyCollided == false)
                {
                    for (size_t k = 0; k < satellite.size(); k++)  //for satellite
                    {
                        if (bullet[i].sprite.getGlobalBounds().intersects(satellite[k].sprite.getGlobalBounds()))//is collided with satellite?
                        {
                            satellite[k].HP--;
                            bullet.erase(bullet.begin() + i);
                            break;
                        }

                        if (satellite[k].HP <= 0)
                        {
                            satellite.erase(satellite.begin() + k);
                            point += 3;
                        }
                    }
                }
                
            }
        }

        for (size_t i = 0; i < eBullet.size(); i++)                                                     //enemy bullet collision check
        {
            if (eBullet[i].sprite.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                playerHP--;
                eBullet.erase(eBullet.begin() + i);
            }
        }

        for (size_t i = 0; i < alien1.size(); i++)                                                      //alien player collision check
        {
            if (alien1[i].sprite.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                playerHP -= 5;
                alien1.erase(alien1.begin() + i);

            }

            for (size_t j = 0; j < satellite.size(); j++)                                               //satellite alien overlaping check
            {
                if (alien1[i].sprite.getGlobalBounds().intersects(satellite[j].sprite.getGlobalBounds()))
                {
                    satellite.erase(satellite.begin() + j); //if overlaped delete it
                }

            }

            alien1[i].eBulletLoad++;                                                                  //enemy bullet generating
             
            if (alien1[i].eBulletLoad > 400) //make a bullet for every alien after 100s of creation
            {
                eBullet.push_back(emagazine(&ebulletTexture, alien1[i].sprite.getPosition()));
                alien1[i].eBulletLoad = 0;
            }
        }

        for (size_t i = 0; i < satellite.size(); i++)
        {
            if (satellite[i].sprite.getGlobalBounds().intersects(player.getGlobalBounds())) //player satellite collision check
            {
                playerHP -= 5;
                satellite.erase(satellite.begin() + i);

            }
       
        }
        
        
        

                                                                                                //Randering section
        window.clear();
        window.draw(background);
        window.draw(bg2);
        window.draw(player);
                                                                        //alien 1 display
        for (size_t i = 0; i < alien1.size(); i++)                                             
        {
            if (alien1[i].sprite.getPosition().x > -200) alien1[i].sprite.move(-1.f, 0.f); //appeared from behind effect
            else alien1.erase(alien1.begin() + i);
              
            window.draw(alien1[i].sprite);
        }
        
                                             //enemy bullet display
        if (!eBullet.empty())
        {
            for (size_t i = 0; i < eBullet.size(); i++)
            {
                eBullet[i].sprite.move(-2.f, 0.f);

                if (eBullet[i].sprite.getPosition().x > -100)
                {
                    window.draw(eBullet[i].sprite);
                }
                else eBullet.erase(eBullet.begin() + i);

            }
        }
        

        if (!bullet.empty() )                                         //Bullet firing animation of player
        {
            for (size_t i = 0; i < bullet.size(); i++)
            {
                bullet[i].sprite.move(6.f, 0.f);     //position change per frame

                if (bullet[i].sprite.getPosition().x < 1200)
                {
                    //bullet.setPosition(magazine[i].first, magazine[i].second);      //bullet dynamic position changing
                    window.draw(bullet[i].sprite);
                }
                else bullet.erase(bullet.begin() + i);
                
            }
        }

       
        for (size_t i = 0; i < mateor1.size(); i++)          //mateor printing
        {
            mateor1[i].sprite.move(-1.f, 1.f);

            if (mateor1[i].sprite.getPosition().x > 1100) 
            {
                mateor1.erase(mateor1.begin() + i); continue;
            }

            window.draw(mateor1[i].sprite);
        }

        for (size_t i = 0; i < satellite.size(); i++)      //satellite printing
        {
            satellite[i].sprite.move(-1.f, 0.f);

            if (satellite[i].sprite.getPosition().x < -200)
            {
                satellite.erase(satellite.begin() + i); continue;
            }

            window.draw(satellite[i].sprite);
        }
        
        
        if (playerHP <= 0)               //player HP check
        {
            window.draw(end);
            window.close();
        }


        window.draw(score);             //printing score
        pnt.setString(to_string(point));
        window.draw(pnt);

        if (playerHP < 20) HP.setFillColor(Color::Red);     //printing Health
        window.draw(HPbox);
        window.draw(HP);
        health.setString(to_string( (playerHP * 100) / 50 ) );
        window.draw(health);
        

        window.display();
    }

    return 0;
}
