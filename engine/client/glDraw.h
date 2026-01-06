#pragma once
#include <GL/gl.h>
#include <cmath>
#include <vector>

// minimal vector structs
struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct vec4 { float x, y, z, w; };

// simple enemy position container
struct EnemyBox {
    vec3 head;
    vec3 feet;
};

class GL
{
public:
    GLint viewport[4];

    // colors
    const GLubyte red[3]   = {255, 0, 0};
    const GLubyte green[3] = {0, 255, 0};
    const GLubyte blue[3]  = {0, 0, 255};

    // 2D overlay setup
    void SetupOrtho();
    void Restore();

    // drawing functions
    void DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
    void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
    void DrawCrosshair(vec2& l1p1, vec2& l1p2, vec2& l2p1, vec2& l2p2, float lineWidth, const GLubyte color[3]);
    void DrawESPBox(vec2 head, vec2 feet, float lineWidth, const GLubyte color[3]);

    // 3D -> 2D projection
    bool WorldToScreen(vec3 pos, vec2& screen, float matrix[16], int windowWidth, int windowHeight);
};
