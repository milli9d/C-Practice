#include <unistd.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <bitset>

#define PAGESIZE 4096
#define INT_BITS 32

#define position(val, idx) ((val & (1U << idx)) ? 1U : 0U)

#define SET_BIT_M(val, idx) (val |= (1U << idx))

#define CLEAR_BIT_M(val, idx) (val &= ~(1U << idx))

#define TOGGLE_BIT_M(val, idx) (val = val ^ (1U << idx))

#define SWAP_ENDIANESS(val) (((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) | ((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24))

using namespace std;

// Rotate by n bits , left == true for left rotation , false for Right
void rotate(uint32_t &num, int rotation, bool left)
{
    if (left)
    {
        rotation = rotation * -1;
    }
    // This gives right rotation of the number , it can also be made left rotation by fliiping the sign on rotation
    num = (num >> rotation) | (num << (INT_BITS - rotation));
}

int main(int argc , char **argv)
{
   typedef struct{
        float b;
        int as;
        char a;
        char bs;
    }tempstruct;

    tempstruct* temp = new tempstruct[10];
    temp[1].a = 12.0;
    temp[2].a = 12.0;

    int** arr2 = (int**) new int*[10]; 
    for(int i = 0 ; i < 10 ; i++){
        arr2[i] =(int*) new int[10];
    }

    arr2[0][0] = 10;


    int* arr =(int*) new int[5];
    free(arr);

    cout << "SIze = " << sizeof(temp) << " | "<<  to_string(temp[1].a)<< endl;
    uint8_t a2 = 0b00001100;
    cout << bitset<8>(a2) << endl;

    SET_BIT_M(a2, 7);
    cout << bitset<8>(a2) << endl;

    CLEAR_BIT_M(a2, 7);
    cout << bitset<8>(a2) << endl;

    TOGGLE_BIT_M(a2, 7);
    cout << bitset<8>(a2) << endl;

    for (int i = 7; i >= 0; i--)
    {
        cout << position(a2, i) << " | ";
    }
    cout << endl;
    // Rotate by n bits
    uint32_t a1 = 0xf1f2f3f4;
    cout << std::hex << SWAP_ENDIANESS(a1) << endl;
    rotate(a1, 16, false);
    cout << std::hex << a1 << endl;
    rotate(a1, 8, true);
    cout << std::hex << a1 << endl;

    unsigned int a = 10;
    unsigned int b = 20;
    // MIN
    cout << to_string(b ^ ((a ^ b) & -(a < b))) << endl;
    // Max
    cout << to_string(a ^ ((a ^ b) & -(a < b))) << endl;

    // Swap without temporary
    a = a ^ b;
    b = a ^ b; // a ^ b ^ b = a
    a = a ^ b; // a ^ b ^ a = b
    cout << to_string(a) << " " << to_string(b) << endl;

    a = a + b;
    b = a - b; // a + b - b  = a
    a = a - b; // a + b - a = b
    cout << to_string(a) << " " << to_string(b) << endl;

    int *const shMem = (int *)mmap64(NULL, sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shMem = 5;
    // Parent Process
    if (fork() == 0)
    {
        *shMem = 80;
        printf(" Child %d\n", *shMem);
        exit(0);
    }
    // Child Process
    else
    {
        printf(" Parent %d\n", *shMem);
        wait(NULL);
        printf(" shared %d\n", *shMem);
        munmap(shMem, sizeof(int));
    }
    return 0;
}
