#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#define MAX_SIZE_QUEUE 20

int num_ppl_ticket;
int num_of_ppl_waiting;
int num_of_ppl_queue;
int num_empty_seats;
int size_of_queue;
int num_ppl_sent;
int driver_pid; 
int ticket_pid;
int queue_pid;
long current_time;
struct timeval start;


void handle_signal_34(int sig){  //ticket to queue maintainer
	size_of_queue = 0;
	kill(ticket_pid,SIGCONT);
}
void handle_signal_35(int sig){  //ticket to queue maintainer
	size_of_queue = 1;
}
void handle_signal_36(int sig){  //ticket to queue maintainer
	size_of_queue = 2;
}
void handle_signal_37(int sig){  //ticket to queue maintainer
	size_of_queue = 3;
}
void handle_signal_38(int sig){  //ticket to queue maintainer
	size_of_queue = 4;
}
void handle_signal_39(int sig){  //ticket to queue maintainer
	size_of_queue = 5;
}
void handle_signal_40(int sig){  //ticket to queue maintainer
	size_of_queue = 6;
}
void handle_signal_41(int sig){  //ticket to queue maintainer
	size_of_queue = 7;
}
void handle_signal_42(int sig){  //ticket to queue maintainer
	size_of_queue = 8;
}
void handle_signal_43(int sig){  //ticket to queue maintainer
	size_of_queue = 9;
}
void handle_signal_44(int sig){  //ticket to queue maintainer
	size_of_queue = 10;
}
void handle_signal_45(int sig){  //ticket to queue maintainer
	size_of_queue = 11;
}
void handle_signal_46(int sig){  //ticket to queue maintainer
	size_of_queue = 12;
}
void handle_signal_47(int sig){  //ticket to queue maintainer
	size_of_queue = 13;
}
void handle_signal_48(int sig){  //ticket to queue maintainer
	size_of_queue = 14;
}
void handle_signal_49(int sig){  //ticket to queue maintainer
	size_of_queue = 15;
}
void handle_signal_50(int sig){  //ticket to queue maintainer
	size_of_queue = 16;
}
void handle_signal_51(int sig){  //ticket to queue maintainer
	size_of_queue = 17;
}
void handle_signal_52(int sig){  //ticket to queue maintainer
	size_of_queue = 18;
}
void handle_signal_53(int sig){  //ticket to queue maintainer
	size_of_queue = 19;
}
void handle_signal_54(int sig){  //ticket to queue maintainer
	size_of_queue = 20;
}

void handle_signal_55(int sig){
	//sigqueue(ticket_pid,SIGRTMIN+size_of_queue,(const union sigval)NULL);
	kill(ticket_pid,SIGRTMIN+size_of_queue);
	kill(ticket_pid,SIGCONT);
}


void handle_signal_56(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=1){
		size_of_queue -= 1;
	}
	printf("Queue size after ride left: %d\n",size_of_queue);
}
void handle_signal_57(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=2){
		size_of_queue -= 2;
	}
	else size_of_queue = 0;
	printf("Queue size after ride left: %d\n",size_of_queue);
}
void handle_signal_58(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=3){
		size_of_queue -= 3;
	}
	else size_of_queue = 0;
	printf("Queue size after ride left: %d\n",size_of_queue);
}
void handle_signal_59(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=4){
		size_of_queue -= 4;
	}
	else size_of_queue = 0;
	printf("Queue size after ride left: %d\n",size_of_queue);
}
void handle_signal_60(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=5){
		size_of_queue -= 5;
	}
	else size_of_queue = 0;
	printf("Queue size after ride left: %d\n",size_of_queue);
}
void handle_signal_61(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=6){
		size_of_queue -= 6;
	}
	else size_of_queue = 0;
	printf("Queue size after ride left: %d\n",size_of_queue);
}
void handle_signal_62(int sig){  //driver to queue maintainer
	printf("Queue size before ride left: %d\n",size_of_queue);
	if(size_of_queue>=7){
		size_of_queue -= 7;
	}
	else size_of_queue = 0;
	printf("Queue size after ride left: %d\n",size_of_queue);
}


void driver_process(){
	while(1){
		int time_wait = (rand()%5)+10;
		sleep(time_wait);
		int num_empty_seats = (rand()%7)+1;
		printf("Ride Capacity: %d\n",num_empty_seats);
		// kill(queue_pid,SIGRTMIN+21+num_empty_seats);
		sigqueue(queue_pid,SIGRTMIN+21+num_empty_seats,(const union sigval)NULL);
		gettimeofday(&start,NULL);
		if(start.tv_sec>current_time+100){
			exit(0);
		}
	}
}

