#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
    private:
        void updateCameraVectors(){
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up = glm::normalize(glm::cross(Right, Front));
        }
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up; 
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;

        Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f) {
            Position = position; 
            WorldUp = up; 
            Yaw = yaw; 
            Pitch = pitch; 
            updateCameraVectors();
          }

          glm::mat4 GetViewMatrix(){
            return glm::lookAt(Position, Position + Front, Up);
          }

          void ProcessKeyboard(Camera_Movement direction, float deltaTime){
            float velocity = MovementSpeed * deltaTime;
            if(direction == FORWARD) // Forward
                Position += Front * velocity;
            if(direction == BACKWARD) // Backward
                Position -= Front * velocity;
            if(direction == LEFT) // Left
                Position -= Right * velocity;
            if (direction == RIGHT) // Right
                Position += Right * velocity;
          }

          void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true){
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw += xoffset;
            Pitch += yoffset;

            if(constrainPitch){
                if(Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }
            updateCameraVectors();
          }
};

#endif // CAMERA_H