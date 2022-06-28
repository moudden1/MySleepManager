/**
 * @brief add a cronJob to the cronTab...
 * JOB: * * * * * WD/script.sh WD PID 
 * how to add job to crontab: echo "* * * * * WD/script.sh WD PID" | crontab - 
 *
 * @param script_hard_path : the hard path of the script that will be executed
 * @param pid : the pid of c file reveil.c
 */
void addCronJob(char script_hard_path[255], int pid);

