#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>
using namespace std;
void setStar(string starLocation, vector<sf::Sprite>& starVect);
void setGameImage(sf::RenderWindow& wind, string starLocation, sf::Sprite& imageSprite);
void drawStars(RenderWindow& wind, vector<sf::Sprite> vect, int act);
void drawText(RenderWindow& wind);
void drawGameList(RenderWindow& wind, vector<sf::Text>& vectorPush);
vector<sf::Text> setGameList(sf::Font& fontt);
//void setDrawURL(RenderWindow& wind);
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Steam Sorter");
    
    vector<sf::Sprite> starVector;
    int starRating = 3; //would calculate this for each node
    setStar("starTexture", starVector);
 
    sf::Sprite imageSprite;
    setGameImage(window,"amogus", imageSprite);

    vector<sf::Text> vectorPush;
    sf::Font font;
    font.loadFromFile("files/font/SteamFont.ttf");
    vectorPush = setGameList(font);
   // vector<sf::Text> gameList = setGameList();
    sf::Color backgroundColor(176,224, 230);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            static bool lock_click; // Create a bool variable for locking the click.
            if (event.type == sf::Event::MouseButtonPressed) //Mouse button Pressed
            {
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true) //specifies
                {
                    /* your code here*/
                    sf::Vector2i mouse_position_leftClick = sf::Mouse::getPosition(window);
                    if (mouse_position_leftClick.x >=  (850-135) && mouse_position_leftClick.x < (850)+120) //Hardcoded values
                    {
                        if (mouse_position_leftClick.y >= (650) && mouse_position_leftClick.y < (680))
                        {
                            cout << "Game URL Clicked" << endl;
                            ShellExecuteA(0, NULL, "http://www.google.com", NULL, NULL, 10);
                        }
                    }
                    lock_click = true; //And now, after all your code, this will lock the loop and not print "lmb" in a x held time. 
                    /* or here idk */
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) //Mouse button Released now.
            {
                if (event.mouseButton.button == sf::Mouse::Left) //specifies the held button       again. (You can make a variable for that if you want)
                {
                    lock_click = false; //unlock when the button has been released.
                }
            } //Released 
        }

        window.clear(backgroundColor);
        drawStars(window, starVector, starRating);
        drawText(window);
        window.draw(imageSprite);
        //window.draw(gameList[0]);
        drawGameList(window, vectorPush);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}

void setStar(string starLocation, vector<sf::Sprite>& starVect)
{
    for (unsigned int i = 0; i < 5; i++)
    {
        sf::Sprite star;
        star.setTexture(TextureManager::textureGetter(starLocation));
        star.setScale(0.025, 0.025);
        star.setPosition(850+(50*i), 350);
        starVect.push_back(star);
    }
   
}

void setGameImage(sf::RenderWindow& wind,string starLocation, sf::Sprite& imageSprite)
{
    imageSprite.setTexture(TextureManager::textureGetter(starLocation));
    imageSprite.setScale(0.75, 0.75);
    imageSprite.setOrigin(imageSprite.getLocalBounds().width / 2.f, imageSprite.getLocalBounds().height / 2.f);
    imageSprite.setPosition(850+(50*2), 300 + (imageSprite.getLocalBounds().height));
}

/*void setDrawURL(RenderWindow& wind)
{
    ///*This isn't the most efficient implementation, as it redeclares the font and text each time it is drawn. If there are performance issues
    //can easily revert.
    sf::Font font;
    font.loadFromFile("files/font/SteamFont.ttf");

    sf::Text URL("https://store.steampowered.com/app/945360/Among_Us/?snr=1_7_7_230_150_1", font);
    URL.setFillColor(sf::Color::Black);
    URL.setPosition(850 - (URL.getLocalBounds().width) - 25, 650);
    URL.setCharacterSize(20);
    wind.draw(URL);
}*/

void drawStars(RenderWindow& wind, vector<sf::Sprite> vect, int act)
{
    for (unsigned int i = 0; i < act; i++)
    {
            wind.draw(vect[i]);
        
    }
}

void drawText(RenderWindow& wind)
{
    // Declare and load a font
    sf::Font font;
    font.loadFromFile("files/font/SteamFont.ttf");

    // Create a text
    sf::Text Rating("Rating:", font);
    Rating.setCharacterSize(35);
    Rating.setStyle(sf::Text::Bold);
    Rating.setFillColor(sf::Color::Black);
    Rating.setPosition(850 - (Rating.getLocalBounds().width)- 25, 350);
    // Draw it

    sf::Text searchCri("Search Criteria:", font);
    searchCri.setCharacterSize(35);
    searchCri.setStyle(sf::Text::Bold);
    searchCri.setFillColor(sf::Color::Black);
    searchCri.setPosition(0, 0);

    sf::Text URL_Text("Game Store Page", font);
    URL_Text.setCharacterSize(30);
    URL_Text.setStyle(sf::Text::Bold);
    URL_Text.setFillColor(sf::Color::Black);
    URL_Text.setPosition(850 - (Rating.getLocalBounds().width) - 25, 650);

    sf::Text Price("Price:", font);
    Price.setCharacterSize(30);
    Price.setStyle(sf::Text::Bold);
    Price.setFillColor(sf::Color::Black);
    Price.setPosition(20, 150);

    sf::Text Developer("Developer:", font);
    Developer.setCharacterSize(30);
    Developer.setStyle(sf::Text::Bold);
    Developer.setFillColor(sf::Color::Black);
    Developer.setPosition(20, 200);

    sf::Text Date("Date Published:", font);
    Date.setCharacterSize(30);
    Date.setStyle(sf::Text::Bold);
    Date.setFillColor(sf::Color::Black);
    Date.setPosition(20, 250);


    wind.draw(searchCri);
    wind.draw(Rating);
    wind.draw(URL_Text);
    wind.draw(Price);
    wind.draw(Developer);
    wind.draw(Date);
}

void drawGameList(RenderWindow& wind, vector<sf::Text>& vect)
{
    for (unsigned int i = 0; i < vect.size(); i++)
    {
        wind.draw(vect[i]);
    }
    
}

vector<sf::Text> setGameList(sf::Font& fontt)
{
    vector<sf::Text> vectorPush;
    sf::Text Game;
    for (unsigned int i = 0; i < 6; i++)
    {
        Game.setFont(fontt);
        Game.setString((to_string(i+1)+ ". GAME_" + to_string(i+1)));
        Game.setCharacterSize(30);
        Game.setStyle(sf::Text::Bold);
        Game.setFillColor(sf::Color::Black);
        Game.setPosition(25, 400+(35*i));
        vectorPush.push_back(Game);
    }
    
    return vectorPush;
}