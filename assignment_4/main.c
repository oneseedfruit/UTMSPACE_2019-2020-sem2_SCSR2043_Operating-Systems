// Randy Tan Shaoxian
// SX180357CSJS04
//
// Assignment 4
//
// SCSR2043 Operating Systems
// UTMSPACE 2019/2020 Semester 2
//
// 6. I got Belady's anomaly when running with belady.txt as input only when using FIFO.
//    When running with belady.txt as input, there's no Belady's anomaly if using LRU.
//
// belady.txt contains:
// 12 3 2 1 0 3 2 4 3 2 1 0 4
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum mode { FIFO, LRU };

void showHelp(char *progName);

int main(int argc, char **argv)
{
    char *algorithm = NULL;
    char *filename = NULL;
    int frame_count = 0;    

    if (argc > 1)
    {
        algorithm = argv[1];
        filename = argv[2];
   
        if (argv[3])
        {
            int i, alldigits = 1;            
            for (i = 0; argv[3][i] != '\0'; ++i)
            {
                alldigits = isdigit(argv[3][i]);
                if (!alldigits)
                {
                    break;
                }
            }
            if (alldigits)
            {
                frame_count = atoi(argv[3]);
                if (frame_count <= 0)
                {
                    printf("Invalid no. of frames!\n");
                }
            }
            else
            {
                printf("Invalid no. of frames!\n");
            }            
        }
    }

    enum mode current_mode;
    int ref_count = -1;

    FILE *input = fopen(filename, "r");
    if (input == NULL)
    {
        printf("Can't open file for reading or file not found!\n");
        showHelp(argv[0]);
        return 1;
    }

    const int input_count = 256;
    char std_input[input_count];
        
    int algoInput = 0;
    while (strcmp(algorithm, "fifo") != 0 && strcmp(algorithm, "fifo\n") != 0 &&
            strcmp(algorithm, "lru") != 0 && strcmp(algorithm, "lru\n") != 0)
    {        
        printf("Invalid algorithm!\n");
        printf("Algorithm: ");
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
        algoInput = 1;
    }
    if (!algoInput)
    {
        printf("Algorithm: ");
        printf("%s\n", algorithm);
    }
    if (strcmp(algorithm, "fifo") == 0 || strcmp(algorithm, "fifo\n") == 0)
    {
        current_mode = FIFO;        
    }
    else if (strcmp(algorithm, "lru") == 0 || strcmp(algorithm, "lru\n") == 0)
    {
        current_mode = LRU;
    }

    printf("No. of frames: ");
    if (frame_count <= 0) 
    {   
        fgets(std_input, input_count, stdin);
        frame_count = atoi(std_input);

        int i, alldigits = 1;
        for (i = 0; std_input[i] != '\0'; ++i)
        {
            alldigits = isdigit(std_input[i]);
            if (!alldigits || frame_count <= 0)
            {
                printf("Invalid no. of frames!\nNo. of frames: ");
                --i;
                fgets(std_input, input_count, stdin);
                frame_count = atoi(std_input);
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        printf("%d\n", frame_count);
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
        printf("\t%d -> [", ref_strings[i]);
        
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
        
        for (j = 0; j < frame_count; ++j)
        {
            frame[j] > -1 ? printf("%d", frame[j]) : printf("");
            j >= frame_count - 1 ? printf("") : frame[j + 1] == -1 ? printf("") : printf(" ");
        }
        printf("] ");
        for (j = 0; j < ref_count && j % frame_count == 0; ++j)
        {
            fault[i] ? printf("fault\n") : printf("no fault\n");
            if (frame_count == 1)
            {
                break;
            }
        }    
    }

    printf("\n");

    fclose(input);

    return 0;
}

void showHelp(char *progName)
{
    printf("\nThis program simulates FIFO and LRU page replacement algorithms with reference strings as input.");
    char *progNameOnly = strrchr(progName, '/');
    if (progNameOnly) 
    {
        progNameOnly += 1;
    } else 
    {
        progNameOnly = progName;
    }    
    printf("\nUsage: %s [fifo, lru] [reference string filename] [no. of frames]\n", progNameOnly);
}