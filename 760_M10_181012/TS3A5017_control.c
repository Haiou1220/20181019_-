//**********************************************************//
//	TS3A5017音量控制源代码　　　　							//
//	ATTINY24-20SSU         									//
//	V1.0	2018.9.12									//
//  														//
//**********************************************************//
//#include "760_M10_MACROH.h" //#define __760_M10_MACROH_H
//#include "760_M10_FUN.h" //#define FUN
//**********************************************************//
//全局变量
unsigned char sound=3;//控制声音变量,
//全局变量

#include <iot24v.h>
#include <macros.h>

//key1定义 SP  IN定义,低电平有效,PA4  输入0001 0000
#define SPCIN    (PINA & 0x10)

//key2定义 PTT IN定义,低电平有效,PA2  输入0000 0100
#define PTTIN   (PINA & 0x04)	

//key3定义，低电平有效,音量减少,PA0 输入0000 0001
#define  VOL_UP    (PINA & 0x01)

//key4定义，低电平有效，音量增加,PA6 输入0100 0000
#define  VOL_DOWN   (PINA & 0x40)

//定义1EN PA1,输出
#define EN1_0() PORTA &=~(1<<1)
#define EN1_1() PORTA |=(1<<1)
 
//定义PD PB1,输出
#define PD_0() PORTB &=~(1<<1)
#define PD_1() PORTB |=(1<<1)

//定义IN1 PB2,输出//
#define IN1_0() PORTB &=~(1<<2)
#define IN1_1() PORTB |=(1<<2)

//定义IN2 PA3,输出
#define IN2_0() PORTA &=~(1<<3)
#define IN2_1() PORTA |=(1<<3)

//定义led PB0, 输出
#define LED_0()  PORTB &=~(1<<0)
#define LED_1()  PORTB |=(1<<0)

//定义 MUOUT,PA7,输出
#define MUOUT_0()   PORTA &=~(1<<7)
#define MUOUT_1()   PORTA |=(1<<7)

//定义PTTOUT PA5,输出
#define PTTOUT_0()   PORTA &=~(1<<5)
#define PTTOUT_1()   PORTA |=(1<<5)

typedef enum enum_buttons	{   //按键类型
				em_NoButton=0,
				em_SPC_IN,
				em_PTT_IN,
				em_VOL_UP,
				em_VOL_DOWN,
				
				}enum_buttons_type ;


//**********************************************************//
#define  ppt_down_mu()   MUOUT_0() 
#define  ppt_up_no_mu()   MUOUT_1() 

#define DELAY_TIME	7000  //DELAY_TIME

void port_init(void)
{
 PORTB = 0x01; //0000 0001//  PB0=1 LED关 PB1=0(节能复位）PB2=0 PB3=0（复位）
 DDRB  = 0xFF; //1111 1111 全输出 

 
 DDRA  = 0xAA; //1010 1010, //PA0=0,输入;PA1=1输出,PA2输入,PA3输出,
												//PA4输入，PA5输出，PA6输入,PA7输出
												
 PORTA = 0x57; //1101 0111,      //PA3=0,PA2=1,PA1=1, PA0=1, 											
}																		//	PA7=0,PA6=1,PA5=0,PA4=1		
																		//pa7是cro_spk 要初始化为0
void delay(unsigned int n)
{
	do
	{
		n--;
	}while(n!=0);
}

void system_init(void)
{
	
		CLI(); //disable all interrupts
    port_init();
    delay(200);//延迟30周期*/

}


void LED(unsigned char s)//LED 闪烁
{
	unsigned char i;
	
	for(i=0;i<80;i++)
	{
		LED_0();

		delay(s);
		
		LED_1();//灭
		delay(s);
	}
} 

void Delay_LED(void)//
{
	unsigned char a, b;

	for (a = 1; a; a++)
		for (b = 1; b<100; b++)
			;
}
	
	
void led_blink(void)
{
	unsigned char i;
	for(  i=0;i<2;i++)
		{
		
		LED_0();//亮
		Delay_LED();//	
		LED_1();//灭
		Delay_LED();//
			
		}
}


