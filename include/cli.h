#ifndef CLI_H
#define CLI_H

#include "dft.h"

/**
 * @brief Parse and error check command line arguments
 *
 * @param argc Number of input argument strings given
 * @param argv Array of input argument strings
 * @param config Program configuration structure
 * @return int 0 if successful 1 otherwise
 */
int parse_cli(int argc, char *argv[], CliConfiguration *cli_config);

#endif  // CLI_H