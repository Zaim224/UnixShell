/******************************************************************************
Zaim Hassan
Project Shell command prompt
*******************************************************************************/


#include "fork.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




void clear(Command **head){//this function does the history -c command

  while(*head!=NULL){
        Command *freer = *head;
        *head = (*head)->next;
        //Command* args = freer;
        for(int i=0; i<freer->argumentslength; i++){
            free(freer->arguments[i]);
        }
        free(freer->command);
        free(freer);
    }
    *head = NULL;
}

	


 void history(Command *head ){//this does the history function

    Command *dummy =head;
    int j=0;

    if(head->command == NULL){
      return;
    }

    	while(dummy != NULL){
        if(dummy->argumentslength==1){
          printf("%d:  \n", j,dummy->command);
        j++;
        }
        else{
		printf("%d: %s ", j,dummy->command);
		 for(int i=1; i<dummy->argumentslength; i++){
            printf("%s", dummy->arguments[i]);
        }
        printf("\n");

    j++;
        }
        dummy = dummy->next;
      }
            
    
		
	}

 

 void delete(Command *head){//this is the delete function, it frees all memory

    while(head!=NULL){
        Command *freer = head;
        head = head->next;

        for(int i=0; i<freer->argumentslength; i++){
            free(freer->arguments[i]);
        }
        free(freer->command);
        free(freer);
    }
    
    exit(1);
 }


 int add(Command ** head, Command * newNode){//adds nodes to linked list
 if(*head == NULL){
        *head = newNode;

        return 0;
    }
else{
Command * trav =*head;
    while(trav->next != NULL){
        trav=trav->next;

    }
    newNode->next= trav->next;
    trav->next = newNode;
 
    return 0;
     
    
 }
 }
int main()
{

int cond=0;
int indexer=0;
Command *head = NULL;

    char input[1000000]= {'\0'};
while(1)
{
  

    printf("262$");

    if(fgets(input, 1000000, stdin) == NULL){
      exit(1);
    }
    if(strcmp(input,"\n") == 0){
      continue;
    }

    
  fflush(stdout);
  if(strcmp(input,"exit\n") == 0){//does exit command

    delete(head);
    exit(1);
  }
  input[strcspn(input, "\n")] = 0;//strips the \n from the input

    char second[100000] = "\0";
    strcat(second, input);
    const char s[] = " ";
    const char v[]=" ";
    char* c;
     int len=0;

   for(int i=0; i<strlen(second);i++){//finds the length of a arguments
   if(second[i] == ' '){
     len++;
   }

  }
  len++;

       if(len >128){//over 127 arguments check
         printf("error: too many arguments\n");
         continue;
       }

    c = strtok(input, s);//breaks the string to each singular string
    if(strcmp(second, "history") ==0){//if the input is history call the history command

      if (head == NULL)
      {
        continue;
      }
      history(head);

    }

    else{
    int index =0;
      Command*command1 = (Command*)malloc(sizeof(Command));//malloc the struct
       command1->command = malloc(sizeof(char)*1500);//malloc the command
       command1->arguments = malloc(sizeof(char*)*len);//malloc the args
       
       for(int i=0; i<len; i++){
         command1->arguments[i] = malloc(sizeof(char*) * 1500);//malloc for each argument
       }
       if(command1->argumentslength >127){
         printf("error: too many arguments\n262$262$262$");
         exit(1);
       }
       command1->argumentslength = len;
       command1->index=indexer;
       indexer++;
    while(c!=NULL){

      if (index == 0){
       strcpy(command1->command,c);//sets command to command
       strcpy(command1->arguments[0], c);//sets first argument to command

       
        index++;
        c = strtok(NULL,v);//next string
        
      }
      else{
        strcpy(command1->arguments[index], c);//puts in the argument

        c = strtok(NULL,v);
        index++;
      }

    } 
    command1->arguments[index] = NULL;




    
    if(strcmp(command1->command, "history") == 0){


    
     if(strcmp(command1->arguments[1], "-c") == 0){//does histor -c checks and functiom call

     if(head->command ==NULL){
       continue;
     }
      clear(&head);

      command1 = NULL;//sets head to clear 
      head=NULL;

    }
    else if(strcmp(command1->arguments[1], "-c") !=0 && command1->argumentslength >1){//does history offset
      int num = atoi(command1->arguments[1]);

      Command * dummy = head; 

    while(dummy!=NULL){





    if(dummy->index == num){//finds the mathcing index

      Command*command2 = (Command*)malloc(sizeof(Command)); //creates new node for for the new call
       command2->command = malloc(sizeof(char)*1500);
       command2->arguments = malloc(sizeof(char*)*dummy->argumentslength);
       strcpy(command2->command, dummy->command);
       
       for(int i=0; i<dummy->argumentslength; i++){
         command2->arguments[i] = malloc(sizeof(char*) * 1500);
         strcpy(command2->arguments[i] , dummy->arguments[i]);
         
       }
       command2->index = indexer;
        command2->argumentslength = dummy->argumentslength;


   if(strcmp(command2->command, "cd") == 0){//checks for cd comamnd

      int call = chdir(command2->arguments[1]);//chdir call

      if(call !=0){
        fprintf(stderr, "error: %s\n", strerror(errno));
      }


    }
    else{
      

      int call = call_exe(command2);//this si the call exe call
      if (call != 0){
        fprintf(stderr, "error: %s\n", strerror(call));
      } 
    }



        break;
    }





    dummy = dummy->next;
    }

    }
    

    continue;
    }

    else if(strcmp(input, "exit\n")==0 || strcmp(command1->command, "exit\n") == 0){//another exit call

      exit(1);

      cond = add(&head, command1);
      delete(head);
      exit(1);
    }
    //printf("%s the command is \n", command1->command);
   if(strcmp(command1->command, "cd") == 0){//checks for cd comamnd
      //printf("\nthis is the command sending in %s and the arg is %s\n", command1->command , command1->arguments[1]);
      int call = chdir(command1->arguments[1]);
      //printf("%d", call);
      if(call !=0){
        fprintf(stderr, "error: %s\n", strerror(errno));
      }


    }
    else{
      

      int call = call_exe(command1);//call exe line if not cd or exit
      if (call != 0){
        fprintf(stderr, "error: %s\n", strerror(call));
      } 
    }

    cond = add(&head, command1);//add command to the linked list
    
    }
    
    }
    delete(head);
}
    

//delete(head);



