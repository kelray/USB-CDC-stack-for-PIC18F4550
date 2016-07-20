
/*****************************************************************************
 * FileName:        	mTouchCap_CtmuAPI.h
 * Dependencies:
 * Processor:       	PIC18, PIC24
 * Compiler:       	C18, C30
 * Linker:          	MPLAB LINK30
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2009 Microchip Technology Inc.  
 * Microchip licenses this software to you solely for use with Microchip products, according to the terms of the  
 * accompanying click-wrap software license.  Microchip and its licensors retain all right, title and interest in 
 * and to the software.  All rights reserved. This software and any accompanying information is for suggestion only.  
 * It shall not be deemed to modify Microchip’s standard warranty for its products.  It is your responsibility to ensure 
 * that this software meets your requirements.

 * SOFTWARE IS PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS LICENSORS BE LIABLE 
 * FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO INCIDENTAL, 
 * SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, OR ANY CLAIMS BY THIRD PARTIES 
 * (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.  
 * The aggregate and cumulative liability of Microchip and its licensors for damages related to the use of the software 
 * will in no event exceed $1000 or the amount you paid Microchip for the software, whichever is greater.

 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS AND 
 * THE TERMS OF THE ACCOMPANYING CLICK-WRAP SOFTWARE LICENSE.
 * 
 *
 * Author               	Date        	Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Naveen. M				     14 Apr 2009		Version 1.0 Initial Draft
 * Sasha. M	/ Naveen. M		4 May 2009  	Version 1.1.release
 * Sasha. M	/ Naveen. M		11 Nov 2009  			Version 1.0 Release
 *****************************************************************************/
#ifndef _mTOUCH_CAP_CTMU_API_H
#define _mTOUCH_CAP_CTMU_API_H
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Includes	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include	"mTouchCap_Config.h"	
#include 	"GenericTypeDefs.h"
#include 	"mTouchCap_HardwareProfile.h" 

#ifdef __PIC24F__
		#include "mTouchCap_PIC24_CTMU_Physical.h"
#else
		#include "mTouchCap_PIC18_CTMU_Physical.h"
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Enums      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

enum
{
	NO,
	YES
};
enum
{
	NOT_AN_ACTIVE_CHANNEL = -1,
	KEY_NOT_PRESSED,
	KEY_PRESSED	
};

enum
{
	FAILED = -1,
	PASSED = 1	
};

enum
{
	NEGATIVE_EDGE_POL=0,
	POSITIVE_EDGE_POL
};

enum
{
	CURRENT_SRC_DISABLED=0,
	CURRENT_RANGE_BASE_CURRENT,
	CURRENT_RANGE_10XBASE_CURRENT,
	CURRENT_RANGE_100XBASE_CURRENT
};

enum
{
	TRIGGER_SOURCE_TIMER1=0,
	TRIGGER_SOURCE_OC,
	TRIGGER_SOURCE_EXTERNAL2,
	TRIGGER_SOURCE_EXTERNAL1
};


enum
{
	OUTPUT=0,
	INPUT
};

enum
{
	LOW=0,
	HIGH
};

enum
{
	DISABLE=0,
	ENABLE
};

enum 
{
	CHANNEL_AN0 ,
	CHANNEL_AN1 ,
	CHANNEL_AN2 ,
	CHANNEL_AN3 ,
	CHANNEL_AN4 ,
	CHANNEL_AN5 ,
	CHANNEL_AN6 ,
	CHANNEL_AN7 ,
	CHANNEL_AN8 ,
	CHANNEL_AN9 ,
	CHANNEL_AN10 ,
	CHANNEL_AN11 ,
	CHANNEL_AN12 
	#if defined(__PIC24F__)	//NC3
	,CHANNEL_AN13 ,	// for PIC24. Not available in PIC18
	CHANNEL_AN14 ,		// for PIC24. Not available in PIC18
	CHANNEL_AN15 		// for PIC24. Not available in PIC18
	#endif 
};


/* chFilterType[ChannelNum] 
	Filter type methods. If the order is changed here, change the condition in the function "mTouchCapPhy_AverageData"

	FilterType - Filter type selection
                     *	0 - Slow moving average 1/20
                     *	1 - Gated average (as soon as the press stop averaging)
                     *	2 - Fast average (average every sample)   
 */

	#define FILTER_METHOD_1BY20				0
	#define FILTER_METHOD_GATEDAVEARAGE		1
	#define FILTER_METHOD_FASTAVERAGE		2



