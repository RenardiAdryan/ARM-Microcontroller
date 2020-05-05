// LCD control lines (must be on the same port)

	#define LCD16X2_RCC_GPIO_CONTROL   RCC_APB2Periph_GPIOB

	#define LCD16X2_GPIO_CONTROL       GPIOB

	#define LCD16X2_GPIO_RS            GPIOB

#define LCD16X2_GPIO_RW            GPIOB

	#define LCD16X2_GPIO_EN            GPIOB

	// LCD data lines (must be on the same port)

	#define LCD16X2_RCC_GPIO_DATA      RCC_APB2Periph_GPIOA

	#define LCD16X2_GPIO_DATA          GPIOA

	#define LCD16X2_GPIO_D4            GPIOA

	#define LCD16X2_GPIO_D5            GPIOA

	#define LCD16X2_GPIO_D6            GPIOA

	#define LCD16X2_GPIO_D7            GPIOA

	// Pin definition

	#define LCD16X2_PIN_RS             GPIO_Pin_12

	#define LCD16X2_PIN_RW             GPIO_Pin_13

	#define LCD16X2_PIN_EN             GPIO_Pin_14

	#define LCD16X2_PIN_D4             GPIO_Pin_8     // 4-bit mode LSB

	#define LCD16X2_PIN_D5             GPIO_Pin_9

	#define LCD16X2_PIN_D6             GPIO_Pin_10

	#define LCD16X2_PIN_D7             GPIO_Pin_11    // 4-bit mode MSB