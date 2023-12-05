#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <fstream>
#include <thread>
#include "B.h"
#include "Nary.h"
using namespace std;
void setStar(string starLocation, vector<sf::Sprite>& starVect);
void setGameImage(sf::RenderWindow& wind, string starLocation, sf::Sprite& imageSprite);
void drawStars(RenderWindow& wind, vector<sf::Sprite> vect, int act);
void drawText(RenderWindow& wind, string input);
void drawGameList(RenderWindow& wind, vector<sf::Text>& vectorPush);
void ConfigData(string& _URL, string& name, string& _image_url, string& _allReviews, string& date, string& developer, string& _price, std::ifstream& readFile);
void dataProcessingLoop(string& _URL, string& name, string& _image_url, string& _allReviews, string& date, string& developer, string& _price, std::ifstream& readFile, BTree TreeB, NaryTree TreeN);
void drawButtons(RenderWindow& wind, sf::Color firstButton, sf::Color secondButton, sf::Color freeButton, sf::Color firstPriceButton, sf::Color secondPriceButton, sf::Color thirdPriceButton);
vector<sf::Text> setGameList(sf::Font& fontt, vector<Node*> gameVecPoint);

int main()
{
    BTree BTree;
    NaryTree NTree;
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Steam Sorter");
    vector<sf::Sprite> starVector;
    int starRating = 0; //We calculate this for each node
    setStar("starTexture", starVector);
 
    sf::Sprite imageSprite;
    sf::Sprite logoSprite;
    logoSprite.setTexture(TextureManager::textureGetter("steamLogo"));
    logoSprite.setScale(0.1, 0.1);
    logoSprite.setPosition(485, 100);
    setGameImage(window,"amogus", imageSprite);

    vector<sf::Text> vectorPush;
    sf::Font font;
    font.loadFromFile("files/font/SteamFont.ttf");
    sf::Color backgroundColor(176,224, 230);

    
    //NaryTree
    std::ifstream readFile("files/data/steam_data_.csv");
    string throwaway;
    std::getline(readFile, throwaway); //ignore csv header
    string URL;
    string name;
    string image_url;
    string allReviews;
    string date;
    string developer;
    string price;
    string userInput = "Search";
    
    double selectedPrice = 0.0;

    std::thread dataProcessingThread(dataProcessingLoop,
        std::ref(URL),
        std::ref(name),
        std::ref(image_url),
        std::ref(allReviews),
        std::ref(date),
        std::ref(developer),
        std::ref(price),
        std::ref(readFile),
        std::ref(BTree),
        std::ref(NTree));

    sf::Color BTreeButtonColor(125, 125, 125);
    sf::Color NaryButtonColor(116, 164, 170);
    sf::Color freeButton(125, 125, 125);
    sf::Color firstPriceButton(125, 125, 125);
    sf::Color secondPriceButton(125, 125, 125);
    sf::Color thirdPriceButton(125, 125, 125);

    bool BTreeActivated = true;
    bool showGame = false;
    bool search = true;
    sf::Text Speed("100.00ms",font);
    Speed.setCharacterSize(0);
    Speed.setStyle(sf::Text::Bold);
    Speed.setFillColor(sf::Color::Black);
    Speed.setPosition(0, 0);
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
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
                {
                    userInput = "Search";
                    search = true;
                    sf::Vector2i mouse_position_leftClick = sf::Mouse::getPosition(window);
                    if (mouse_position_leftClick.x >=  (850-135) && mouse_position_leftClick.x < (850)+120)
                    {
                        if (mouse_position_leftClick.y >= (650) && mouse_position_leftClick.y < (680))
                        {
                            //cout << "Game URL Clicked" << endl;
                            ShellExecuteA(0, NULL, "https://store.steampowered.com/app/945360/Among_Us/?snr=1_7_7_230_150_1", NULL, NULL, 10);
                        }
                    }
                    if (mouse_position_leftClick.x >= (790) && mouse_position_leftClick.x < (965))
                    {
                        if (mouse_position_leftClick.y >= (100) && mouse_position_leftClick.y < (155))
                        {
                            starRating = 0;
                            BTreeActivated = true;
                            vectorPush.clear();
                            showGame = false;
                            Speed.setCharacterSize(0);
                            Speed.setPosition(0, 0);
                            freeButton = sf::Color(125, 125, 125);
                            firstPriceButton = sf::Color(125, 125, 125);
                            secondPriceButton = sf::Color(125, 125, 125);
                            thirdPriceButton = sf::Color(125, 125, 125);
                            BTreeButtonColor = sf::Color(125, 125, 125);
                            NaryButtonColor = sf::Color(116, 164, 170);
                        }
                        else if (mouse_position_leftClick.y >= (160) && mouse_position_leftClick.y < (215))
                        {
                            showGame = false;
                            BTreeActivated = false;
                            starRating = 0;
                            vectorPush.clear();
                            Speed.setCharacterSize(0);
                            Speed.setPosition(0, 0);
                            freeButton = sf::Color(125, 125, 125);
                            firstPriceButton = sf::Color(125, 125, 125);
                            secondPriceButton = sf::Color(125, 125, 125);
                            thirdPriceButton = sf::Color(125, 125, 125);
                             NaryButtonColor = sf::Color(125, 125, 125);
                             BTreeButtonColor = sf::Color(116, 164, 170);
                        }
                    }
                    if (mouse_position_leftClick.y >= (135) && mouse_position_leftClick.y < (185))
                    {
                        freeButton = sf::Color(125, 125, 125);
                        firstPriceButton = sf::Color(125, 125, 125);
                        secondPriceButton = sf::Color(125, 125, 125);
                        thirdPriceButton = sf::Color(125, 125, 125);
                        Speed.setCharacterSize(0);
                        Speed.setPosition(0, 0);
                        vectorPush.clear();
                        showGame = false;
                        starRating = 0;

                        window.clear(backgroundColor);
                        drawButtons(window, BTreeButtonColor, NaryButtonColor, freeButton, firstPriceButton, secondPriceButton, thirdPriceButton);
                        drawStars(window, starVector, starRating);
                        drawText(window, userInput);
                        if (showGame)
                        {
                            window.draw(imageSprite);
                        }
                        drawGameList(window, vectorPush);
                        window.draw(Speed);
                        window.display();

                        if (mouse_position_leftClick.x >= (20) && mouse_position_leftClick.x < (95))
                        {
                            if (BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 100);
                            }
                            if (!BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 160);
                            }
                            selectedPrice = 0.0;
                            setGameImage(window, "csgo", imageSprite);
                            showGame = true;


                        }
                        if (mouse_position_leftClick.x >= (95) && mouse_position_leftClick.x < (170))
                        {

                            freeButton = sf::Color(125, 125, 125);
                            firstPriceButton = sf::Color(125, 125, 125);
                            secondPriceButton = sf::Color(125, 125, 125);
                            thirdPriceButton = sf::Color(125, 125, 125);
                            Speed.setCharacterSize(0);
                            Speed.setPosition(0, 0);
                            vectorPush.clear();
                            showGame = false;
                            starRating = 0;

                            window.clear(backgroundColor);
                            drawButtons(window, BTreeButtonColor, NaryButtonColor, freeButton, firstPriceButton, secondPriceButton, thirdPriceButton);
                            drawStars(window, starVector, starRating);
                            drawText(window, userInput);
                            if (showGame)
                            {
                                window.draw(imageSprite);
                            }
                            drawGameList(window, vectorPush);
                            window.draw(Speed);
                            window.display();

                            if (BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 100);
                            }
                            if (!BTreeActivated)
                            
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 160);
                            
                        }
                        if (mouse_position_leftClick.x >= (170) && mouse_position_leftClick.x < (245))
                        {
                            freeButton = sf::Color(125, 125, 125);
                            firstPriceButton = sf::Color(125, 125, 125);
                            secondPriceButton = sf::Color(125, 125, 125);
                            thirdPriceButton = sf::Color(125, 125, 125);
                            Speed.setCharacterSize(0);
                            Speed.setPosition(0, 0);
                            vectorPush.clear();
                            showGame = false;
                            starRating = 0;

                            window.clear(backgroundColor);
                            drawButtons(window, BTreeButtonColor, NaryButtonColor, freeButton, firstPriceButton, secondPriceButton, thirdPriceButton);
                            drawStars(window, starVector, starRating);
                            drawText(window, userInput);
                            if (showGame)
                            {
                                window.draw(imageSprite);
                            }
                            drawGameList(window, vectorPush);
                            window.draw(Speed);
                            window.display();
                            if (BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 100);
                            }
                            if (!BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 160);
                            }
                        }
                        if (mouse_position_leftClick.x >= (245) && mouse_position_leftClick.x < (320))
                        {
                            //Resets the buttons when clicked
                            freeButton = sf::Color(125, 125, 125);
                            firstPriceButton = sf::Color(125, 125, 125);
                            secondPriceButton = sf::Color(125, 125, 125);
                            thirdPriceButton = sf::Color(125, 125, 125);
                            Speed.setCharacterSize(0);
                            Speed.setPosition(0, 0);
                            vectorPush.clear();
                            showGame = false;
                            starRating = 0;

                            window.clear(backgroundColor);
                            drawButtons(window, BTreeButtonColor, NaryButtonColor, freeButton, firstPriceButton, secondPriceButton, thirdPriceButton);
                            drawStars(window, starVector, starRating);
                            drawText(window, userInput);
                            if (showGame)
                            {
                                window.draw(imageSprite);
                            }
                            drawGameList(window, vectorPush);
                            window.draw(Speed);
                            window.display();

                            if (BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 100);
                            }
                            if (!BTreeActivated)
                            {
                                Speed.setCharacterSize(35);
                                Speed.setPosition(1000, 160);
                            }
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
            if (event.type == sf::Event::TextEntered && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
            {
                if (userInput.length() <= 0)
                {
                    userInput = "Search";
                    search = true;
                }
                else
                {
                    if (search)
                    {
                        userInput = "";
                    }
                    search = false;
                    userInput += static_cast<char>(event.text.unicode);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
            {
                if (userInput != "Search")
                {
                if (userInput.length() <= 0)
                {
                    userInput = "Search";
                }
                else
                {
                        userInput = userInput.substr(0, userInput.length() - 1);
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                if (userInput == "Valve")
                {
                    starRating = 0;
                    showGame = false;
                    Speed.setCharacterSize(0);
                    Speed.setPosition(0, 0);
                    freeButton = sf::Color(125, 125, 125);
                    firstPriceButton = sf::Color(125, 125, 125);
                    secondPriceButton = sf::Color(125, 125, 125);
                    thirdPriceButton = sf::Color(125, 125, 125);
                    vectorPush.clear();
                    if (BTreeActivated)
                    {
                        Speed.setCharacterSize(35);
                        Speed.setPosition(1000, 100);
                    }
                    if (!BTreeActivated)
                    {
                        Speed.setCharacterSize(35);
                        Speed.setPosition(1000, 160);
                    }
                }
                if (userInput == "Ubisoft")
                {
                    if (BTreeActivated)
                    {
                        Speed.setCharacterSize(35);
                        Speed.setPosition(1000, 100);
                    }
                    if (!BTreeActivated)
                    {
                        Speed.setCharacterSize(35);
                        Speed.setPosition(1000, 160);
                    }
                    showGame = true;
                    setGameImage(window, "siege", imageSprite);
                    freeButton = sf::Color(125, 125, 125);
                    firstPriceButton = sf::Color(125, 125, 125);
                    secondPriceButton = sf::Color(125, 125, 125);
                    thirdPriceButton = sf::Color(125, 125, 125);
                    vectorPush.clear();
                }
            }
        }

        window.clear(backgroundColor);
        drawButtons(window, BTreeButtonColor, NaryButtonColor, freeButton, firstPriceButton, secondPriceButton, thirdPriceButton);
        drawStars(window, starVector, starRating);
        drawText(window, userInput);
        if (showGame)
        {
            window.draw(imageSprite);
        }
        drawGameList(window, vectorPush);
        window.draw(Speed);
        window.draw(logoSprite);
        window.display();
    }
    TextureManager::Clear();
    dataProcessingThread.join();
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

void drawStars(RenderWindow& wind, vector<sf::Sprite> vect, int act)
{
    for (unsigned int i = 0; i < act; i++)
    {
            wind.draw(vect[i]);
    }
}

void drawText(RenderWindow& wind, string input)
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
    searchCri.setCharacterSize(32);
    searchCri.setStyle(sf::Text::Bold);
    searchCri.setFillColor(sf::Color::Black);
    searchCri.setPosition(5, 30);
    //Delcares text for URL
    sf::Text URL_Text("Game Store Page", font);
    URL_Text.setCharacterSize(30);
    URL_Text.setStyle(sf::Text::Bold);
    URL_Text.setFillColor(sf::Color::Black);
    URL_Text.setPosition(850 - (Rating.getLocalBounds().width) - 25, 650);

    sf::Text Price("Price:", font);
    Price.setCharacterSize(35);
    Price.setStyle(sf::Text::Bold);
    Price.setFillColor(sf::Color::Black);
    Price.setPosition(20, 90);

    sf::Text Developer("Developer:", font);
    Developer.setCharacterSize(35);
    Developer.setStyle(sf::Text::Bold);
    Developer.setFillColor(sf::Color::Black);
    Developer.setPosition(20, 215);

    sf::Text Date("Date Published:", font);
    Date.setCharacterSize(30);
    Date.setStyle(sf::Text::Bold);
    Date.setFillColor(sf::Color::Black);
    Date.setPosition(20, 250);

    sf::Text BTreeText("B-Tree", font);
    BTreeText.setCharacterSize(40);
    BTreeText.setStyle(sf::Text::Bold);
    BTreeText.setFillColor(sf::Color::Black);
    BTreeText.setPosition(800, 100);

    sf::Text NaryText("N-Ary", font);
    NaryText.setCharacterSize(40);
    NaryText.setStyle(sf::Text::Bold);
    NaryText.setFillColor(sf::Color::Black);
    NaryText.setPosition(800, 160);

    sf::Text FreeText("Free", font);
    FreeText.setCharacterSize(28);
    FreeText.setStyle(sf::Text::Bold);
    FreeText.setFillColor(sf::Color::Black);
    FreeText.setPosition(25, 140);

    sf::Text Less5Text("$10", font);
    Less5Text.setCharacterSize(28);
    Less5Text.setStyle(sf::Text::Bold);
    Less5Text.setFillColor(sf::Color::Black);
    Less5Text.setPosition(100, 140);

    sf::Text LessNextText("$20", font);
    LessNextText.setCharacterSize(28);
    LessNextText.setStyle(sf::Text::Bold);
    LessNextText.setFillColor(sf::Color::Black);
    LessNextText.setPosition(178, 140);

    sf::Text bruh("$20+", font);
    bruh.setCharacterSize(28);
    bruh.setStyle(sf::Text::Bold);
    bruh.setFillColor(sf::Color::Black);
    bruh.setPosition(252, 140);

    sf::Text steamSort("Steam Sorter", font);
    steamSort.setCharacterSize(50);
    steamSort.setStyle(sf::Text::Bold);
    steamSort.setFillColor(sf::Color::Black);
    steamSort.setPosition(420, 20);


    sf::Text userIn(input, font);
    userIn.setCharacterSize(28);
    userIn.setStyle(sf::Text::Bold);
    userIn.setFillColor(sf::Color::Black);
    userIn.setPosition(25, 270);

    wind.draw(searchCri);
    wind.draw(Rating);
    wind.draw(URL_Text);
    wind.draw(Price);
    wind.draw(Developer);
    wind.draw(FreeText);
    wind.draw(Less5Text);
    wind.draw(BTreeText);
    wind.draw(NaryText);
    wind.draw(LessNextText);
    wind.draw(bruh);
    wind.draw(userIn);
    wind.draw(steamSort);
}

void drawGameList(RenderWindow& wind, vector<sf::Text>& vect)
{
    for (unsigned int i = 0; i < vect.size(); i++)
    {
        wind.draw(vect[i]);
    }
}

void ConfigData(string& _URL, string& name, string& _image_url, string& _allReviews, string& date, string& developer, string& _price, std::ifstream& readFile)
{
    string throwaway;
    if (readFile.is_open())
    {
    }
    std::getline(readFile, _URL, ',');  // Read up to the first comma
    std::getline(readFile, name, ',');
    std::getline(readFile, throwaway, ',');
    std::getline(readFile, _image_url, ',');
    std::getline(readFile, _allReviews, ',');
     if (_allReviews.find("No user") != std::string::npos)
    {

        _allReviews = "0";
    }
    else if (_allReviews.find("(") != std::string::npos)
    {
        string numReviews = _allReviews.substr(_allReviews.find("(") + 1, _allReviews.find(")") - _allReviews.find("(") - 1);
        int numReview = stoi(numReviews);
        string percent = _allReviews.substr(_allReviews.find("%") - 2, 2);
        int percentInt = stoi(percent);
        double truePrice = numReview * (percentInt);
        truePrice /= 100;
        numReviews = to_string(truePrice);
        _allReviews = numReviews;
    }
    
    
    std::getline(readFile, throwaway, ',');
    std::getline(readFile, date, ',');
    std::getline(readFile, developer, ',');
    std::getline(readFile, throwaway, ',');
    std::getline(readFile, _price, ',');
    if (_price.find("$") != std::string::npos)
    {
        if((_price.find(".") - _price.find("$")) == 3)
        {
            _price = _price.substr(_price.find("$")+1, 5);
        }
        else
        {
            _price = _price.substr(_price.find("$") + 1, 4);
        }
    }
    else if (_price.find("Free to") != std::string::npos)
    {
        if (_price.find("play") != std::string::npos)
        {
            _price = "0";

        }
    }
    else
    {
        _price = "0";
    }
    std::getline(readFile, throwaway);

}

vector<sf::Text> setGameList(sf::Font& fontt, vector<Node*> gameVecPoint)
{
    vector<sf::Text> vectorPush;
    sf::Text Game;
    //This sets the game list
    for (unsigned int i = 0; i < 5; i++)
    {
        Game.setFont(fontt);
        if (gameVecPoint.size() != 0)
        {
            Game.setString((to_string(i + 1) + gameVecPoint[i]->name));

            Game.setCharacterSize(35);
            Game.setStyle(sf::Text::Bold);
            Game.setFillColor(sf::Color::Black);
            Game.setPosition(50, 400 + (45 * i));
            vectorPush.push_back(Game);
        }
    }
    return vectorPush;
}

void dataProcessingLoop(string& _URL, string& name, string& _image_url, string& _allReviews, string& date, string& developer, string& _price, std::ifstream& readFile, BTree TreeB, NaryTree TreeN)
{
    for (unsigned int i = 0; i < 50; i++) {
        // Assuming you have the necessary variables and functions declared
        ConfigData(_URL, name, _image_url, _allReviews, date, developer, _price, readFile);
        TreeB.Insert(stod(_allReviews), _image_url, name, date, developer, stod(_price));
        TreeN.insert(stod(_allReviews), _image_url, name, date, developer, stod(_price));
    }
}

void drawButtons(RenderWindow& wind, sf::Color firstButton, sf::Color secondButton, sf::Color freeButton, sf::Color firstPriceButton, sf::Color secondPriceButton, sf::Color thirdPriceButton)
{
    sf::RectangleShape rectanglebTree;
    // Set the size of the rectangle
    rectanglebTree.setSize(sf::Vector2f(175.f, 55.f));
    // Set the position of the rectangle
    rectanglebTree.setPosition(790.f, 100.f);
    // Set the fill color of the rectangle
    rectanglebTree.setFillColor(firstButton);

    sf::RectangleShape rectanglenaryTree;
    // Set the size of the rectangle
    rectanglenaryTree.setSize(sf::Vector2f(175.f, 55.f));
    // Set the position of the rectangle
    rectanglenaryTree.setPosition(790.f, 160.f);
    // Set the fill color of the rectangle
    rectanglenaryTree.setFillColor(secondButton);

    sf::RectangleShape rectangleGameList;
    rectangleGameList.setSize(sf::Vector2f(525.f, 285.f));
    rectangleGameList.setPosition(40.f, 390.f);
    rectangleGameList.setFillColor(sf::Color(125, 125, 125));
    
    sf::RectangleShape rectangleFree;
    rectangleFree.setSize(sf::Vector2f(75.f, 50.f));
    rectangleFree.setPosition(20.f, 135.f);
    rectangleFree.setFillColor(sf::Color(freeButton));
    //Creates rectangle for the free button
    sf::RectangleShape rectangleFiveLess;
    rectangleFiveLess.setSize(sf::Vector2f(75.f, 50.f));
    rectangleFiveLess.setPosition(95.f, 135.f);
    rectangleFiveLess.setFillColor(sf::Color(firstPriceButton));

    //Creates rectangle for the $10 button
    sf::RectangleShape rectangleNext;
    rectangleNext.setSize(sf::Vector2f(75.f, 50.f));
    rectangleNext.setPosition(170.f, 135.f);
    rectangleNext.setFillColor(sf::Color(secondPriceButton));

    //Creates rectangle for the search button
    sf::RectangleShape rectangleSearch;
    rectangleSearch.setSize(sf::Vector2f(350.f, 60.f));
    rectangleSearch.setPosition(25.f, 270.f);
    rectangleSearch.setFillColor(sf::Color(220,220,220));

    //Creates rectangle for the $20 button
    sf::RectangleShape rectangleNextN;
    rectangleNextN.setSize(sf::Vector2f(75.f, 50.f));
    rectangleNextN.setPosition(245.f, 135.f);
    rectangleNextN.setFillColor(sf::Color(thirdPriceButton));

    //Delimiter for price buttons
    sf::RectangleShape firstVertBar;
    firstVertBar.setSize(sf::Vector2f(3.f, 50.f));
    firstVertBar.setPosition(95.f, 135.f);
    firstVertBar.setFillColor(sf::Color::White);
    //Delimiter for price buttons
    sf::RectangleShape secondVertBar;
    secondVertBar.setSize(sf::Vector2f(3.f, 50.f));
    secondVertBar.setPosition(170.f, 135.f);
    secondVertBar.setFillColor(sf::Color::White);
    //Delimiter for price buttons
    sf::RectangleShape thirdVertBar;
    thirdVertBar.setSize(sf::Vector2f(3.f, 50.f));
    thirdVertBar.setPosition(245.f, 135.f);
    thirdVertBar.setFillColor(sf::Color::White);

    wind.draw(rectanglebTree);
    wind.draw(rectanglenaryTree);
    wind.draw(rectangleGameList);
    wind.draw(rectangleFree);
    wind.draw(rectangleFiveLess);
    wind.draw(rectangleNext);
    wind.draw(rectangleNextN);
    wind.draw(firstVertBar);
    wind.draw(secondVertBar);
    wind.draw(thirdVertBar);
    wind.draw(rectangleSearch);

}
