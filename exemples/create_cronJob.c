#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// TODO: execute this || echo "* * * * * WD/script.sh WD PID" | crontab - ||

/**
 * @brief add a cronJob to the cronTab...
 *
 * @param script_hard_path : the hard path of the script that will be executed
 * @param pid : the pid of c file reveil.c
 */
void addCronJob(char script_hard_path[255], int pid);

int main() {
	char linux_command[255];	
	int pid = getpid();

	addCronJob("xxxx/scrip.sh", pid);

	return 0;
}

void addCronJob(char script_hard_path[255], int pid) {
	char linux_command[255];

	sprintf(linux_command, "echo \"* * * * * %s %d\" | crontab -", script_hard_path, pid);

	system(linux_command);
	printf("%s\n", linux_command);
}
