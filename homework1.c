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

// What to do with the different options should the user select them
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
	// and set the default values
	struct arguments arguments = {false, false, DEFAULT_PENALTY_FILE, 
								  DEFAULT_OWNERS_FILE, "output.txt"};

	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
	// FOR TESTING PURPOSES
	if(ARG_DEBUG){
		printf("penalties file: %s\n", arguments.input_file);
		printf("output file: %s\n", arguments.output_file);
		printf("hooligans file: %s\n", arguments.hooligans_file);
		printf("Prints: %s\n", arguments.noprint ? "no" : "yes");
		printf("Output to a file: %s\n", arguments.disable_output ? "no" : "yes");
	}

	penalty test[PEOPLE_MAX];
	ReadInfo(arguments.input_file, arguments.hooligans_file, test);
	CalculateFine(test, 11);
	if ((arguments.noprint == true) && (arguments.disable_output == true))
	{
		return 0;
	}
	else
	{
		PrintFines(arguments.output_file, test, 12, arguments.noprint, arguments.disable_output);
	}

	return 0;
}