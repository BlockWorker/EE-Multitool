/*
@file    FT8_config.h
@brief   configuration information for some TFTs and some pre-defined colors
@version 3.9
@date    2018-14-04
@author  Rudolph Riedel

@section History

2.2
- added prototypes for hardware abstraction funtions
- added hardware-selection defines, first implemented for AVR8
- added FT8_VM800B50A TFT setup as copy of FT8_VM800B43A since FTDI uses the same setup for both

2.3
- moved pin definitions for FT8_CS and FR_PDN to here from FT8_config.c
- added a set of definitions for Arduino

2.4
- switched from custom AVR8 to standard __AVR__ symbol to automatically generate plattform specific code
- removed the definition of the ARDUINO symbol at it already is defined by the Arduino enviroment

2.5
- added support for RH850
- switched to standard-C compliant comment-style
- added FT8_HAS_CRYSTAL to make FT8_init() automatically use the correct option

3.0
- renamed from FT800_config.h to FT8_config.h
- changed FT_ prefixes to FT8_
- changed ft800_ prefixes to FT8_

3.1
- added "#if defined (__ESP8266__)" for the Arduino side, now empty

3.2
- added config for FT811CB_HY50HD

3.3
- switched to inline definitions for all those one-line support-functions -> faster and FT8_config.c is no longer needed
- added timing parameters for Matrix Orbital EVE2 displays, derived from their sample code, untested
- added FT8_CSPREAD values to all display settings

3.4
- forgot that I switched to SPI.write() for Arduino/ESP8266 and that the standard Arduino only has SPI.transfer()
- added auto-detection for AVR over 64kB FLASH 

3.5
- switched from "#if defined (RAMPZ)" to "#if defined (__AVR_HAVE_ELPM__)" as it turned out there are AVR that have the RAMPZ register but less than 64k FLASH

3.6
- changed the FT8_HAS_CRYSTAL for the Matrix Orbital modules from '1' to '0' as it turned out these are not using a crystal

3.7
- added timing parameters for Newhaven EVE2 displays, derived from their datasheets, untested

3.8
- added timing parameters for Glyn ADAM101-LCP-SWVGA-NEW 10.1" TFT with 1024x600
- fixed a copy-paste error with my latest changes to the Arduino code that killed the SPI 

3.9
- changed the timing parameters for EVE2-38A to match those listed in the 1.3 manual from Matrix Orbital
- added a FT8_EVE2_35G profile with a new define: FT8_HAS_GT911
- added more explanatory text before the code-block
- added more FT8_EV2_xxG profiles as the other cap-touch modules from Matrix Orbital also have a GT911 as touch-controller

*/

#ifndef FT8_CONFIG_H_
#define FT8_CONFIG_H_

/* switch over to FT81x */
#define FT8_81X_ENABLE


/* select the settings for the TFT attached */
#if 0
	#define FT8_VM800B35A
	#define FT8_VM800B43A
	#define FT8_VM800B50A
	#define FT8_FT810CB_HY50HD
	#define FT8_FT811CB_HY50HD
	#define FT8_ET07
	#define FT8_RVT70AQ
	#define FT8_EVE2_29
	#define FT8_EVE2_35
	#define FT8_EVE2_35G
	#define FT8_EVE2_38
	#define FT8_EVE2_38G
	#define FT8_EVE2_43
	#define FT8_EVE2_43G
	#define FT8_EVE2_50
	#define FT8_EVE2_50G
	#define FT8_EVE2_70
	#define FT8_EVE2_70G
	#define FT8_NHD_35
	#define FT8_NHD_43
	#define FT8_NHD_50
	#define FT8_NHD_70
	#define ADAM101
#endif

#define FT8_NHD_35


/* some pre-definded colors */
#define RED		0xff0000UL
#define ORANGE	0xffa500UL
#define GREEN	0x00ff00UL
#define BLUE	0x0000ffUL
#define YELLOW	0xffff00UL
/*#define PINK	0xff00ffUL*/
#define PURPLE	0x800080UL
#define WHITE	0xffffffUL
#define BLACK	0x000000UL


