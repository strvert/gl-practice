#ifndef __GL_GAME_GAME_H
#define __GL_GAME_GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class GameState
{
    ACTIVE,
    MENU,
    WIN,
};

class Game
{
public:
    GameState State;
    GLboolean Keys[1024];
    GLuint Width, Height;
    
    Game(GLuint width, GLuint height);
    ~Game();

    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};

#endif // __GL_GAME_GAME_H
