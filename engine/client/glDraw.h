#pragma once
#include <GL/gl.h>
#include <math.h>

// -------------------- vector types --------------------
typedef struct { float x, y; } vec2;
typedef struct { float x, y, z; } vec3;

// -------------------- GL overlay struct --------------------
typedef struct {
    GLint viewport[4];
    GLubyte red[3];
    GLubyte green[3];
    GLubyte blue[3];
} GL_t;

// -------------------- init --------------------
void GL_Init(GL_t* gl);

// -------------------- 2D overlay setup --------------------
void GL_SetupOrtho(GL_t* gl);
void GL_Restore(GL_t* gl);

// -------------------- drawing --------------------
void GL_DrawFilledRect(float x, float y, float width, float height, GLubyte color[3]);
void GL_DrawOutline(float x, float y, float width, float height, float lineWidth, GLubyte color[3]);
void GL_DrawCrosshair(vec2 l1p1, vec2 l1p2, vec2 l2p1, vec2 l2p2, float lineWidth, GLubyte color[3]);
void GL_DrawESPBox(vec2 head, vec2 feet, float lineWidth, GLubyte color[3]);

// -------------------- 3D -> 2D projection --------------------
int GL_WorldToScreen(vec3 pos, vec2* screen, float matrix[16], int windowWidth, int windowHeight);
