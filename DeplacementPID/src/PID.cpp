#include "PID.h"

void AvancerPID(uint32_t nbrPulse) 
{
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
    uint32_t compteRight = 0;
    uint32_t compteLeft = 0;
    uint32_t ancienneCorrection = 0;
    static uint32_t correction_P = 0;
    static uint32_t correction_I = 0;
    static uint32_t correction_D = 0;

    float vitesse = 0.1;
    MOTOR_SetSpeed(RIGHT,vitesse);
    MOTOR_SetSpeed(LEFT,vitesse);

    uint16_t compteDelai = 0;
    while(compteRight < nbrPulse)
    {
        if (compteRight > 1400)
        {
            vitesse = 0.5;
        }
        else if (compteRight > 700)
        {
            vitesse = 0.3;
        }

        compteDelai++;
        compteRight = ENCODER_Read(RIGHT);
        if(compteDelai > 20)
        {
            compteLeft = ENCODER_Read(LEFT);
            ancienneCorrection = correction_P;
            correction_P = compteRight - compteLeft;
            correction_I += correction_P;
            correction_D = correction_P - ancienneCorrection;
            MOTOR_SetSpeed(LEFT,(vitesse + 0.3*correction_P + 0.3*correction_I + 0.3*correction_D));
            compteDelai = 0;
        }
    }
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}