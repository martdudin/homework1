#ifndef INFO_MANIPULATION_H
#define INFO_MANIPULATION_H

int ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db);
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners,
                 int ownersLen);
void CalculateFine(penalty *db, int penaltiesLen);
void PrintFines(char *output, penalty *db, int penaltiesLen, bool print,
                bool no_output);
int ReadOwners(char *ownersInput, penalty *owners);
int ReadPenalties(char *penaltiesInput, penalty *db);

#endif