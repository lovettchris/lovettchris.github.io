## AirSim with PX4 on WSL 2

[![snapshot](thumbnail.png)](https://youtu.be/DiqgsWIOoW4)

[AirSim](https://github.com/microsoft/airsim) now works with [PX4 latest bits](https://github.com/PX4/PX4-Autopilot) on 
the [Windows Subsystem for Linux version 2](https://docs.microsoft.com/en-us/windows/wsl/).

Click the thumbnail to watch the video to see how to set it all up from scratch!

Those who don't know WSL 2 runs in a virtual machine which causes PX4 and Windows Host to have
different IP addresses, so they can't share localhost anymore.

This video is showing off a brand new feature of PX4 SITL mode, namely, the ability for PX4 SITL to
connect to a remote simulator (AirSim in this case).  This also means you could have PX4 running on a [Raspberry Pi](https://docs.px4.io/master/en/dev_setup/dev_env_linux_ubuntu.html#raspberry-pi) talking to AirSim on your Windows machine.

