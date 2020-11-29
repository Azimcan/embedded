# sbt kurulum
```
echo "deb https://dl.bintray.com/sbt/debian /" | sudo tee -a /etc/apt/sources.list.d/sbt.list
```
```
curl –sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | sudo apt-key add
```
```
sudo apt-get update
```
```
sudo apt-get install sbt
```


# gdb kurulum
```
sudo apt-get update
```
```
sudo apt-get install gdb
```


# verilator kurulum
```
sudo apt-get install git make autoconf g++ flex bison
```
```
sudo apt-get install libfl2
```
```
sudo apt-get install libfl-dev
```
```
git clone https://github.com/verilator/verilator
```
```
cd verilator
```
```
autoconf
```
```
./configure
```
```
make
```
```
sudo make install
```


# openocd kurulum

```
sudo apt-get install libtool automake libusb-1.0.0-dev texinfo libusb-dev libyaml-dev pkg-config
```
```
git clone https://github.com/SpinalHDL/openocd_riscv.git openocd
```
```
./bootstrap
```
```
./configure --prefix=/usr/local --program-suffix=-vexriscv \
--datarootdir=/usr/local/share/vexriscv --enable-maintainer-mode \
--disable-werror --enable-ft232r --enable-ftdi --enable-jtag_vpi \
--disable-aice --disable-amtjtagaccel --disable-armjtagew \
--disable-assert --disable-at91rm9200 --disable-bcm2835gpio \
--disable-buspira --disable-cmsis-dap --disable-doxygen-html \
--disable-doxygen-pdf --disable-dummy --disable-ep93xx \
--disable-gw16012 --disable-imx_gpio --disable-jlink \
--disable-kitprog --disable-minidriver-dummy --disable-oocd_trace \
--disable-opendous --disable-openjtag --disable-osbdm \
--disable-parport --disable-parport-giveio --disable-parport-ppdev \
--disable-presto --disable-remote-bitbang --disable-rlink \
--disable-stlink --disable-sysfsgpio --disable-ti-icdi \
--disable-ulink --disable-usb-blaster --disable-usb-blaster-2 \
--disable-usbprog --disable-verbose-jtag-io \
--disable-verbose-usb-comms --disable-verbose-usb-io \
--disable-vsllink --disable-xds110 --disable-zy1000 \
--disable-zy1000-master
```
```
make
```
```
sudo make install
```


# RISC-V GCC kurulum

```
wget https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14.tar.gz
```
```
tar -xzvf riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14.tar.gz
```
```
sudo mv riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14 /opt/riscv
```
```
echo 'export PATH=/opt/riscv/bin:$PATH' >> ~/.bashrc
```


# Kullanım

```
git clone https://github.com/mupq/pqriscv-vexriscv.git
```

- Terminal 1
```
sbt "runMain mupq.PQVexRiscvSim --ram 256,128 --uart uartoutput.txt"
```

- Terminal 2
```
openocd-vexriscv -f pqvexriscvsim.cfg
```

- Terminal 3
```
tail -f uartoutput.txt
```

- Terminal 4
```
riscv64-unknown-elf-gdb -ex 'set remotetimeout 10' -ex 'target remote:3333' -ex load -ex 'break main' hello.elf
```

# EK:
https://github.com/mupq/pqriscv

https://github.com/SpinalHDL/openocd_riscv

https://ubuntu.pkgs.org/20.04/ubuntu-universe-armhf/gcc-riscv64-unknown-elf_9.3.0-0ubuntu1_armhf.deb.html