/* While the following lines make things a lot easier like automatically compiling the code for the platform you are compiling for, */
/* a few things are expected to be taken care of beforehand. */
/* - setting the Chip-Select and Power-Down pins to Output, Chip-Select = 1 and Power-Down = 0 */
/* - setting up the SPI which may or not include things like
       - setting the pins for the SPI to output or some alternate I/O function or mapping that functionality to that pin
	   - if that is an option with the controller your are using you probably should set the drive-strength for the SPI pins to high
	   - setting the SS pin on AVRs to output in case it is not used for Chip-Select or Power-Down
	   - setting SPI to mode 0
	   - setting SPI to 8 bit with MSB first
	   - setting SPI clock to no more than 11 MHz for the init - if the display-module works as high

  For the SPI transfers single 8-Bit transfers are used with busy-wait for completion.
  While this is okay for AVRs that run at 16MHz with the SPI at 8 MHz and therefore do one transfer in 16 clock-cycles,
  this is wasteful for any 32 bit controller even at higher SPI speeds.
  However, 32 bit controllers are not my main target (yet) and the amount of data sent over the SPI is really small with the FT8xx.
  This will be met with a DMA friendly approach in a future release.
*/	    

#ifndef ARDUINO
	#if defined (__GNUC__)
		#if	defined (__AVR__)

			#include <avr/io.h>
			#include <avr/pgmspace.h>
			#define F_CPU 16000000UL
			#include <util/delay.h>

			#define DELAY_MS(ms) _delay_ms(ms)

			#define FT8_CS_PORT	PORTB
			#define FT8_CS 		(1<<PB5)
			#define FT8_PDN_PORT	PORTB
			#define FT8_PDN		(1<<PB4)

			static inline void FT8_pdn_set(void)
			{
				FT8_PDN_PORT &= ~FT8_PDN;	/* Power-Down low */
			}

			static inline void FT8_pdn_clear(void)
			{
				FT8_PDN_PORT |= FT8_PDN;	/* Power-Down high */
			}

			static inline void FT8_cs_set(void)
			{
				FT8_CS_PORT &= ~FT8_CS;	/* cs low */
			}

			static inline void FT8_cs_clear(void)
			{
				FT8_CS_PORT |= FT8_CS;	/* cs high */
			}

			static inline void spi_transmit(uint8_t data)
			{
				SPDR = data; /* start transmission */
				while(!(SPSR & (1<<SPIF))); /* wait for transmission to complete - 1us @ 8MHz SPI-Clock */
			}
			
			static inline uint8_t spi_receive(uint8_t data)
			{
				SPDR = data; /* start transmission */
				while(!(SPSR & (1<<SPIF))); /* wait for transmission to complete - 1us @ 8MHz SPI-CLock */
				return SPDR;
			}

			static inline uint8_t fetch_flash_byte(const uint8_t *data)
			{
				#if defined (__AVR_HAVE_ELPM__)	/* we have an AVR with more than 64kB FLASH memory */
					return(pgm_read_byte_far(data));
				#else
					return(pgm_read_byte_near(data));
				#endif
			}

		#endif /* AVR */

		#if defined (__v851__)

			#include <stdint.h>
			#include "rh850_regs.h"
			#include "os.h"

			#define DELAY_MS(ms)	OS_Wait(ms * 1000)	

			static inline void FT8_pdn_set(void)
			{
				P0 &= ~(1u<<6);
			}

			static inline void FT8_pdn_clear(void)
			{
				P0 |= (1u<<6);
			}

			static inline void FT8_cs_set(void)
			{
				P8 &= ~(1u<<2); /* manually set chip-select to low */
			}

			static inline void FT8_cs_clear(void)
			{
				P8 |= (1u<<2);  /* manually set chip-select to high */
			}

			static inline void spi_transmit(uint8_t data)
			{
				CSIH0CTL0 = 0xC1; /* CSIH2PWR = 1;  CSIH2TXE=1; CSIH2RXE = 0; direct access mode  */
				CSIH0TX0H = data;	/* start transmission */
				while(CSIH0STR0 & 0x00080);	/* wait for transmission to complete - 800ns @ 10MHz SPI-Clock */
			}

			static inline uint8_t spi_receive(uint8_t data)
			{
				CSIH0CTL0 = 0xE1; /* CSIH2PWR = 1;  CSIH2TXE=1; CSIH2RXE = 1; direct access mode  */
				CSIH0TX0H = data;	/* start transmission */
				while(CSIH0STR0 & 0x00080);	/* wait for transmission to complete - 800ns @ 10MHz SPI-Clock */
				return (uint8_t) CSIH0RX0H;
			}

			static inline uint8_t fetch_flash_byte(const uint8_t *data)
			{
				return *data;
			}

		#endif /* RH850 */

	#endif
