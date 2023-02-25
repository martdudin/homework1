void ReadInfo(char *penaltiesInput, char *ownersInput, penalty *db);
void CheckOwners(penalty *penalties, int penaltiesLen, penalty *owners, int ownersLen);
void CalculateFine(penalty *db, int penaltiesLen);
void PrintFines(char *output, penalty *db, int penaltiesLen, bool print, bool no_output);