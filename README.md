# esp32-audio-channel-switch

Problem: I had too many jack plugs in my room: guitar, amplifier, listening to music from computer, 
listening to music from vinyl disc, headphones, etc. So I always had hard time to find the proper jack plug in the 
cable jungle.

Purpose of this project: This project is the "firmware" of a little electronic device that allows me to select one  
input source (computer, vinly, guitar), and select one output source (amplifier, speakers, headset), without having to 
plug any cable.  

## Build on Windows

```
> c:\Users\Akos\Desktop\esp-idf-2\export.bat
> d:
> cd d:\esp32\esp32-audio-channel-switch
> idf.py build
> idf.py flash
> idf.py monitor 
```

## Versions

ESP-IDF: 4.1-dirty, commit hash: 5ef1b3900

## Circuit

The circuit is using 3V relays to connect input signals to output signals. This guarantees that there is no added 
noise (eg. opto transistor would probably add some noise).

### Shift register SN74HC595

This IC is driving the relays for the audio channels; 
this IC is driven by ESP32 (GPIOs: 32 latch, 24 data, 33 clock)

Shift register's output signals:

 - A: Computer input
 - B: Guitar input
 - C: Vinyl input
 - D: Speakers output
 - E: Headphones output
 - F: Amplifier output
 - G: unused
 - H: unused
 
 ```
   GND
    | 
    |                      + +3.3V
  [indicator led]          |
    |
    |                      |
  [1k Ohm]            [3.3V relay] 
    |                      |
    |                      | (collector)
    +------[510 Ohm]---[BC 182 transistor]
    |                      | (emitter)
    |                      |
--------------------      GND
|  shift register  |
--------------------
 ```
 
### Audio Bus

Input channels have two relays always, one for Left signal, and another for Right audio signal; even if the audio 
source (input) is not stereo: input signal is dispatched to a Left and a Right audio bus.

Output channels consider the target: guitar amplifier is mono, so we only take signal from either left or right, and 
connect that signal to the bus.  

## TODO

 - Mute button to be placed to the front board (wired)
 - Muted LED to be added (not wired)
 - Child lock indicator led to be added (not wired)