#endif

#ifdef ARDUINO
	#include <stdio.h>
	#include <SPI.h>

	#define FT8_CS 		9
	#define FT8_PDN		8

	#define DELAY_MS(ms) delay(ms)

	#ifdef ESP8266

	#endif
	
	#if	defined (__AVR__)
		#include <avr/pgmspace.h>

	#endif


	static inline void FT8_pdn_set(void)
	{
		digitalWrite(FT8_PDN, LOW);	/* Power-Down low */
	}

	static inline void FT8_pdn_clear(void)
	{
		digitalWrite(FT8_PDN, HIGH);	/* Power-Down high */
	}

	static inline void FT8_cs_set(void)
	{
		SPI.setDataMode(SPI_MODE0);
		digitalWrite(FT8_CS, LOW);
	}

	static inline void FT8_cs_clear(void)
	{
		digitalWrite(FT8_CS, HIGH);
	}

	#ifdef ESP8266
		static inline void spi_transmit(uint8_t data)
		{
			SPI.write(data);
		}
	#else
		static inline void spi_transmit(uint8_t data)
		{
			SPI.transfer(data);
		}
	#endif

	static inline uint8_t spi_receive(uint8_t data)
	{
		return SPI.transfer(data);
	}

	static inline uint8_t fetch_flash_byte(const uint8_t *data)
	{
		#if defined(RAMPZ)
			return(pgm_read_byte_far(data));
		#else
			return(pgm_read_byte_near(data));
		#endif
	}

#endif /* Arduino */


/* display timing parameters below */


/* VM800B35A: FT800 320x240 3.5" FTDI */
#ifdef FT8_VM800B35A
#define FT8_VSYNC0	(0L)	/* Tvf Vertical Front Porch */
#define FT8_VSYNC1	(2L)	/* Tvf + Tvp Vertical Front Porch plus Vsync Pulse width */
#define FT8_VOFFSET	(13L)	/* Tvf + Tvp + Tvb Number of non-visible lines (in lines) */
#define FT8_VCYCLE	(263L)	/* Tv Total number of lines (visible and non-visible) (in lines) */
#define FT8_VSIZE	(240L)	/* Tvd Number of visible lines (in lines) - display height */
#define FT8_HSYNC0	(0L)	/* Thf Horizontal Front Porch */
#define FT8_HSYNC1	(10L)	/* Thf + Thp Horizontal Front Porch plus Hsync Pulse width */
#define FT8_HOFFSET	(70L)	/* Thf + Thp + Thb Length of non-visible part of line (in PCLK cycles) */
#define FT8_HCYCLE 	(408L)	/* Th Total length of line (visible and non-visible) (in PCLKs) */
#define FT8_HSIZE	(320L)	/* Thd Length of visible part of line (in PCLKs) - display width */
#define FT8_PCLKPOL	(0L)	/* PCLK polarity (0 = rising edge, 1 = falling edge) */
#define FT8_SWIZZLE	(2L)	/* Defines the arrangement of the RGB pins of the FT800 */
#define FT8_PCLK	(8L)	/* 48MHz / REG_PCLK = PCLK frequency */
#define FT8_CSPREAD	(1L)	/* helps with noise, when set to 1 fewer signals are changed simultaneously, reset-default: 1 */
#define FT8_TOUCH_RZTHRESH (1200L)	/* touch-sensitivity */
#define FT8_HAS_CRYSTAL 1	/* use external crystal or internal oscillator? */
#endif


