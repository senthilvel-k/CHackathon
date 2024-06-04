#include "hackathonapp.h"
 
FILE* readDrivingRangeEstimatorFile(FILE* fp, struct CarFuel* cf)
{
    if (fscanf(fp, "%f %f %f %f", &cf->fuel_cap, &cf->fuel_level, &cf->kmpl, &cf->engine_rpm) == 4) {
        return fp;
    }
    else {
        return NULL;
    }
}
 
int calculateDrivingRange(struct CarFuel cf)
{
    if (cf.fuel_level < 0 || cf.fuel_level > 100 || cf.kmpl <= 0 || cf.fuel_cap <= 0) {
        return -1;
    }
 
    float consumption_multiplier;
    if (cf.engine_rpm < 2000) {
        consumption_multiplier = 1.0;
    } else if (cf.engine_rpm < 3200) {
        consumption_multiplier = 1.2;
    } else {
        consumption_multiplier = 1.5;
    }
 
    float usableFuel = cf.fuel_level * cf.fuel_cap / 100;
    int estimatedDrivingRange = (int)(usableFuel * cf.kmpl / consumption_multiplier);
 
    return estimatedDrivingRange;
}