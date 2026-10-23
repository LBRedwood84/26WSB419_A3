#include "led.hpp"
#include "common.hpp"
#include "boebot.hpp"

unsigned long current_time = 0;

// Global variables, stop the pointers going out of scope
boebot_t bot;
led_t led_red;

void setup( void )
{
  Serial.begin(9600);
  BOEBOT_Init( &bot, BWHEEL_LEFT_PIN, BWHEEL_RIGHT_PIN );
  
  
  pin_t example_pin = 10;
  LED_SetPin( &led_red, 10 ); // Automatically sets the pin to OUTPUT
  LED_SetBrightnessValue( &led_red, 255 ); // Default/maximum brightness

}



void loop( void )
{
  current_time = CurrentTime;
  

  //BOEBOT_Steer( &bot, -0.5f );
  //BOEBOT_SteerLerp( &bot, 0.5f, 0.8f);
  BOEBOT_Accelerate( &bot, 1.0f, 0.0001f);
  BOEBOT_DriveStraight( &bot, bot.forward );


}
