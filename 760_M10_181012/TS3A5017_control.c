//**********************************************************//
//	TS3A5017��������Դ���롡������							//
//	ATTINY24-20SSU         									//
//	V1.0	2018.9.12									//
//  														//
//**********************************************************//
//#include "760_M10_MACROH.h" //#define __760_M10_MACROH_H
//#include "760_M10_FUN.h" //#define FUN
//**********************************************************//
//ȫ�ֱ���
unsigned char sound=3;//������������,
//ȫ�ֱ���

#include <iot24v.h>
#include <macros.h>

//key1���� SP  IN����,�͵�ƽ��Ч,PA4  ����0001 0000
#define SPCIN    (PINA & 0x10)

//key2���� PTT IN����,�͵�ƽ��Ч,PA2  ����0000 0100
#define PTTIN   (PINA & 0x04)	

//key3���壬�͵�ƽ��Ч,��������,PA0 ����0000 0001
#define  VOL_UP    (PINA & 0x01)

//key4���壬�͵�ƽ��Ч����������,PA6 ����0100 0000
#define  VOL_DOWN   (PINA & 0x40)

//����1EN PA1,���
#define EN1_0() PORTA &=~(1<<1)
#define EN1_1() PORTA |=(1<<1)
 
//����PD PB1,���
#define PD_0() PORTB &=~(1<<1)
#define PD_1() PORTB |=(1<<1)

//����IN1 PB2,���//
#define IN1_0() PORTB &=~(1<<2)
#define IN1_1() PORTB |=(1<<2)

//����IN2 PA3,���
#define IN2_0() PORTA &=~(1<<3)
#define IN2_1() PORTA |=(1<<3)

//����led PB0, ���
#define LED_0()  PORTB &=~(1<<0)
#define LED_1()  PORTB |=(1<<0)

//���� MUOUT,PA7,���
#define MUOUT_0()   PORTA &=~(1<<7)
#define MUOUT_1()   PORTA |=(1<<7)

//����PTTOUT PA5,���
#define PTTOUT_0()   PORTA &=~(1<<5)
#define PTTOUT_1()   PORTA |=(1<<5)

typedef enum enum_buttons	{   //��������
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
 PORTB = 0x01; //0000 0001//  PB0=1 LED�� PB1=0(���ܸ�λ��PB2=0 PB3=0����λ��
 DDRB  = 0xFF; //1111 1111 ȫ��� 

 
 DDRA  = 0xAA; //1010 1010, //PA0=0,����;PA1=1���,PA2����,PA3���,
												//PA4���룬PA5�����PA6����,PA7���
												
 PORTA = 0x57; //1101 0111,      //PA3=0,PA2=1,PA1=1, PA0=1, 											
}																		//	PA7=0,PA6=1,PA5=0,PA4=1		
																		//pa7��cro_spk Ҫ��ʼ��Ϊ0
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
    delay(200);//�ӳ�30����*/

}


void LED(unsigned char s)//LED ��˸
{
	unsigned char i;
	
	for(i=0;i<80;i++)
	{
		LED_0();

		delay(s);
		
		LED_1();//��
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
		
		LED_0();//��
		Delay_LED();//	
		LED_1();//��
		Delay_LED();//
			
		}
}


