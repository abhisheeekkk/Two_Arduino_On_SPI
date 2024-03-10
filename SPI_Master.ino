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
  Array to store the received two bytes of data.
*/
uint8_t arr[2] = {0};

/*
  Array to store the response from slave. size is 5 since we send command 5 times.
*/
int8_t responseArr[5] = {0}; 

/**
*	@brief		 Function to send subtraction command to slave via SPI.
*	@test		   MISRA-C 2012 Compliant function.
*	@return    void
*/
void sendSubCommand(void)
{
  Serial.println();
  Serial.println("------------------START SUB_1 Command-----------------");

  /*
    To send command 5 times we initialize a counter.
  */
  int counter = 0;

  /*
    Sending command 5 times.
  */
  while(counter <5)
  {
    /*
      Giving little bit of time after every time we send a command.
    */
    delay(50);
    int8_t numToSend = -127;                 //you are allowed to change this number from -127 to 127,-128's response will overflow.
    arr[DATA_POS] = numToSend;           
    
    /*
      Sending subtract command.
    */
    arr[CMD_POS]  = SUB_1;    

    /*
      Sending both command and data over SPI bus.
      storing the response in m_receive
    */
    int8_t m_receive=SPI.transfer(arr[0]);
    SPI.transfer(arr[1]);

    /*
      Storing the response in array.
    */
    responseArr[counter] = m_receive;

    /*
      We are only printing the response once, since we have to see it on terminal
      we don't want it to fill it completely with same command.
    */
    if(counter == 1)
    {
      Serial.print("Sent by Master: ");
      Serial.println(numToSend);
      Serial.print("Revceived responde: ");
      Serial.println(responseArr[counter]);
    }
    /*
      incrimenting the counter.
    */
    counter++;
  }

  Serial.println("------------------END SUB_1 Command-----------------");
}

/**
*	@brief		 Function to send Addition command to slave via SPI.
*	@test		   MISRA-C 2012 Compliant function.
*	@return    void
*/
void sendAddCommand(void)
{
  Serial.println();
  Serial.println("------------------START ADD_1 Command-----------------");
  
  /*
    To send command 5 times we initialize a counter.
  */
  int counter = 0;

  /*
    Sending command 5 times.
  */
  while(counter <5)
  {
    /*
      Giving little bit of time after every time we send a command.
    */
    delay(50);
    int8_t numToSend = 126;                 //you are allowed to change this number from -128 to 126, 127's response will overflow.
    arr[DATA_POS] = numToSend;           
    
    /*
      Sending add command.
    */
    arr[CMD_POS]  = ADD_1;

    /*
      Sending both command and data over SPI bus.
      storing the response in m_receive
    */
    int8_t m_receive=SPI.transfer(arr[0]);
    SPI.transfer(arr[1]);

    /*
      Storing the response in array.
    */
    responseArr[counter] = m_receive;

    /*
      We are only printing the response once, since we have to see it on terminal
      we don't want it to fill it completely with same command.
    */
    if(counter == 1)
    {
      Serial.print("Sent by Master: ");
      Serial.println(numToSend);
      Serial.print("Revceived responde: ");
      Serial.println(responseArr[counter]);
    }
    /*
      incrimenting the counter.
    */
    counter++;
  }
  Serial.println();
  Serial.println("------------------END ADD_1 Command-----------------");
}


void sendMulCommand(void)
{
  Serial.println();
  Serial.println("------------------START MUL_2 Command-----------------");
  /*
    To send command 5 times we initialize a counter.
  */
  int counter = 0;

  /*
    Sending command 5 times.
  */
  while(counter <5)
  {
    /*
      Giving little bit of time after every time we send a command.
    */
    delay(50);
    int8_t numToSend = -60;                 //please note that, whatever number you select it 2 times of it must not be lesser than -128 and must not be greater than 127.
    arr[DATA_POS] = numToSend;           
    /*
      Sending Multiply command.
    */
    arr[CMD_POS]  = MUL_2;

    /*
      Sending both command and data over SPI bus.
      storing the response in m_receive
    */
    int8_t m_receive=SPI.transfer(arr[0]);
    SPI.transfer(arr[1]);

    /*
      Storing the response in array.
    */
    responseArr[counter] = m_receive;

    /*
      We are only printing the response once, since we have to see it on terminal
      we don't want it to fill it completely with same command.
    */
    if(counter == 1)
    {
      Serial.print("Sent by Master: ");
      Serial.println(numToSend);
      Serial.print("Revceived responde: ");
      Serial.println(responseArr[counter]);
    }

    /*
      incrimenting the counter.
    */
    counter++;
  }

  Serial.println("------------------END MUL_2 Command-----------------");
}


void sendFloorDivCommand(void)
{
  Serial.println();
  Serial.println("------------------START FLOOR_X_3 Command-----------------");
  /*
    To send command 5 times we initialize a counter.
  */
  int counter = 0;

  /*
    Sending command 5 times.
  */
  while(counter <5)
  {
    /*
      Giving little bit of time after every time we send a command.
    */
    delay(50);
    int8_t numToSend = -128;                 //you are allowed to change this number from -128 to 127.
    arr[DATA_POS] = numToSend;           
    /*
      Sending Floor(X/3) command.
    */
    arr[CMD_POS]  = FLOOR_X_3;

    /*
      Sending both command and data over SPI bus.
      storing the response in m_receive
    */
    int8_t m_receive=SPI.transfer(arr[0]);
    SPI.transfer(arr[1]);

    /*
      Storing the response in array.
    */
    responseArr[counter] = m_receive;

    /*
      We are only printing the response once, since we have to see it on terminal
      we don't want it to fill it completely with same command.
    */
    if(counter == 1)
    {
      Serial.print("Sent by Master: ");
      Serial.println(numToSend);
      Serial.print("Revceived responde: ");
      Serial.println(responseArr[counter]);
    }

    /*
      incrimenting the counter.
    */
    counter++;
  }

  Serial.println("------------------END FLOOR_X_3 Command-----------------");
}

/**
*	@brief		 Initialization function for Arduino UNO.
*	@test		   MISRA-C 2012 Compliant function.
*	@return    void
*/
void setup (void)
{
  /*
    Initializing Serial communication at 115200 bps.
  */
  Serial.begin(115200);
  Serial.println("Setup done!!!");
  
  /*
    Initializing Serial peripheral interface.
  */
  SPI.begin();

  /*
    SPI running at 2MHz.
  */
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  /*
    Pulling high and then LOW chip select pin.
  */
  digitalWrite(SS,HIGH);
  digitalWrite(SS, LOW);
}

void loop(void)
{
  /*
    calling the function to send ADD command and giving delay so we can see it on serial monitor.
  */
  sendAddCommand();
  delay(1000);

  /*
    calling the function to send Subtract command and giving delay so we can see it on serial monitor.
  */
  sendSubCommand();
  delay(1000);

  /*
    calling the function to send Multiply command and giving delay so we can see it on serial monitor.
  */
  sendMulCommand();
  delay(1000);

  /*
    calling the function to send Floor(X/3) command and giving delay so we can see it on serial monitor.
  */
  sendFloorDivCommand();
  delay(1000);
}