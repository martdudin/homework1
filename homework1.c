#include <stdio.h>
#include "header.h"
#include "read_info.h"

int main(int argc, char **argv)
{
	penalty test[PEOPLE_MAX];
	ReadInfo("./data/violation_records.txt", "./data/car_owners.txt", test);
	//argp_parse()
	return 0;
}