void queue_process(){
	signal(SIGRTMIN+22,handle_signal_56);
	signal(SIGRTMIN+23,handle_signal_57);
	signal(SIGRTMIN+24,handle_signal_58);
	signal(SIGRTMIN+25,handle_signal_59);
	signal(SIGRTMIN+26,handle_signal_60);
	signal(SIGRTMIN+27,handle_signal_61);
	signal(SIGRTMIN+28,handle_signal_62);

	signal(SIGRTMIN+21,handle_signal_55);

	signal(SIGRTMIN+0,handle_signal_34);
	signal(SIGRTMIN+1,handle_signal_35);
	signal(SIGRTMIN+2,handle_signal_36);
	signal(SIGRTMIN+3,handle_signal_37);
	signal(SIGRTMIN+4,handle_signal_38);
	signal(SIGRTMIN+5,handle_signal_39);
	signal(SIGRTMIN+6,handle_signal_40);
	signal(SIGRTMIN+7,handle_signal_41);
	signal(SIGRTMIN+8,handle_signal_42);
	signal(SIGRTMIN+9,handle_signal_43);
	signal(SIGRTMIN+10,handle_signal_44);
	signal(SIGRTMIN+11,handle_signal_45);
	signal(SIGRTMIN+12,handle_signal_46);
	signal(SIGRTMIN+13,handle_signal_47);
	signal(SIGRTMIN+14,handle_signal_48);
	signal(SIGRTMIN+15,handle_signal_49);
	signal(SIGRTMIN+16,handle_signal_50);
	signal(SIGRTMIN+17,handle_signal_51);
	signal(SIGRTMIN+18,handle_signal_52);
	signal(SIGRTMIN+19,handle_signal_53);
	signal(SIGRTMIN+20,handle_signal_54);
	while(wait(NULL)!=-1){}
}

void ticket_process(){
	signal(SIGRTMIN+0,handle_signal_34);
	signal(SIGRTMIN+1,handle_signal_35);
	signal(SIGRTMIN+2,handle_signal_36);
	signal(SIGRTMIN+3,handle_signal_37);
	signal(SIGRTMIN+4,handle_signal_38);
	signal(SIGRTMIN+5,handle_signal_39);
	signal(SIGRTMIN+6,handle_signal_40);
	signal(SIGRTMIN+7,handle_signal_41);
	signal(SIGRTMIN+8,handle_signal_42);
	signal(SIGRTMIN+9,handle_signal_43);
	signal(SIGRTMIN+10,handle_signal_44);
	signal(SIGRTMIN+11,handle_signal_45);
	signal(SIGRTMIN+12,handle_signal_46);
	signal(SIGRTMIN+13,handle_signal_47);
	signal(SIGRTMIN+14,handle_signal_48);
	signal(SIGRTMIN+15,handle_signal_49);
	signal(SIGRTMIN+16,handle_signal_50);
	signal(SIGRTMIN+17,handle_signal_51);
	signal(SIGRTMIN+18,handle_signal_52);
	signal(SIGRTMIN+19,handle_signal_53);
	signal(SIGRTMIN+20,handle_signal_54);
	while(1){
		int time_wait = (rand()%15)+5;
		//printf("%d\n",time_wait);
		sleep(time_wait);
		int new_ppl = (rand()%6)+1;
		printf("%d people bought a ticket\n",new_ppl);
		//kill(queue_pid,SIGRTMIN+21);
		sigqueue(queue_pid,SIGRTMIN+21,(const union sigval)NULL);
		kill(getpid(),SIGSTOP);
		num_ppl_ticket += new_ppl;
		int num_ppl_free = MAX_SIZE_QUEUE - size_of_queue;
		if(num_ppl_ticket>num_ppl_free){
			printf("%d people sent to ride queue\n",num_ppl_free);
			num_ppl_free = 0;
			num_ppl_ticket -= num_ppl_free;
			size_of_queue +=num_ppl_free;
		}
		else{
			printf("%d people sent to ride queue\n",num_ppl_ticket);
			size_of_queue += num_ppl_ticket;
			num_ppl_ticket = 0;
			num_ppl_free = 0;
		}
		//kill(queue_pid,SIGRTMIN+size_of_queue);
		sigqueue(queue_pid,SIGRTMIN+size_of_queue,(const union sigval)NULL);
		//kill(getpid(),SIGSTOP);
		gettimeofday(&start,NULL);
		if(start.tv_sec>current_time+100){
			exit(0);
		}
	}
}


int main(void){
	size_of_queue = 0;
	num_ppl_ticket = 0;
	num_of_ppl_waiting = 0;
	num_of_ppl_queue = 0;
	num_empty_seats = 0;
	size_of_queue = 0;
	num_ppl_sent = 0;
	srand(time(0));
	queue_pid = getpid();
	driver_pid = fork();
	gettimeofday(&start,NULL);
	current_time = start.tv_sec;
	if(driver_pid == 0){
		driver_process();
	}
	ticket_pid = fork();
	if(ticket_pid == 0){
		ticket_process();
	}
	queue_process();
	//while(wait(NULL)!=-1){}
	exit(0);
}
