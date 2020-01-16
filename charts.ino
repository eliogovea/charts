#include <UTFT.h>

#include "chart.hpp"
#include "reader.hpp"
#include "signal.hpp"

UTFT display(ITDB32S, 38, 39, 40, 41);

chart chart_{display};

mock_reader input_mock{0, 1 << 10};
analog_reader input_A0{A0};
analog_reader input_A1{A1};

signal signal_mock{input_mock};
signal signal_A0{input_A0};
signal signal_A1{input_A1};

void setup() {
  display.InitLCD();
  display.clrScr();
}

void loop() {
  // remove prev drawings
  chart_.remove_signal(signal_mock);
  chart_.remove_signal(signal_A0);
  // chart_.remove_signal(signal_A1);

  // read new data
  signal_mock.read();
  signal_A0.read();
  signal_A1.read();

  chart_.draw_axis(0, 255, 0);
  
  //
  chart_.draw_signal(signal_mock, 0, 0, 255);
  chart_.draw_signal(signal_A0, 255, 0, 0);
  // chart_.draw_signal(signal_A1, 128, 0, 128);

  delay(100); 
}
