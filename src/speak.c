#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>


int main (int argc, char* argv[])
{
    if (argc <=1) {
        DIR *dp;
        struct dirent *dirp;
        char path [300];
        getcwd(path,300);
    
        argv[1] = path;
        if ((dp = opendir(argv[1])) == NULL) {
             perror("ERROR");
        }

        while ((dirp = readdir(dp)) != NULL)
            if(dirp -> d_type == DT_REG){ //ONLY FILES ARE PRINTeD, NO DIRECTORIES.
                //printf("%hhu\n", dirp -> d_type);
                
                if(strstr(dirp->d_name,"char-")){ //printing only characters.
                    char character[30];
                    strcpy(character,dirp->d_name);
                    char *last = strchr(character,'-');
                    char charname[20];
                    memset(charname, 0, sizeof charname); //resetting the array
                    int i = 1;
                    while(last[i]!='.'){
                        charname[i-1] = last[i];
                        i++;
                    }
                   
                    printf("\n%s\n\n", charname);
                    memset(charname, 0, sizeof charname); //resetting the array
                    
                }
            }

        if (closedir(dp) == -1)
            perror("closedir");

    }else if(argc==2){

        char character [30];

        strcpy(character, "char-");
        strcat(character,argv[1]);
        strcat(character,".txt");
        int fd = open(character, O_RDONLY); 

        if(fd<0){

            puts("Who? \nAm i talking with ghosts?");
            exit(0);

        }
        
        char buf[(5*90)];
        int lung = sizeof(buf);
        int lower = 0, upper = 4;
        srand(time(0));
        int num = (rand() % (upper - lower + 1)) + lower;           //RANDOMLy SELECTING ONE Of THE DIALOGueS.
        lseek(fd,0,SEEK_SET);
        lseek(fd,lung*num+13,SEEK_CUR);

        read(fd,buf,sizeof(buf)); //read as much as a chunk of dialogue in file
        
             puts("\n");
             write(0,buf,lung); //write on terminal
             puts("\n");

        close(fd);
    }

}