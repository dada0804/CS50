// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //uint8_t is a type that stores an 8-bit unsigned (i.e., not negative) integer.
    //We can treat each byte of a WAV file’s header as a uint8_t value.
    uint8_t header[44];
    for (int i = 0; i < 44; i++)
    {
        fread(&header, sizeof(header[0]), 1, input);
        fwrite(&header, sizeof(header[0]), 1, output);
    }

    // fread(&header, sizeof(header[0]), 44, input);
    // fwrite(&header, sizeof(header[0]), 44, output);

    // TODO: Read samples from input file and write updated data to output file
    // int16_t is a type that stores a 16-bit signed (i.e., positive or negative) integer.
    // We can treat each sample of audio in a WAV file as an int16_t value.
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        int16_t new = factor * buffer;
        fwrite(&new, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}


