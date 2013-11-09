
#include "user_button.h"



__IO uint32_t UserButtonPressed = 0x00;


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
