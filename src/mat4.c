#include "mat4.h"

#include <stdio.h>
#include <stdint.h>

void mat4_zero(Mat4 mat) {
	for(uint8_t i = 0; i < 4; i++) {
		for(uint8_t j = 0; j < 4; j++) {
			mat[j][i] = 0.0f;
		}
	}
}

void mat4_identity(Mat4 mat) {
	mat[0][0] = 1.0f; mat[1][0] = 0.0f; mat[2][0] = 0.0f; mat[3][0] = 0.0f;
	mat[0][1] = 0.0f; mat[1][1] = 1.0f; mat[2][1] = 0.0f; mat[3][1] = 0.0f;
	mat[0][2] = 0.0f; mat[1][2] = 0.0f; mat[2][2] = 1.0f; mat[3][2] = 0.0f;
	mat[0][3] = 0.0f; mat[1][3] = 0.0f; mat[2][3] = 0.0f; mat[3][3] = 1.0f;
}

void mat4_translate(Mat4 mat, Vec3 vec) {
	mat[3][0] += vec.x;
	mat[3][1] += vec.y;
	mat[3][2] += vec.z;
}

void mat4_translate_x(Mat4 mat, const float x) {
	mat4_translate(mat, (Vec3){x, 0.0f, 0.0f});
}

void mat4_translate_y(Mat4 mat, const float y) {
	mat4_translate(mat, (Vec3){0.0f, y, 0.0f});
}

void mat4_translate_z(Mat4 mat, const float z) {
	mat4_translate(mat, (Vec3){0.0f, 0.0f, z});
}

void mat4_translate_xyz(Mat4 mat, const float x, const float y, const float z) {
	mat4_translate(mat, (Vec3){x, y, z});
}

void mat4_printf(Mat4 mat) {
	for(uint8_t i = 0; i < 4; i++) {
		for(uint8_t j = 0; j < 4; j++) {
			printf("%f ", mat[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}
