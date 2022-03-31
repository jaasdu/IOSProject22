// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "go.h"
#include "investigate.h"

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20

/////////// reading commands:



int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
   int ret,i;

   *argcp = 0;
   *eofp = 0;
   i=0;
   while ((ret=read(0,cmd+i,1)) == 1) {
      if (cmd[i]=='\n') break;  // correct line
      i++;
      if (i>=MAXLINE) {
         ret=-2;        // line too long
         break;
      }
   }
   switch (ret)
   {
     case 1 : cmd[i+1]='\0';    // correct reading 
              break;
     case 0 : *eofp = 1;        // end of file
              return 0;
              break;
     case -1 : *argcp = -1;     // reading failure
              fprintf(stderr,"Reading failure \n");
              return 0;
              break;
     case -2 : *argcp = -1;     // line too long
              fprintf(stderr,"Line too long -- removed command\n");
              return 0;
              break;
   }
   // Analyzing the line
   cmdp= cmd;
   for (i=0; i<max; i++) {  /* to show every argument */
      if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
      cmdp= NULL;
   }
   if (i >= max) {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   *argcp= i;
   return 1;
}

///////////////////////////////////////

int execute(int argc, char *argv[])
{
    pid_t pid;
		// If the quit statement is found 
		if(strcmp(*(argv), "quit") == 0)			
			exit(0);
		
		if(strcmp(argv[0], "go") == 0) {
        //pid = fork();
        
        //if(pid ==0){
			go(argc, argv);
          
        //}
           // kill(pid, SIGKILL);
			//go(argc, argv);
		}		
      if(strcmp(argv[0], "investigate") == 0) {

         investigate(argc, argv);

      }
		

}

int main ()
{
   chdir("gameTree/Home");
   char dir [MAXLINE]; 
   getcwd(dir, sizeof(dir));
   char *last = strrchr(dir, '/');
   char * Prompt = strcat(last+1, ">");
   int eof= 0;
   int argc;
   char *args[MAXARGS];

    
   while (1) {
      getcwd(dir, sizeof(dir));
      char *last = strrchr(dir, '/');
      char * Prompt = strcat(last+1, ">");
      write(0,Prompt, strlen(Prompt));
      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         
         execute(argc, args);
        
      }
     
      if (eof) exit(0);
   }
}