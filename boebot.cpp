#include "boebot.hpp"
#include "common.hpp"

#include <Arduino.h>

static inline void init_wheel( wheel_t* wheel, pin_t pin )
{
    if (!wheel){
        SerialMessage("init_wheel: cannot initialise NULL wheel\n");
        return;
    }
    wheel->value = 0;
    SerialMessage("Attaching wheel to pin %d\n", pin );
    wheel->servo.attach( pin, BWHEEL_MOTOR_MIN, BWHEEL_MOTOR_MAX );
}


static inline void calculate_drive( boebot_t* bot )
{
    float throttle = bot->forward - bot->back;

    float left = throttle + bot->steer * fabsf( throttle );
    float right = throttle - bot->steer * fabsf( throttle );

    float max_drive = 1.0f;
    max_drive = ( fabsf(left) > max_drive ) ? fabsf(left) : max_drive;
    max_drive = ( fabsf(right) > max_drive ) ? fabsf(right) : max_drive;
    float i_md = 1.0f / max_drive;

    bot->L = left * i_md;
    bot->R = right * i_md;

    SerialMessage( "L,R = %0.2f, %0.2f\n", bot->L, bot->R );
}



void BOEBOT_Init( boebot_t* bot, pin_t pin_leftwheel, pin_t pin_rightwheel )
{
    init_wheel( &bot->wheels[BWHEEL_LEFT], pin_leftwheel );
    init_wheel( &bot->wheels[BWHEEL_RIGHT], pin_rightwheel );
    bot->forward = 0;
    bot->back = 0;
    bot->steer = 0;
    bot->L = 0;
    bot->R = 0;
}


void BOEBOT_DriveWheel( boebot_t *bot, wheelindex_t wheel_index, float drive )
{
    // -1 = 0 or 180, depending on wheel
    // 1 = 180 or 0 depending on wheel

    float factor = drive + 1.0f;
    int mov = (wheel_index == BWHEEL_LEFT) ? factor * 90 : 180 - (factor * 90 );
    SerialMessage("factor  = %0.2f, mov = %d\n", factor, mov );
    bot->wheels[wheel_index].servo.write(mov);
}

void BOEBOT_DriveStraight( boebot_t* bot, float drive )
{
    // I wonder if the number of cyles between each call can be large enough
    // to cause one wheel to move well before the other, or atleast after an amount of time
    // significant enough to affect the direction of the bot
    float clamped = drive;
    clamp( -1.0f, 1.0f, &clamped );
    BOEBOT_DriveWheel( bot, BWHEEL_RIGHT, clamped );
    BOEBOT_DriveWheel( bot, BWHEEL_LEFT, clamped );
}


/*
 *
float gain = fabsf(T) + k * (1.0f - fabsf(T));  // k ~ 0.5-1: spin strength at T=0
float L = T + S * gain;
float R = T - S * gain;

float m = fmaxf(1.0f, fmaxf(fabsf(L), fabsf(R)));
L /= m;  R /= m;   // scale, don't clamp, to preserve the ratio
 *
 *
 */

void BOEBOT_Drive( boebot_t* bot, float forward, float backward )
{
    bot->forward = forward;
    bot->back = backward;
    calculate_drive(bot);
    BOEBOT_DriveWheel( bot, BWHEEL_LEFT, bot->L);
    BOEBOT_DriveWheel( bot, BWHEEL_RIGHT, bot->R);
}

void BOEBOT_Steer( boebot_t* bot, float steer )
{
    bot->steer = 1.5f *  steer; // random magic multiplication
    //clamp( -1.0f, 1.0f, &bot->steer ); 
}


void BOEBOT_Accelerate( boebot_t* bot, float max_vel, float lerp )
{
    float forward = max_vel;
    clamp( 0.1f, 1.0f, &forward ); // Just one direction for now
    float c_lerp = lerp;
    //clamp(0.05f, 1.0f, &c_lerp);
    SerialMessage("BotF: %g\n", bot->forward ); 
    if (bot->forward < forward )
    {
        bot->forward += (forward - bot->forward) * c_lerp;
        bot->forward = rnd_float(bot->forward);
    }

}


void BOEBOT_SteerLerp( boebot_t* bot, float end, float lerp )
{
    if (bot->steer < end )
        bot->steer += (end - bot->steer ) * lerp;
}
