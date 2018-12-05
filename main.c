#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(){

  key_t key;
  int shmid;
  char* data;
    
  shmid = shmget(key, 200, 0777 | IPC_CREAT);
  key = ftok('.', 'R');
  data = shmat(shmid,(void *) 0, 0);
  
  if(data[0]){
    printf("shared contents: %s\n", data);
  }else{
    printf("just created\n");
  }
  
  printf("do you want to change data? [y\\n]: \n");
  char * ans = malloc(10);
  fgets(ans, 10, stdin);
  
  //char * yes = "y";
  if (strcmp(ans, "y")){
    printf("enter data: \n");
    fgets(data, 200, stdin);
    printf("shared contents now: %s\n", data);
  }
  
  printf("do you want to delete data? [y\\n]: \n");
  char * ans2 = malloc(10);
  fgets(ans2, 10, stdin);
  
  if (strcmp(ans2, "y")){
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("data deleted\n");
  }
  
}
