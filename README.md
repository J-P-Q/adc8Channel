# 8 Channel ADC to UART Stream

An ATmega-based 8-channel ADC converter and UART transmitter, prototyped as a cost-effective feasibility test for a planned sEMG signal acquisition system for a group thesis project.

## Hardware

- ATmega328p (Arduino Nano)

## How It Works

- Interrupt-driven continuous 8-channel ADC conversion, streaming UART packets in parallel after each channel conversion.
- Sampling frequency configurable via timer peripheral period 1ms (1kHz).
- Timer interrupt triggers channel 0's conversion; each subsequent channel is triggered by the ADC ISR.
- ADC ISR enables the UART ISR to transmit newly converted data. UART ISR disables itself once the ring buffer is empty, preventing a block on constant interrupts when the UART data register is empty but no data remains to send.

## Testing

Inputs tested using potentiometers on 2 channels at a time, with the remaining channels held at fixed 5V or 0V. Output verified using a pyserial-based Python script: https://github.com/J-P-Q/rPiUart

## Status

Currently functions as a raw ADC-to-UART stream to a receiver (planned to be a Raspberry Pi). The ADC requires a conversion time of 104us per channel in this implementation, and this puts a hard limit on the sampling rate even after refactoring from polling to interrupt based architecture. 

## Build / Setup

- PlatformIO (VS Code)

## Demo

<link>
