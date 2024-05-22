#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>

#define WIDTH 50
#define HEIGHT 11
#define JUMP_HEIGHT 5

int gameOver;
int score;
int dinoX, dinoY;
int cactusX, cactusY;
bool isJumping; // Variable to track if the dino is currently jumping
int jumpCounter; // Variable to manage the jump height

void setup() {
    gameOver = 0;
    score = 0;
    dinoX = 5;
    dinoY = HEIGHT - 2; // Dino starting position
    cactusX = WIDTH - 5;
    cactusY = HEIGHT - 2; // Cactus starting position, same as dinoY
    isJumping = false; // Initialize the jumping state
    jumpCounter = 0; // Initialize the jump counter
}

void draw() {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == dinoY && j == dinoX) // Draw dino
                std::cout << "R";
            else if (i == cactusY && j == cactusX) // Draw cactus
                std::cout << "+";
            else if (i == HEIGHT - 1) // Draw continuous ground line
                std::cout << "_";
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\nScore: " << score << "\n";
}

void input() {
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !isJumping) { // Check space bar input and if not already jumping
        isJumping = true;
        jumpCounter = JUMP_HEIGHT; // Start the jump
    }
}

void jump() {
    if (isJumping) {
        if (jumpCounter > 0) {
            dinoY--; // Move dino up
            jumpCounter--;
        } else {
            isJumping = false;
        }
    }
}

void update() {
    if (!isJumping && dinoY < HEIGHT - 2) {
        dinoY++; // Gravity effect: bring dino back to the ground
    }
    cactusX--;
    if (cactusX <= 0) {
        cactusX = WIDTH - 5;
        score++;
    }

    // Improved collision detection
    if ((dinoX == cactusX) && (dinoY == cactusY)) {
        gameOver = 1;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        jump(); // Call jump to handle jumping logic
        update();
        Sleep(150); // Reduced sleep time for a more realistic game speed
    }
    std::cout << "\nGame Over! Final Score: " << score << "\n";
    return 0;
}
