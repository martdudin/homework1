#include <argp.h>

#define ARG_DEBUG 1
#define DEBUG 0

#define NAME_MAX_LEN 50
#define REG_NUM_MAX 7
#define PEOPLE_MAX 150
#define DEFAULT_OWNERS_FILE "./data/car_owners.txt"
#define DEFAULT_PENALTY_FILE "./data/violation_records.txt"

typedef struct
{
	float measured_speed;
	char registration_number[REG_NUM_MAX];
	char first_name[NAME_MAX_LEN];
	char last_name[NAME_MAX_LEN];
    float fine;
}penalty;

static struct argp_option options[] = {
    {"input",       'i', "FILE", 0, "Name of the input file with penalties", 0}, // 105 is ASCII for 'i'
    {"hooligans",   'h', "FILE", 0, "Name of the input file with owners of the cars", 0}, // 105 is ASCII for 'i'
    {"output",      'o', "FILE", 0, "Name of the output file", 0}, // 111 is ASCII for 'o'
    {"noprint",     'n', 0,      0, "Disable printing on screen", 0}, // 110 is ASCII for 'n'
    {"nooutput",    'd', 0,      0, "Disable writing the output to the file", 0}, // 100 is ASCII for 'd'
    { 0 }
};

struct arguments
{
    //char *args[2];
    bool noprint, disable_output;
    char *input_file;
    char *hooligans_file;
    char *output_file;
};