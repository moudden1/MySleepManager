#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/cronJobs.h"

void addCronJob(char script_hard_path[255], int pid) {
	char linux_command[255];

	sprintf(linux_command, "echo \"0 2 * * * %s %d\" | crontab -", script_hard_path, pid);

	system(linux_command);
	printf("%s\n", linux_command);
}
