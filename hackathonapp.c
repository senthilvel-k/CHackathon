#include "hackathonapp.h"

void runLaneDeparture(void);
void runBlindSpotDetection(void);
void runAirbagActuator(void);
void runReverseCameraCat(void);
void runDrivingRangeEstimator(void);
void runMonitorTyrePressure(void);

int main()
{

    initTermios(0);
    while (!kbhit())
    {
        // runLaneDeparture();
        // runBlindSpotDetection(); 
        // runAirbagActuator();
        // runReverseCameraCat();   
        // runDrivingRangeEstimator();
        runMonitorTyrePressure();
        break;
    }
    
    resetTermios();
    return 0;
}


void runLaneDeparture(void)
{
   FILE* lane_fp = fopen("files/LaneDeparture.txt", "r");
    if (lane_fp == NULL) {
        printf("Error: could not open LaneDeparture.txt\n");
        return;
    }

    float lane_width, car_width, left_sensor_distance, right_sensor_distance;

    while (readLaneDepartureFile(lane_fp, &lane_width, &car_width, &left_sensor_distance, &right_sensor_distance) != NULL) {
        int result = determineLaneDeparture(lane_width, car_width, left_sensor_distance, right_sensor_distance);
        printf("Lane Departure: %d\n", result);

    }

    fclose(lane_fp);

}

void runBlindSpotDetection(void) {
    FILE *fp = fopen("files/BSDetection.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        return;
    }
 
    unsigned long int time_side;
    float threshold;
    while (fscanf(fp, "%lu %f", &time_side, &threshold) == 2) {
        uint8_t status = activateBlindSpot(time_side, threshold);
        printf("Blind spot status: %u\n", status);
    }
 
    fclose(fp);
}

void runMonitorTyrePressure(void)
{
    int record_num = rand() % 25 + 1;
    struct Tyre tyre = readTyreMonitorRecord("files/TPMonitor.dat", record_num);
    unsigned char result = monitorTyrePressure(tyre);
    printf("Tyre Pressure: %u\n", result);
    while(tyre)
    {
        runMonitorTyrePressure();
    }
}

void runReverseCameraCat(void)
{
    // Reading the lookup table
    struct Category categories[100]; // Assuming there are less than 100 categories
    int category_count = readLookupTable("files/lookup_table.txt", categories);
    if (category_count == 0) {
        printf("Error: Unable to read lookup table.\n");
        return;
    }
 
    // Opening the reverse category file
    FILE* reverse_fp = fopen("files/ReverseData.txt", "r");
    if (reverse_fp == NULL) {
        printf("Error: Unable to open ReverseData.txt\n");
        return;
    fclose(reverse_fp);
    }
}
void runAirbagActuator(void)
{
    FILE* airbagacc = fopen("files/ABActuator.txt","r"); /* Check if file available or not */
    if(airbagacc == NULL)
    {
        printf("Error: could not open ABActuator.txt\n");
        return;
    }
 
    struct Airbag AB;
 
    while(readAirbagActuatorFile(airbagacc,&AB)!= NULL)
    {
        int result = activateAirbags(AB);
        printf("AirbagActuator: %d\n",result);
        
    }
    fclose(airbagacc);
}

void runDrivingRangeEstimator(void)
{
    FILE* dre_fp = fopen("files/DREstimator.txt", "r");
    if (dre_fp == NULL) {
        printf("Error: could not open DREstimator.txt\n"); /* Check if file available or not */
        return;
    }
 
    struct CarFuel cf;
 
    while (readDrivingRangeEstimatorFile(dre_fp, &cf) != NULL) {
        int range = calculateDrivingRange(cf);
        printf("Estimated Driving Range: %d\n", range);
    }
 
    fclose(dre_fp);
}