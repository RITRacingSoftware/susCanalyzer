Project to read BMS related CAN messages so we can at least charge F30 Accumulator while Canalyzer gets replaced and/or we seek a proper alternative. (And maybe do other fancier canalyzer stuff).

Goals:
- Show cell voltages, temps
- Show cell balancing 
- Use Serial out from that and throw together some UI with python or go or something

Extra goals:
- Controls to switch baudrate (500K charging, 1000K regular)
- Controls to switch/monitor specific messages rather than showing all (could do in UI)
- On board monitor??
- Use the shield's SD card slot to log stuff (at button press or something)
- Maybe port to something faster

Hardware setup:
	seeed v2.0 can shield + uno 

