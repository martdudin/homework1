/* Homework 1

Author: Mart Dudin
Date: 23.02.2023

*/

#include <stdio.h>
#include <stdbool.h>
#include "header.h"
#include "info_manipulation.h"

static char args_doc[] = "ARG1 ARG2";

static char doc[] = "Argp test for homework 1";

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key)
	{
	case 'i':
		arguments->input_file = arg;
		break;
	case 'h':
		arguments->hooligans_file = arg;
		break;
	case 'o':
		arguments->output_file = arg;
		break;
	case 'n':
		arguments->noprint = 1;
		break;
	case 'd':
		arguments->disable_output = 1;
		break;
	// case ARGP_KEY_ARG:
	// 	if (state->arg_num >= 2)
	// 	{
	// 		// if too many arguments
	// 		argp_usage(state);
	// 	}
	// 	arguments->args[state->arg_num] = arg;
	// 	break;
	default:
		break;
	}
	return 0;
}

// The three nulls are at the end are there to have no warnings
static struct argp argp = { options, parse_opt, args_doc, doc, NULL, NULL , NULL};

int main(int argc, char **argv)
{
	// create a struct variable where to store all the options chosen
	struct arguments arguments;

	// Default values of the options
	arguments.noprint = false;
	arguments.disable_output = false;
	arguments.input_file = DEFAULT_PENALTY_FILE;
	arguments.output_file = "output.txt";
	arguments.hooligans_file = DEFAULT_OWNERS_FILE;
	

	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
	if(ARG_DEBUG){
		printf("penalties file: %s\n", arguments.input_file);
		printf("output file: %s\n", arguments.output_file);
		printf("hooligans file: %s\n", arguments.hooligans_file);
		printf("Prints: %s\n", arguments.noprint ? "no" : "yes");
		printf("Output to a file: %s\n", arguments.disable_output ? "no" : "yes");
		// printf("ARG1 = %s\n", arguments.args[0]);
		// printf("ARG1 = %s\n", arguments.args[1]);
	}
	penalty test[PEOPLE_MAX];
	ReadInfo(arguments.input_file, arguments.hooligans_file, test);
	CalculateFine(test, 11);
	PrintFines(arguments.output_file, test, 11, arguments.noprint, arguments.disable_output);
	return 0;
}