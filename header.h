#include <argp.h>

#define NAME_MAX_LEN 50
#define REG_NUM_MAX 7
#define PEOPLE_MAX 150

typedef struct
{
	float measured_speed;
	char registration_number[REG_NUM_MAX];
	char first_name[NAME_MAX_LEN];
	char last_name[NAME_MAX_LEN];
}penalty;

static struct argp_option options[] = {
    {"input",   105, "FILE", 0, "Name of the input file", 0}, // 105 is ASCII for 'i'
    {"output",  111, "FILE", 0, "Name of the output file", 0}, // 111 is ASCII for 'o'
    {"noprint", 110, 0,      0, "Disable printing on screen", 0}, // 110 is ASCII for 'n'
    {"doutput", 100, 0,      0, "Disable writin the output to the file", 0}, // 100 is ASCII for 'd'
};


