#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db);
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners, int ownersLen);

void ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db)
{
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
	if (fPenalties == NULL)
	{
		printf("ERROR: Couldn't open the file with owners!\n");
		exit(EXIT_FAILURE);
	}
	
	int i = 0;
	while (fscanf(fPenalties, "%s %f", (db + i)->registration_number, &(db + i)->measured_speed) == 2)
	{
		printf("GOT: %s %.2f\n", (db + i)->registration_number, (db + i)->measured_speed);
		i++;
	}
	int j = 0;
	while (fscanf(fOwners, "%s %s %s", owners[j].registration_number, owners[j].first_name, owners[j].		 last_name) == 3)
	{
		printf("GOT owner: %s %s %s\n", owners[j].registration_number, owners[j].first_name, owners[j].		 last_name);
		j++;
	}
	
	CheckOwners(db, i, owners, j);
}

void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners, int ownersLen)
{
	for (int i = 0; i < penaltiesLen; i++)
	{
		printf("This is the %dth iteration of the loop\n", i);
		for (int j = 0; j < ownersLen; j++)
		{
			if (strcmp((penalties + i)->registration_number, (owners + j)->registration_number) == 0)
			{
				printf("GOT MATCH ON j = %d which means line %d\n", j, j + 1);
				strcpy((penalties + i)->first_name, (owners + j)->first_name);
				strcpy((penalties + i)->last_name, (owners + j)->last_name);
			}
		}
	}
}
