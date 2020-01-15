#include <UTFT.h>

#include "chart.hpp"
#include "reader.hpp"

UTFT display(ITDB32S, 38, 39, 40, 41);
chart signals{display};

mock_reader input{};

void setup() {
  display.InitLCD();
  display.clrScr();
}

void loop() {
  signals.remove_signal(input.get_buffer());
  input.read();
  signals.draw_axis(0, 255, 0);
  signals.draw_signal(input.get_buffer(), 0, 0, 255);
  delay(100); 
}
