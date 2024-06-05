#include "hackathonapp.h"
 
// Function to read a tyre monitor record from the file
struct Tyre readTyreMonitorRecord(const char* filename, int record_num) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        // Returning an empty struct with zeros
        struct Tyre empty = {0};
        return empty;
    }
 
    // Calculate the offset to the record
    int offset = (record_num - 1) * sizeof(struct Tyre);
    fseek(file, offset, SEEK_SET);
 
    // Read the record
    struct Tyre tyre;
    fread(&tyre, sizeof(struct Tyre), 1, file);
 
    // Close the file
    fclose(file);
 
    return tyre;
}
 
// Function to monitor tyre pressure and set flags accordingly
unsigned char monitorTyrePressure(struct Tyre ty) {
    unsigned char tyrePressureFlags = 0;
 
    // Extract pressure values
    uint8_t front_left = ty.front_pressure >> 4;
    uint8_t front_right = ty.front_pressure & 0x0F;
    uint8_t rear_left = ty.rear_pressure >> 4;
    uint8_t rear_right = ty.rear_pressure & 0x0F;
 
    // Extract threshold values
    uint8_t front_left_threshold = ty.threshold >> 24;
    uint8_t front_right_threshold = (ty.threshold >> 16) & 0xFF;
    uint8_t rear_left_threshold = (ty.threshold >> 8) & 0xFF;
    uint8_t rear_right_threshold = ty.threshold & 0xFF;
 
    // Check each tyre's pressure against the threshold value
    if (front_left < front_left_threshold)
        tyrePressureFlags |= (1 << 0); // FL flag
    if (front_right < front_right_threshold)
        tyrePressureFlags |= (1 << 1); // FR flag
    if (rear_left < rear_left_threshold)
        tyrePressureFlags |= (1 << 2); // RL flag
    if (rear_right < rear_right_threshold)
        tyrePressureFlags |= (1 << 3); // RR flag
 
    // Check if more than 2 tyre pressures are below threshold values
    int count = 0;
    if (front_left < front_left_threshold) count++;
    if (front_right < front_right_threshold) count++;
    if (rear_left < rear_left_threshold) count++;
    if (rear_right < rear_right_threshold) count++;
    if (count > 2)
        tyrePressureFlags |= (1 << 5); // W flag
 
    return tyrePressureFlags;
}