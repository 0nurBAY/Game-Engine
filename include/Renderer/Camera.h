//Camera.h

#pragma once
#include <glm/glm.hpp>
#include "PerlinNoise.hpp"

class Camera
{
private:
    glm::vec3 Baseposition;
    glm::vec3 position;
    float rotation;
    float zoom;
    float width;
    float height;
    float resW;
    float resH;

    float worldWidth;
    float worldHeight;
    float worldLeft;
    float worldRight;
    float worldBottom;
    float worldTop;

    
    float shakeMagnnitude=2.0f;
    float shakeDuration=0.0f;
    float shakeTime =0.0f;
    float frequency = 30.0f;
    glm::vec3 shakeOffset = glm::vec3(0.0f);
    const siv::PerlinNoise::seed_type seed = 52534;
    const siv::PerlinNoise perlin {seed};

public:
    Camera(float width, float height);
    void Update(float dt);
    void SetPosition(const glm::vec3& new_position);
    void SetRotation(const float& new_rotation);
    void SetZoom    (const float& new_zoom);
    void SetSize(float width, float height,float w, float h);
    void SetWorldSize(float width, float height, float r, float l, float t, float b);
    glm::vec2 ScreentoWorld(float ScreenX,float ScreenY);
    glm::vec2 ScreentoWorld(glm::vec2 ScreenPos);
    glm::vec2 WorldToScreen(float WindowX,float WindowY);
    glm::vec2 WorldToScreen(glm::vec2 WindowPos);
    glm::vec3 GetPosition() const;
    float GetRotation() const;
    float GetZoom    () const;
    float GetWidth   () const;
    float GetHeight  () const;
    float GetResW    () const;
    float GetResH    () const;

    float GetMagnitude    () const;
    float GetShakeDuration() const;
    void  Shake(float strength=10.0f, float duration=0.5f);

    float GetWorldWidthAspect   ();
    float GetWorldHeightAspect  ();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

};

