#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include <stdbool.h>
#include<string.h>

typedef struct{
    char* buffer; // a pointer to hold user's input string
    size_t buffer_length; //allocated size of buffer
    ssize_t input_length; // actual lenght of user input 
} InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer)); //reserves enough heap memory to hold one Input Buffer
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt(){
    printf("db > ");
}

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length),stdin);
    //number of characters read including \n 

    if(bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1; //ignores newline
    input_buffer->buffer[bytes_read - 1] = 0; //replace newline with null terminator
}

void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();

    while(true){
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer,".exit") == 0){
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Unrecognised command '%s'.\n",input_buffer->buffer);
        }
    }
}