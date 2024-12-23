#ifndef CARS_HPP
#define CARS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct Car {
    sf::RectangleShape shape;
    sf::Color color;
    float speed;
    bool moveRight; // Added to determine direction of movement
};

void spawnCars(std::vector<Car>& cars, float dt); // Updated function signature
void updateCars(std::vector<Car>& cars, float dt);
void drawCars(sf::RenderWindow& window, const std::vector<Car>& cars);

#endif

