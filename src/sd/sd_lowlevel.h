#ifndef _SD_LOWLEVEL_H
#define _SD_LOWLEVEL_H

#define SD_SPI                           SPI1
#define SD_SPI_CLK                       RCC_APB2Periph_SPI1
#define SD_SPI_SCK_PIN                   GPIO_Pin_5                  /* PA.05 */
#define SD_SPI_SCK_GPIO_PORT             GPIOA                       /* GPIOA */
#define SD_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOA
#define SD_SPI_MISO_PIN                  GPIO_Pin_6                  /* PA.06 */
#define SD_SPI_MISO_GPIO_PORT            GPIOA                       /* GPIOA */
#define SD_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOA
#define SD_SPI_MOSI_PIN                  GPIO_Pin_7                  /* PA.07 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOA                       /* GPIOA */
#define SD_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOA
#if 1
#define SD_DETECT_PIN                    GPIO_Pin_7                  /* PE.07 */
#define SD_DETECT_GPIO_PORT              GPIOE                       /* GPIOE */
#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOE
#endif


/*******************export api********/
void SD_LowLevel_Init(void);
void SD_LowLevel_DeInit(void);
uint8_t SD_WriteByte(uint8_t Data);
uint8_t SD_ReadByte(void);
void spi_choose_stm32(uint8_t);
uint16_t spi_speed(uint32_t speed);
void gpio_spi_LowLevel_Init(void);
uint8_t gpio_spi_ReadByte(void);
uint8_t gpio_spi_WriteByte(uint8_t num);
int spi_is_stm32_type();
#endif
