#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

int matrix[5][5] = {
	{0,0,1,0,0},
	{1,0,0,1,0},
	{1,1,0,1,1},
	{1,0,0,1,0},
	{1,0,0,0,0},
};
int vis[5][5] = {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};
int x_val = 0;
int y_val = 0;
int last_row = 4;
int last_col = 4;
int pidfirst = 0;

int dfs(){
	int pid;
	int status=0;
	if(x_val < last_row){
		if(vis[x_val+1][y_val]==0){
			vis[x_val+1][y_val] = 1;
			pid = fork();
			if(pid==0){
				x_val++;
				if(matrix[x_val][y_val] == 1){
					exit(0);
				}
				else if(x_val==last_row && y_val==last_col){
					exit(last_row*10+last_col);
				}
				else{
					dfs();
				}
			}	
		}
	}
	if(y_val < last_col){
		if(vis[x_val][y_val+1]==0){
			vis[x_val][y_val+1] = 1;
			pid = fork();
			if(pid==0){
				y_val++;
				if(matrix[x_val][y_val] == 1){
					exit(0);
				}
				else if(x_val==last_row && y_val==last_col){
					exit(last_row*10+last_col);
				}
				else{
					dfs();
				}
			}
		}
	}
	int val_prin = 0;
	while(waitpid(-1,&status,0)!=-1){
		//printf("%d\n",status);
		status/=256;
		if(status != 0){
			val_prin++;
			int x_print = status/10;
			int y_print = status%10;
			printf("Val: %d %d\n",x_print,y_print);
		}
	}
	//printf("%d %d\n",x_val,y_val);
	int num = x_val*10+y_val;
	//printf("num: %d\n",num);
	//exit(num)
	if(val_prin==0){
		exit(0);
	}
	if(pidfirst==getpid()){
		printf("Val: 0 0\n");
	}
	exit(num);
}

int main(int argc, char* argv[]){
	pidfirst = getpid();
	dfs();
	exit(0);
}
