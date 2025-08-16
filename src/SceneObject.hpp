#pragma once

class SceneObject
{
private:
    /* data */
public:
    ~SceneObject() = default;
    virtual void render(SDL_Surface *surface,Uint32 color) const = 0;
};