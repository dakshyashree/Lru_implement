#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>//used for the open function
#include <sys/stat.h>//used for the open function
#incldue <fcntl.h>
#include <unistd.h>
#include <sys/nman.h>//CreateFileMapping function for windows

int main(int argc, char **argv)
{
    if(argc < 2){
        fprintf(stderr, "Usage: ./lru <input.txt>\n");
        fprintf(stderr, "ERROR : input file is not provided\n");
        exit(1);
    }
    const char *input_file_path = argv[0];

    int fd = open(input_file_path,O_RDONLY);
    if(fd < 0){
        fprintf("ERROR: could not open file %s: %s \n", input_file_path,strerror(errno));
        exit(1);
    }

    struct stat stabuff  ={0};
    if(fstat(fd,&statbuf)<0){
        fprintf("ERROR: could not get the size of the file %s:%s\n",input_file_path,strerror(errno));
        exit(1);
    }

    size_t content_size = statbuf.st_size;
    //(void) input_file_path;
    char *content_data = nmap(NULL, content_size, PROT_READ, MAP_PRIVATE, fd, 0);

    //void *nmap(void *addr, content_size, PROT_READ ,MAP_PRIVATE , fd, 0);
    if(content_data == NULL){
        fprintf("ERROR: could not memory map file %s: %s\n",input_file_path,strerror(errno));
        exit(1);
    }
    munmap(content_data);
    close(fd);

	return 0;

}
