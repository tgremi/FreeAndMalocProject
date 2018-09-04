#include <stdio.h>
#include <stdlib.h>

//Memory struct
typedef struct
{
    char *area;
} memory;

//Functions
void printMemory(char *memory);
void initMemory(char *memory);
char *addContent(char *memory, char content[], int arraySize);
int verifyFreeSpace(char *memory, int size);
void clearMemory(char *memory);
void clearMemoryArea(char *content, int startPosition, int lastPosition);

    int main()
{
    memory data;
    initMemory(data.area);
    printf("ADO 0x001 - Sistemas Operacionais\n");
    char array[100];
    int startPosition = -1;
    int lastPosition = -1;

    while (1)
    {
        printf("1 - Print memory\n");
        printf("2 - Insert data memory\n");
        printf("3 - Free area\n");
        printf("4 - Clear memory\n");
        printf("0 - Finish\n");

        int option = 0;
        scanf("%d", &option);

        switch (option)
        {
        case 0:
            return 0;
            break;
        case 1:
            printMemory(data.area);
            break;
        case 2:
        {
            while (1)
            {
                printf("How many chars do you need 1 - 16?\n");
                int size = 0;
                scanf("%d", &size);

                if (size > 0 && size < 17)
                {

                    for (int i = 0; i < size; i++)
                    {
                        printf("Byte (char) [%d] = ", i);
                        scanf(" %c", &array[i]);
                    }
                    printf("\n");
                    addContent(data.area, array, size);
                    printf("1 - Insert more data.\n");
                }
                else
                    printf("Error!\n1 - Try again.\n");

                printf("0 - Main menu.\n");
                int again = 0;
                scanf(" %d", &again);
                if (!again)
                    break;
            }
            break;
        }
        case 3:
            while (1)
            {
                printf("Start position of the area you want to free:");
                scanf("%d", &startPosition);
                printf("Last position of the area you want to free:");
                scanf("%d", &lastPosition);
                printf("\n"); 
                
                if (startPosition == lastPosition)
                    printf("Start postion and last position can't be equal\n");
                else if (startPosition > lastPosition)
                    printf("Start position can't be greater than last position\n");
                else if (startPosition > 15 || startPosition < 0 || lastPosition > 15 || lastPosition < 0)
                    printf("Start position and last position need to be between 0 and 15\n");
                else break;
            }
            clearMemoryArea(data.area, startPosition, lastPosition);
            startPosition = -1;
            lastPosition = -1;
            break;
        case 4:
            clearMemory(data.area);
            break;
        }
    }
    return 0;
}

//Clears the whole memory
void clearMemory(char *content)
{
    int i = 0;
    while (i < 16)
    {
        content[i] = '\0';
        i++;
    }
}

//Clear a certain portion of memory area
void clearMemoryArea(char *content, int startPosition, int lastPosition)
{
    for (int i = startPosition; i <= lastPosition; i++)
        content[i] = '\0';
}

//Prints the memory
void printMemory(char *memory)
{
    //printf("Memory = %s \n", memory);

    printf("Memory = ");
    for (int i = 0; i < 16; i++)
    {
        printf("%c ", memory[i]);
    }
    printf("\n");
}

//Inits a memory struct
void initMemory(char *memory)
{
    //Here memory receives the equivalent to 16 kbytes since the char data type size is 1 kbyte.
    memory = (char *)malloc(16 * sizeof(char));
    clearMemory(memory);
}

//Copy the array content to the memory
char *addContent(char *memory, char content[], int arraySize)
{
    if (arraySize > 16)
        return NULL;

    //If there is enough space to add content.
    int index = verifyFreeSpace(memory, arraySize);

    //printf("verifyFreeSpace = %d\n", index);
    if (index != -1)
    {
        for (int i = index; i < (index + arraySize); i++)
            memory[i] = content[i - index];
        printf("\n");
    }

    return 0;
}

//Verifies if there is enough free memory to allocate
int verifyFreeSpace(char *memory, int size)
{
    int total = 0;
    int index = -1;
    for (int i = 0; i < 16; i++)
    {
        //printf("memory = %d.\n", memory[i]);
        if (memory[i] == '\0' && index == -1)
        {
            //printf("start count index.\n");
            index = i;
            total++;
        }
        else if (memory[i] == '\0')
        {
            //printf("total = %d.\n", total);
            total++;
        }

        else if (total > 0)
        {
            //printf("reseted index.\n");
            index = -1;
            total = 0;
        }
    }
    if (total >= size)
        return index;
    return -1;
}