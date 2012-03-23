#ifndef OGL_INCLUDES_H
#define OGL_INCLUDES_H
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
void draw_square(float x, float y, float width) {
    float hw = width / 2;
    glBegin(GL_LINES);
    //TOP
    glVertex2f(x - hw, y - hw);
    glVertex2f(x + hw, y - hw);
    //bottom
    glVertex2f(x - hw, y + hw);
    glVertex2f(x + hw, y + hw);
    //left
    glVertex2f(x - hw, y + hw);
    glVertex2f(x - hw, y - hw);
    //right
    glVertex2f(x + hw, y + hw);
    glVertex2f(x + hw, y - hw);
    glEnd();
}
#endif //OGL_INCLUDES_H