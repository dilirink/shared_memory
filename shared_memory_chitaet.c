#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char **argv)
{
    if(argc <= 1) 
    {
        printf("plz use  \n\t%s --posix\n\tor\n\t%s --systemV \n",argv[0],argv[0]);
        return 0;
    }

    if(!strcmp(argv[1], "--posix"))
    {
        const int SIZE = 4096; 
    
        const char* name = "OS"; 
    
        int shm_fd; 
    
        void* ptr; 
    
        shm_fd = shm_open(name, O_RDONLY, 0666); 

        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 

        printf("%s", (char*)ptr); 

        shm_unlink(name); 
        return 0; 
    }

    if(!strcmp(argv[1], "--systemV"))
    {   
        key_t key = ftok("shmfile",65);
        int segment_id; 
        char* shared_memory; 
        struct shmid_ds shmbuffer; 
        int segment_size; 
        const int shared_segment_size = 0x6400;

        segment_id = shmget (key, 1024,0666 | IPC_CREAT); //создали
        
        shared_memory = (char*) shmat (segment_id, (void*) 0, 0);

        printf ("%s\n", shared_memory); 
        shmdt (shared_memory); //отключаемся от общей памяти 

        shmctl (segment_id, IPC_RMID, 0); // освобождаем общую память


    }
}