/* VM800B43A: FT800 480x272 4.3" FTDI */
#ifdef FT8_VM800B43A
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(548L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


/* VM800B50A: FT800 480x272 5.0" FTDI */
#ifdef FT8_VM800B50A
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(548L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


/* FT810CB-HY50HD: FT810 800x480 5.0" HAOYU */
#ifdef FT8_FT810CB_HY50HD
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(13L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(20L)
#define FT8_HOFFSET	(64L)
#define FT8_HCYCLE 	(952L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (2000L)	/* touch-sensitivity */
#define FT8_HAS_CRYSTAL 1
#endif


/* FT811CB-HY50HD: FT811 800x480 5.0" HAOYU */
#ifdef FT8_FT811CB_HY50HD
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(13L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(20L)
#define FT8_HOFFSET	(64L)
#define FT8_HCYCLE 	(952L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)	/* touch-sensitivity */
#define FT8_HAS_CRYSTAL 1
#endif


/* some test setup */
#ifdef FT8_800x480x
#define FT8_VSYNC0	(0L)	/* Tvf Vertical Front Porch */
#define FT8_VSYNC1	(10L)	/* Tvf + Tvp Vertical Front Porch plus Vsync Pulse width */
#define FT8_VOFFSET	(35L)	/* Tvf + Tvp + Tvb Number of non-visible lines (in lines) */
#define FT8_VCYCLE	(516L)	/* Tv Total number of lines (visible and non-visible) (in lines) */
#define FT8_VSIZE	(480L)	/* Tvd Number of visible lines (in lines) - display height */
#define FT8_HSYNC0	(0L)	 /* (40L)	// Thf Horizontal Front Porch */
#define FT8_HSYNC1	(88L)	/* Thf + Thp Horizontal Front Porch plus Hsync Pulse width */
#define FT8_HOFFSET	(169L)	/* Thf + Thp + Thb Length of non-visible part of line (in PCLK cycles) */
#define FT8_HCYCLE 	(969L)	/* Th Total length of line (visible and non-visible) (in PCLKs) */
#define FT8_HSIZE	(800L)	/* Thd Length of visible part of line (in PCLKs) - display width */
#define FT8_PCLKPOL	(1L)	/* PCLK polarity (0 = rising edge, 1 = falling edge) */
#define FT8_SWIZZLE	(0L)	/* Defines the arrangement of the RGB pins of the FT800 */
#define FT8_PCLK	(2L)	/* 60MHz / REG_PCLK = PCLK frequency	30 MHz */
#define FT8_CSPREAD	(1L)	/* helps with noise, when set to 1 fewer signals are changed simultaneously, reset-default: 1 */
#define FT8_TOUCH_RZTHRESH (1200L)	/* touch-sensitivity */
#define FT8_HAS_CRYSTAL 1
#endif


/* G-ET0700G0DM6 800x480 7.0" Glyn, untested */
#ifdef FT8_ET07
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(35L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(128L)
#define FT8_HOFFSET (203L)
#define FT8_HCYCLE 	(1056L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL (1L)
#define FT8_SWIZZLE (0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0	/* no idea if these come with a crystal populated or not */
#endif


/* RVT70AQxxxxxx 800x480 7.0" Riverdi, various options, FT812/FT813, tested with RVT70UQFNWC0x */
#ifdef FT8_RVT70AQ
#define FT8_VSYNC0	(0L)	/* Tvf Vertical Front Porch */
#define FT8_VSYNC1	(10L)	/* Tvf + Tvp Vertical Front Porch plus Vsync Pulse width */
#define FT8_VOFFSET	(23L)	/* Tvf + Tvp + Tvb Number of non-visible lines (in lines) */
#define FT8_VCYCLE	(525L)	/* Tv Total number of lines (visible and non-visible) (in lines) */
#define FT8_VSIZE	(480L)	/* Tvd Number of visible lines (in lines) - display height */
#define FT8_HSYNC0	(0L)	/* Thf Horizontal Front Porch */
#define FT8_HSYNC1	(10L)	/* Thf + Thp Horizontal Front Porch plus Hsync Pulse width */
#define FT8_HOFFSET (46L)	/* Thf + Thp + Thb Length of non-visible part of line (in PCLK cycles) */
#define FT8_HCYCLE 	(1056L)	/* Th Total length of line (visible and non-visible) (in PCLKs) */
#define FT8_HSIZE	(800L)	/* Thd Length of visible part of line (in PCLKs) - display width */
#define FT8_PCLKPOL (1L)	/* PCLK polarity (0 = rising edge, 1 = falling edge) */
#define FT8_SWIZZLE (0L)	/* Defines the arrangement of the RGB pins of the FT800 */
#define FT8_PCLK	(2L)	/* 60MHz / REG_PCLK = PCLK frequency 30 MHz */
#define FT8_CSPREAD	(1L)	/* helps with noise, when set to 1 fewer signals are changed simultaneously, reset-default: 1 */
#define FT8_TOUCH_RZTHRESH (1800L)	/* touch-sensitivity */
#define FT8_HAS_CRYSTAL 0
#endif


/* untested */
/* EVE2-29A 320x102 2.9" 1U Matrix Orbital, non-touch, FT812 */
#ifdef FT8_EVE2_29
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(156L)
#define FT8_VCYCLE	(262L)
#define FT8_VSIZE	(102L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(10L)
#define FT8_HOFFSET	(70L)
#define FT8_HCYCLE 	(408L)
#define FT8_HSIZE	(320L)
#define FT8_PCLKPOL	(0L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(8L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#endif


/* EVE2-35A 320x240 3.5" Matrix Orbital, resistive, or non-touch, FT812 */
#ifdef FT8_EVE2_35
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(18L)
#define FT8_VCYCLE	(262L)
#define FT8_VSIZE	(240L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(10L)
#define FT8_HOFFSET	(70L)
#define FT8_HCYCLE 	(408L)
#define FT8_HSIZE	(320L)
#define FT8_PCLKPOL	(0L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(8L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#endif


/* EVE2-35G 320x240 3.5" Matrix Orbital, capacitive touch, FT813 */
#ifdef FT8_EVE2_35G
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(18L)
#define FT8_VCYCLE	(262L)
#define FT8_VSIZE	(240L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(10L)
#define FT8_HOFFSET	(70L)
#define FT8_HCYCLE 	(408L)
#define FT8_HSIZE	(320L)
#define FT8_PCLKPOL	(0L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(8L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#define FT8_HAS_GT911 1		/* special treatment required for out-of-spec touch-controller */
#endif


/* EVE2-38A 480x116 3.8" 1U Matrix Orbital, resistive touch, FT812 */
#ifdef FT8_EVE2_38
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(524L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#endif


/* EVE2-38G 480x116 3.8" 1U Matrix Orbital, capacitive touch, FT813 */
#ifdef FT8_EVE2_38G
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(524L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#define FT8_HAS_GT911 1		/* special treatment required for out-of-spec touch-controller */
#endif


/* untested */
/* EVE2-43A 480x272 4.3" Matrix Orbital, resistive or no touch, FT812 */
#ifdef FT8_EVE2_43
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(548L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#endif


/* untested */
/* EVE2-43G 480x272 4.3" Matrix Orbital, capacitive touch, FT813 */
#ifdef FT8_EVE2_43G
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(548L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#define FT8_HAS_GT911 1		/* special treatment required for out-of-spec touch-controller */
#endif


/* untested */
/* EVE2-50A 800x480 5.0" Matrix Orbital, resistive, or no touch, FT812 */
#ifdef FT8_EVE2_50
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(3L)
#define FT8_VOFFSET	(32L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(48L)
#define FT8_HOFFSET	(88L)
#define FT8_HCYCLE 	(928L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(0L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#endif


/* untested */
/* EVE2-50G 800x480 5.0" Matrix Orbital, capacitive touch, FT813 */
#ifdef FT8_EVE2_50G
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(3L)
#define FT8_VOFFSET	(32L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(48L)
#define FT8_HOFFSET	(88L)
#define FT8_HCYCLE 	(928L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(0L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#define FT8_HAS_GT911 1		/* special treatment required for out-of-spec touch-controller */
#endif


/* untested */
/* EVE2-70A 800x480 7.0" Matrix Orbital, resistive or no touch, FT812 */
#ifdef FT8_EVE2_70
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(3L)
#define FT8_VOFFSET	(32L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(48L)
#define FT8_HOFFSET	(88L)
#define FT8_HCYCLE 	(928L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(0L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#endif


/* untested */
/* EVE2-70G 800x480 7.0" Matrix Orbital, capacitive touch, FT813 */
#ifdef FT8_EVE2_70G
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(3L)
#define FT8_VOFFSET	(32L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(48L)
#define FT8_HOFFSET	(88L)
#define FT8_HCYCLE 	(928L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(0L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 0
#define FT8_HAS_GT911 1		/* special treatment required for out-of-spec touch-controller */
#endif


/* untested */
/* NHD-3.5-320240FT-CxXx-xxx 320x240 3.5" Newhaven, resistive or capacitive, FT81x */
#ifdef FT8_NHD_35
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(2L)
#define FT8_VOFFSET	(13L)
#define FT8_VCYCLE	(263L)
#define FT8_VSIZE	(240L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(10L)
#define FT8_HOFFSET	(70L)
#define FT8_HCYCLE 	(408L)
#define FT8_HSIZE	(320L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(2L)
#define FT8_PCLK	(6L)
#define FT8_CSPREAD	(0L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


/* untested */
/* NHD-4.3-480272FT-CxXx-xxx 480x272 4.3" Newhaven, resistive or capacitive, FT81x */
#ifdef FT8_NHD_43
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(10L)
#define FT8_VOFFSET	(12L)
#define FT8_VCYCLE	(292L)
#define FT8_VSIZE	(272L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(41L)
#define FT8_HOFFSET	(43L)
#define FT8_HCYCLE 	(548L)
#define FT8_HSIZE	(480L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(5L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


/* untested */
/* NHD-5.0-800480FT-CxXx-xxx 800x480 5.0" Newhaven, resistive or capacitive, FT81x */
#ifdef FT8_NHD_50
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(3L)
#define FT8_VOFFSET	(32L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(48L)
#define FT8_HOFFSET	(88L)
#define FT8_HCYCLE 	(928L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(0L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


/* untested */
/* NHD-7.0-800480FT-CxXx-xxx 800x480 7.0" Newhaven, resistive or capacitive, FT81x */
#ifdef FT8_NHD_70
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(3L)
#define FT8_VOFFSET	(32L)
#define FT8_VCYCLE	(525L)
#define FT8_VSIZE	(480L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(48L)
#define FT8_HOFFSET	(88L)
#define FT8_HCYCLE 	(928L)
#define FT8_HSIZE	(800L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


/* ADAM101-LCP-SWVGA-NEW 1024x600 10.1" Glyn, capacitive, FT813 */
#ifdef ADAM101
#define FT8_VSYNC0	(0L)
#define FT8_VSYNC1	(1L)
#define FT8_VOFFSET	(1L)
#define FT8_VCYCLE	(720L)
#define FT8_VSIZE	(600L)
#define FT8_HSYNC0	(0L)
#define FT8_HSYNC1	(1L)
#define FT8_HOFFSET	(1L)
#define FT8_HCYCLE 	(1100L)
#define FT8_HSIZE	(1024L)
#define FT8_PCLKPOL	(1L)
#define FT8_SWIZZLE	(0L)
#define FT8_PCLK	(2L)
#define FT8_CSPREAD	(1L)
#define FT8_TOUCH_RZTHRESH (1200L)
#define FT8_HAS_CRYSTAL 1
#endif


#endif /* FT8_CONFIG_H */
