#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(glm::vec3 pos, glm::vec3 orientation, float fov, float aspectRatio);
        void update();
        void handleMouse(float xPos, float yPos, float deltaTime);
        void handleScroll(float xOffset, float yOffset, float deltaTime);
        void handleKeyboard(int KEY, float deltaTime);
        void updateCameraAspectRatio(float ar);
        glm::mat4& getViewMatrix();
        glm::mat4& getProjectionMatrix();
        
        glm::vec3 worldCoord;
        glm::vec3 cameraFrontDirection;
        const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        float fieldOfView;
        float aspectRatio;
        float minFrustum = 0.01f;
        float maxFrustum = 10000.0f;	// For the projection matrix

        float roll, pitch, yaw;
        float lastXPos = 0, lastYPos = 0;
        float minZoom = 0.01f;
        float maxZoom = 90.0f;
        float lookSensitivity = 0.01f;
        float zoomSensitivity = 0.05f;
        float movementSpeed = 200;
};

#endif
