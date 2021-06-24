# espLed2
After having some Problems with EspAsyncWebserver and AsyncTCP i decided to rewrite my code so that it uses UDP instead of TCP. 

The main problem with the TCP requests was that my ESP32 keeps crashing when too many requests arrive. The problem with this UDP approach is that you can't just easily send UDP packages from a browser.

The final solution for this system is that it comes with a simple mobile App (preferibly written in Flutter) that send the UDP packages!

The app will be released soon!
