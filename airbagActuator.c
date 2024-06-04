#include "hackathonapp.h"
#include <math.h>
FILE* readAirbagActuatorFile(FILE* fp, struct Airbag* ab)
{  
    /* Read data from the database and validate its integrity */
    if (fscanf(fp, "%f %f %f %f %f", &ab->start_time, &ab->init_speed, &ab->end_time, &ab->final_speed, &ab->gforce) == 5)
    {
        return fp;
    }
    else
    {
        return NULL;
    }
   
}
 
int activateAirbags(struct Airbag ab)
{
    float gforce_act;
 
    // Conversion of kmph to m/s
    ab.init_speed = ab.init_speed * (5.0 / 18.0);
    ab.final_speed = ab.final_speed * (5.0 / 18.0);
 
    // Calculation of actual g-force
    // 9.81 is acceleration due to gravity  
    gforce_act = ((fabs(ab.final_speed - ab.init_speed)) / (ab.end_time - ab.start_time)) / 9.81;
 
    if (ab.gforce < gforce_act) {
        return 1;  // Airbag open
    } else {
        return 0; // Airbag closed
    }
}