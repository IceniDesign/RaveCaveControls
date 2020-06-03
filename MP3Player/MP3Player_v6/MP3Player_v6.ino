//code rearranged by Javier Muñoz 10/11/2016 ask me at javimusama@hotmail.com
//additional tweaks (lots of them) by Iceni Design.

#include <SoftwareSerial.h>

#define ARDUINO_TX 14//should connect to TX of the Serial MP3 Player module
#define ARDUINO_RX 15//connect to RX of the module
SoftwareSerial mySerial(ARDUINO_TX, ARDUINO_RX);//init the serial protocol, tell to myserial wich pins are TX and RX

////////////////////////////////////////////////////////////////////////////////////
//all the commands needed in the datasheet(http://geekmatic.in.ua/pdf/Catalex_MP3_board.pdf)
static int8_t Send_buf[8] = {0} ;//The MP3 player undestands orders in a 8 int string
//0X7E FF 06 command 00 00 00 EF;(if command =01 next song order)
#define NEXT_SONG 0X01
#define PREV_SONG 0X02

#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song)

#define VOLUME_UP_ONE 0X04
#define VOLUME_DOWN_ONE 0X05
#define CMD_SET_VOLUME 0X06//DATA IS REQUIRED (number of volume from 0 up to 30(0x1E))
#define SET_DAC 0X17
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song)

#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED

#define SLEEP_MODE_START 0X0A
#define SLEEP_MODE_WAKEUP 0X0B

#define CMD_RESET 0X0C//CHIP RESET
#define CMD_PLAY 0X0D //RESUME PLAYBACK
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED

#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3

#define STOP_PLAY 0X16

#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care)

#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close

#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output
////////////////////////////////////////////////////////////////////////////////////

//I have two columns (A, B) of 6 rows (Black, Red, Yellow, Blue, Green, White) of buttons
//Cycle variables are needed for buttons that play multiple samples sequentially

//~~~~ COLUMN A ~~~~
#define buttonPin_BLACK_A   30
int buttonState_BLACK_A = 0;      // variable for reading the pushbutton status
int Cycle_BLACK_A = 0;            // variable current Track Number
int Cycle_BLACK_A_NEXT = 1;       // variable next Track Number
#define buttonPin_RED_A   32
int buttonState_RED_A = 0;        // variable for reading the pushbutton status
#define buttonPin_YELLOW_A   34
int buttonState_YELLOW_A = 0;     // variable for reading the pushbutton status
#define buttonPin_BLUE_A   36
int buttonState_BLUE_A = 0;       // variable for reading the pushbutton status
#define buttonPin_GREEN_A   38
int buttonState_GREEN_A = 0;      // variable for reading the pushbutton status
#define buttonPin_WHITE_A   40
int buttonState_WHITE_A = 0;      // variable for reading the pushbutton status

//~~~~ COLUMN B ~~~~
#define buttonPin_BLACK_B   31
int buttonState_BLACK_B = 0;      // variable for reading the pushbutton status
int Cycle_BLACK_B = 1;            // variable current Track Number
int Cycle_BLACK_B_NEXT = 2;       // variable next Track Number
#define buttonPin_RED_B   33
int buttonState_RED_B = 0;        // variable for reading the pushbutton status
#define buttonPin_YELLOW_B   35
int buttonState_YELLOW_B = 0;     // variable for reading the pushbutton status
int Cycle_YELLOW_B = 1;           // variable current Track Number
int Cycle_YELLOW_B_NEXT = 2;       // variable next Track Number
#define buttonPin_BLUE_B   37
int buttonState_BLUE_B = 0;       // variable for reading the pushbutton status
#define buttonPin_GREEN_B   39
int buttonState_GREEN_B = 0;      // variable for reading the pushbutton status
#define buttonPin_WHITE_B   41
int buttonState_WHITE_B = 0;      // variable for reading the pushbutton status

