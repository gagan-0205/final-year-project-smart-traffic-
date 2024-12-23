#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

class Car {
public:
    sf::RectangleShape shape;
    float speed;
    bool horizontal; 
    float originalSpeed;

    Car(float x, float y, float speed, sf::Color color, bool horizontal) {
        shape.setSize(horizontal ? sf::Vector2f(50, 35) : sf::Vector2f(35, 50));
        shape.setPosition(x, y);
        shape.setFillColor(color);
        this->speed = speed;
        this->originalSpeed = speed;
        this->horizontal = horizontal;
    }

    void update(float deltaTime) {
        if (horizontal) {
            shape.move(speed * deltaTime, 0);  
        } else {
            shape.move(0, speed * deltaTime);  
        }
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    void restoreSpeed() {
        speed = originalSpeed;
    }
};

void spawnCars(std::vector<Car*>& cars, float deltaTime, bool canSpawnHorizontal, bool canSpawnVertical) {
    static float spawnTimer = 0.0f;
    spawnTimer += deltaTime;

    if (spawnTimer >= 1.5f) {
        float speed = (std::rand() % 100) + 50;
        sf::Color color(rand() % 256, rand() % 256, rand() % 256);

        if (canSpawnHorizontal && std::rand() % 2 == 0) {
            cars.push_back(new Car(0, 450, speed, color, true));  // Left to right
        } 
        else if (canSpawnHorizontal) {
            cars.push_back(new Car(1000, 550, -speed, color, true));  // Right to left
        }

        if (canSpawnVertical && std::rand() % 2 == 0) {
            cars.push_back(new Car(550, 0, speed, color, false));  // Top to bottom
        } 
        else if (canSpawnVertical) {
            cars.push_back(new Car(450, 1000, -speed, color, false));  // Bottom to top
        }

        spawnTimer = 0.0f;
    }
}

bool checkCarsApproaching(const std::vector<Car*>& cars, bool horizontal) {
    for (const auto& car : cars) {
        if (horizontal && car->getPosition().x >= 300 && car->getPosition().x <= 600 && car->getPosition().y == 450) {
            return true;  // Cars are approaching horizontally
        }
        if (!horizontal && car->getPosition().y >= 300 && car->getPosition().y <= 600 && (car->getPosition().x == 450 || car->getPosition().x == 550)) {
            return true;  // Cars are approaching vertically
        }
    }
    return false;
}

void updateCars(std::vector<Car*>& cars, float deltaTime, bool light1Red, bool light2Red) {
    float safeDistance = 60.0f;  

    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i]->horizontal) {
            float carPosX = cars[i]->getPosition().x;

            // Stop horizontal cars at red lights
            if ((carPosX >= 350 && carPosX <= 400 && light1Red && cars[i]->getPosition().y == 450) ||
                (carPosX >= 600 && carPosX <= 650 && light2Red && cars[i]->getPosition().y == 550)) {
                cars[i]->setSpeed(0);  // Stop the car
            } else {
                cars[i]->restoreSpeed();  // Resume speed when green
            }
        } else {
            float carPosY = cars[i]->getPosition().y;

            // Stop vertical cars at red lights
            if ((carPosY >= 350 && carPosY <= 400 && light1Red && (cars[i]->getPosition().x == 450 || cars[i]->getPosition().x == 550)) ||
                (carPosY >= 600 && carPosY <= 650 && light2Red && (cars[i]->getPosition().x == 450 || cars[i]->getPosition().x == 550))) {
                cars[i]->setSpeed(0);  // Stop the car
            } else {
                cars[i]->restoreSpeed();  // Resume speed when green
            }
        }

        // Check for cars ahead in the same lane and adjust speed
        for (size_t j = 0; j < cars.size(); ++j) {
            if (i == j) continue;

            if ((cars[i]->horizontal && cars[j]->horizontal && cars[i]->getPosition().y == cars[j]->getPosition().y) ||
                (!cars[i]->horizontal && !cars[j]->horizontal && cars[i]->getPosition().x == cars[j]->getPosition().x)) {

                if ((cars[i]->speed > 0 && cars[i]->horizontal && cars[i]->getPosition().x < cars[j]->getPosition().x && cars[j]->getPosition().x - cars[i]->getPosition().x < safeDistance) ||
                    (cars[i]->speed > 0 && !cars[i]->horizontal && cars[i]->getPosition().y < cars[j]->getPosition().y && cars[j]->getPosition().y - cars[i]->getPosition().y < safeDistance) ||
                    (cars[i]->speed < 0 && cars[i]->horizontal && cars[i]->getPosition().x > cars[j]->getPosition().x && cars[i]->getPosition().x - cars[j]->getPosition().x < safeDistance) ||
                    (cars[i]->speed < 0 && !cars[i]->horizontal && cars[i]->getPosition().y > cars[j]->getPosition().y && cars[i]->getPosition().y - cars[j]->getPosition().y < safeDistance)) {
                    
                    cars[i]->setSpeed(cars[j]->speed);
                }
            }
        }

        cars[i]->update(deltaTime);

        if (cars[i]->horizontal && (cars[i]->getPosition().x > 1000 || cars[i]->getPosition().x < -50) || 
            !cars[i]->horizontal && (cars[i]->getPosition().y > 1000 || cars[i]->getPosition().y < -50)) {
            delete cars[i];
            cars.erase(cars.begin() + i);
            --i;
        }
    }
}

