#ifndef __MESH_H_
#define __MESH_H_

#include <vertex.h>
#include <stdint.h>

typedef struct {
	uint32_t vertex_count, index_count;
	Vertex *vertices;
	uint32_t *indices;
	uint32_t vao, vbo, ebo;
} Mesh;

Mesh mesh_create(const Vertex *vertices, const uint32_t *indices, 
		const uint32_t vertex_count, const uint32_t index_count);

void mesh_destroy(Mesh *mesh);

#endif
