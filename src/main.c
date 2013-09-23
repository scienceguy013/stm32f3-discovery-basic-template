#include "stm32f30x.h"
#include "stm32f3_discovery.h"

/* Private variables ---------------------------------------------------------*/
  RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t TimingDelay = 0;
__IO uint32_t UserButtonPressed = 0x00;

/* Private function prototypes -----------------------------------------------*/
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/*
 *	from stm32f30x_it.c this is the button interrupt handler...
 */

void EXTI0_IRQHandler(void)
{
	int i;
	if ((EXTI_GetITStatus(USER_BUTTON_EXTI_LINE) == SET)&&(STM_EVAL_PBGetState(BUTTON_USER) != RESET))
	{
		/* Delay */
		for(i=0; i<0x7FFFF; i++);

		/* Wait for the SEL button to be pressed */
		while(STM_EVAL_PBGetState(BUTTON_USER) != RESET);
		/* Delay */
		for(i=0; i<0x7FFFF; i++);
		UserButtonPressed ++;

		if (UserButtonPressed > 0x1)
		{
			UserButtonPressed = 0x0;
		}
		/* Clear the EXTI line pending bit */
		EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
	}
}

/**
  * @brief  Main program.
  * @param  None 
  * @retval None
  */
int main(void)
{  
  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
  /* Initialize LEDs and User Button available on STM32F3-Discovery board */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);
  STM_EVAL_LEDInit(LED8);
  STM_EVAL_LEDInit(LED9);
  STM_EVAL_LEDInit(LED10);

	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
	UserButtonPressed = 0x00; //Reset variable?   

	/* Infinite loop */
  while (1)
  {   
		if(UserButtonPressed == 0x00)
		{
			/* LEDs Off */
			STM_EVAL_LEDOff(LED3);
			STM_EVAL_LEDOff(LED6);
			STM_EVAL_LEDOff(LED7);
			STM_EVAL_LEDOff(LED4);
			STM_EVAL_LEDOff(LED10);
			STM_EVAL_LEDOff(LED8);
			STM_EVAL_LEDOff(LED9);
			STM_EVAL_LEDOff(LED5);
    }
		else
		{
    //Delay(50); // 500ms - half second
    
    /* LEDs Off */
			STM_EVAL_LEDOn(LED3);
			STM_EVAL_LEDOn(LED6);
			STM_EVAL_LEDOn(LED7);
			STM_EVAL_LEDOn(LED4);
			STM_EVAL_LEDOn(LED10);
			STM_EVAL_LEDOn(LED8);
			STM_EVAL_LEDOn(LED9);
			STM_EVAL_LEDOn(LED5);
		}
    Delay(50); /*500ms - half second*/
  }
}
/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