void control_sound(unsigned char sound_level)  
 {
  switch (sound_level)
   {
	   case (1):
	    EN1_1();//PA1,最大声
		  IN2_0();//PA3  
		  IN1_0();//PB2
	            break;
	            	
	   case (2):
      EN1_0();//D-1S1
		  IN2_0();
		  IN1_0();
	            break;
				
	   case (3):
	    EN1_0();//D-1S2
		  IN2_0();
		  IN1_1();
	            break;
	   
	   case (4):
	    EN1_0();//D-1S3
		  IN2_1();
		  IN1_0();	   
	    				break;
	   
	   case (5):
	    EN1_0();//D-1S4
		  IN2_1();
		  IN1_1();	      
	    				break; 
	   }

 }
 

 
#define buttons_press(which_buttons)  ((which_buttons)==0)
#define buttons_still_press(which_buttons)  ((which_buttons)==0)    //#define SQUARE(X) (X*X)
																																	//#define SPCIN   (PINA & 0x10)
																																	
																																	
																																	
enum_buttons_type  buttons_once_press (void) 
{
	 if ( buttons_press(SPCIN) ){ /*em_NoButton=0,em_SPC_IN,em_PTT_IN,em_VOL_UP,em_VOL_DOWN,*/
	 															/*SPCIN,PTTIN,VOL_UP,VOL_DOWN*///io口按键
	 	return em_SPC_IN ;
	 	
	 }
	 	else if( buttons_press(PTTIN) ){
	 		
	 		return em_PTT_IN ;
	 		
	  }
	 	else if( buttons_press(VOL_UP) ){
	 		
	 	return em_VOL_UP ;	
	 		
	 	}
	 	else if( buttons_press(VOL_DOWN) ){
	 		
	 		return em_VOL_DOWN ;
	 			
	 	}else{
	 		
	 		return em_NoButton ;
	 		
	 	}	
	 		
	   
}


enum_buttons_type  get_key(void)
{  
	  
	 
	static	enum_buttons_type  buttons_once_press_num = em_NoButton;//哪一个按键按下了
	static	unsigned char      mu_count=0;//mu按键按时间，, static 局部静态提高运行效率
	static  unsigned char  do_mu_flag=1;							// static 局部静态提高运行效率
 	static  unsigned char  mu_count_ok=0; //长按时间到了 , static 局部静态提高运行效率
 	static  unsigned char	 return_num = em_NoButton ;//默认返回0
  
		buttons_once_press_num = buttons_once_press ();  //获取button，enum_buttons_type  buttons_once_press (void) ;
  //test
 // if(buttons_once_press_num == em_VOL_UP )
 // {
  //	led_blink() ;led_blink() ;led_blink() ;led_blink() ;
 // 	
 // }	
  //test
  
  
		if(buttons_once_press_num == em_SPC_IN	)//mute静音切换按键，按键要释放//两秒长按松开返回1//SPCIN() == 0
		{
			delay(DELAY_TIME);//去抖动，修改为上变沿触发，这样就只会在按下时候触发一次
			return_num=0;
			if(buttons_still_press(SPCIN) )//SPCIN() == 0
			{	
				while(buttons_still_press(SPCIN) )//等待按键释放	，以防多个按键同时按下	
				{
					delay(10000); mu_count++; 
					if(mu_count>=20)//大约2秒
					{
							if(do_mu_flag){
								return_num = em_SPC_IN ;	//按死只会做一次mu静音操作 
								mu_count_ok = 1;
								do_mu_flag=0;
								mu_count = 0;
								led_blink() ; 
						  }
					}
						
				}	
				mu_count = 0;
			}
			do_mu_flag=1; 
			if (mu_count_ok == 0 ) //时间wei到了
				{ 
					mu_count_ok = 0;return_num = em_NoButton ; 
					
				}
			
	    return ( (return_num>em_NoButton)? em_SPC_IN : em_NoButton );   //长按return  1 ，无长按返回0 ;
		
		}

		
		if(buttons_once_press_num == em_PTT_IN)//PPT不需要，按键释放
		{
			delay(DELAY_TIME);//去抖动
	
			if(buttons_still_press(PTTIN) )  //buttons_still_press(PTTIN)//PTTIN() == 0
			{
				return em_PTT_IN;
			}
	      
				return em_NoButton;
		}
		
		 if(buttons_once_press_num == em_VOL_UP)//加 按键释放，按一下加减一档
		{
			
			delay(DELAY_TIME);//去抖动
			if(buttons_still_press(VOL_UP) )   //buttons_still_press(PTTIN)//VOL_UP() == 0
			{	
				while(buttons_still_press(VOL_UP) );//等待按键释放
				return em_VOL_UP;
			}
					
			return em_NoButton;
			
		}
		
		 if(buttons_once_press_num == em_VOL_DOWN)//加 按键释放，按一下加减一档
		{
			delay(DELAY_TIME);//去抖动
			if(buttons_still_press(VOL_DOWN) ) //buttons_still_press(PTTIN)//VOL_DOWN() == 0
			{
				while(buttons_still_press(VOL_DOWN) );//等待按键释放
				return em_VOL_DOWN;
			}
			
				return em_NoButton;
				
		}
		
		 if( buttons_once_press_num == em_NoButton )//无按下按键
		{
			
			return em_NoButton;//em_NoButton;
		}
	/*em_NoButton=0,em_SPC_IN,em_PTT_IN,em_VOL_UP,em_VOL_DOWN,枚举值*/
	/*SPCIN,PTTIN,VOL_UP,VOL_DOWN*///io口按键	
		
} 



