/*
 * Fluffy Remote Control v2.0
 * Modified by ShadowTec AT / DrNachtschatten
 * 
 * Serial1 is used for the remote control
 * See external document for protocol details
 */

// defines
#define       REM_TIMEOUT     3000

// includes

// general vars
uint16_t      rem_timeout_cnt;      // timeout counter

// rx (receive data) vars
uint8_t       rem_rx_buf[128];      // buffer
uint8_t       rem_rx_len;           // length
uint8_t       rem_rx_dln;           // announced byte count
uint16_t      rem_rx_crc;           // crc checksum
uint8_t       rem_rx_sys_spa;       // special action index
uint8_t       rem_rx_sys_cmd;       // system command bits
uint8_t       rem_rx_mpc_cmd;       // media player command

// tx (transmit data) vars
uint8_t       rem_tx_buf[128];
uint8_t       rem_tx_len;
uint8_t       rem_tx_dln;           // announced byte count
uint16_t      rem_tx_crc;           // crc checksum
uint8_t       rem_tx_bat_num;       // battery number 1-5
uint8_t       rem_tx_bat_lvl;       // battery level
uint8_t       rem_tx_sys_stb;       // system status bits
uint8_t       rem_tx_sys_ecb;       // system cmd echo bits
uint8_t       rem_tx_mpc_stb;       // media player control status
uint8_t       rem_tx_mpc_ecb;       // media player control echo
uint16_t      rem_tx_mpc_csp;       // media player song pos [sec]
uint16_t      rem_tx_mpc_cst;       // media player song total [sec]
uint8_t       rem_tx_mpc_sti;       // media player song title index
uint8_t       rem_tx_mpc_stt[8];    // media player song title frame
uint8_t       rem_tx_mpc_sli;       // song length indicator

void Remote_init()
{
  // 9600 baud, 8 data, 1 stop, no parity
	Serial1.begin(9600, SERIAL_8N1);
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
  // reset timeout flag
  RemoteTimeout = false;
}

void Remote_loop()
{
  // call every cycle
  if(receive() == 1)
  {
    //Serial.println("RX OK - TX");
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
      // timeout reached, kill switch
      killed = true;
      // set remote timeout flag
      RemoteTimeout = true;
    }
    else
    {
      // not yet timeout, increment counter
      rem_timeout_cnt++;
    }
  }
}

// does all the receiving stuff
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
      // 0x61 = 'a'
      if(rxb == 0x61)
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
        tmp16 = CRC16(rem_rx_buf, 0, rem_rx_len - 3);
        // generate CRC from data and compare
        if(rem_rx_crc == tmp16)
        {
          // crc match, read data to vars
          // movement forward / throttle
          Movement_forward = rem_rx_buf[2];
          // steering
          Movement_steering = rem_rx_buf[3];
          // special action index (1-255)
          tmp8 = rem_rx_sys_spa = rem_rx_buf[4];
          fxbank1 = getbit8(tmp8, 0);
          fxbank2 = getbit8(tmp8, 1);
          fxbank3 = getbit8(tmp8, 2);
          fxbank4 = getbit8(tmp8, 3);
          fxbtn1 = getbit8(tmp8, 4);
          fxbtn2 = getbit8(tmp8, 5);
          fxbtn3 = getbit8(tmp8, 6);
          fxbtn4 = getbit8(tmp8, 7);
          // system command byte
          tmp8 = rem_rx_sys_cmd = rem_rx_buf[5];
          // boost
          boosting = getbit8(tmp8, 0);
          // manual kill
          killed_man = getbit8(tmp8, 1);
          // kill reset
          if(getbit8(tmp8, 2)) { killed = killed_man = false; }
          // action (special action?)
          if(getbit8(tmp8, 3))
          {
            // select special action by index
            switch(rem_rx_sys_spa)
            {
              case 1: /* do special action 1 */ break;
              case 2: /* do special action 2 */ break;
            }
          }
          // next battery number (1-5)
          if(getbit8(tmp8, 4))
          {
            if(++rem_tx_bat_num > 5) rem_tx_bat_num = 0;
            else if(rem_tx_bat_num < 1) rem_tx_bat_num = 1;
          }
          // next string bit of media player title
          if(getbit8(tmp8, 5)) nextTitleFrame(0);
          // display song pos (0) or length (1)
          rem_tx_mpc_sli = getbit8(tmp8, 6);
          // media player command byte
          tmp8 = rem_rx_buf[6];
          // stop
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 0)) { /* stop media player */ }
          // play
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 1)) { /* start media player */ }
          // pause
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 2)) { /* start media player */ }
          // previous title
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 3)) { /* start media player */ }
          // next title
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 4)) { /* start media player */ }
          // source card
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 5)) { /* start media player */ }
          // source USB
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 6)) { /* start media player */ }
          // source BT
          if(getbit8re(tmp8, rem_rx_mpc_cmd, 7)) { /* start media player */ }
          // save for later and edge detection
          rem_rx_mpc_cmd = tmp8;
          // set return value to success
          ret = 1;
        }
        // done with processing or not, reset
        rem_rx_len = 0;
        // start over next cycle
        break;
      }
    }
    else
    {
      // avoid overflow of process buffer, reset
      // discard current data and await next packet
      rem_rx_len = 0;
      // start over next cycle
      break;
    }
  }
  // return result
  return ret;
}

