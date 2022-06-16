# Satellite radio TX test

## Output power

When the frequency is set to frequencies listed in module datasheet, the TX power should be similar to what is described in the datasheet.


## Current draw

When the test frequency is set to frequencies described in module datasheet, the current draw would be similar to what is described in the datasheet.
The module current draws peak when transmitting. The board design should be able to support continuous TX current draw for at least one tranmission period. For real uplink transmissions, the duration is about 260ms.


## RF path connectivity

RF TX test to used to check if the connectivity of RF path is good and specifically the antenna has been connected.
If there is no connectivity issue and the antenna/matching circuit has been tuned properly, the TX current draw should similar to what is described in the datasheet.
The TX power can be checked as well to verify the connectivity. Since the signal is attenuated over the air, the signal strength won't be as strong.
If equipment like spectrum analyser is not available, the satellite simulator USB dongle can be repurposed for coarse measurement. Multiple free [software](https://www.rtl-sdr.com/big-list-rtl-sdr-supported-software) for both Windows and Linux/macOS can be used for the measurement.
Contact support@myriota.com if further information is required.
Both TX and RX paths can be checked. Antenna selection logic may need to be adjusted if different antennas for TX and RX are being used. When checking RX path of VHF(M1-24) modules, the TX power will be significant lower.

## Notes
Make sure the is enough attenuation between the device under test and the testing equipment/device when doing conducted measurement.
Make sure the is enough separation between the device under test and the testing equipment/device when doing radiated measurement.
