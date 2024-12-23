#include "traffic_lights.hpp"

void drawTrafficLights1(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape redLight(sf::Vector2f(20, 20));
    redLight.setFillColor(sf::Color::Red);
    redLight.setPosition(x, y);

    sf::RectangleShape yellowLight(sf::Vector2f(20, 20));
    yellowLight.setFillColor(sf::Color::Yellow);
    yellowLight.setPosition(x, y + 20);

    sf::RectangleShape greenLight(sf::Vector2f(20, 20));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x, y + 40);


    window.draw(greenLight);
    window.draw(yellowLight);
    window.draw(redLight);
}



void drawTrafficLights2(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape redLight(sf::Vector2f(20, 20));
    redLight.setFillColor(sf::Color::Red);
    redLight.setPosition(x, y + 40);

    sf::RectangleShape yellowLight(sf::Vector2f(20, 20));
    yellowLight.setFillColor(sf::Color::Yellow);
    yellowLight.setPosition(x, y + 20);

    sf::RectangleShape greenLight(sf::Vector2f(20, 20));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x, y);


    window.draw(redLight);
    window.draw(yellowLight);
    window.draw(greenLight);
}


void drawTrafficLights3(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape redLight(sf::Vector2f(20, 20));
    redLight.setFillColor(sf::Color::Red);
    redLight.setPosition(x, y);

    sf::RectangleShape yellowLight(sf::Vector2f(20, 20));
    yellowLight.setFillColor(sf::Color::Yellow);
    yellowLight.setPosition(x + 20, y);

    sf::RectangleShape greenLight(sf::Vector2f(20, 20));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x + 40, y);


    window.draw(greenLight);
    window.draw(yellowLight);
    window.draw(redLight);
}



void drawTrafficLights4(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape redLight(sf::Vector2f(20, 20));
    redLight.setFillColor(sf::Color::Red);
    redLight.setPosition(x + 40, y);

    sf::RectangleShape yellowLight(sf::Vector2f(20, 20));
    yellowLight.setFillColor(sf::Color::Yellow);
    yellowLight.setPosition(x + 20, y);

    sf::RectangleShape greenLight(sf::Vector2f(20, 20));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x, y);


    window.draw(greenLight);
    window.draw(yellowLight);
    window.draw(redLight);
}

