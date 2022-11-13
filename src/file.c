#include "file.h"

#include <stdio.h>
#include <malloc.h>

char *file_contents_load(const char *path) {
	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char *ret = calloc(file_size + 1, sizeof(char));
	fread(ret, sizeof(char), file_size + 1, file);
	ret[file_size] = 0;
	fclose(file);

	return ret;
}