// sends data
void transmit()
{
  // temp vars
  uint8_t tmp8;
  uint16_t tmp16;
  // build the message, start with header 0x41 'A'
  rem_tx_buf[0] = 0x41;
  // number of bytes to follow
  rem_tx_buf[1] = 19;
  // battery index
  rem_tx_buf[2] = rem_tx_bat_num;
  // battery level
  switch(rem_tx_bat_num)
  {
    case 1:   tmp8 = Battery_1;   break;
    case 2:   tmp8 = Battery_2;   break;
    case 3:   tmp8 = Battery_3;   break;
    case 4:   tmp8 = Battery_4;   break;
    case 5:   tmp8 = Battery_5;   break;
    default:  tmp8 = 0;           break;
  }
  rem_tx_buf[3] = tmp8;
  // system state bits
  tmp8 = 0;
  if(killed)      tmp8 = setbit8(tmp8, 0);
  if(killed_man)  tmp8 = setbit8(tmp8, 1);
  if(boosting)    tmp8 = setbit8(tmp8, 2);
  rem_tx_buf[4] = tmp8;
  // system command echo
  rem_tx_buf[5] = rem_rx_sys_cmd;
  // media player state
  tmp8 = 0;
  if(0/* audio_stop */)    tmp8 = setbit8(tmp8, 0);
  if(0/* audio_play */)    tmp8 = setbit8(tmp8, 1);
  if(0/* audio_paus */)    tmp8 = setbit8(tmp8, 2);
  if(0/* audio_card */)    tmp8 = setbit8(tmp8, 5);
  if(0/* audio_usb */)     tmp8 = setbit8(tmp8, 6);
  if(0/* audio_bt */)      tmp8 = setbit8(tmp8, 7);
  rem_tx_buf[6] = tmp8;
  // media player command echo
  rem_tx_buf[7] = rem_rx_mpc_cmd;
  // media player current song position
  if(rem_tx_mpc_sli) tmp16 = song_length;
  else tmp16 = song_place;
  rem_tx_buf[8] = getuint8hw(tmp16);
  rem_tx_buf[9] = getuint8lw(tmp16);
  // song title packet index
  rem_tx_buf[10] = rem_tx_mpc_sti;
  // song title packet (prepared in receive)
  for(uint8_t i = 0; i < 8; i++) rem_tx_buf[11 + i] = rem_tx_mpc_stt[i];
  // crc
  tmp16 = CRC16(rem_tx_buf, 0, 18);
  rem_tx_buf[19] = getuint8hw(tmp16);
  rem_tx_buf[20] = getuint8lw(tmp16);
  // send data to serial (array, amount of bytes)
  Serial1.write(rem_tx_buf, 21);
  /*
  // debug
  Serial.print("TX: ");
  for(uint8_t i = 0; i < 21; i++)
  {
    Serial.print(rem_tx_buf[i], HEX);
    Serial.print("-");
  }
  Serial.println("");
  */
}

// gets next 8 bytes of song title string or resets to first frame
void nextTitleFrame(uint8_t reset)
{
  // get song length
  uint16_t sl = Audio_current_song.length();
  // get amount of frames (8 byte each)
  uint16_t fc = ((sl + 7) / 8);
  // reset or count to next frame
  if(reset)                       rem_tx_mpc_sti = 0;
  else if(++rem_tx_mpc_sti > fc)  rem_tx_mpc_sti = 0;
  // get start pos in string
  uint16_t sti = ((uint16_t)rem_tx_mpc_sti) * ((uint16_t)8);
  // put 8 bytes of string into the transmit array
  for(uint16_t i = 0; i < 8; i++)
  {
    rem_tx_mpc_stt[i] = Audio_current_song.charAt(i + sti);
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
  return (uint8_t)(val & 0xFF);
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
