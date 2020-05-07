# Instalasi NS-2.35 di Linux Mint

## Deskripsi
NS-2 adalah sebuah simulator yang ditargetkan untuk penelitian jaringan. NS-2 menyediakan dukungan yang substansial untuk simulasi protokol TCP, routing, dan multicast, baik melalui jaringan kabel dan nirkabel (lokal dan satelit).

![Logo NS-2](https://4.imimg.com/data4/KS/NI/MY-10797795/ns2-projects-in-chennai-500x500.jpg)

## Langkah Instalasi

> Lingkup: Linux debian-based (Linux Mint 18.3 Sylvia)
> * Instalasi pada Ubuntu 14.04 dapat dilihat [disini](https://www.howtoforge.com/tutorial/ns2-network-simulator-on-ubuntu-14.04/)
> * Instalasi pada Ubuntu 18.04 dapat dilihat [disini](https://www.nsnam.com/2018/06/installation-of-ns2-in-ubuntu-1804.html)
> * Instalasi pada Debian 9.4 dapat dilihat [disini](https://docs.google.com/document/d/1iEMl5YeRZ35RjkIbV34BGF126x4_elja6ceYwGHyGFk/edit)


### 1. Download NS-2.35
1. Download NS-2.35 terlebih dahulu [disini](http://sourceforge.net/projects/nsnam/)
2. Copy file yang telah terdownload (`ns-allinone-2.35.tar.gz`) dari direktori `~/Download` ke direktori home `~`
    ```bash
    cp ~/Downloads/ns-allinone-2.35.tar.gz ~/ns-allinone-2.35.tar.gz
    ```
    Keterangan:
    * `~` artinya `/home/<user>`

3. Pindah ke direktori `~`dan extract tar `ns-allinone-2.35.tar.gz`  
    ```bash
    tar zxvf ns-allinone-2.35.tar.gz
    ```

### 2. Install Dependencies
1. Menginstall **gcc-4.4** dan **g++-4.4**
   
    ```bash
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-4.4 g++-4.4
    ```
2. Menginstall dependensi yang diperlukan
   
    ```bash
    sudo apt-get install build-essential automake autoconf libxmu-dev
    ```

### 3. Install NS-2.35
1. Melakukan perubahan sedikit pada `ls.h` pada folder `ns-2.35/linkstate/`
    ```bash
    nano ~/ns-allinone-2.35/ns-2.35/linkstate/ls.h
    ```
   Dengan menambahkan `this->` sebelum `erase`, menjadi:
    ```bash
    void eraseAll() { this->erase(baseMap::begin(), baseMap::end()); }
    ```
2. Mengedit `Makefile.in` pada folder `otcl-1.14/`
    ```bash
    nano ~/ns-allinone-2.35/otcl-1.14/Makefile.in
    ```
    Dengan mengubah:
    ```bash
    # edit 
    CC=     gcc-4.4
    # tambahkan pada baris dibawahnya
    CXX=    gcc-4.4
    ```
3. Export GCC
    ```bash
    export CC=gcc-4.4 CXX=g++-4.4
    ```
    Bisa dicek dengan command `export`.
4. Kemudian menginstall NS-2.35 dengan kembali ke folder `~/ns-allinone-2.35` dengan melakukan:
    ```bash
    ./install
    ```
    Tunggu hingga proses instalasi selesai.

5. Jika menemukan error seperti di bawah ini, jangan panik terlebih dahulu. Kita hanya perlu mengatur environmentnya (.bashrc).
    ```bash
    Please put /home/mocatfrio/ns-allinone-2.35/bin:/home/mocatfrio/ns-allinone-2.35/tcl8.5.10/unix:/home/mocatfrio/ns-allinone-2.35/tk8.5.10/unix
    into your PATH environment; so that you\'ll be able to run itm/tclsh/wish/xgraph.

    IMPORTANT NOTICES:

    (1) You MUST put /home/mocatfrio/ns-allinone-2.35/otcl-1.14, /home/mocatfrio/ns-allinone-2.35/lib, 
        into your LD_LIBRARY_PATH environment variable.
        If it complains about X libraries, add path to your X libraries 
        into LD_LIBRARY_PATH.
        If you are using csh, you can set it like:
        setenv LD_LIBRARY_PATH <paths>
        If you are using sh, you can set it like:
        export LD_LIBRARY_PATH=<paths>

    (2) You MUST put /home/mocatfrio/ns-allinone-2.35/tcl8.5.10/library into your TCL_LIBRARY environmental
        variable. Otherwise ns/nam will complain during startup.
    ```
6. Membuka **.bashrc**
    ```bash
    nano ~/.bashrc
    ```
    Tambahkan berikut di bagian paling bawah:
    ```bash
    #LD_LIBRARY_PATH
    OTCL_LIB=/home/mocatfrio/ns-allinone-2.35/otcl-1.14/
    NS2_LIB=/home/mocatfrio/ns-allinone-2.35/lib/
    USR_Local_LIB=/usr/local/lib/
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OTCL_LIB:$NS2_LIB:$USR_Local_LIB

    # TCL_LIBRARY
    TCL_LIB=/home/mocatfrio/ns-allinone-2.35/tcl8.5.10/library/
    USR_LIB=/usr/lib/
    export TCL_LIBRARY=$TCL_LIBRARY:$TCL_LIB:$USR_LIB

    # PATH
    XGRAPH=/home/mocatfrio/ns-allinone-2.35/xgraph-12.2/:/home/mocatfrio/ns-allinone-2.35/bin/:/home/mocatfrio/ns-allinone-2.35/tcl8.5.10/unix/:/home/mocatfrio/ns-allinone-2.35/tk8.5.10/unix/
    NS=/home/mocatfrio/ns-allinone-2.35/ns-2.35/
    NAM=/home/mocatfrio/ns-allinone-2.35/nam-1.15/
    export PATH=$PATH:$XGRAPH:$NS:$NAM
    ```
    Kemudian simpan file dan reload **.bashrc**.
    ```bash
    source ~/.bashrc
    ```
7. Melakukan validasi NS untuk memastikan apakah semuanya berjalan dengan baik. Proses validasi ini akan memakan waktu agak lama (sekitar setengah jam).
    ```bash
    cd ~/ns-allinone-2.35/ns-2.35/
    ./validate
    ```
    Validasi berhasil:
    ```bash
    SORTING LISTS ...DONE!
    NS EXITING...
    finishing..
    Test output agrees with reference output
    Running test dsr:
    ../../ns test-suite-wireless-tdma.tcl dsr QUIET
    num_nodes is set 50
    INITIALIZE THE LIST xListHead
    Loading connection pattern...
    Loading scenario file...
    Load complete...
    Starting Simulation...
    channel.cc:sendUp - Calc highestAntennaZ_ and distCST_
    highestAntennaZ_ = 1.5,  distCST_ = 550.0
    SORTING LISTS ...DONE!
    NS EXITING...
    finishing..
    Test output agrees with reference output
    All test output agrees with reference output.
    Tue Oct 16 06:32:06 WIB 2018
    These messages are NOT errors and can be ignored:
        warning: using backward compatibility mode
        This test is not implemented in backward compatibility mode


    validate overall report: all tests passed
    ```
    p.s. Perhatikan selama proses validasi. Jika keluar `failed` maka hentikan dan cermati. Biasanya ada suatu library yang menjadi dependencies yang belum terinstall di PC kalian. 
8. Instalasi selesai!

### 4. Testing
1. Ketikkan `ns` di terminal, jika keluar tanda `%` setelah di-enter, maka instalasi berhasil!
2. Ketikkan `nam`di terminal, jika keluar pop-up nam console, maka instalasi berhasil!

## Referensi
https://www.techerina.com/2015/02/installing-ns-235-in-linux-mint-171.html