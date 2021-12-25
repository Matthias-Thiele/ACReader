# ACReader

Measuring alternating current values is not an easy job on the Arduino platform. There has to be an offset since the A/D converter can only process positive values. And you have to measure at the peak time, otherwise you will get a random value between zero and the real value.

This ACReader object will do a measurement every millisecond over the given cycle time and memorizes the minimum and maximum values. The difference between these two is the peak to peak AC voltage. This kind of measurement does not need to know where the zero line is.

The cycle time should be slightly longer than one complete period of the AC signal to make sure that there is a maximum and minimum within every cycle. 25 milliseconds with 50 Herz and 20 milliseconds with 60 Herz seems to be reasonable.
