/*
 * Fluffy Remote Control v2.0
 * Modified by ShadowTec AT / DrNachtschatten
 * 
 * Serial1 is used for the remote control
 * See external document for protocol details
 */

// defines
#define       REM_TIMEOUT     6

// includes
#include <SoftwareSerial.h>

// general vars
uint16_t      rem_timeout_cnt;      // timeout counter
SoftwareSerial Serial1(8, 7);
// rx (receive data) vars
uint8_t       rem_rx_buf[128];      // buffer
uint8_t       rem_rx_len;           // length
uint8_t       rem_rx_dln;           // announced byte count
uint16_t      rem_rx_crc;           // crc checksum
uint8_t       rem_rx_bat_num;       // battery number 1-5
uint8_t       rem_rx_bat_lvl;       // battery level
uint8_t       rem_rx_sys_stb;       // system status bits
uint8_t       rem_rx_sys_ecb;       // system cmd echo bits
uint8_t       rem_rx_mpc_stb;       // media player control status
uint8_t       rem_rx_mpc_ecb;       // media player control echo
uint16_t      rem_rx_mpc_csp;       // media player song pos [sec]
uint16_t      rem_rx_mpc_cst;       // media player song total [sec]
uint8_t       rem_rx_mpc_sti;       // media player song title index
uint8_t       rem_rx_mpc_stt[8];    // media player song title frame
uint8_t       rem_rx_mpc_stc[260];  // complete buffer for song title
uint8_t       rem_rx_mpc_sli;       // song length indicator

// tx (transmit data) vars
uint8_t       rem_tx_buf[128];
uint8_t       rem_tx_len;
uint8_t       rem_tx_dln;           // announced byte count
uint16_t      rem_tx_crc;           // crc checksum
uint8_t       rem_tx_sys_spa;       // special action index
uint8_t       rem_tx_sys_cmd;       // system command bits
uint8_t       rem_tx_mpc_cmd;       // media player command

