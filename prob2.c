#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#define N 50

int main()
{
	int x = 0;
	struct Process {
		int pid;
		int ppid;
		int numChild;
	};
	key_t key = ftok("/Desktop/OSprograms/lab3",68);
	//key_t key2 = ftok("/Desktop/OSprograms",68);
	//printf("%x %x\n",key,key2);
	int shmid = shmget(key,N*sizeof(struct Process),0666 | IPC_CREAT);
	//int shmid2 = shmget(key2,sizeof(int),0666 | IPC_CREAT);
	struct Process* tree = (struct Process*)shmat(shmid,0,0);
	//int* size = (int*)shmat(shmid2,0,0);
	//printf("%d %d\n",shmid,shmid2);
	//*size = 0;
	//printf("%d\n",*size); 
	int firstProcessChild = 0;
	int numLevels = 0;
	int totalChild = 0;
	int lastLevel = 0;
	scanf("%d %d",&firstProcessChild,&numLevels);
	int nchild = firstProcessChild;
	totalChild+=nchild;
	for(int i=1;i<numLevels;i++){
		if(i==numLevels-1){
			lastLevel = totalChild;
		}
		int tempChild = (nchild*(nchild+1))/2;
		totalChild += tempChild;
		nchild = tempChild;
	}
	printf("%d %d\n",totalChild,lastLevel);
	tree[0].pid = 0; //numLevels
	tree[0].numChild = 1; //size of arr
	tree[0].ppid = 0; 
	tree[1].pid = getpid();
	tree[1].numChild = firstProcessChild;
	tree[1].ppid = getppid();
	int posNumber= 0;
	//printf("%d %d\n",tree[1].pid,tree[1].numChild);
	int numChildCreate = firstProcessChild;
	here:
		if(tree[0].pid == totalChild){
			shmdt(tree);
			exit(0);
			//goto here2;
		}
		int pidCheck = getpid();
		for(int i = 1;i<=tree[0].numChild;i++){
			if(tree[i].pid == pidCheck){
				numChildCreate = tree[i].numChild;
				//posNumber = i;
				printf("%d %d\n",getpid(),numChildCreate);
				break; 
			}
		}
		for(int i = 0;i<numChildCreate;i++){
			int pidCreated = fork();
			if(pidCreated){
				kill(pidCreated,SIGSTOP);
				tree[0].numChild++;
				tree[tree[0].numChild].pid = pidCreated;
				tree[tree[0].numChild].numChild = numChildCreate+i;
				tree[tree[0].numChild].ppid = getpid();
				if(getpid() == tree[1].pid){
					tree[tree[0].numChild].numChild = i+1;
				}
				if(tree[0].numChild>lastLevel+1){
					tree[tree[0].numChild].numChild = 0;
				}
			}
			else{
				struct Process* tree = (struct Process*)shmat(shmid,0,0);
				goto here;
			}
		}
	here2:
		tree[0].pid++;
		while(x!=-1){
			x=waitpid(-1,NULL,WUNTRACED);
			kill(x,SIGCONT);
		}
		if(getpid() != tree[1].pid){
			shmdt(tree);
			exit(0);
		}
	shmctl(shmid, IPC_RMID, NULL);
	for(int i = tree[0].numChild;i>0;i--){
		printf("Child: %d, Parent: %d\n",tree[i].pid,tree[i].ppid);
	}
	exit(0);
}
