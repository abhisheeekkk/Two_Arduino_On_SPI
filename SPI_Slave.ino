/*
  Pinout for Connection between Arduino Boards
  GND       -   GND
  D13       -   D13 (SCLK)
  D12       -   D12 (MISO)
  D11       -   D11 (MOSI)
  D10       -   D10 (CS)
*/

#include <SPI.h>

typedef enum
{
	ADD_1 = 0,										/**<To check if it's command for addition with 1. */ 
	SUB_1, 										    /**<To check if it's command for Subtraction with 1. */ 
	MUL_2, 										    /**<To check if it's command for multiplication with 2. */ 
	FLOOR_X_3,		 								/**<To check if it's command for doing X/3 and then doing floor operation. */
}commadType;

/*
  Defination for DATA_POS index.
*/
#define DATA_POS (uint8_t)(0U)

/*
  Defination for CMD_POS index.
*/
#define CMD_POS  (uint8_t)(1U)

/*
  Flags set as volatile because the values will changes in Interrupt service routine.
*/
volatile boolean received = false;

/*
  Array to store the received two bytes of data.
*/
uint8_t arr[2] = {0U};


/**
*	@brief		 Initialization function for Arduino UNO.
*	@test		   MISRA-C 2012 Compliant function.
*	@return    void
*/
void setup()
{
  /*
    Initializing Serial communication at 115200 bps.
  */
  Serial.begin(115200);

  /*
    Initializing pin of MISO as output.
  */
  pinMode(MISO,OUTPUT);
  
  /*
    enabling the SPI.
  */
  SPCR |= _BV(SPE);

  /*
    Attaching the interrupt to SPI.
  */
  SPI.attachInterrupt();

  Serial.println("Setup done!!!");
}

/**
*	@brief		 Interrupt service routine for SPI
*	@test		   MISRA-C 2012 Compliant function.
*	@return    void
*/
ISR (SPI_STC_vect)
{
  //We initialize indexPos for the array.
  static int indexPos = 0;
  if(indexPos == 0)
  {
  /*
    Filling the array with received data from SPI line.
  */
    arr[indexPos] = SPDR;
    indexPos++;
  }
  else if(indexPos == 1 && (SPDR >= ADD_1 && SPDR <= FLOOR_X_3))    //the command shall be between 0 to 3.
  {
    arr[indexPos] = SPDR;
    indexPos = 0;
    /*
      setting the received flag to indicate that we have receieved data from SPI line.
    */
    received = true;
  }
  else
  {
    indexPos = 0;
  }
}

/**
*	@brief		 Loop function for arduino framework, this will run continuously.
*	@test		   MISRA-C 2012 Compliant function.
*	@return    void
*/
void loop()
{
  /*
    Checking the flag that if data has been received from SPI line.
  */
  if(received)
  {
    /*
      We set this flag to true, so that our code doesn't go inside again and again, sine it's a continuous loop.
    */
    received = false;

    /*
      We check if the received command is to add the number with 1.
    */
    if (arr[CMD_POS] == ADD_1)
    {
      /*
        Received number is added with 1 and sent back to the Master.
      */
      SPDR = arr[DATA_POS] + 1;
      Serial.println("ADD_1 !!!");
    }

    /*
      We check if the received command is to subtract the number with 1.
    */
    else if(arr[CMD_POS] == SUB_1)
    {
      /*
        Received number is subtracted with 1 and sent back to the Master.
      */
      SPDR = arr[DATA_POS] - 1;
      Serial.println("SUB_1 !!!");
    }

    /*
      We check if the received command is to multiply the number with 2.
    */
    else if(arr[CMD_POS] == MUL_2)
    {
      /*
        Received number is multiplied with 2 and sent back to the Master.
      */
      SPDR = arr[DATA_POS] * 2;
      Serial.println("MUL_2 !!!");
    }

    /*
      We check if the received command is to floor operation after diving the number by 3.
    */
    else if(arr[CMD_POS] == FLOOR_X_3)
    {
      /*
        Received number is divided with 3 and then we do floor operation and sent back to the Master.
      */
      SPDR = floor(arr[DATA_POS]/3);
      Serial.println("FLOOR_X_3 !!!");
    }
  }
}
