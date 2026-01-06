#include "glDraw.h"
#include <cstring> // for memcpy

// -------------------- Setup / Restore --------------------
void GL::SetupOrtho()
{
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, viewport[2], viewport[3], 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
}

void GL::Restore()
{
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

// -------------------- Draw functions --------------------
void GL::DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
    glColor4ub(color[0], color[1], color[2], 255);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
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

void GL::DrawCrosshair(vec2& l1p1, vec2& l1p2, vec2& l2p1, vec2& l2p2, float lineWidth, const GLubyte color[3])
{
    glLineWidth(lineWidth);
    glColor4ub(color[0], color[1], color[2], 255);
    glBegin(GL_LINES);
    glVertex2f(l1p1.x, l1p1.y);
    glVertex2f(l1p2.x, l1p2.y);
    glVertex2f(l2p1.x, l2p1.y);
    glVertex2f(l2p2.x, l2p2.y);
    glEnd();
}

void GL::DrawESPBox(vec2 head, vec2 feet, float lineWidth, const GLubyte color[3])
{
    int height = std::abs(feet.y - head.y);
    vec2 tl = { head.x - height / 4.0f, head.y };
    vec2 tr = { head.x + height / 4.0f, head.y };
    vec2 bl = { feet.x - height / 4.0f, feet.y };
    vec2 br = { feet.x + height / 4.0f, feet.y };

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
bool GL::WorldToScreen(vec3 pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight)
{
    vec4 clip;
    clip.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8]  + matrix[12];
    clip.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9]  + matrix[13];
    clip.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    clip.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    if (clip.w < 0.1f) return false;

    vec3 ndc;
    ndc.x = clip.x / clip.w;
    ndc.y = clip.y / clip.w;
    ndc.z = clip.z / clip.w;

    screen.x = (windowWidth / 2.0f * ndc.x) + (ndc.x + windowWidth / 2.0f);
    screen.y = -(windowHeight / 2.0f * ndc.y) + (ndc.y + windowHeight / 2.0f);

    return true;
}
