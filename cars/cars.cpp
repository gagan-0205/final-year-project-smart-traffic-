#include "cars.hpp"

const float SPAWN_DELAY = 1.0f; // Increase spawn delay for slower spawn frequency (in seconds)
const int MAX_CARS_PER_INTERVAL = 1; // Adjust the maximum number of cars spawned per interval
const float MIN_SPEED = 200.0f; // Minimum speed for cars
const float MAX_SPEED = 250.0f; // Maximum speed for cars

void spawnCars(std::vector<Car>& cars, float dt) {
    static float elapsedTime = 0.0f; // Move elapsedTime to a static variable

    elapsedTime += dt;

    if (elapsedTime >= SPAWN_DELAY) {
        int numCars = rand() % (MAX_CARS_PER_INTERVAL + 1); // Randomize the number of cars spawned within the limit
        for (int i = 0; i < numCars; ++i) {
            Car car;
            car.shape.setSize(sf::Vector2f(80, 60));
            car.shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            car.speed = static_cast<float>((rand() % static_cast<int>((MAX_SPEED - MIN_SPEED) * 100)) + (MIN_SPEED * 100)) / 100; // Random speed between MIN_SPEED and MAX_SPEED
            car.moveRight = rand() % 2 == 0; // Random direction of movement
            if (car.moveRight)
                car.shape.setPosition(-30, 420); // Start from left at lane 420
            else
                car.shape.setPosition(1030, 520); // Start from right at lane 500
            cars.push_back(car);
        }
        elapsedTime = 0.0f;
    }
}

void updateCars(std::vector<Car>& cars, float dt) {
    for (auto& car : cars) {
        if (car.moveRight)
            car.shape.move(car.speed * dt, 0); // Move right
        else
            car.shape.move(-car.speed * dt, 0); // Move left
    }
}

void drawCars(sf::RenderWindow& window, const std::vector<Car>& cars) {
    for (const auto& car : cars) {
        window.draw(car.shape);
    }
}

