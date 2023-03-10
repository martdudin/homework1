#ifndef HEADER_H
#define HEADER_H

#include <argp.h>

#define NAME_MAX_LEN 50
#define REG_NUM_MAX 7 // The registration number is 6 characters + '\0'
#define PEOPLE_MAX 50
#define DEFAULT_OWNERS_FILE "./data/car_owners.txt"
#define DEFAULT_PENALTY_FILE "./data/violation_records.txt"

typedef struct
{
    float measured_speed;
    char registration_number[REG_NUM_MAX];
    char first_name[NAME_MAX_LEN];
    char last_name[NAME_MAX_LEN];
    int fine;
} penalty;

static struct argp_option options[] = {
    {"input",     'i', "FILE", 0, "Name of the input file with penalties", 0},
    {"hooligans", 'h', "FILE", 0, "Name of the input file with owners of the cars", 0},
    {"output",    'o', "FILE", 0, "Name of the output file", 0},
    {"noprint",   'n',      0, 0, "Disable printing on screen", 0},
    {"nooutput",  'd',      0, 0, "Disable writing the output to the file", 0},
    {0}};

typedef struct
{
    bool noprint, disable_output;
    char *input_file;
    char *hooligans_file;
    char *output_file;
} arguments;

static char args_doc[] = "ARG1 ARG2";

static char doc[] = "Find the hooligans that committed heinous crimes";

// What to do with the different options should the user select them
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    arguments *arguments = state->input;

    switch (key)
    {
    case 'i':
        // custom file name for the penalties
        arguments->input_file = arg;
        break;
    case 'h':
        // custom file name for the owners of the vehicles
        arguments->hooligans_file = arg;
        break;
    case 'o':
        // custom name for the output file
        arguments->output_file = arg;
        break;
    case 'n':
        // true = no printing in the terminal
        arguments->noprint = true;
        break;
    case 'd':
        // true = do not output anything to a file
        arguments->disable_output = true;
        break;
    default:
        break;
    }
    return 0;
}

// The three nulls are at the end are there to have no warnings
static struct argp argp = {options, parse_opt, args_doc, doc, NULL, NULL, NULL};

#endif