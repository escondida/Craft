/* model.h
	Functions for modeling the game world
*/

#pragma once

#define MAX_CHUNKS 8192
#define MAX_PLAYERS 128
#define WORKERS 4
#define MAX_TEXT_LENGTH 256
#define MAX_PATH_LENGTH 256
#define MAX_ADDR_LENGTH 256

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

#define MODE_OFFLINE 0
#define MODE_ONLINE 1

#define WORKER_IDLE 0
#define WORKER_BUSY 1
#define WORKER_DONE 2

typedef struct {
	GLuint program;
	GLuint position;
	GLuint normal;
	GLuint uv;
	GLuint matrix;
	GLuint sampler;
	GLuint camera;
	GLuint timer;
	GLuint extra1;
	GLuint extra2;
	GLuint extra3;
	GLuint extra4;
} Attrib;

typedef struct {
	int x;
	int y;
	int z;
	int w;
} Block;

typedef struct {
	Map map;
	Map lights;
	SignList signs;
	int p;
	int q;
	int faces;
	int sign_faces;
	int dirty;
	int miny;
	int maxy;
	GLuint buffer;
	GLuint sign_buffer;
} Chunk;

typedef struct {
	int p;
	int q;
	int load;
	Map *block_maps[3][3];
	Map *light_maps[3][3];
	int miny;
	int maxy;
	int faces;
	GLfloat *data;
} WorkerItem;

typedef struct {
	int index;
	int state;
	thrd_t thrd;
	mtx_t mtx;
	cnd_t cnd;
	WorkerItem item;
} Worker;

typedef struct {
	GLFWwindow *window;
	Worker workers[WORKERS];
	Chunk chunks[MAX_CHUNKS];
	int chunk_count;
	int create_radius;
	int render_radius;
	int delete_radius;
	int sign_radius;
	Player players[MAX_PLAYERS];
	int player_count;
	int typing;
	char typing_buffer[MAX_TEXT_LENGTH];
	int message_index;
	char messages[MAX_MESSAGES][MAX_TEXT_LENGTH];
	int width;
	int height;
	int observe1;
	int observe2;
	int gait;
	int item_index;
	int scale;
	int ortho;
	float fov;
	int suppress_char;
	int mode;
	int mode_changed;
	char db_path[MAX_PATH_LENGTH];
	char server_addr[MAX_ADDR_LENGTH];
	int server_port;
	int day_length;
	int time_changed;
	Block block0;
	Block block1;
	Block copy0;
	Block copy1;
} Model;

/*
	Most of these have only one or two consumers outside of model.c;
	see about reducing the need for them outside that file.
*/
int chunked(float);

void draw_chunk(Attrib *, Chunk *);
void draw_cube(Attrib *, GLuint);
void draw_plant(Attrib *, GLuint);
void draw_lines(Attrib *, GLuint, int, int);
void draw_player(Attrib *, Player *);
void draw_sign(Attrib *, GLuint, int);
void draw_signs(Attrib *, Chunk *);
void draw_text(Attrib *, GLuint, int);
void draw_triangles_3d(Attrib *, GLuint, int);

GLuint gen_crosshair_buffer(int width, int height, int scale);
GLuint gen_cube_buffer(float x, float y, float z, float n, int w);
GLuint gen_plant_buffer(float x, float y, float z, float n, int w);
GLuint gen_player_buffer(float x, float y, float z, float rx, float ry);
GLuint gen_sky_buffer(void);
GLuint gen_text_buffer(float x, float y, float n, char *text);
GLuint gen_wireframe_buffer(float x, float y, float z, float n);