void key_control(enum_buttons_type  which_buttons)
{
	/*em_NoButton=0,em_SPC_IN,em_PTT_IN,em_VOL_UP,em_VOL_DOWN,枚举值*/
	/*SPCIN,PTTIN,VOL_UP,VOL_DOWN*///io口按键	
static unsigned char FlagBit_EN_MU = 0;	  

switch (which_buttons)
{
	case(em_SPC_IN):// mute静音
	{
		
  	if (!FlagBit_EN_MU) //非静音状态可进； //开机第一次条件，FlagBit_EN_MU=0；可进
  	{
  		MUOUT_0();//静音开
  		FlagBit_EN_MU=1; 
  		
  	}
  	else{
  	MUOUT_1();//静音关
  	FlagBit_EN_MU=0;
  	
  	}
    //led_blink() ;   
		//LED(120);//提醒
		break;
	}
		
		
	case(em_PTT_IN):// PPT对讲
	{ 
			/*ppt_down_mu();//静音开启*/
			PD_1();//POWER DOWN,电源开启非节能
			delay(6000);delay(6000);delay(6000);delay(6000);delay(6000);
			
			PTTOUT_1();//PPT录音开启
			LED_0(); //LED灯亮
			
			while( buttons_still_press(PTTIN)  );//等待PPT按键释放
			
      PTTOUT_0();//PPT录音关
			LED_1();//LED灯灭
			
			PD_0();//POWER DOWN,电源关闭节能
			/*ppt_up_no_mu();*/
			
			break;
	}
	
	case(em_VOL_UP):   // 音量UP // 5 ,4,3,2,1  小音量到大音量
	{	
		 
  
		if(sound == 1)//音量最大
		{
			//发声报警音
			 led_blink();//LED闪烁
		}
		else
		{
			sound--;//增音量   
			control_sound(sound);
			LED(60);
		}
		break;
	}
	
	case(em_VOL_DOWN): //em_VOL_DOWN
	{	
		if(sound == 5)//音量最小
		{
			//发声报警音
			 led_blink();//LED闪烁
		}
		else
		{
			sound++;//减音量
			control_sound(sound);
			LED(60);
			
			
			
			/*
			LED_1(); 
			delay(DEY);led错了
			LED_0();*/
		}
		break;
	}
		
	
	case(em_NoButton): //无按键状态
		{
			break;			//do nothing
		}
	
	default:
		{
			break;//do nothing
		}
		
	
	}/*switch*/
}


//**********************************************************//



void main(void)
{
   
	system_init();
	delay(30);//延迟30周期*/

	while(1)
	{
	
	 key_control( get_key() );//do forever
			
	}/*while(1)*/
		
	
}/*MAIN*/
