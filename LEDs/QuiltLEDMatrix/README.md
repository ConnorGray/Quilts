Code for drawing patterns on a matrix of LEDs embedded in [a quilt](https://home.theodoregray.com/quilts).

## Development

To upload to a connected Arduino Uno, using the [`arduino-cli`](https://github.com/arduino/arduino-cli) command-line tool, run:

```shell
$ ./compile.sh && ./upload.sh
```

Note that the `<FastLED.h>` import requires that v3.5.0 of the FastLED library is installed, which can be done via the Library Manager in the Arduino app.