/*  chDecodeMethod	[ChannelNum]
		- The decoding method used
                     *	0 - most pressed
                     *	1 - multiple presses detected at the same time
                     *	2 - press-and-release asserts the press
                     *	3 - press it self assert the press
          	     	*	4 - key press freezes the key board, until it is released

Filter type methods. If the order is changed here, change the condition in the function "mTouchCapPhy_AverageData" 
*/
enum
{
	DECODE_METHOD_MOST_PRESSED,		/* Future exapansion pending */
	DECODE_METHOD_MULTIPLE_PRESS,		/* Future exapansion pending */
	DECODE_METHOD_PRESS_AND_RELEASE,	/* Future exapansion pending */
	DECODE_METHOD_PRESS_ASSERT,			/* Implemented */
	DECODE_METHOD_KEY_PRESS_FREEZ		/* Future exapansion pending */
};

/* Return values of the API "mTouchCapAPI_SetUpChannel" */
enum
{
	SETUP_SUCCESS,		/* The setup process is successfull */
	SETUP_ERROR		/* There is some kind of error in Setup */
};
	  
enum
{
	TWO_CHANNEL_SLIDER = 2,		// A two channel Slider
	FOUR_CHANNEL_SLIDER =4		// A four channel Slider
};
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Constants / Macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* Allow 5% variations in ADC value to achieve on a channel in Auto adjust functionality */
#define	AUTO_ADJUST_BAND_PERCENT	8		 

#define AUTO_ADJUST_STEP_SIZE			3	//Fix the appropriate value


#define CURRENT_SOURCE_TRIM_BITS_MAX_POSITIVE	0x1F
#define CURRENT_SOURCE_TRIM_BITS_MIN_POSITIVE	0x01
#define CURRENT_SOURCE_TRIM_BITS_NOMINAL	0x00
#define CURRENT_SOURCE_TRIM_BITS_MIN_NEGATIVE	0x3F
#define CURRENT_SOURCE_TRIM_BITS_MAX_NEGATIVE	0x21

#define CURRENT_SOURCE_TRIM_BITS_POSITIVE_RANGE_MASK	0x3F
#define CURRENT_SOURCE_TRIM_BITS_NEGATIVE_RANGE_MASK	0x1F


#define 	ADC_UNTOUCHED_VALUE_10_BIT	0x3FF	//Untouched value for a 12-bit ADC


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Externs  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Function Prototypes  ~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

CHAR mTouchCapAPI_GetStatusDirectButton (WORD ChannelNumber);
CHAR mTouchCapAPI_GetStatusMatrixButton (WORD RowChannelNum, WORD ColChannelNum);
WORD  mTouchCapAPI_GetStatusSlider (BYTE NoOfSliderChannels); 
BYTE mTouchCapAPI_SetUpChannel (WORD ChannelNum, BYTE TripThreshold, BYTE DecodeMethod, BYTE FilterType);
void mTouchCapAPI_SetUpCTMU_Default(WORD ChannelNum);
void mTouchCapAPI_SetUpCSM_Default(WORD ChannelNum);
WORD mTouchCapAPI_CTMU_GetChannelReading (WORD ChannelNum);
CHAR mTouchCapAPI_AutoAdjustChannel (WORD ChannelNum, WORD AdcValueToAchieve);
void mTouchCapAPI_CTMU_SetupCurrentSource (BYTE CurrentSourceRange, BYTE TrimValue);
void mTouchCapAPI_CSM_SetCurrentSource (BYTE CurrentSourceRange);
WORD mTouchCapAPI_ScanChannelIterative (WORD ChannelNum, BYTE SampleCount);

void SetChannelBit(WORD,BYTE);
void InitAvgDelay(void);
BYTE getChannelTouchStatus(WORD ChIndex);
void DynamicTripValueCalculation(WORD Index);
void mTouchCapPhy_AverageData(WORD Index);

#ifdef USE_SLIDER_2CHNL
extern WORD mTouchCapApp_TwoChannelSliderLogic(WORD Channel_L, WORD Channel_R);
#endif

#ifdef USE_SLIDER_4CHNL
    
extern WORD mTouchCapApp_FourChannelSliderLogic(float deltaCh0,float deltaCh1,float deltaCh2,float deltaCh3 );
#endif

#endif	// _mTOUCH_CAP_CTMU_API_H