void updateTrafficLights(bool& light1Red, bool& light2Red, const std::vector<Car*>& cars) {
    // Green light if cars are approaching, red light if the lane is empty
    light1Red = !checkCarsApproaching(cars, true);  // Horizontal lane
    light2Red = !checkCarsApproaching(cars, false);  // Vertical lane
}

// Traffic light drawing functions (same as the original code)
void drawTrafficLights1(sf::RenderWindow& window, float x, float y, bool isRed) {
    sf::CircleShape redLightGlow(20);
    redLightGlow.setFillColor(sf::Color(255, 0, 0, isRed ? 150 : 50));
    redLightGlow.setPosition(x - 10, y - 10);
    window.draw(redLightGlow);

    sf::RectangleShape redLight(sf::Vector2f(30, 35));
    redLight.setFillColor(isRed ? sf::Color::Red : sf::Color(100, 0, 0));
    redLight.setPosition(x, y);
    window.draw(redLight);

    sf::RectangleShape yellowLight(sf::Vector2f(30, 40));
    yellowLight.setFillColor(sf::Color(255, 255, 0));
    yellowLight.setPosition(x, y + 35);
    window.draw(yellowLight);

    sf::RectangleShape greenLight(sf::Vector2f(30, 32));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x, y + 70);
    window.draw(greenLight);
}

void drawTrafficLights2(sf::RenderWindow& window, float x, float y, bool isRed) {
    y += -30;

    sf::CircleShape redLightGlow(20);
    redLightGlow.setFillColor(sf::Color(255, 0, 0, isRed ? 150 : 50));
    redLightGlow.setPosition(x - 10, y - 10);
    window.draw(redLightGlow);

    sf::RectangleShape redLight(sf::Vector2f(30, 35));
    redLight.setFillColor(isRed ? sf::Color::Red : sf::Color(100, 0, 0));
    redLight.setPosition(x, y);
    window.draw(redLight);

    sf::RectangleShape yellowLight(sf::Vector2f(30, 40));
    yellowLight.setFillColor(sf::Color(255, 255, 0));
    yellowLight.setPosition(x, y + 35);
    window.draw(yellowLight);

    sf::RectangleShape greenLight(sf::Vector2f(30, 32));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x, y + 70);
    window.draw(greenLight);
}

