#ifndef __MAT4_H_
#define __MAT4_H_

#include "vec3.h"

typedef float Mat4[4][4];

void mat4_zero(Mat4 mat);
void mat4_identity(Mat4 mat);
void mat4_translate(Mat4 mat, Vec3 vec);
void mat4_translate_x(Mat4 mat, const float x);
void mat4_translate_y(Mat4 mat, const float y);
void mat4_translate_z(Mat4 mat, const float z);
void mat4_translate_xyz(Mat4 mat, const float x, const float y, const float z);
void mat4_printf(Mat4 mat);

#endif
