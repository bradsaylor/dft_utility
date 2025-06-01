#include "../include/meta_file.h"

#include <stdio.h>
#include <string.h>

int write_meta_file(ProgramConfig *program_config, CliConfiguration *cli_config,
                    int output_length) {
  char *algorithm_list[] = {"unknown", "direct", "fft", "ifft", "goertzl"};
  char *window_list[] = {"unknown", "hanning",         "hamming",
                         "kaiser",  "blackman-harris", "flat-top"};
  char *output_type_list[] = {"unknown", "txt", "csv", "bin"};
  char output_path[50] = {0};
  strcat(output_path, program_config->output_dir);
  strcat(output_path, "meta_");
  strcat(output_path, cli_config->output_file_name);
  char *token = NULL;
  token = strtok(output_path, ".");
  if (!token) {
    printf("Could not rename meta file\n");
    return 1;
  }
  strcat(token, ".json\0");

  FILE *fp = fopen(output_path, "w");
  if (!fp) {
    printf("Unable to open output file\n");
    return 1;
  }

  fprintf(fp, "{\n");
  fprintf(fp, "\t\"dft_util_metadata\":  {\n");

  fprintf(fp, "\t\t\"cli_config\":  {\n");

  fprintf(fp, "\t\t\t\"input_file\":\"%s\",\n", cli_config->input_file_name);
  fprintf(fp, "\t\t\t\"output_file\":\"%s\",\n",
          cli_config->output_file_name);
  fprintf(fp, "\t\t\t\"algorithm_mode\":\"%s\",\n",
          algorithm_list[cli_config->algorithm_mode]);
  fprintf(fp, "\t\t\t\"output_mode\":\"%s\",\n",
          output_type_list[cli_config->output_mode]);
  fprintf(fp, "\t\t\t\"window_param\":%lf,\n", cli_config->window_param);
  fprintf(fp, "\t\t\t\"output_source\":%d,\n", cli_config->output_source);
  fprintf(fp, "\t\t\t\"sampling_freq\":%lf\n", cli_config->sampling_freq);

  fprintf(fp, "\t\t},\n");
  fprintf(fp, "\t\t\"program_config\":  {\n");

  fprintf(fp, "\t\t\t\"max_input\":%ld,\n", program_config->MAX_INPUT);
  fprintf(fp, "\t\t\t\"output_dir\":\"%s\"\n", program_config->output_dir);

  fprintf(fp, "\t\t},\n");
  fprintf(fp, "\t\t\"output_length\":%d\n", output_length);

  fprintf(fp, "\t}\n");
  fprintf(fp, "}");
  fclose(fp);

  return 0;
}