void control_sound(unsigned char sound_level)  
 {
  switch (sound_level)
   {
	   case (1):
	    EN1_1();//PA1,�����
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
	 															/*SPCIN,PTTIN,VOL_UP,VOL_DOWN*///io�ڰ���
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
	  
	 
	static	enum_buttons_type  buttons_once_press_num = em_NoButton;//��һ������������
	static	unsigned char      mu_count=0;//mu������ʱ�䣬, static �ֲ���̬�������Ч��
	static  unsigned char  do_mu_flag=1;							// static �ֲ���̬�������Ч��
 	static  unsigned char  mu_count_ok=0; //����ʱ�䵽�� , static �ֲ���̬�������Ч��
 	static  unsigned char	 return_num = em_NoButton ;//Ĭ�Ϸ���0
  
		buttons_once_press_num = buttons_once_press ();  //��ȡbutton��enum_buttons_type  buttons_once_press (void) ;
  //test
 // if(buttons_once_press_num == em_VOL_UP )
 // {
  //	led_blink() ;led_blink() ;led_blink() ;led_blink() ;
 // 	
 // }	
  //test
  
  
		if(buttons_once_press_num == em_SPC_IN	)//mute�����л�����������Ҫ�ͷ�//���볤���ɿ�����1//SPCIN() == 0
		{
			delay(DELAY_TIME);//ȥ�������޸�Ϊ�ϱ��ش�����������ֻ���ڰ���ʱ�򴥷�һ��
			return_num=0;
			if(buttons_still_press(SPCIN) )//SPCIN() == 0
			{	
				while(buttons_still_press(SPCIN) )//�ȴ������ͷ�	���Է��������ͬʱ����	
				{
					delay(10000); mu_count++; 
					if(mu_count>=20)//��Լ2��
					{
							if(do_mu_flag){
								return_num = em_SPC_IN ;	//����ֻ����һ��mu�������� 
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
			if (mu_count_ok == 0 ) //ʱ��wei����
				{ 
					mu_count_ok = 0;return_num = em_NoButton ; 
					
				}
			
	    return ( (return_num>em_NoButton)? em_SPC_IN : em_NoButton );   //����return  1 ���޳�������0 ;
		
		}

		
		if(buttons_once_press_num == em_PTT_IN)//PPT����Ҫ�������ͷ�
		{
			delay(DELAY_TIME);//ȥ����
	
			if(buttons_still_press(PTTIN) )  //buttons_still_press(PTTIN)//PTTIN() == 0
			{
				return em_PTT_IN;
			}
	      
				return em_NoButton;
		}
		
		 if(buttons_once_press_num == em_VOL_UP)//�� �����ͷţ���һ�¼Ӽ�һ��
		{
			
			delay(DELAY_TIME);//ȥ����
			if(buttons_still_press(VOL_UP) )   //buttons_still_press(PTTIN)//VOL_UP() == 0
			{	
				while(buttons_still_press(VOL_UP) );//�ȴ������ͷ�
				return em_VOL_UP;
			}
					
			return em_NoButton;
			
		}
		
		 if(buttons_once_press_num == em_VOL_DOWN)//�� �����ͷţ���һ�¼Ӽ�һ��
		{
			delay(DELAY_TIME);//ȥ����
			if(buttons_still_press(VOL_DOWN) ) //buttons_still_press(PTTIN)//VOL_DOWN() == 0
			{
				while(buttons_still_press(VOL_DOWN) );//�ȴ������ͷ�
				return em_VOL_DOWN;
			}
			
				return em_NoButton;
				
		}
		
		 if( buttons_once_press_num == em_NoButton )//�ް��°���
		{
			
			return em_NoButton;//em_NoButton;
		}
	/*em_NoButton=0,em_SPC_IN,em_PTT_IN,em_VOL_UP,em_VOL_DOWN,ö��ֵ*/
	/*SPCIN,PTTIN,VOL_UP,VOL_DOWN*///io�ڰ���	
		
} 



void key_control(enum_buttons_type  which_buttons)
{
	/*em_NoButton=0,em_SPC_IN,em_PTT_IN,em_VOL_UP,em_VOL_DOWN,ö��ֵ*/
	/*SPCIN,PTTIN,VOL_UP,VOL_DOWN*///io�ڰ���	
static unsigned char FlagBit_EN_MU = 0;	  

switch (which_buttons)
{
	case(em_SPC_IN):// mute����
	{
		
  	if (!FlagBit_EN_MU) //�Ǿ���״̬�ɽ��� //������һ��������FlagBit_EN_MU=0���ɽ�
  	{
  		MUOUT_0();//������
  		FlagBit_EN_MU=1; 
  		
  	}
  	else{
  	MUOUT_1();//������
  	FlagBit_EN_MU=0;
  	
  	}
    //led_blink() ;   
		//LED(120);//����
		break;
	}
		
		
	case(em_PTT_IN):// PPT�Խ�
	{ 
			/*ppt_down_mu();//��������*/
			PD_1();//POWER DOWN,��Դ�����ǽ���
			delay(6000);delay(6000);delay(6000);delay(6000);delay(6000);
			
			PTTOUT_1();//PPT¼������
			LED_0(); //LED����
			
			while( buttons_still_press(PTTIN)  );//�ȴ�PPT�����ͷ�
			
      PTTOUT_0();//PPT¼����
			LED_1();//LED����
			
			PD_0();//POWER DOWN,��Դ�رս���
			/*ppt_up_no_mu();*/
			
			break;
	}
	
	case(em_VOL_UP):   // ����UP // 5 ,4,3,2,1  С������������
	{	
		 
  
		if(sound == 1)//�������
		{
			//����������
			 led_blink();//LED��˸
		}
		else
		{
			sound--;//������   
			control_sound(sound);
			LED(60);
		}
		break;
	}
	
	case(em_VOL_DOWN): //em_VOL_DOWN
	{	
		if(sound == 5)//������С
		{
			//����������
			 led_blink();//LED��˸
		}
		else
		{
			sound++;//������
			control_sound(sound);
			LED(60);
			
			
			
			/*
			LED_1(); 
			delay(DEY);led����
			LED_0();*/
		}
		break;
	}
		
	
	case(em_NoButton): //�ް���״̬
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
	delay(30);//�ӳ�30����*/

	while(1)
	{
	
	 key_control( get_key() );//do forever
			
	}/*while(1)*/
		
	
}/*MAIN*/
