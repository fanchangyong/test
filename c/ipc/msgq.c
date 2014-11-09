#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

char* file = ".";
int proj_id = 1;

int main(int argc,char** argv)
{
	key_t key = ftok(file,proj_id);
	if(key==-1)
	{
		perror("ftok");
		return 1;
	}

	int qid = -1;
	if((qid=msgget(key,IPC_CREAT|0660))==-1)
	{
		perror("msgget");
		return 1;
	}



	return 0;
}
