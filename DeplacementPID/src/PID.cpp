#include "PID.h"

void AvancerPID(uint32_t nbrPulse) 
{
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
    uint32_t compteRight = 0;
    uint32_t compteRightTotal = 0;
    uint32_t compteLeft = 0;
    uint32_t ancienneCorrection = 0;
    uint32_t correction_P = 0;
    uint32_t correction_I = 0;
    uint32_t correction_D = 0;

    float vitesse = 0.1;
    MOTOR_SetSpeed(RIGHT,vitesse);
    MOTOR_SetSpeed(LEFT,vitesse);

    uint16_t compteDelai = 0;
    while(compteRightTotal < nbrPulse)
    {
        //Serial.print("Compte right ");
        //Serial.println(compteRightTotal,DEC);
        if (compteRightTotal > (nbrPulse-700))
        {
            vitesse = 0.1;
            MOTOR_SetSpeed(RIGHT,vitesse);
            //Serial.println("Vitesse 0.1");
        }
        else if ((compteRightTotal > 1400) && (compteRightTotal < (nbrPulse-1400)))
        {
            vitesse = 0.5;
            MOTOR_SetSpeed(RIGHT,vitesse);
            //Serial.println("Vitesse 0.5");
        }
        else if ((compteRightTotal > (nbrPulse-1400)) || (compteRightTotal > 700))
        {
            vitesse = 0.3;
            MOTOR_SetSpeed(RIGHT,vitesse);
            //Serial.println("Vitesse 0.3");
        }

        compteDelai++;
        if(compteDelai > 10)
        {
            compteRight = ENCODER_ReadReset(RIGHT);
            compteRightTotal += compteRight;
            compteLeft = ENCODER_ReadReset(LEFT);
            ancienneCorrection = correction_P;
            correction_P = compteRight - compteLeft;
            correction_I += correction_P;
            correction_D = correction_P - ancienneCorrection;
            MOTOR_SetSpeed(LEFT,(vitesse + 0.5*correction_P + 0.4*correction_I + 0.2*correction_D));
            compteDelai = 0;
        }
    }
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}