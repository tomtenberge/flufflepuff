static const unsigned char PROGMEM logo_bmp[] =
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x03, 0xf2, 0x00, 0x00, 
0x0f, 0xff, 0x28, 0x00, 0x0f, 0xea, 0xff, 0x00, 0x3f, 0xfb, 0xff, 0xe0, 0x17, 0xfb, 0xff, 0xc0, 
0x10, 0xad, 0xff, 0xf0, 0x2b, 0x5f, 0xff, 0xf0, 0x1b, 0x1f, 0xff, 0xf0, 0x0a, 0x1f, 0xff, 0xf8, 
0x1f, 0x3f, 0xff, 0xf8, 0x2c, 0xff, 0xff, 0xf8, 0x3e, 0xff, 0xff, 0xfc, 0x33, 0x7f, 0xff, 0xfa, 
0x1c, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x37, 0x7f, 0xff, 0xfc, 
0x37, 0x7f, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xfc, 0x1e, 0xff, 0xff, 0xfc, 0x1d, 0xff, 0xff, 0xf8, 
0x07, 0xff, 0xff, 0xf8, 0x07, 0xff, 0xff, 0xf8, 0x03, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xc0, 
0x00, 0x2d, 0x75, 0x40, 0x00, 0x32, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#define LOGO_HEIGHT   32
#define LOGO_WIDTH    32
static const unsigned char PROGMEM SFX_btn[] =//20x8
{
	B11111111, B11111111, B11111111, B11111111, B11111111, B11001000, B10110100, B00011011, B10111011, B01000001, B11011001, B11001100, B00011110, B10111011, B01000001, B10011011, B10110100, B00011111, B11111111, B11111111
};
static const unsigned char PROGMEM SFX_one[] =//5x5 offset 14x2
{
	B11011100, B11110111, B10110000, B00000000
};
static const unsigned char PROGMEM SFX_two[] =//5x5 offset 14x2
{
	B11001101, B10111011, B10111000, B00000000
};
static const unsigned char PROGMEM SFX_tree[] =//5x5 offset 14x2
{
	B10001111, B10110011, B11101000, B10000000
};
void display_init()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    display_ok = false;
  }
  else
  {
    display_ok = true;
    display.clearDisplay();
    display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
    delay(1000);
  }
}
void display_loop()
{
  if (display_ok)
  {
    //drawing display
    display.clearDisplay();
    //Batt 1
    display.drawLine(0,0,0,4,1);
    display.drawLine(1,0,7,0,1);
    display.drawLine(1,4,7,4,1);
    display.drawLine(8,1,8,3,1);
    //Batt 2
    display.drawLine(10,0,10,4,1);
    display.drawLine(11,0,17,0,1);
    display.drawLine(11,4,17,4,1);
    display.drawLine(18,1,18,3,1);
    //Batt 3
    display.drawLine(20,0,20,4,1);
    display.drawLine(21,0,27,0,1);
    display.drawLine(21,4,27,4,1);
    display.drawLine(28,1,28,3,1);
    //Batt 4
    display.drawLine(30,0,30,4,1);
    display.drawLine(31,0,37,0,1);
    display.drawLine(31,4,37,4,1);
    display.drawLine(38,1,38,3,1);
    //Batt 5
    display.drawLine(40,0,40,4,1);
    display.drawLine(41,0,47,0,1);
    display.drawLine(41,4,47,4,1);
    display.drawLine(48,1,48,3,1);
    //Batt 6
    display.drawLine(50,0,50,4,1);
    display.drawLine(51,0,57,0,1);
    display.drawLine(51,4,57,4,1);
    display.drawLine(58,1,58,3,1);
    //trottle display
    //T
    display.drawLine(0,8,4,8,1);
    display.drawLine(2,9,2,12,1);
    //R
    display.drawLine(6,8,6,12,1);
    display.drawLine(7,8,8,8,1);
    display.drawLine(7,10,8,10,1);
    display.drawLine(8,11,9,12,1);
    display.drawPixel(9,9,1);
    //doubledot
    display.drawPixel(11,9,1);
    display.drawPixel(11,11,1);
    //bar
    display.drawRect(13,6,47,8,1);
    //steering display
    //L
    display.drawLine(0,17,0,21,1);
    display.drawLine(0,21,2,21,1);
    //\\
    display.drawLine(2,17,4,21,1);
    //R
    display.drawLine(6,17,6,21,1);
    display.drawLine(7,17,8,17,1);
    display.drawLine(7,19,8,19,1);
    display.drawLine(8,20,9,21,1);
    display.drawPixel(9,18,1);
    // doubledot
    display.drawPixel(11,9,1);
    display.drawPixel(11,11,1);
    //bar
    display.drawRect(13,15,47,8,1);
    //middledots
    display.drawPixel(35,14,1); 
    display.drawPixel(35,23,1);
    display.drawPixel(35,5,1); 
    //volume
    //V
    display.drawLine(62,8,64,12,1);
    display.drawLine(66,8,64,12,1);
    //O
    display.drawLine(68,9,68,11,1);
    display.drawLine(71,9,71,11,1);
    display.drawLine(69,8,70,8,1);
    display.drawLine(69,12,70,12,1);
    //L
    display.drawLine(73,8,73,12,1);
    display.drawLine(73,9,75,12,1);
    // doubledot
    display.drawPixel(77,9,1);
    display.drawPixel(77,11,1);
    //bar
    display.drawRect(79,6,48,8,1);
    //enter values
    //bat_1
    display.fillRect(1,1,bat_1,3,1);

    //trottle 54 max
    display.fillRect(14,7,map(trottle,0,255,0,45),6,1);
    //steering
    display.fillRect(14,17,map(steering,0,255,0,45),6,1);
    //volume
    display.fillRect(80,7,map(Audio_volume,0,30,0,45),6,1);
    if (controller_firstboot)
    {
      display.drawBitmap(
      (display.width()  - LOGO_WIDTH ) / 2,
      (display.height() - LOGO_HEIGHT) / 2,
      logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    }
	switch(fxbank)
	{
		case 0:
		break;
		case 1:
		  display.drawBitmap(61,15,SFX_btn,20,8,1);
		  display.drawBitmap(75,17,SFX_one,5,5,1);
		break;
		case 2:
		  display.drawBitmap(82,15,SFX_btn,20,8,1);
		  display.drawBitmap(61,17,SFX_two,5,5,1);
		break;
		case 3:
		  display.drawBitmap(103,15,SFX_btn,20,8,1);
		  display.drawBitmap(61,17,SFX_tree,5,5,1);
		break;
		default:
		  fxbank = 0;
		break;
	}
	
	// draw mp3 file
	display.setCursor(1,25);
	display.setTextColor(1);
	display.setTextSize(1);
	display.setTextWrap(false);
	display.print(mp3file);
    display.display();
  }
}
