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
        // runMonitorTyrePressure();
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

void runBlindSpotDetection(void)
{
   FILE* blind_fp = fopen("files/BSDetection.txt", "r");
    if (blind_fp == NULL) {
        printf("Error: could not open BSDetection.txt\n");  /* Check if file available or not */
        return;
    }

    float l_threshold;
    long unsigned int l_time_side;

    while (readBlindSpotDetectionFile(blind_fp, &l_time_side, &l_threshold) != NULL) {
        int result = activateBlindSpot(l_time_side, l_threshold);
        printf("BS: %d\n", result);

    }

    fclose(blind_fp);

}

void runMonitorTyrePressure(void)
{
    int record_num = rand() % 25 + 1;
    struct Tyre tyre = readTyreMonitorRecord("files/TPMonitor.dat", record_num);
    unsigned char result = monitorTyrePressure(tyre);
    printf("Tyre Pressure: %u\n", result);
}

void runReverseCameraCat(void)
{
       struct Category categories[3];

    unsigned long int time_taken;
   FILE* reverse_fp = fopen("files/ReverseData.txt", "r");
    if (reverse_fp == NULL) {
        printf("Error: could not open ReverseData.txt\n"); /* Check if file available or not */
        return;
    }

        int cat_count = readLookupTable("files/lookup_table.txt", categories);

    while (readReverseCategoryFile(reverse_fp, &time_taken) != NULL) {
        const char* result = classifyObjectsWhileReversing(categories, cat_count, time_taken);
        printf("Reverse CAM: %d\n", result);

    }

    fclose(reverse_fp);


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
        printf("result: %d\n",result);
    }
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