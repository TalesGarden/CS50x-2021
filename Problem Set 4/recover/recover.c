#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>


typedef uint8_t BYTE;
bool isJPEG(BYTE buffer[]);
void writeBuffer(BYTE buffer[], FILE *f, char *filename_out);
int count = 0;   //count the number of files

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("\n Enter the name of a file");
        return 1;
    }

    char *file_name = argv[1];

    FILE *f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("Could not open %s.\n", file_name);
        return 1;
    }
    int end;
    char filename_out[10];
    bool true_false;
    BYTE buffer[512];
    BYTE *aux_buffer = buffer;

    do
    {
        if (count < 1)
        {
            end = fread(buffer, sizeof(buffer), 1, f);
        }

        true_false = isJPEG(buffer);

        if (true_false)
        {
            sprintf(filename_out, "%03i.jpg", count++);
            writeBuffer(buffer, f, filename_out);
        }
    }
    while (!feof(f));

    fclose(f);

}
// check if is a JPEG file
bool isJPEG(BYTE buffer[])
{
    bool last_byte = ((buffer[3] >= 224) && (buffer[3] <= 239));
    if ((buffer[0] == 0xff)  && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && last_byte)
    {
        return true;
    }
    return false;
}
//create a file and save
void writeBuffer(BYTE buffer[], FILE *f, char *filename_out)
{

    FILE *img = fopen(filename_out, "a");
    if (img == NULL)
    {
        printf("\nCould not open to write %s\n", filename_out);
        return;
    }
    int end = 0;
    bool true_false;
    do
    {
        fwrite(buffer, sizeof(BYTE), 512, img);
        end = fread(buffer, sizeof(BYTE), 512, f);
        true_false = isJPEG(buffer);

        if (end < 1)
        {
            break;
        }

    }
    while (!true_false);

    fclose(img);
}