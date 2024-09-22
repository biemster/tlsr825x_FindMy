# tlsr825x_FindMy
FindMy firmware for the Telink 825x MCU

## Installation
These instructions require linux. Although they almost can't be called instructions, since it's just cloning three repositories and unpacking the toolchain tarball to `/opt`:
```bash
git clone https://github.com/biemster/FindMy
git clone https://github.com/biemster/tlsr825x_FindMy
git clone https://github.com/pvvx/TlsrComSwireWriter
wget http://shyboy.oss-cn-shenzhen.aliyuncs.com/readonly/tc32_gcc_v2.0.tar.bz2
sudo tar -xvjf　tc32_gcc_v2.0.tar.bz2　-C /opt/
export PATH=$PATH:/opt/tc32/bin
```
For convenience you could add the PATH export to whatever gets called on starting a new shell, so it's always available.

## Further preparation
I assume here you are already familiar with the FindMy scripts from `biemster/FindMy`. If you're not, please refer to that repository for further info.
1. Generate a `.keys` file with `FindMy/generate_keys.py`
2. Add the key to the firmware using the `prep_fw.py` script like this: `./prep_fw.py <path to .keys file>`
- Additionally the firmware could be recompiled before this, by running `make`.
3. Flash the new `FindMy_XXXXXXX.bin` file using `TLSR825xComFlasher.py` over an UART, for example an USB UART dongle:
```
cd TlsrComSwireWriter
python TLSR825xComFlasher.py -p /dev/ttyUSB0 -t 1000 -r wf 0 ../tlsr825x_FindMy/FindMy_XXXXXXX.bin
```

## Retrieving the location of the module
This is explained in more detail in the `FindMy` repository, but boils down to running the `request_reports.py` script in the same
directory as the `.keys` file generated here.
