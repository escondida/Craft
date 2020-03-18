#pragma once

#define MAX_NAME_LENGTH 32

enum gait {CLIMB, CRAWL, EDGE, FLY, JOG, RUN, SWIM, WALK};

typedef struct {
	float x;
	float y;
	float z;
	float rx;
	float ry;
	float t;
} State;

typedef struct {
	int id;
	char name[MAX_NAME_LENGTH];
	State state;
	State state1;
	State state2;
	GLuint buffer;
} Player;
