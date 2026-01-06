#include "glDraw.h"
#include <string.h> // for memcpy
#include <stdlib.h> // for abs / fabsf

// -------------------- init --------------------
void GL_Init(GL_t* gl)
{
    gl->red[0]   = 255; gl->red[1]   = 0;   gl->red[2]   = 0;
    gl->green[0] = 0;   gl->green[1] = 255; gl->green[2] = 0;
    gl->blue[0]  = 0;   gl->blue[1]  = 0;   gl->blue[2]  = 255;
}

// -------------------- 2D overlay --------------------
void GL_SetupOrtho(GL_t* gl)
{
    glGetIntegerv(GL_VIEWPORT, gl->viewport);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, gl->viewport[2], gl->viewport[3], 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
}

void GL_Restore(GL_t* gl)
{
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

// -------------------- Draw functions --------------------
void GL_DrawFilledRect(float x, float y, float width, float height, GLubyte color[3])
{
    glColor4ub(color[0], color[1], color[2], 255);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void GL_DrawOutline(float x, float y, float width, float height, float lineWidth, GLubyte color[3])
{
    glLineWidth(lineWidth);
    glColor4ub(color[0], color[1], color[2], 255);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void GL_DrawCrosshair(vec2 l1p1, vec2 l1p2, vec2 l2p1, vec2 l2p2, float lineWidth, GLubyte color[3])
{
    glLineWidth(lineWidth);
    glColor4ub(color[0], color[1], color[2], 255);
    glBegin(GL_LINES);
    glVertex2f(l1p1.x, l1p1.y); glVertex2f(l1p2.x, l1p2.y);
    glVertex2f(l2p1.x, l2p1.y); glVertex2f(l2p2.x, l2p2.y);
    glEnd();
}

void GL_DrawESPBox(vec2 head, vec2 feet, float lineWidth, GLubyte color[3])
{
    float height = fabsf(feet.y - head.y);
    vec2 tl = { head.x - height/4.0f, head.y };
    vec2 tr = { head.x + height/4.0f, head.y };
    vec2 bl = { feet.x - height/4.0f, feet.y };
    vec2 br = { feet.x + height/4.0f, feet.y };

    glLineWidth(lineWidth);
    glColor4ub(color[0], color[1], color[2], 255);
    glBegin(GL_LINE_LOOP);
    glVertex2f(tl.x, tl.y);
    glVertex2f(tr.x, tr.y);
    glVertex2f(br.x, br.y);
    glVertex2f(bl.x, bl.y);
    glEnd();
}

// -------------------- WorldToScreen --------------------
int GL_WorldToScreen(vec3 pos, vec2* screen, float matrix[16], int windowWidth, int windowHeight)
{
    float clipX = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8]  + matrix[12];
    float clipY = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9]  + matrix[13];
    float clipZ = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    float clipW = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clipW < 0.1f) return 0;

    float ndcX = clipX / clipW;
    float ndcY = clipY / clipW;

    screen->x = (windowWidth  / 2.0f * ndcX) + (ndcX + windowWidth  / 2.0f);
    screen->y = -(windowHeight / 2.0f * ndcY) + (ndcY + windowHeight / 2.0f);

    return 1;
}
