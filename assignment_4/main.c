#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum mode { NONE, FIFO, LRU };

int main(int argc, char **argv)
{
    char *algorithm = NULL;
    const char *filename = "ref3.txt";
    int frame_count = -1;    

    enum mode current_mode = NONE;
    int ref_count = -1;

    FILE *input = fopen(filename, "r");
    if (input == NULL)
    {
        printf("Can't open file for reading or file not found!\n");
        return 1;
    }

    const int input_count = 256;
    char std_input[input_count];
    
    printf("Algorithm: ");
    if (!algorithm)
    {
        fgets(std_input, input_count, stdin);

        int a;
        for (a = 0; a < input_count; ++a)
        {            
            if (std_input[a] == '\n')
            {
                break;
            }
            std_input[a] = tolower(std_input[a]);
        }

        algorithm = std_input;
    }
    if (strcmp(algorithm, "fifo\n") == 0)
    {
        current_mode = FIFO;        
    }
    else if (strcmp(algorithm, "lru\n") == 0)
    {
        current_mode = LRU;
    }

    printf("No. of frames: ");
    if (frame_count == -1) 
    {
        fgets(std_input, input_count, stdin);
        frame_count = atoi(std_input);
    }

    printf("No. of reference string: ");
    if (ref_count == -1) 
    {
        fscanf(input, "%d", &ref_count);
    }
    printf("%d\n", ref_count);

    int i;

    printf("reference string: ");
    int least_recently_used[ref_count];
    for (i = 0; i < ref_count; ++i)
    {
        least_recently_used[i] = -1;
    }

    int ref_strings[ref_count];
    for (i = 0; i < ref_count; ++i)
    {
        int j;
        fscanf(input, "%d ", &j);
        ref_strings[i] = j;
        printf("%d ", ref_strings[i]);
    }

    printf("\n\n");
        
    int fault[ref_count];
    for (i = 0; i < ref_count; ++i)
    {
        fault[i] = 1;
    }

    int frame[frame_count];
    for (i = 0; i < frame_count; ++i)
    {
        frame[i] = -1;
    }

    int f = 0, step = 0;    
    for (i = 0; i < ref_count; ++i)
    {
        if (current_mode != NONE)
        {
            printf("\t%d -> [", ref_strings[i]);
        }
        
        least_recently_used[ref_strings[i]] = step;
        ++step;

        int j;
        for (j = 0; j < frame_count; ++j)
        {
            if (frame[j] == ref_strings[i])
            {   
                fault[i] = 0;
                break;
            }
        }
        if (fault[i])
        {     
            switch (current_mode)
            {
                case NONE:                
                    break;

                case FIFO:
                    frame[f] = ref_strings[i];
                    ++f;
                    f = f > frame_count - 1 ? 0 : f;                    
                    break;
                
                case LRU:
                    if (frame[f] == -1)
                    {
                        frame[f] = ref_strings[i];
                        ++f;
                        f = f > frame_count - 1 ? 0 : f;
                    }
                    else
                    {
                        int k = INT_MAX;
                        for (j = 0; j < frame_count; ++j)
                        {
                            if (k > least_recently_used[frame[j]])
                            {
                                k = least_recently_used[frame[j]];                                
                                f = j;
                            }                            
                        }
                        frame[f] = ref_strings[i];
                    }                    
                    break;
            }
        }

        if (current_mode != NONE)
        {
            for (j = 0; j < frame_count; ++j)
            {
                frame[j] > -1 ? printf("%d", frame[j]) : printf("");
                j >= frame_count - 1 ? printf("") : frame[j + 1] == -1 ? printf("") : printf(" ");
            }
            printf("] ");
            for (j = 0; j < ref_count && j % frame_count == 0; ++j)
            {
                fault[i] ? printf("fault\n") : printf("no fault\n");
            }
        }
    }

    printf("\n");

    fclose(input);

    return 0;
}