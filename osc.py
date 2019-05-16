# Python Oscilliscope

import RPi.GPIO as GPIO
import time

inputPins = [21, 5, 6, 13, 19, 26]

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
for pin in inputPins:
    GPIO.setup(pin, GPIO.IN)

clear_combo = 0
last_s = ''
while True:
    s = ''
    is_clear = True
    for pin in inputPins:
        d = GPIO.input(pin)
        if str(d) == '1':
            is_clear = False
        s += str(d) + ', '
    
    clear_combo = clear_combo + 1 if is_clear else 0

    if ((not is_clear) or clear_combo < 4) and last_s != s:
        print(s)
    if clear_combo > 20 and clear_combo % 100 is 0:
        print('waiting...')
    time.sleep(0.01)
    last_s = s
