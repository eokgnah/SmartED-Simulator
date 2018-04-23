//
// CAN Sender for SmartED-Display development
//

#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);     // Set CS to pin 10

// SOC     0x518 01 4E 00 00 F8 7F C8 B4
// realSOC 0x2D5 00 00 4F 14 03 40 00 00
// odo     0x412 26 04 00 5B D3 8D 20 10
// reichw. 0x318 58 00 00 07 FF 63 00 50
// ECO     0x3F2 61 84 73 73 00 00 00 00 
// HV V    0x448 0F 00 00 0E 00 00 0E C9
// HV A    0x508 08 00 1F F3 7E FC 02 3F 
// Temp.   0x408 FF 00 7A 00 7A 02 46 02 
// Speed   0x200 00 78 01 7D 01 7D 01 44 

void setup()
{
  Serial.begin(115200);

  Serial.println("CAN-Simulator for SMART-ED");
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

long TIMER = millis();

byte   SOC[8] = {0x01, 0x4E, 0x00, 0x00, 0xF8, 0x7F, 0xC8, 0xB0};
byte  rSOC[8] = {0x00, 0x00, 0x4F, 0x14, 0x03, 0x40, 0x00, 0x00};
byte   ODO[8] = {0x26, 0x04, 0x00, 0xA8, 0xCA, 0x8D, 0x20, 0x10};
byte    rw[8] = {0x58, 0x00, 0x00, 0x07, 0xFF, 0x63, 0x00, 0x50};
byte   ECO[8] = {0x20, 0x30, 0x40, 0x50, 0x00, 0x00, 0x00, 0x00};
byte   hvV[8] = {0x0F, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x0E, 0xA0};
byte   hvA[8] = {0x08, 0x00, 0x1F, 0xF9, 0x7E, 0xFC, 0x02, 0x3F};
byte   Tmp[8] = {0xFF, 0x00, 0x7A, 0x00, 0x7A, 0x02, 0x46, 0x02};
byte Speed[8] = {0xFF, 0x00, 0x7A, 0x00, 0x7A, 0x02, 0x46, 0x02};

void loop()
{
  CAN0.sendMsgBuf(0x200, 0, 8,Speed ); delay(10);
  CAN0.sendMsgBuf(0x518, 0, 8,  SOC ); delay(10);
  CAN0.sendMsgBuf(0x2D5, 0, 8, rSOC ); delay(10);
  CAN0.sendMsgBuf(0x412, 0, 8,  ODO ); delay(10);
  CAN0.sendMsgBuf(0x318, 0, 8,   rw ); delay(10);
  CAN0.sendMsgBuf(0x3F2, 0, 8,  ECO ); delay(10);
  CAN0.sendMsgBuf(0x408, 0, 8,  Tmp ); delay(10);
  CAN0.sendMsgBuf(0x448, 0, 8,  hvV ); delay(10);
  CAN0.sendMsgBuf(0x508, 0, 8,  hvA ); delay(10);
  delay(100);
  
if (millis()-TIMER > 4000)  {
  SOC[7]={0xB1}; rSOC[5]={0x50}; ODO[4]={0xCB}; rw[7]={0x51}; rw[5]={0x42};
  ECO[0]={0x21}; ECO[1]={0x31}; ECO[2]={0x41}; ECO[3]={0x51}; 
  hvA[2]={0x10}; hvA[3]={0x00}; hvV[0]={0x0F};  hvV[7]={0xB0};
  Tmp[4]={0x7B}; Speed[3]={0x75};
  }

if (millis()-TIMER > 8000)  {
  SOC[7]={0xB2}; rSOC[5]={0x60}; ODO[4]={0xCC}; rw[7]={0x52}; rw[5]={0x21};
  ECO[0]={0x22}; ECO[1]={0x32}; ECO[2]={0x42}; ECO[3]={0x52}; 
  hvA[2]={0x1F}; hvA[3]={0x55}; hvV[0]={0x0F}; hvV[7]={0xC0};
  Tmp[4]={0x7C}; Speed[3]={0x77};
  }

if (millis()-TIMER > 12000) {
  SOC[7]={0xB3}; rSOC[5]={0x70}; ODO[4]={0xCD}; rw[7]={0x53}; rw[5]={0x42};
  ECO[0]={0x23}; ECO[1]={0x33}; ECO[2]={0x43}; ECO[3]={0x53}; 
  hvA[2]={0x21}; hvA[3]={0x55}; hvV[0]={0x0F}; hvV[7]={0xD0};
  Tmp[4]={0x7D}; Speed[3]={0x79};
  }

if (millis()-TIMER > 16000) {
  SOC[7]={0xB4}; rSOC[5]={0x80}; ODO[4]={0xCF}; rw[7]={0x54}; rw[5]={0x00};
  ECO[0]={0x24}; ECO[1]={0x34}; ECO[2]={0x44}; ECO[3]={0x54}; 
  hvA[2]={0x21}; hvA[3]={0xAA}; hvV[0]={0x00}; hvV[7]={0xE0};
  Tmp[4]={0x7E}; Speed[3]={0x7B};
  }

if (millis()-TIMER > 20000) {
  SOC[7]={0xB0}; rSOC[5]={0x40}; ODO[4]={0xCA}; rw[7]={0x50};  rw[5]={0x63};
  ECO[0]={0x20}; ECO[1]={0x30}; ECO[2]={0x40}; ECO[3]={0x50}; 
  hvA[2]={0x1F}; hvA[3]={0xF9}; hvV[0]={0x0F}; hvV[7]={0xA0};
  Tmp[4]={0x7A}; Speed[3]={0x7D};
  TIMER=millis();
  }
  
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
