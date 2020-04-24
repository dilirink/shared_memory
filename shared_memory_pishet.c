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
#include <stdio.h>
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

        const char* message_0 = "Hello"; 
        const char* message_1 = "World!"; 

        int shm_fd; 

        void* ptr; 

        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 

        ftruncate(shm_fd, SIZE); 

        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 

        sprintf(ptr, "%s", message_0); 
    
        ptr += strlen(message_0); 
        sprintf(ptr, "%s", message_1); 
        ptr += strlen(message_1); 
        return 0; 
        
    }

    if(!strcmp(argv[1], "--systemV"))
    {    
        key_t key = ftok("shmfile",65);    
        struct shmid_ds shmbuffer; 
        int segment_size; 
        const int shared_segment_size = 0x6400; 
        char fp[]="hello world";
        int segment_id = shmget(key,1024,0666|IPC_CREAT); //создали
        char *shared_memory = (char*) shmat (segment_id, 0, 0); 
        printf ("shared memory address %p\n", shared_memory); //подключили общую памать по адресу

        shmctl (segment_id, IPC_STAT, &shmbuffer);    //
        segment_size = shmbuffer.shm_segsz;          ///размер сегмента общей памяти
        printf ("segment size: %d\n", segment_size); //
        strcat(shared_memory,"Hello world"); //записали в общую память
       
        
        shmdt (shared_memory); //отключились от общей памяти

    }
}