/*
*  미유미니 스피커의 팝 노이즈 제거용 프로그램
*  WCH 사의 CH32V003J4M6 사용 SOP8 페키지
*  개발환경 PlatformIO + wch32v Arduino 사용
*  다운로드툴로 wch-linkE 사용
*/
#include <Arduino.h>

#define LED D6          //C4 →  D6

#define SPEAKER_MUTE C2 //D6 → PC2
#define PW_SW_IN C4     //C1 → C4 
#define BL_PWM_IN C1    //D4 → C1 

void setup()
{
  pinMode(LED,OUTPUT); 

  pinMode(SPEAKER_MUTE,OUTPUT);   // 
  pinMode(PW_SW_IN,INPUT_PULLUP); // 내부 풀업저항 사용 45k옴 + 역전압 방지 다이오드
  pinMode(BL_PWM_IN,INPUT);       // 

}

void loop()
{

  uint16_t led_cnt;

  uint32_t tick_cnt = 0;
  uint32_t tick_old = 0;
  uint8_t audio_out_flag;

  uint8_t bl_out_flag;
  uint8_t bl_pwm_flag;
  uint16_t bl_off_cnt;

  uint16_t pw_out_cnt;
  uint16_t pw_push_cnt;


  // 1. 초기 8초간 off
  digitalWrite(SPEAKER_MUTE,LOW);
  digitalWrite(LED,LOW);

  delay(8000); // 8sec
  digitalWrite(SPEAKER_MUTE,HIGH);
  digitalWrite(LED,HIGH);

  while(1)
  {
    //1msec
    tick_cnt = (uint32_t)(SysTick->CNT) /48000;
    if (tick_cnt!= tick_old)
    {
      tick_old = tick_cnt;

      led_cnt++;

      if (led_cnt < 500)
      {
        digitalWrite(LED,HIGH);
      }
      else if (led_cnt <1000)
      {
        digitalWrite(LED,LOW);
      }
      else
      {
        led_cnt = 0;
      }

      // 2. power switch
      if (digitalRead(PW_SW_IN) == LOW)
      {
        pw_push_cnt++;
        if (pw_push_cnt > 500)
        {
          pw_push_cnt = 500;
          pw_out_cnt = 5000;
        }
      }
      else
      {
        pw_push_cnt = 0;
      }

      // 3. pwm output
      if (bl_pwm_flag == 0)
      {
        bl_off_cnt++;
        if (bl_off_cnt > 500)
        {
          bl_out_flag = 1;
          bl_off_cnt = 500;
        }
        else
        {
          bl_out_flag = 0;
        }
      }
      else
      {
        bl_off_cnt = 0;
        bl_out_flag = 0;
      }

      bl_pwm_flag = 0;

      
      if(pw_out_cnt > 0) pw_out_cnt--;

      if ((pw_out_cnt > 0) || (bl_out_flag == 1))
      {
        audio_out_flag = LOW;
      }
      else
      {
        audio_out_flag = HIGH;
      }

      digitalWrite(SPEAKER_MUTE,audio_out_flag);
    }
    
    delayMicroseconds(10);

    if(digitalRead(BL_PWM_IN) == HIGH)
    {
      bl_pwm_flag = 1;
    }
  }
}


