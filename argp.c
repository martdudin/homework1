#include <stdlib.h>
#include <argp.h>

const char *argp_program_version = "0.5";
const char *argp_program_bug_address = "<lol@hotmail.ee>";

static char *doc =
"Homework 1: will issue a penalty to the bad guys";

static struct argp_option *options =
{
    {"input",   'i', "FILE", 0, "Name of the input file"},
    {"output",  'o', "FILE", 0, "Name of the output file"},
    {"noprint", 'n', 0,      0, "Disable printing on screen"},
    {"doutput", 'd', 0,      0, "Disable writin the output to the file"},
    { 0 }
};
