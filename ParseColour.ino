void parse_colour(int code) {
   switch (code) {
     case WHITE:
       paint_led(255,255,255);
       break;
     case RED:
       paint_led(255,0,0);
       break;
     case GREEN:
       paint_led(0,255,0);
       break;
     case BLUE:
       paint_led(0,0,255);
       break;
     case CYAN:
       paint_led(0,255,255);
       break;
     case YELLOW:
       paint_led(255,255,0);
       break;
     case MAGENTA:
       paint_led(255,0,255);
       break;
     default:
       break;
   }
}

