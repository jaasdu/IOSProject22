#include <fcntl.h>
#include<limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <libgen.h>

int copyfile(char* infilename, char* outfileDir) {
    FILE* infile; //File handles for source and destination.
    FILE* outfile;
    char outfilename[PATH_MAX];

    infile = fopen(infilename, "r"); // Open the input and output files.
    if (infile == NULL) {
      return -1;
    }
    sprintf(outfilename, "%s/%s", outfileDir, basename(infilename));

    outfile = fopen(outfilename, "w");

    char buf[4096];
             int lung;

            while(fgets(buf,sizeof(buf), infile)) //read as much as 4096 in file
            {
                fputs(buf,outfile); //COPY CONTENT OF FILE 
            }
            fclose(infile);
            fclose(outfile);
}


int main (int argc, char* argv[])
{
    char path[PATH_MAX];
    getcwd(path, sizeof(path));
    char* p = strstr(path, "IOSProject22");
    p[0] = 0;
    strcat(path, "IOSProject22/gameTree/inventory");

    //printf("%s", path);


if(strstr(argv[1], "possiblekid") !=NULL || strstr(argv[1], "kid")!=NULL){

        char character [30];
        memset(character, 0, sizeof character); //resetting the array


        strcat(character, "char-");
        strcat(character, argv[1]);
        strcat(character, ".txt");
        char characterPath[PATH_MAX];
        getcwd(characterPath, sizeof(characterPath));
        strcat(characterPath, "/");
        strcat(characterPath, character);
        int chara = open(characterPath, O_RDONLY);
        if(chara < 0){
            printf("There isn't such object\n");
            return -1;
        }else{
            copyfile(characterPath, path);    
            memset(character, 0, sizeof character); //resetting the array
            unlink(characterPath);
            return 0;

           }

    }else if(strcmp (argv[1], "notes")!=0){
        char object [30];

        memset(object, 0, sizeof object); //resetting the array

        strcat(object, "item-");
        strcat(object, argv[1]);
        strcat(object, ".txt");
        char objectPath[PATH_MAX];
        getcwd(objectPath, sizeof(objectPath));
        strcat(objectPath, "/");
        strcat(objectPath, object);
        //printf("%s", objectPath);
        int obj = open(objectPath, O_RDONLY);
        //printf("%d", obj);
        if(obj < 0){
            printf("There isn't such object\n");
            return -1;
        }else{
            
            copyfile(objectPath, path);    

            memset(object, 0, sizeof object); //resetting the array

            unlink(objectPath);
            return 0;


    }

    }else if(strcmp (argv[1], "notes")==0){
        printf("I better keep those in my hand... i need to look quickly\n");
        return 0;
    }
}



