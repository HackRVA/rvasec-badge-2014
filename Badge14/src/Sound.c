#include "Sound.h"
#define NUM_SAMPLES 24


char sample_a[] = {1,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0};
void getNextSample(char* sample_i, char* sample_val)
{
    *sample_val = sample_a[*sample_i];

    *sample_i = *sample_i + 1;

    if (*sample_i >= NUM_SAMPLES)
    {
        *sample_i = 0;
    }
}