void setup()
{
  // initialize the pushbutton pins as an input:
  pinMode(buttonPin_BLACK_A, INPUT);
  pinMode(buttonPin_RED_A, INPUT);
  pinMode(buttonPin_YELLOW_A, INPUT);
  pinMode(buttonPin_BLUE_A, INPUT);
  pinMode(buttonPin_GREEN_A, INPUT);
  pinMode(buttonPin_WHITE_A, INPUT);

  pinMode(buttonPin_BLACK_B, INPUT);
  pinMode(buttonPin_RED_B, INPUT);
  pinMode(buttonPin_YELLOW_B, INPUT);
  pinMode(buttonPin_BLUE_B, INPUT);
  pinMode(buttonPin_GREEN_B, INPUT);
  pinMode(buttonPin_WHITE_B, INPUT);

  Serial.begin(9600);//Start our Serial coms for serial monitor in our pc
  mySerial.begin(9600);//Start our Serial coms for THE MP3
  delay(500);//Wait chip initialization is complete
  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card
  delay(200);//wait for 200ms
  sendCommand(CMD_SET_VOLUME, 0X08); //Set volume in hex 0-30

}
void loop()
{

  buttonState_BLACK_A = digitalRead(buttonPin_BLACK_A);
  buttonState_RED_A = digitalRead(buttonPin_RED_A);
  buttonState_YELLOW_A = digitalRead(buttonPin_YELLOW_A);
  buttonState_BLUE_A = digitalRead(buttonPin_BLUE_A);
  buttonState_GREEN_A = digitalRead(buttonPin_GREEN_A);
  buttonState_WHITE_A = digitalRead(buttonPin_WHITE_A);

  buttonState_BLACK_B = digitalRead(buttonPin_BLACK_B);
  buttonState_RED_B = digitalRead(buttonPin_RED_B);
  buttonState_YELLOW_B = digitalRead(buttonPin_YELLOW_B);
  buttonState_BLUE_B = digitalRead(buttonPin_BLUE_B);
  buttonState_GREEN_B = digitalRead(buttonPin_GREEN_B);
  buttonState_WHITE_B = digitalRead(buttonPin_WHITE_B);


  if (buttonState_BLACK_A == HIGH) {
    
    Cycle_BLACK_A = Cycle_BLACK_A_NEXT;
  
    if (Cycle_BLACK_A == 1) { //if its 1 then play the first track and make the next one track 2
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0101);
      Cycle_BLACK_A_NEXT = 2;
      delay(1000);
    }
    else if (Cycle_BLACK_A == 2) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0102);
      Cycle_BLACK_A_NEXT = 3;
      delay(1000);
    }
    else if (Cycle_BLACK_A == 3) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0103);
      Cycle_BLACK_A_NEXT = 4;
      delay(1000);
    }
    else {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0101); //something has gone wrong so play the first track and make the next one track 2
      Cycle_BLACK_A_NEXT = 1;
      delay(1000);
    }

  }
  else if (buttonState_BLACK_B == HIGH) {
    
    Cycle_BLACK_B = Cycle_BLACK_B_NEXT;

    if (Cycle_BLACK_B == 1) { //if its 1 then play the first track and make the next one track 2
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0201);
      Cycle_BLACK_B_NEXT = 2;
      delay(1000);
    }
    else if (Cycle_BLACK_B == 2) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0202);
      Cycle_BLACK_B_NEXT = 3;
      delay(1000);
    }
    else if (Cycle_BLACK_B == 3) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0203);
      Cycle_BLACK_B_NEXT = 4;
      delay(1000);
    }
    else {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0201); //something has gone wrong so play the first track and make the next one track 2
      Cycle_BLACK_B_NEXT = 2;
      delay(1000);
    }
  }
  else if (buttonState_RED_A == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0301);//play the song in folder 01, named 001xxxxxx.xxx
    delay(1000);
  }
  else if (buttonState_RED_B == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0401);//play the song in folder 01, named 001xxxxxx.xxx
    delay(1000);
  }
  else if (buttonState_YELLOW_A == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0501);//play the song in folder 01, named 001xxxxxx.xxx
    delay(1000);
  }
  else if (buttonState_YELLOW_B == HIGH) {
    
    Cycle_YELLOW_B = Cycle_YELLOW_B_NEXT;
    delay(1000);

    if (Cycle_YELLOW_B == 1) { //if its 1 then play the first track and make the next one track 2
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0601);
      Cycle_YELLOW_B_NEXT = 2;
      delay(1000);
    }
    else if (Cycle_YELLOW_B == 2) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0602);
      Cycle_YELLOW_B_NEXT = 3;
      delay(1000);
    }
    else if (Cycle_YELLOW_B == 3) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0603);
      Cycle_YELLOW_B_NEXT = 4;
      delay(1000);
    }
    else if (Cycle_YELLOW_B == 4) {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0604);
      Cycle_YELLOW_B_NEXT = 1;
      delay(1000);
    }
    else {
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0601); //something has gone wrong so play the first track and make the next one track 2
      Cycle_YELLOW_B_NEXT = 2;
      delay(1000);
    }

  }
  else if (buttonState_BLUE_A == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0701);
    delay(1000);
  }
  else if (buttonState_BLUE_B == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0801);
    delay(1000);
  }
  else if (buttonState_GREEN_A == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0901);
    delay(1000);
  }
  else if (buttonState_GREEN_B == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0A01);
    delay(1000);
  }
  else if (buttonState_WHITE_A == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0B01);
    delay(10000);
  }
  else if (buttonState_WHITE_B == HIGH) {
    sendCommand(CMD_PLAY_WITHFOLDER, 0X0C01);
    delay(1000);
  }
}

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x01;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for (uint8_t i = 0; i < 8; i++) //
  {
    mySerial.write(Send_buf[i]) ;//send bit to serial mp3
    Serial.print(Send_buf[i], HEX); //send bit to serial monitor in pc
  }
  Serial.println();
}
