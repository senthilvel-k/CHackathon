#include "hackathonapp.h"

#define SPEED_OF_RADIO_WAVES 300000000.0

FILE* readBlindSpotDetectionFile(FILE* fp, unsigned long int* time_side, float* threshold)
{
    if (fp == NULL) {
        printf("Error: File pointer is NULL.\n");
        return NULL;
    }
    int time_side_int;
    float threshold_float;
    if (fscanf(fp, "%d %f", &time_side_int, &threshold_float) != 2) {
        printf("Error: Failed to read values from the file.\n");
        return NULL;
    }
 
    *time_side = (unsigned long int)time_side_int;
    *threshold = threshold_float;
   
    rewind(fp);
    return fp;
}

uint8_t activateBlindSpot(unsigned long int time_side, float threshold)
{
    uint8_t blind_spot_status = 0;
    uint8_t side = time_side & 1;
    uint32_t time_taken_ns = time_side >> 1;
    double distance = ((SPEED_OF_RADIO_WAVES * time_taken_ns) / 2.0) * 1e-9;
    printf("%lf \n", distance);
 
    if (distance <= threshold) {
        if (side == 0) {
            blind_spot_status = 1;
        } else if (side == 1) {
            blind_spot_status = 2;
        }
    }
    return blind_spot_status;
}