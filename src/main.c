#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "file.h"
#include "mesh.h"
#include "callbacks.h"
#include "mat4.h"

#define WINDOW_W 1920
#define WINDOW_H 1080
#define WINDOW_RATIO ((float)WINDOW_W / (float)WINDOW_H)
#define WINDOW_NAME "[Executable Name Here]"

int main() {
	{
		int32_t glfw_init = glfwInit();
		assert(glfw_init);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(WINDOW_W, WINDOW_H, "Test", NULL,
			NULL);
	assert(window);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, glfw_callback_input);

	{
		int32_t glad_init = gladLoadGL();
		assert(glad_init);
	}
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* base triangle vao */
	Mesh mesh;
	{
		Vertex vertices[] = {
			{.pos = {-0.5f, -0.5f, 0.0f}, .uv = {0.0f, 0.0f}},
			{.pos = { 0.5f, -0.5f, 0.0f}, .uv = {1.0f, 0.0f}},
			{.pos = {-0.5f,  0.5f, 0.0f}, .uv = {0.0f, 1.0f}},
			{.pos = { 0.5f,  0.5f, 0.0f}, .uv = {1.0f, 1.0f}},
		};

		uint32_t indices[] = {
			0, 1, 2,
			2, 1, 3,
		};
		mesh = mesh_create(vertices, indices,
				sizeof(vertices) / sizeof(Vertex),
				sizeof(indices) / sizeof(uint32_t));
	}

	/* base shader */
	uint32_t shader_prog = glCreateProgram();
	{
		uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);
		uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

		char *vert_source = file_contents_load("res/shaders/vert.glsl");
		assert(vert_source);
		char *frag_source = file_contents_load("res/shaders/frag.glsl");
		assert(frag_source);

		glShaderSource(vert_shader, 1, (const char **)&vert_source, NULL);
		glShaderSource(frag_shader, 1, (const char **)&frag_source, NULL);
		glCompileShader(vert_shader);
		glCompileShader(frag_shader);

		int32_t vert_status;
		glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &vert_status);
		if(!vert_status) {
			char log[512];
			glGetShaderInfoLog(vert_shader, 512, NULL, log);
			fprintf(stderr, "Vertex Shader Error: %s\n", log);
			return 1;
		}

		int32_t frag_status;
		glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &frag_status);
		if(!frag_status) {
			char log[512];
			glGetShaderInfoLog(frag_shader, 512, NULL, log);
			fprintf(stderr, "Fragment Shader Error: %s\n", log);
			return 1;
		}

		glAttachShader(shader_prog, vert_shader);
		glAttachShader(shader_prog, frag_shader);
		glLinkProgram(shader_prog);
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);
		free(vert_source);
		free(frag_source);
	}

	mat4 mat_proj;
	/* TODO: Make function for perspetive matrix */
	glm_perspective(glm_rad(45.0f), WINDOW_RATIO, 0.1f, 32.0f, mat_proj);

	Mat4 mat_view;
	mat4_identity(mat_view);

	glViewport(0, 0, WINDOW_W, WINDOW_H);
	while(!glfwWindowShouldClose(window)) {
		/* updating */
		Mat4 mat_model;
		mat4_identity(mat_model);
		mat4_translate_z(mat_model, -3.0f);

		/* drawing */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(mesh.vao);
		glUseProgram(shader_prog);
		glUniformMatrix4fv(glGetUniformLocation(shader_prog, "proj"), 1,
				GL_FALSE, (const float *)mat_proj);
		glUniformMatrix4fv(glGetUniformLocation(shader_prog, "view"), 1,
				GL_FALSE, (const float *)mat_view);
		glUniformMatrix4fv(glGetUniformLocation(shader_prog, "model"), 1,
				GL_FALSE, (const float *)mat_model);
		glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT,
				mesh.indices);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	mesh_destroy(&mesh);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
