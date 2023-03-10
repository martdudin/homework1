/* Homework 1

Author: Mart Dudin
Date: 23.02.2023

*/

#include <stdio.h>
#include <stdbool.h>
#include "header.h"
#include "info_manipulation.h"

int main(int argc, char **argv)
{
	// create a struct variable where to store all the options chosen
	// and set the default values
	arguments arguments = {false, false, DEFAULT_PENALTY_FILE,
						   DEFAULT_OWNERS_FILE, "output.txt"};
	// parse the arguments that the user selected
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// Create the struct to store the info
	penalty people[PEOPLE_MAX] = {0};

	// Read the info from files
	int nPenalties = ReadInfo(arguments.input_file, arguments.hooligans_file,
							  people);
	CalculateFine(people, nPenalties);
	// The program can be finished early if the user doesn't want printed output
	// nor any output to a file
	if ((arguments.noprint == true) && (arguments.disable_output == true))
	{
		return 0;
	}
	else
	{
		PrintFines(arguments.output_file, people, nPenalties, arguments.noprint,
				   arguments.disable_output);
	}
	return 0;
}