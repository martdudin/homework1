#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

int ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db);
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners,
				 int ownersLen);
void CalculateFine(penalty *db, int penaltiesLen);
void PrintFines(char *output, penalty *db, int penaltiesLen, bool print,
				bool no_output);
int ReadOwners(char *ownersInput, penalty *owners);
int ReadPenalties(char *penaltiesInput, penalty *db);

// Consolidation of all the smaller functions into a single function
int ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db)
{
	// Create a local struct for temporary owners' info storage
	penalty owners[PEOPLE_MAX];
	int nPenalties = ReadPenalties(penaltiesInput, db);
	int nOwners = ReadOwners(ownersInput, owners);
	// Call the function to match the penalties to the vehicle owners
	CheckOwners(db, nPenalties, owners, nOwners);

	// Return the number of penalties
	return nPenalties;
}

int ReadOwners(char *ownersInput, penalty *owners)
{
	// Create a separate struct where to store the names of the hooligans before
	// they can be assigned to a correct fine
	FILE *fOwners;

	fOwners = fopen(ownersInput, "r");
	if (fOwners == NULL)
	{
		perror("Couldnt open the hooligans file");
		exit(EXIT_FAILURE);
	}

	// Use j for iteration of the while loop and to also store how many car owners
	// there are
	int j = 0;
	while (fscanf(fOwners, "%s %s %s", owners[j].registration_number,
				  owners[j].first_name, owners[j].last_name) == 3)
	{
		j++;
	}
	fclose(fOwners);
	return j;
}

int ReadPenalties(char *penaltiesInput, penalty *db)
{
	FILE *fPenalties;
	fPenalties = fopen(penaltiesInput, "r");
	if (fPenalties == NULL)
	{
		perror("Couldnt open the penalties file");
		exit(EXIT_FAILURE);
	}

	// Use i for iteration of the while loop and also to store how many
	// penalties there are
	int i = 0;
	while (fscanf(fPenalties, "%s %f", (db + i)->registration_number,
				  &(db + i)->measured_speed) == 2)
	{
		// Checking if the licence plate is of the format 3 numbers followed by
		// 3 letters
		for (int j = 0; j < 3; j++)
		{
			if (!isdigit((db + i)->registration_number[j]))
			{
				printf("Incorrect licence plate!\n");
				printf("The 1st half of the plate should be numbers!\n");
				printf("The corrupt field is on the %d. line of the input file!\n",
					   i + 1);
				fclose(fPenalties);
				exit(EXIT_FAILURE);
			}
		}
		for (int j = 3; j < 6; j++)
		{
			if (isdigit((db + i)->registration_number[j]))
			{
				printf("Incorrect licence plate!\n");
				printf("The 2nd half of the plate should be lettesr!\n");
				printf("The corrupt field is on the %d. line of the input file!\n",
					   i + 1);
				fclose(fPenalties);
				exit(EXIT_FAILURE);
			}
		}
		// Check if the measured speed is positive
		if ((db + i)->measured_speed < 0)
		{
			printf("Negative speed? Interesting\n");
			printf("The corrupt field is on the %d. line of the input file!\n",
				   i + 1);
			fclose(fPenalties);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	fclose(fPenalties);
	return i;
}

// Function that matches the penalties to the car owners
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners,
				 int ownersLen)
{
	// Have to loop as many times as there are penalties
	for (int i = 0; i < penaltiesLen; i++)
	{
		// Have to check every owner
		for (int j = 0; j < ownersLen; j++)
		{
			if (strcmp((penalties + i)->registration_number,
					   (owners + j)->registration_number) == 0)
			{
				strcpy((penalties + i)->first_name, (owners + j)->first_name);
				strcpy((penalties + i)->last_name, (owners + j)->last_name);
			}
		}
		// If no owner was found write "Owner unknown"
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
		// The penalty is only given if the speed was 97 km/h or above
		if ((db + i)->measured_speed >= 97)
		{
			(db + i)->fine = ((db + i)->measured_speed - 94) * 3;
			// The max fine possible is 190 EUR
			if ((db + i)->fine > 190)
			{
				(db + i)->fine = 190;
			}
		}
	}
}

void PrintFines(char *output, penalty *db, int penaltiesLen, bool print,
				bool no_output)
{
	FILE *fOutput;
	if (no_output == false)
	{
		fOutput = fopen(output, "w");
		if (fOutput == NULL)
		{
			perror("Couldnt create/open the output file");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < penaltiesLen; i++)
	{
		if (print == false)
		{
			printf("Name: %s %s, ", (db + i)->first_name, (db + i)->last_name);
			printf("Fine: %d EUR\n", (db + i)->fine);
		}
		if (no_output == false)
		{
			fprintf(fOutput, "Name: %s %s, ", (db + i)->first_name,
					(db + i)->last_name);
			fprintf(fOutput, "Fine: %d EUR\n", (db + i)->fine);
		}
	}
	if (no_output == false)
	{
		fclose(fOutput);
	}
}