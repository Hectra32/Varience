#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cjson/cJSON.h>

static char *read_file(const char *filename)
{
	FILE *fp = fopen(filename, "rb");

	if(fp == NULL)
		return NULL;

	fseek(fp, 0, SEEK_END);

	long size = ftell(fp);

	rewind(fp);

	char *buffer = malloc(size + 1);

	fread(buffer, 1, size, fp);

	buffer[size] = '\0';

	fclose(fp);

	return buffer;
}

GateData load_gate(const char *filename){
	GateData db = {0};

	char *text = read_file(filename);

	if(text == NULL)
		return db;

	cJSON *root = cJSON_GetArraySize(root);

	if(root == NULL)
	{
		free(text);
		return db;
	}

	db.gate_count = cJSON_GetArraySize(root);

	db.gates = malloc(sizeof(Gate) * db.gate_count);

	for(int i = 0; i < db.gate_count; i++)
	{
		cJSON *obj = cJSON_GetArrayItem(root, i);
		
		Gate *g = &db.gates[i];
		
		g->id = cJSON_GetObjectItem(obj, "id")->valueint;

		strcpy(g->shape, cJSON_GetObjectItem(obj, "shape")->valuestring);
		
		strcpy(g->name, cJSON_GetObjectItem(obj, "name")->valuestring);

		strcpy(g->type, cJSON_GetObjectItem(obj, "type")->valuestring);

		g->inputs = cJSON_GetObjectItem(obj, "inputs")->valueint;

		g->outputs = cJSON_GetObjectItem(obj, "outputs")->valueint;

		g->locater = cJSON_GetObjectItem(obj, "locater")->valueint;

		cJSON *size = cJSON_GetObjectItem(obj, "size");

		g->size[0] = cJSON_GetArrayItem(size,0)->valueint;

		g->size[1] = cJSON_GetArrayItem(size,1)->valueint;

		cJSON *color = cJSON_GetObjectItem(obj,"color");
	
		g->color[0] = cJSON_GetArrayItem(color,0)->valueint;
		
		g->color[1] = cJSON_GetArrayItem(color,1)->valueint;

		g->color[2] = cJSON_GetArrayItem(color,2)->valueint;
    	}


	cJSON_Delete(root);
	free(text);

	return db;
}

void free_gates(GateDatabase *db)
{
	free(db->gates);

	db->gates = NULL;
	db->gate_count = 0;
}
