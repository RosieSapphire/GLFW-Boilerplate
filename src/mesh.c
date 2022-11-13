#include "mesh.h"

#include <malloc.h>
#include <string.h>

#include "glad/glad.h"

Mesh mesh_create(const Vertex *vertices, const uint32_t *indices, 
		const uint32_t vertex_count, const uint32_t index_count) {
	Mesh ret;
	ret.vertices = malloc(vertex_count * sizeof(Vertex));
	ret.vertex_count = vertex_count;
	memcpy(ret.vertices, vertices, sizeof(Vertex) * vertex_count);
	ret.indices = malloc(index_count * sizeof(uint32_t));
	ret.index_count = index_count;
	memcpy(ret.indices, indices, sizeof(uint32_t) * index_count);

	glGenVertexArrays(1, &ret.vao);
	glBindVertexArray(ret.vao);

	glGenBuffers(1, &ret.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ret.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices,
			GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void *)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void *)offsetof(Vertex, uv));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ret.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * index_count,
			indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return ret;
}

void mesh_destroy(Mesh *mesh) {
	free(mesh->vertices);
	free(mesh->indices);
}
