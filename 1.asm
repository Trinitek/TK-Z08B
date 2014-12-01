main:
ld hl, string

sendChar:

; If A is null, then go to the beginning of the string and restart
ld a,(hl)
cp 0
jp z, main

; Send character to serial port
out (2),a
inc hl
jp sendChar

string: db "Hello world! ",0