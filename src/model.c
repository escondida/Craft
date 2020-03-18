#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <string.h>

// clang-fromat off
#include "tinycthread.h"
// clang-format on

#include "cube.h"
#include "map.h"
#include "player.h"
#include "sign.h"
#include "util.h"

// clang-format off
#include "model.h"
// clang-format on

void draw_item(Attrib *, GLuint, int);
void draw_triangles_2d(Attrib *, GLuint, int);
void draw_triangles_3d_ao(Attrib *, GLuint, int);
void draw_triangles_3d_text(Attrib *, GLuint, int);

int
chunked(float x)
{
	return floorf(roundf(x) / CHUNK_SIZE);
}

void
draw_chunk(Attrib *attrib, Chunk *chunk)
{
	draw_triangles_3d_ao(attrib, chunk->buffer, chunk->faces * 6);
}

void
draw_cube(Attrib *attrib, GLuint buffer)
{
	draw_item(attrib, buffer, 36);
}

void
draw_item(Attrib *attrib, GLuint buffer, int count)
{
	draw_triangles_3d_ao(attrib, buffer, count);
}

void
draw_lines(Attrib *attrib, GLuint buffer, int components, int count)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(attrib->position);
	glVertexAttribPointer(
			attrib->position, components, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_LINES, 0, count);
	glDisableVertexAttribArray(attrib->position);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
draw_plant(Attrib *attrib, GLuint buffer)
{
	draw_item(attrib, buffer, 24);
}

void
draw_player(Attrib *attrib, Player *player)
{
	draw_cube(attrib, player->buffer);
}

void
draw_sign(Attrib *attrib, GLuint buffer, int length)
{
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-8, -1024);
	draw_triangles_3d_text(attrib, buffer, length * 6);
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void
draw_signs(Attrib *attrib, Chunk *chunk)
{
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-8, -1024);
	draw_triangles_3d_text(attrib, chunk->sign_buffer, chunk->sign_faces * 6);
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void
draw_text(Attrib *attrib, GLuint buffer, int length)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	draw_triangles_2d(attrib, buffer, length * 6);
	glDisable(GL_BLEND);
}

void
draw_triangles_2d(Attrib *attrib, GLuint buffer, int count)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(attrib->position);
	glEnableVertexAttribArray(attrib->uv);
	glVertexAttribPointer(
			attrib->position, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(
			attrib->uv, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4,
			(GLvoid *)(sizeof(GLfloat) * 2));
	glDrawArrays(GL_TRIANGLES, 0, count);
	glDisableVertexAttribArray(attrib->position);
	glDisableVertexAttribArray(attrib->uv);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
draw_triangles_3d(Attrib *attrib, GLuint buffer, int count)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(attrib->position);
	glEnableVertexAttribArray(attrib->normal);
	glEnableVertexAttribArray(attrib->uv);
	glVertexAttribPointer(
			attrib->position, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
	glVertexAttribPointer(
			attrib->normal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,
			(GLvoid *)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(
			attrib->uv, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,
			(GLvoid *)(sizeof(GLfloat) * 6));
	glDrawArrays(GL_TRIANGLES, 0, count);
	glDisableVertexAttribArray(attrib->position);
	glDisableVertexAttribArray(attrib->normal);
	glDisableVertexAttribArray(attrib->uv);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
draw_triangles_3d_ao(Attrib *attrib, GLuint buffer, int count)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(attrib->position);
	glEnableVertexAttribArray(attrib->normal);
	glEnableVertexAttribArray(attrib->uv);
	glVertexAttribPointer(
			attrib->position, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10, 0);
	glVertexAttribPointer(
			attrib->normal, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10,
			(GLvoid *)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(
			attrib->uv, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 10,
			(GLvoid *)(sizeof(GLfloat) * 6));
	glDrawArrays(GL_TRIANGLES, 0, count);
	glDisableVertexAttribArray(attrib->position);
	glDisableVertexAttribArray(attrib->normal);
	glDisableVertexAttribArray(attrib->uv);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
draw_triangles_3d_text(Attrib *attrib, GLuint buffer, int count)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(attrib->position);
	glEnableVertexAttribArray(attrib->uv);
	glVertexAttribPointer(
			attrib->position, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
	glVertexAttribPointer(
			attrib->uv, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,
			(GLvoid *)(sizeof(GLfloat) * 3));
	glDrawArrays(GL_TRIANGLES, 0, count);
	glDisableVertexAttribArray(attrib->position);
	glDisableVertexAttribArray(attrib->uv);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint
gen_crosshair_buffer(int w, int h, int scale)
{
	int x = w / 2;
	int y = h / 2;
	int p = 10 * scale;

	float data[] = {x, y - p, x, y + p, x - p, y, x + p, y};
	return gen_buffer(sizeof(data), data);
}

GLuint
gen_cube_buffer(float x, float y, float z, float n, int w)
{
	GLfloat *data = malloc_faces(10, 6);
	float ao[6][4] = {0};
	float light[6][4] = {{0.5, 0.5, 0.5, 0.5}, {0.5, 0.5, 0.5, 0.5},
						 {0.5, 0.5, 0.5, 0.5}, {0.5, 0.5, 0.5, 0.5},
						 {0.5, 0.5, 0.5, 0.5}, {0.5, 0.5, 0.5, 0.5}};
	make_cube(data, ao, light, 1, 1, 1, 1, 1, 1, x, y, z, n, w);
	return gen_faces(10, 6, data);
}

GLuint
gen_plant_buffer(float x, float y, float z, float n, int w)
{
	GLfloat *data = malloc_faces(10, 4);
	float ao = 0;
	float light = 1;
	make_plant(data, ao, light, x, y, z, n, w, 45);
	return gen_faces(10, 4, data);
}

GLuint
gen_player_buffer(float x, float y, float z, float rx, float ry)
{
	GLfloat *data = malloc_faces(10, 6);
	make_player(data, x, y, z, rx, ry);
	return gen_faces(10, 6, data);
}

GLuint
gen_sky_buffer()
{
	float data[12288];
	make_sphere(data, 1, 3);
	return gen_buffer(sizeof(data), data);
}

GLuint
gen_text_buffer(float x, float y, float n, char *text)
{
	int length = strlen(text);
	GLfloat *data = malloc_faces(4, length);
	for (int i = 0; i < length; i++) {
		make_character(data + i * 24, x, y, n / 2, n, text[i]);
		x += n;
	}
	return gen_faces(4, length, data);
}

GLuint
gen_wireframe_buffer(float x, float y, float z, float n)
{
	float data[72];
	make_cube_wireframe(data, x, y, z, n);
	return gen_buffer(sizeof(data), data);
}
