#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <cmath>

class MovementHandler {
public:
    MovementHandler() : posX(0.0f), posY(0.0f), rotation(0.0f), moveUp(false), moveDown(false), moveLeft(false), moveRight(false) {}

    void update(float deltaTime) {
        if (moveUp) posY += speed * deltaTime;
        if (moveDown) posY -= speed * deltaTime;
        if (moveLeft) posX -= speed * deltaTime;
        if (moveRight) posX += speed * deltaTime;
    }

    void setMoveUp(bool value) { moveUp = value; }
    void setMoveDown(bool value) { moveDown = value; }
    void setMoveLeft(bool value) { moveLeft = value; }
    void setMoveRight(bool value) { moveRight = value; }
    void rotate(float deltaX) { rotation += deltaX * rotationSpeed; }

    void getTransformationMatrix(float matrix[16]) const {
        float cosR = cos(rotation);
        float sinR = sin(rotation);

        matrix[0] = cosR; matrix[4] = -sinR; matrix[8] = 0.0f; matrix[12] = posX;
        matrix[1] = sinR; matrix[5] = cosR;  matrix[9] = 0.0f; matrix[13] = posY;
        matrix[2] = 0.0f; matrix[6] = 0.0f;  matrix[10] = 1.0f; matrix[14] = 0.0f;
        matrix[3] = 0.0f; matrix[7] = 0.0f;  matrix[11] = 0.0f; matrix[15] = 1.0f;
    }

private:
    float posX, posY;
    float rotation;
    bool moveUp, moveDown, moveLeft, moveRight;
    const float speed = 0.1f;
    const float rotationSpeed = 0.01f;
};

#endif // MOVEMENT_H