void serial_init()
{
  // open up your eyes... and the serial port
  Serial.begin(9600, SERIAL_8N1);
  Serial1.begin(9600);
  pinMode(serial1_command, OUTPUT);
  digitalWrite(serial1_command,LOW);
  delay(50);
  Serial1.print(F("AT+B9600"));
  delay(50);
  Serial1.print(F("AT+C028")); // set to channel
  delay(50);
  digitalWrite(serial1_command,HIGH);
  delay(80);
  while (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  Serial.println("serial started");
  // init timeout counter
  rem_timeout_cnt = 0;
  // send initial packet
  transmit();
  // reset timeout flag
  RemoteTimeout = false;
  // reset title
  resetTitle();
  Serial.println("serial up");
}

void serial_loop()
{
  // call every cycle
  if(receive() == 1)
  {
    // receive succes, send response
    transmit();
    // reset timeout counter
    rem_timeout_cnt = 0;
    // reset timeout flag
    RemoteTimeout = false;
  }
  else
  {
    // receive not (yet) success
    if(rem_timeout_cnt >= REM_TIMEOUT)
    {
      // timeout reached, send again
      transmit();
      // reset counter
      rem_timeout_cnt = 0;
      // set flag
      RemoteTimeout = true;
    }
    else
    {
      // not yet timeout, increment counter
      rem_timeout_cnt++;
    }
  }
}

uint8_t receive()
{
  // returns 1 when good packet existed
  uint8_t ret = 0;
  // single receive buffer
  int16_t rx16t;
  uint16_t tmp16;
  uint8_t rxb, tmp8;
  // check if there's data on serial port (-1 is no data)
  while((rx16t = Serial1.read()) >= 0 && rx16t <= 255)
  {
    // get data byte from receive value
    rxb = (uint8_t)(rx16t);
    // check if data has begun
    if(rem_rx_len == 0)
    {
      // no previous data, check for header byte
      // 0x41 = 'A'
      if(rxb == 0x41)
      {
        // header byte, message starts
        rem_rx_buf[rem_rx_len++] = rxb;
      }
      else
      {
        // not header byte, continue
        continue;
      }
    }
    else if(rem_rx_len == 1)
    {
      // data packet has begun, this is byte count
      rem_rx_dln = rem_rx_buf[rem_rx_len++] = rxb;
    }
    else if(rem_rx_len < 120)
    {
      // rest of the data and no overflow
      rem_rx_buf[rem_rx_len++] = rxb;
      // check if data length is reached
      if(rem_rx_len >= (rem_rx_dln + 2))
      {
      // HD DL XX XX CR CR -> LEN=6, DL=4
      // get received crc, high and low word
      rem_rx_crc = getuint16(rem_rx_buf[rem_rx_len - 2], rem_rx_buf[rem_rx_len - 1]);
      //Serial.print("Check CRC: ");
      //Serial.print(rem_rx_crc, HEX);
      //Serial.print("/");
      // generate CRC from data and compare
      tmp16 = CRC16(rem_rx_buf, 0, rem_rx_len - 3);
      //Serial.println(tmp16, HEX);
      if(rem_rx_crc == tmp16)
      {
        //Serial.println("HECK-2");
        // crc match, read data to vars
        // battery index
        rem_rx_bat_num = rem_rx_buf[2];
        // battery value
        tmp8 = rem_rx_bat_lvl = rem_rx_buf[3];
        switch(rem_rx_bat_num)
        {
          case 1:   bat_1 = tmp8;   break;
          case 2:   bat_2 = tmp8;   break;
          case 3:   bat_3 = tmp8;   break;
          case 4:   bat_4 = tmp8;   break;
          case 5:   bat_5 = tmp8;   break;
        }
        // system state bits
        tmp8 = rem_rx_sys_stb = rem_rx_buf[4];
        // auto kill
        //var = getbit8(tmp8, 0);
        // manual kill
        //var = getbit8(tmp8, 1);
        // boost
        //var = getbit8(tmp8, 2);
        // Command Echo Bits
        tmp8 = rem_rx_sys_ecb = rem_rx_buf[5];
        // boost
        //var = getbit8(tmp8, 0);
        // manual kill
        //var = getbit8(tmp8, 1);
        // kill reset
        //var = getbit8(tmp8, 2);
        // action select
        //var = getbit8(tmp8, 3);
        // battery next index
        //var = getbit8(tmp8, 4);
        // media player next text packet
        //var = getbit8(tmp8, 5);
        // media player length (0=current song pos)
        //var = getbit8(tmp8, 6);
        // Media Player state bits
        tmp8 = rem_rx_mpc_stb = rem_rx_buf[6];
        // stop
        //var = getbit8(tmp8, 0);
        // play
        //var = getbit8(tmp8, 1);
        // pause
        //var = getbit8(tmp8, 2);
        // song length indicator (0=pos, 1=len)
        rem_rx_mpc_sli = getbit8(tmp8, 3);
        // card
        //var = getbit8(tmp8, 5);
        // usb
        //var = getbit8(tmp8, 6);
        // bluetooth
        //var = getbit8(tmp8, 7);
        // media player command echo bits
        tmp8 = rem_rx_mpc_ecb = rem_rx_buf[7];
        // stop
        //var = getbit8(tmp8, 0);
        // play
        //var = getbit8(tmp8, 1);
        // pause
        //var = getbit8(tmp8, 2);
        // prev
        //var = getbit8(tmp8, 3);
        // next
        //var = getbit8(tmp8, 4);
        // card
        //var = getbit8(tmp8, 5);
        // usb
        //var = getbit8(tmp8, 6);
        // bluetooth
        //var = getbit8(tmp8, 7);
        // media player song time indicator
        tmp16 = getuint16(rem_rx_buf[8], rem_rx_buf[9]);
        // indicator 1=totallength, indicator 0=position
        if(rem_rx_mpc_sli)  rem_rx_mpc_cst = tmp16;
        else                rem_rx_mpc_csp = tmp16;
        // current song packet index
        rem_rx_mpc_sti = rem_rx_buf[10];
        // current song packet
        for(uint8_t i = 0; i < 8; i++) rem_rx_mpc_stt[i] = rem_rx_buf[11 + i];
        nextTitleFrame(0);
        // set return value to success
        ret = 1;
      }
      // done with processing or not, reset
      rem_rx_len = 0;
      // start over next cycle
      break;
      }
    }
  }
  // return result
  return ret;
}

void transmit()
{
  // temp vars
  uint8_t tmp8;
  uint16_t tmp16;
  // build the message, start with header 0x61 'a'
  rem_tx_buf[0] = 0x61;
  // number of bytes to follow
  rem_tx_buf[1] = 7;
  // system command analog throttle
  rem_tx_buf[2] = (uint8_t)trottle;
  // system command analog steering
  rem_tx_buf[3] = (uint8_t)steering;
  // system command special action number
  tmp8 = 0;
  if(fxbank1) tmp8 = setbit8(tmp8, 0);
  if(fxbank2) tmp8 = setbit8(tmp8, 1);
  if(fxbank3) tmp8 = setbit8(tmp8, 2);
  if(fxbank4) tmp8 = setbit8(tmp8, 3);
  if(Action1) tmp8 = setbit8(tmp8, 4);
  if(Action2) tmp8 = setbit8(tmp8, 5);
  if(Action3) tmp8 = setbit8(tmp8, 6);
  if(Action4) tmp8 = setbit8(tmp8, 7);
  rem_tx_buf[4] = tmp8; // special action nr goes here
  // system command bits go here
  tmp8 = 0;
  // boosting
  if(boosting) tmp8 = setbit8(tmp8, 0);
  // manual kill
  if(0/* var */) tmp8 = setbit8(tmp8, 1);
  // kill reset
  if(0/* var */) tmp8 = setbit8(tmp8, 2);
  // special action trigger
  if(0/* var */) tmp8 = setbit8(tmp8, 3);
  // next battery index
  if(0/* var */) tmp8 = setbit8(tmp8, 4);
  // media player next text packet
  if(0/* var */) tmp8 = setbit8(tmp8, 5);
  // media player song length (0 = currentpos)
  if(0/* var */) tmp8 = setbit8(tmp8, 6);
  rem_tx_buf[5] = tmp8;
  // media player command
  tmp8 = 0;
  // stop
  if(0/* var */) tmp8 = setbit8(tmp8, 0);
  // play
  if(0/* var */) tmp8 = setbit8(tmp8, 1);
  // pause
  if(0/* var */) tmp8 = setbit8(tmp8, 2);
  // prev
  if(0/* var */) tmp8 = setbit8(tmp8, 3);
  // next
  if(0/* var */) tmp8 = setbit8(tmp8, 4);
  // source card
  if(0/* var */) tmp8 = setbit8(tmp8, 5);
  // source usb
  if(0/* var */) tmp8 = setbit8(tmp8, 6);
  // source bt
  if(0/* var */) tmp8 = setbit8(tmp8, 7);
  rem_tx_buf[6] = tmp8;
  // create crc
  tmp16 = CRC16(rem_tx_buf, 0, 6);
  rem_tx_buf[7] = getuint8hw(tmp16);
  rem_tx_buf[8] = getuint8lw(tmp16);
  // send data to serial (array, amount of bytes)
  Serial1.write(rem_tx_buf, 9);
}

// takes the received 8 bytes and adds to entire title string
void nextTitleFrame(uint8_t reset)
{
  // reset
  if(rem_rx_mpc_sti == 0 || reset) resetTitle();
  // put chars into place if index is legal
  if(rem_rx_mpc_sti < 32)
  {
    // get start index
    uint16_t sti = ((uint16_t)rem_rx_mpc_sti) * ((uint16_t)8);
    // move the bytes from buffer to string cache
    for(uint16_t i = 0; i < 8; i++)
    {
      rem_rx_mpc_stc[i + sti] = rem_rx_mpc_stt[i];
    }
    // set global string to cache (NOT CONFIRMED TO WORK)
    mp3file = rem_rx_mpc_stc;
  }
}

// resets the title buffer
void resetTitle()
{
  for(uint16_t i = 0; i < sizeof(rem_rx_mpc_stc); i++)
  {
    rem_rx_mpc_stc[i] = 0x00;
  }
}

// get uint16 from uint8 high and low word
uint16_t getuint16(uint8_t hw, uint8_t lw)
{
  return (uint16_t)(((uint16_t)(hw)) << 8) + ((uint16_t)(lw));
}

// get uint8 high word from uint16
uint8_t getuint8hw(uint16_t val)
{
  return (uint8_t)(val >> 8);
}

// get uint8 low word from uint16
uint8_t getuint8lw(uint16_t val)
{
  return (uint8_t)(val);
}

// return 1 if bit at pos is act 1 and prv 0 (rise edge)
uint8_t getbit8re(uint8_t valact, uint8_t valprv, uint8_t pos)
{
  return (getbit8(valact, pos) && !getbit8(valprv, pos));
}

// get bit at pos in val
uint8_t getbit8(uint8_t val, uint8_t pos)
{
  return (((val) & (1 << pos)) != 0);
}

// set bit at pos in val
uint8_t setbit8(uint8_t val, uint8_t pos)
{
  return (val |= (1 << pos));
}

// reset bit at pos in val
uint8_t rstbit8(uint8_t val, uint8_t pos)
{
  return (val &= ~(1 << pos));
}

// somewhat modified CRC for C++
// give byte array, first index and last index
uint16_t CRC16(uint8_t *buf, uint8_t first, uint8_t last)
{
  // initial value. must be the same on master and client
  uint16_t crc = 0xFFFF;
  uint16_t gen = 0xA001;
  // go through all relevant bytes
  for (int i = first; i <= last; i++)
  {
    // XOR byte into least sig. byte of crc
    crc ^= (uint16_t)(buf[i]);
    // loop over each bit
    for (uint8_t j = 8; j != 0; j--)
    {
      if ((crc & 0x0001) != 0)
      {
        // LSB is set, shift right
        crc >>= 1;
        // and XOR the generator
        crc ^= gen;
      }
      else
      {
        // LSB is not set, shift right
        crc >>= 1;
      }
    }
  }
  // return result
  return crc;
}
