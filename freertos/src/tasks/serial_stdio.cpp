#include "serial_stdio.h"
#include <Arduino.h>

static int uart_putchar(char c, FILE *stream) {
  if (c == '\n') {
    Serial.write('\r');
  }
  Serial.write(c);
  return 0;
}

static int uart_getchar(FILE *stream) {
  while (!Serial.available());
  return Serial.read();
}

static FILE uart_stream;

void init_stdio() {
  fdev_setup_stream(&uart_stream, uart_putchar, uart_getchar, _FDEV_SETUP_RW);
  stdout = &uart_stream;
  stdin  = &uart_stream;
}
