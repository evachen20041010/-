#include <analogWrite.h>

const int PWM = 6;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

int i;

void loop()
{
  for(i = 0;i > 255;i += 50){
    analogWrite(LED_BUILTIN, i);
    delay(500); // Wait for 1000 millisecond(s)
  }
  for(i = 255;i > 0;i -= 50){
    analogWrite(LED_BUILTIN, i);
    delay(500); // Wait for 1000 millisecond(s)
  }
}
