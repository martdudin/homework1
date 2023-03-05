#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

void ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db);
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners, int ownersLen);
void CalculateFine(penalty *db, int penaltiesLen);
void PrintFines(char *output, penalty *db, int penaltiesLen, bool print, bool no_output);

void ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db)
{
	// Create a separate struct where to store the names of the hooligans before
	// they can be assigned to a correct fine
	penalty owners[PEOPLE_MAX];
	FILE *fPenalties;
	FILE *fOwners;
	fPenalties = fopen(penaltiesInput, "r");
	if (fPenalties == NULL)
	{
		printf("ERROR: Couldn't open the file with penalties!\n");
		exit(EXIT_FAILURE);
	}
	
	fOwners = fopen(ownersInput, "r");
	if (fOwners == NULL)
	{
		printf("ERROR: Couldn't open the file with owners!\n");
		exit(EXIT_FAILURE);
	}
	
	// Use i for iteration of the while loop and also to store how many 
	// penalties there are
	int i = 0;
	while (fscanf(fPenalties, "%s %f", (db + i)->registration_number, &(db + i)->measured_speed) == 2)
	{
		// Checking if the licence plate is of the format 3 numbers followed by 
		// 3 letters
		for (int j = 0; j < 3; j++)
		{
			if (!isdigit((db + i)->registration_number[j]))
			{
				printf("Incorrect licence plate!\n");
				printf("The 1st half of the plate should be numbers!\n");
				printf("The corrupt field is on the %d. line of the input file!\n", i + 1);
				exit(EXIT_FAILURE);
			}
		}
		for (int j = 3; j < 6; j++)
		{
			if (isdigit((db + i)->registration_number[j]))
			{
				printf("Incorrect licence plate!\n");
				printf("The 2nd half of the plate should be lettesr!\n");
				printf("The corrupt field is on the %d. line of the input file!\n", i + 1);
				exit(EXIT_FAILURE);
			}
		}
		
		// Only for debugging
		if (DEBUG)
		{
			printf("GOT: %s %.2f\n", (db + i)->registration_number, (db + i)->measured_speed);
		}
		i++;
	}
	fclose(fPenalties);

	// Use j for iteration of the while loop and to also store how many car owners
	// there are
	int j = 0;
	while (fscanf(fOwners, "%s %s %s", owners[j].registration_number, owners[j].first_name, owners[j].last_name) == 3)
	{
		if (DEBUG)
		{
			printf("GOT owner: %s %s %s\n", owners[j].registration_number, owners[j].first_name, owners[j].last_name);
		}
		j++;
	}
	fclose(fOwners);

	// Call the function to match the penalties to the vehicle owners
	CheckOwners(db, i, owners, j);
}


// Function that matches the penalties to the car owners
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners, int ownersLen)
{
	// 
	for (int i = 0; i < penaltiesLen; i++)
	{
		for (int j = 0; j < ownersLen; j++)
		{
			if (strcmp((penalties + i)->registration_number, (owners + j)->registration_number) == 0)
			{
				strcpy((penalties + i)->first_name, (owners + j)->first_name);
				strcpy((penalties + i)->last_name, (owners + j)->last_name);
			}
		}
		if (strcmp((penalties + i)->first_name, "\0") == 0)
		{
			strcpy((penalties + i)->first_name, "Owner");
			strcpy((penalties + i)->last_name, "unknown");	
		}
		
	}
}

void CalculateFine(penalty *db, int penaltiesLen)
{
	for (int i = 0; i < penaltiesLen; i++)
	{
		if ((db + i)->measured_speed >= 97)
		{
			(db + i)->fine = ((db + i)->measured_speed - 94) * 3;
			if ((db + i)->fine > 190)
			{
				(db + i)->fine = 190;
			}	
		}	
	}
}

void PrintFines(char *output, penalty *db, int penaltiesLen, bool print, bool no_output)
{
	FILE *fOutput;
	if (no_output == false)
	{
		fOutput = fopen(output, "w");
		if (fOutput == NULL)
		{
			printf("Couldn't create the output file\n");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < penaltiesLen; i++)
	{
		if (print == false)
		{
			printf("Name: %s %s\n", (db + i)->first_name, (db + i)->last_name);
			printf("Fine: %.2f EUR\n", (db + i)->fine);
		}
		if (no_output == false)
		{
			fprintf(fOutput, "Name: %s %s\n", (db + i)->first_name, (db + i)->last_name);
			fprintf(fOutput, "Fine: %.2f EUR\n", (db + i)->fine);
		}
	}
	if (no_output == false)
	{
		fclose(fOutput);
	}
}