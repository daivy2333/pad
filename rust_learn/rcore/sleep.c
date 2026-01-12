#include<stdio.h>
#include<unistd.h>

int main()
{
    sleep(5);
    const char* hello_string = "hello Linux\n";
    printf(hello_string);
    FILE *output_file = fopen("output.txt", "w");
    fputs(hello_string, output_file);
    fclose(output_file);
    return 0;
}