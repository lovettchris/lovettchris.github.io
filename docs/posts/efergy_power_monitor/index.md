# Efergy Power Monitor

Alex Kelly showed me this really cool project by [Nathaniel Elijah](http://rtlsdr-dongle.blogspot.com/2013/11/finally-complete-working-prototype-of.html) where he used a software defined radio to decode the power data from an [Efergy power monitor](http://efergy.com/).  So I had some fun adding an [AllJoyn](https://openconnectivity.org/developer/reference-implementation/alljoyn) wrapper on that so that my Raspberry Pi can act as an Alljoyn sensor which I can then easily connect to using my PC where I can grab the data and have fun with it in C#.

[![link](thumbnail.png)](http://lovettsoftware.com/videos/EnergyHub.mp4)