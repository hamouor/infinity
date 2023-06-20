#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10
  
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
  
    sprintf(message.mesg_text, "%s", "ping");
  
    msgsnd(msgid, &message, sizeof(message), 0);
  
    return 0;
}