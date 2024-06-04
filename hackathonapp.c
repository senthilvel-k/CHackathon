#include "hackathonapp.h"

void runLaneDeparture(void);
void runBlindSpotDetection(void);
void runAirbagActuator(void);
void runReverseCameraCat(void);
void runDrivingRangeEstimator(void);

int main()
{

    initTermios(0);
    while (!kbhit())
    {
        // runLaneDeparture();
        // runBlindSpotDetection(); 
        // runAirbagActuator();
        // runReverseCameraCat();   
        runDrivingRangeEstimator();
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
        printf("Error: could not open BSDetection.txt\n");
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
   FILE* tpms_fp = fopen("files/tyrePressureMonitor.txt", "r");
    if (tpms_fp == NULL) {
        printf("Error: could not open tyrePressureMonitor.txt\n");
        return;
    }

    float l_threshold;
    long unsigned int l_time_side;

    while (readBlindSpotDetectionFile(tpms_fp, &l_time_side, &l_threshold) != NULL) {
        int result = activateBlindSpot(l_time_side, l_threshold);
        printf("BS: %d\n", result);

    }

    fclose(tpms_fp);

}

void runReverseCameraCat(void)
{
   FILE* reverse_fp = fopen("files/DREstimator.txt", "r");
    if (reverse_fp == NULL) {
        printf("Error: could not open DREstimator.txt\n");
        return;
    }

    float l_threshold;
    long unsigned int l_time_side;

    while (readBlindSpotDetectionFile(reverse_fp, &l_time_side, &l_threshold) != NULL) {
        int result = activateBlindSpot(l_time_side, l_threshold);
        printf("BS: %d\n", result);

    }

    fclose(reverse_fp);

}

void runAirbagActuator(void)
{
    FILE* airbagacc = fopen("files/ABActuator.txt","r");
    if(airbagacc == NULL)
    {
        printf("Error: could not open LaneDeparture.txt\n");
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
        printf("Error: could not open DREstimator.txt\n");
        return;
    }
 
    struct CarFuel cf;
 
    while (readDrivingRangeEstimatorFile(dre_fp, &cf) != NULL) {
        int range = calculateDrivingRange(cf);
        printf("Estimated Driving Range: %d\n", range);
    }
 
    fclose(dre_fp);
}