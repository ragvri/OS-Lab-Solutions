#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "PageTable.h"
#include<time.h>

int numPage,numFrame;
page_table_pointer PageTable;
int * FrameTable;

void printPageTable()
{
	for (int i =  0;i < numPage;i++)
    {
        printf("%2d: Valid=%1d Frame=%2d Dirty=%1d Requested=%1d\n",i,PageTable[i].Valid,PageTable[i].Frame,PageTable[i].Dirty,
PageTable[i].Requested);
    }
}

void ContinueHandler(int signal)
{
	static int disk = 0;
	srand(time(0));
	int page = INT_MAX;
	for(int i=0;i<numPage;i++)
	{
		if(PageTable[i].Requested!=0)
		{
			page = i;
			break;
		}
	}
	if(page == INT_MAX)
	{
		printf("Final state of Page Table \n");
		printPageTable();
		printf("Total disk access = %d \n",disk);
		if (shmdt(PageTable) == -1)
		{
        	perror("ERROR: Error detaching segment\n");
    	}
		exit(EXIT_FAILURE);
	}
	int MMUID = PageTable[page].Requested;
	printf("requested Page by MMU Process %d\n",page);
	PageTable[page].Requested = 0;

	int FrameNum = -1;
	for(int i=0;i<numFrame;i++)
	{
		if(FrameTable[i]==-1)
		{
			FrameNum = i;
			break;
		}
	}
	if(FrameNum != -1)
	{
		printf("Page %d is Put in %d\n",page,FrameNum);
		FrameTable[FrameNum] = page;
		PageTable[page].Frame = FrameNum;
		PageTable[page].Valid = 1;
		disk++;
		sleep(1);
	}
	else
	{
		int replacedFrame = rand()%numFrame;
		int replacedPage = FrameTable[replacedFrame];
		printf("Replaced Page =  %d\n",replacedPage);
		if(PageTable[replacedPage].Dirty == 1)
		{
			printf("Page is dirty, write out\n");
			disk++;
			sleep(1);
		}
		FrameTable[replacedFrame]=page;
		PageTable[replacedPage].Dirty = 0;
		PageTable[replacedPage].Valid = 0;
		PageTable[replacedPage].Frame = -1;
		PageTable[page].Frame = replacedFrame;
		PageTable[page].Valid = 1;
		printf("Page %d is put in frame %d\n",page,replacedFrame);
		disk++;
		sleep(1);
	}
	kill(MMUID,SIGCONT);
	printPageTable();
}


int main(int argc ,char** argv)
{
	if(argc != 3)
	{
		printf("Please enter valid Input");
		return 0;
	}  
	numPage = atoi(argv[1]);
	numFrame = atoi(argv[2]);
	int Key = getpid();
    int SID;
	if((SID = shmget(Key,numPage*sizeof(page_table_entry),IPC_CREAT | 0666)) == -1 ||(PageTable = (page_table_pointer)shmat(SID,NULL,0))==NULL)
	{
	      perror("ERROR: Could not get page table");
          exit(EXIT_FAILURE);
    }
    if (signal(SIGUSR1,ContinueHandler) == SIG_ERR)
    {
        printf("ERROR: Could not initialize continue handler\n");
        exit(EXIT_FAILURE);
    }	
	printf("OS Process ID is %d\n",Key);
	for(int i=0;i<numPage;i++)
	{
		PageTable[i].Valid = 0;
		PageTable[i].Frame = -1;
		PageTable[i].Dirty = 0;
		PageTable[i].Requested = 0;
	}	
	printf("page table initialized\n");
	FrameTable = malloc(numFrame*sizeof(int));
    for(int i=0;i<numFrame;i++)
	{
		FrameTable[i] = -1;
	}
    while(1)
	{
		sleep(1);
	}
}
