#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Define a structure for a car
typedef struct {
    float x;
    float y;
    float speed;
    float size; // Size of the car (width and height)
    int direction; // 0: left, 1: right, 2: up, 3: down
    float red;
    float green;
    float blue;
} Car;

Car cars[3]; // Array to store the three types of cars
int numCars = 0; // Number of currently active cars

void drawCarH(float x, float y, float size, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size / 2);
    glVertex2f(x, y + size / 2);
    glEnd();
}

void drawCarV(float x, float y, float size, float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size / 2, y);
    glVertex2f(x + size / 2, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

void drawRoad(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void removeOutOfViewCars() {
    int i = 0;
    while (i < numCars) {
        if (cars[i].x < -20 || cars[i].x > 20 || cars[i].y < -20 || cars[i].y > 20) {
            // Car is out of the viewport, remove it from the array
            for (int j = i; j < numCars - 1; ++j) {
                cars[j] = cars[j + 1];
            }
            numCars--;
        } else {
            i++;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw black background
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Draw horizontal road extending to the edges of the window
    glColor3f(0.3, 0.3, 0.3);
    drawRoad(-5, -15, 5, 15);
    drawRoad(-15, -5, 15, 5);

    // Draw dividers
    glColor3f(1.0, 1.0, 1.0);
    drawRoad(-0.2, -15, 0.2, -5);
    drawRoad(-0.2, 15, 0.2, 5);
    drawRoad(-15, -0.2, -5, 0.2);
    drawRoad(15, -0.2, 5, 0.2);

    // Draw cars
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].direction == 0 || cars[i].direction == 1) { // Left or Right
            drawCarH(cars[i].x, cars[i].y, cars[i].size, cars[i].red, cars[i].green, cars[i].blue);
        } else { // Up or Down
            drawCarV(cars[i].x, cars[i].y, cars[i].size, cars[i].red, cars[i].green, cars[i].blue);
        }
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set initial clear color to black
    gluOrtho2D(-15, 15, -15, 15); // Adjusted viewing area
}

void spawnCar(int direction) {
    if (numCars >= 3) return;

    float x, y;
    float speed = 0.3;
    float size = 7;

    // Determine spawn position based on direction
    if (direction == 0) { // Left
        x = 15;
        y = -4;
    } else if (direction == 1) { // Right
        x = -15;
        y = 1;
    } else if (direction == 2) { // Up
        x = 1;
        y = -15;
    } else if (direction == 3) { // Down
        x = -4;
        y = 15;
    }

    // Generate random RGB values with higher saturation
    float red = ((rand() % 256) + 128) / 256.0;
    float green = ((rand() % 256) + 128) / 256.0;
    float blue = ((rand() % 256) + 128) / 256.0;

    // Add the car to the array
    cars[numCars++] = (Car){x, y, speed, size, direction, red, green, blue};

    // Print RGB values for debugging
    printf("Red: %f, Green: %f, Blue: %f\n", red, green, blue);
}

void update(int value) {
    // Remove cars that are out of view
    removeOutOfViewCars();

    // Move the cars
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].direction == 0) { // Left
            cars[i].x -= cars[i].speed;
        } else if (cars[i].direction == 1) { // Right
            cars[i].x += cars[i].speed;
        } else if (cars[i].direction == 2) { // Up
            cars[i].y += cars[i].speed;
        } else if (cars[i].direction == 3) { // Down
            cars[i].y -= cars[i].speed;
        }
    }

    glutPostRedisplay();

    // Call update function again after a delay
    glutTimerFunc(50, update, 0); // Reduced delay for smoother frame rate
}

// Function to handle arrow key presses
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: // Up arrow key
            spawnCar(2); // Spawn a car moving up
            break;
        case GLUT_KEY_DOWN: // Down arrow key
            spawnCar(3); // Spawn a car moving down
            break;
        case GLUT_KEY_LEFT: // Left arrow key
            spawnCar(0); // Spawn a car moving left
            break;
        case GLUT_KEY_RIGHT: // Right arrow key
            spawnCar(1); // Spawn a car moving right
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 1200); // Adjusted window size
    glutCreateWindow("TRAFFIC SIMULATOR");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0); // Start the update function with a reduced delay

    // Register the specialKeys function to handle arrow key presses
    glutSpecialFunc(specialKeys);

    glutMainLoop();

    return 0;
}

