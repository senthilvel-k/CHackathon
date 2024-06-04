#include "hackathonapp.h"
#include <math.h>
FILE* readLaneDepartureFile(FILE* fp, float* f1, float* f2, float* f3, float* f4)
{
    // Check if the file pointer is NULL
    if (fp == NULL) {
        printf("Error: could not open file\n");
        return NULL;
    }

    // Read the data from the file
    if (fscanf(fp, "%f %f %f %f", f1, f2, f3, f4) != 4) {
        printf("Error: could not read data from file\n");
        return NULL;
    }

    return fp;
}

int determineLaneDeparture(
    float lane_width,
    float car_width,
    float left_sensor_distance,
    float right_sensor_distance)
{
        // Check for invalid input
    if (lane_width <= 0 || car_width <= 0 || left_sensor_distance < 0 || right_sensor_distance < 0) {
        return -1;
    }
 
    // Calculate the adjusted threshold
    float adjusted_threshold = (lane_width - car_width) / 2;
 
    // Calculate the deviation from the mean position
    float deviation = fabs(left_sensor_distance - right_sensor_distance);
 
    // Determine if the car is deviating from its lane
    if (deviation > adjusted_threshold) {
        return 1;
    } else {
        return 0;
    }

}