void drawTrafficLights3(sf::RenderWindow& window, float x, float y, bool isRed) {
    x += 30;

    sf::CircleShape redLightGlow(20);
    redLightGlow.setFillColor(sf::Color(255, 0, 0, isRed ? 150 : 50));
    redLightGlow.setPosition(x - 10, y - 10);
    window.draw(redLightGlow);

    sf::RectangleShape redLight(sf::Vector2f(30, 35));
    redLight.setFillColor(isRed ? sf::Color::Red : sf::Color(100, 0, 0));
    redLight.setPosition(x, y);
    redLight.setRotation(90);
    window.draw(redLight);
    
    sf::RectangleShape yellowLight(sf::Vector2f(30, 37));
    yellowLight.setFillColor(sf::Color(255, 255, 0));
    yellowLight.setPosition(x + 35, y);
    yellowLight.setRotation(90);
    window.draw(yellowLight);

    sf::RectangleShape greenLight(sf::Vector2f(30, 35));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x + 70, y);
    greenLight.setRotation(90);
    window.draw(greenLight);
}

void drawTrafficLights4(sf::RenderWindow& window, float x, float y, bool isRed) {
    y += -30;

    sf::CircleShape redLightGlow(20);
    redLightGlow.setFillColor(sf::Color(255, 0, 0, isRed ? 150 : 50));
    redLightGlow.setPosition(x - 10, y - 10);
    window.draw(redLightGlow);

    sf::RectangleShape redLight(sf::Vector2f(30, 35));
    redLight.setFillColor(isRed ? sf::Color::Red : sf::Color(100, 0, 0));
    redLight.setPosition(x, y);
    redLight.setRotation(90);
    window.draw(redLight);

    sf::RectangleShape yellowLight(sf::Vector2f(30, 35));
    yellowLight.setFillColor(sf::Color(255, 255, 0));
    yellowLight.setPosition(x + 35, y);
    yellowLight.setRotation(90);
    window.draw(yellowLight);

    sf::RectangleShape greenLight(sf::Vector2f(30, 35));
    greenLight.setFillColor(sf::Color::Green);
    greenLight.setPosition(x + 70, y);
    greenLight.setRotation(90);
    window.draw(greenLight);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Traffic Light Simulation");

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RectangleShape hor_road(sf::Vector2f(1000, 200));
    sf::RectangleShape hor_div(sf::Vector2f(1000, 10));
    hor_road.setFillColor(sf::Color(100, 100, 100));
    hor_div.setFillColor(sf::Color(200, 200, 200));
    hor_road.setPosition(0, 400);
    hor_div.setPosition(0, 500);

    sf::RectangleShape ver_road(sf::Vector2f(200, 1000));
    sf::RectangleShape ver_div(sf::Vector2f(10, 400));
    sf::RectangleShape ver_div2(sf::Vector2f(10, 400));
    ver_road.setFillColor(sf::Color(100, 100, 100));
    ver_div.setFillColor(sf::Color(200, 200, 200));
    ver_div2.setFillColor(sf::Color(200, 200, 200));
    ver_road.setPosition(400, 0);
    ver_div.setPosition(500, 0);
    ver_div2.setPosition(500, 600);

    std::vector<Car*> cars;

    sf::Clock clock;

    bool light1Red = true;
    bool light2Red = true;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        spawnCars(cars, deltaTime, true, true);
        updateCars(cars, deltaTime, light1Red, light2Red);
        updateTrafficLights(light1Red, light2Red, cars);

        window.clear();

        window.draw(hor_road);
        window.draw(hor_div);
        window.draw(ver_road);
        window.draw(ver_div);
        window.draw(ver_div2);

        for (const auto& car : cars) {
            window.draw(car->shape);
        }

        drawTrafficLights1(window, 400, 400, light1Red); 
        drawTrafficLights2(window, 600, 540, light2Red); 
        drawTrafficLights3(window, 400, 600, light1Red); 
        drawTrafficLights4(window, 540, 400, light2Red); 

        window.display();
    }

    for (auto car : cars) {
        delete car;
    }

    return 0;
}

