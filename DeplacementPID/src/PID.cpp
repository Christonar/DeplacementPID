#include "PID.h"

/* #################################################
Description : Fonction permettant de faire 
avancer les 2 roues du robot d'un certain nombre 
de pulse à la même vitesse
Le robot fait d'abord une phase d'accélération progressive 
avant d'atteindre une vitesse de pointe pour ensuite 
ralentir de façon progressive
Entrée : Nombre de pulse voulu
Sortie : Aucune
################################################# */

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
        if (compteRightTotal > (nbrPulse-700))
        {
            vitesse = 0.1;
            MOTOR_SetSpeed(RIGHT,vitesse);
        }
        else if ((compteRightTotal > 1400) && (compteRightTotal < (nbrPulse-1400)))
        {
            vitesse = 0.5;
            MOTOR_SetSpeed(RIGHT,vitesse);
        }
        else if ((compteRightTotal > (nbrPulse-1400)) || (compteRightTotal > 700))
        {
            vitesse = 0.3;
            MOTOR_SetSpeed(RIGHT,vitesse);
        }

        compteDelai++;
        if(compteDelai > 20)
        {
            compteRight = ENCODER_ReadReset(RIGHT);
            compteRightTotal += compteRight;
            compteLeft = ENCODER_ReadReset(LEFT);
            ancienneCorrection = correction_P;
            correction_P = compteRight - compteLeft;
            correction_I += correction_P;
            correction_D = correction_P - ancienneCorrection;
            MOTOR_SetSpeed(LEFT,(vitesse + (0.2*correction_P + 0.1*correction_I + 0.1*correction_D)));
            compteDelai = 0;
        }
    }
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}

/* #################################################
Description : Fonction permettant de faire 
avancer le robot en le faisant tourner un peu à droite
Le robot fait d'abord une phase d'accélération progressive 
avant d'atteindre une vitesse de pointe pour ensuite 
ralentir de façon progressive
Entrée : Nombre de pulse voulu, différence de vitesse 
voulue entre les deux roues
Sortie : Aucune
################################################# */
void AvancerDroite(uint32_t nbrPulse, float difference)
{
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
    uint32_t compteTotal = 0;
    float vitesse = 0.1;

    MOTOR_SetSpeed(LEFT,vitesse);
    MOTOR_SetSpeed(RIGHT,(vitesse-0.05));
    while(compteTotal < nbrPulse)
    {
        compteTotal = ENCODER_Read(LEFT);
        if (compteTotal > (nbrPulse-400))
        {
            vitesse = 0.1;
            MOTOR_SetSpeed(LEFT,vitesse);
            MOTOR_SetSpeed(RIGHT,(vitesse-0.05));
        }
        else if (compteTotal > 400)
        {
            vitesse = 0.3;
            MOTOR_SetSpeed(LEFT,vitesse);
            MOTOR_SetSpeed(RIGHT,(vitesse-difference));
        }
    }
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}

/* #################################################
Description : Fonction permettant de faire 
avancer le robot en le faisant tourner un peu à gauche
Le robot fait d'abord une phase d'accélération progressive 
avant d'atteindre une vitesse de pointe pour ensuite 
ralentir de façon progressive
Entrée : Nombre de pulse voulu, différence de vitesse 
voulue entre les deux roues
Sortie : Aucune
################################################# */
void AvancerGauche(uint32_t nbrPulse, float difference)
{
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
    uint32_t compteTotal = 0;
    float vitesse = 0.1;

    MOTOR_SetSpeed(RIGHT,vitesse);
    MOTOR_SetSpeed(LEFT,(vitesse-0.05));
    while(compteTotal < nbrPulse)
    {
        compteTotal = ENCODER_Read(RIGHT);
        if (compteTotal > (nbrPulse-400))
        {
            vitesse = 0.1;
            MOTOR_SetSpeed(RIGHT,vitesse);
            MOTOR_SetSpeed(LEFT,(vitesse-0.05));
        }
        else if (compteTotal > 400)
        {
            vitesse = 0.3;
            MOTOR_SetSpeed(RIGHT,vitesse);
            MOTOR_SetSpeed(LEFT,(vitesse-difference));
        }
    }
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}

/* #################################################
Description : Fonction permettant de faire 
tourner le robot sur place à droite
Le robot fait d'abord une phase d'accélération progressive 
avant d'atteindre une vitesse de pointe pour ensuite 
ralentir de façon progressive
Entrée : Nombre de pulse voulu
Sortie : Aucune
################################################# */
void TournerDroitePID(uint32_t nbrPulse)
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
    MOTOR_SetSpeed(RIGHT,-vitesse);
    MOTOR_SetSpeed(LEFT,vitesse);

    uint16_t compteDelai = 0;
    while(compteRightTotal < nbrPulse)
    {
        if (compteRightTotal > (nbrPulse-700))
        {
            vitesse = 0.1;
            MOTOR_SetSpeed(RIGHT,-vitesse);
        }
        else if ((compteRightTotal > (nbrPulse-1400)) || (compteRightTotal > 700))
        {
            vitesse = 0.3;
            MOTOR_SetSpeed(RIGHT,-vitesse);
        }

        compteDelai++;
        if(compteDelai > 20)
        {
            compteRight = -ENCODER_ReadReset(RIGHT);
            compteRightTotal += compteRight;
            compteLeft = ENCODER_ReadReset(LEFT);
            ancienneCorrection = correction_P;
            correction_P = compteRight - compteLeft;
            correction_I += correction_P;
            correction_D = correction_P - ancienneCorrection;
            MOTOR_SetSpeed(LEFT,(vitesse + (0.2*correction_P + 0.1*correction_I + 0.1*correction_D)));
            compteDelai = 0;
        }
    }
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}

/* #################################################
Description : Fonction permettant de faire 
tourner le robot sur place à gauche
Le robot fait d'abord une phase d'accélération progressive 
avant d'atteindre une vitesse de pointe pour ensuite 
ralentir de façon progressive
Entrée : Nombre de pulse voulu
Sortie : Aucune
################################################# */
void TournerGauchePID(uint32_t nbrPulse)
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
    MOTOR_SetSpeed(LEFT,-vitesse);

    uint16_t compteDelai = 0;
    while(compteRightTotal < nbrPulse)
    {
        if (compteRightTotal > (nbrPulse-700))
        {
            vitesse = 0.1;
            MOTOR_SetSpeed(RIGHT,vitesse);
        }
        else if ((compteRightTotal > (nbrPulse-1400)) || (compteRightTotal > 700))
        {
            vitesse = 0.3;
            MOTOR_SetSpeed(RIGHT,vitesse);
        }

        compteDelai++;
        if(compteDelai > 20)
        {
            compteRight = ENCODER_ReadReset(RIGHT);
            compteRightTotal += compteRight;
            compteLeft = -ENCODER_ReadReset(LEFT);
            ancienneCorrection = correction_P;
            correction_P = compteRight - compteLeft;
            correction_I += correction_P;
            correction_D = correction_P - ancienneCorrection;
            MOTOR_SetSpeed(LEFT,(-vitesse + (-0.2*correction_P + -0.1*correction_I + -0.1*correction_D)));
            compteDelai = 0;
        }
    }
    MOTOR_SetSpeed(RIGHT,0);
    MOTOR_SetSpeed(LEFT,0);
    ENCODER_Reset(RIGHT);
    ENCODER_Reset(LEFT);
}


void Tourner90DroitePID(void)
{
    TournerDroitePID(1675);
}

void Tourner90GauchePID(void)
{
    TournerGauchePID(1680);
}