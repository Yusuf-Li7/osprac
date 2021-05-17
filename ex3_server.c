#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Structure of custom for message
struct mymsgbuf
{
  long mtype;
  struct {
    double mvalue;
    long msender;
  } info;
} mybuf;


void send_response(int msqid, double value, long client) {
  mybuf.mtype = client;
  mybuf.info.mvalue = value;
  mybuf.info.msender = client;
  
  // Send the message
  //If there is an error, report it and delete the message queue from the system
  if (msgsnd(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.info), 0) < 0) {
    printf("Error! Can\'t send response to client\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }
}


void receive_request(int msqid) {
  if (msgrcv(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.info), 1, 0) < 0) {
    printf("Error! Can\'t receive request from client\n");
    exit(-1);
  }
}

int main(void)
{
  int msqid;
  char pathname[] = "ex3_server.c";
  key_t  key;
  double calc_result;

  
  if ((key = ftok(pathname,0)) < 0) {
    printf("Error! Can\'t generate key\n");
    exit(-1);
  }

  
  if ((msqid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
    printf("Server is already running\n");
    exit(-1);
  }

  
  while(1) {
    receive_request(msqid);

    // Shutdown when received = 0.
    if (mybuf.info.mvalue == 0) {
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      printf("Server shut down.\n");
      exit(0);
    }

    
    calc_result = mybuf.info.mvalue * mybuf.info.mvalue;
    send_response(msqid, calc_result, mybuf.info.msender);
  }

  
  return 0;
}
