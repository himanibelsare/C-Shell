#include "headers.h"

int sig(char * buffer_command)
{
	strtok(buffer_command, " ");
	int jobNumber = atoi(strtok(NULL, " "));
	int signalNo = atoi(strtok(NULL, " "));

    // printf("%d %d\n", jobNumber, signalNo);
	if(jobNumber == 0)
	{
		printf("Job Number does not exist\n");
		return 1;
	}
    // if(signalNo == 0)
	// {
	// 	printf("Signal Number does not exist\n");
	// 	return;
	// }

    int temp = kill(jobNumber, signalNo);
    if (temp < 0) 
    {
        perror("Error");
        return -1;
    }

}