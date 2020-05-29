# MAODV - Power and Delay-aware Multi-path Routing Protocol
```
Moh. Muzayyin Amrullah
05111640000095

Imam Fadhila
05111640000181

Pervasif 2020
```

## Table of Content
- [MAODV - Power and Delay-aware Multi-path Routing Protocol](#maodv---power-and-delay-aware-multi-path-routing-protocol)
  - [Table of Content](#table-of-content)
  - [1. Konsep](#1-konsep)
    - [1.1 Deskripsi Paper](#11-deskripsi-paper)
    - [1.2 Latar Belakang](#12-latar-belakang)
    - [1.3 Dasar Teori](#13-dasar-teori)
      - [1.3.1 AODV Routing Protocol](#131-aodv-routing-protocol)
      - [1.3.2 SPR Routing Protocol](#132-spr-routing-protocol)
    - [1.4 Routing Protokol yang Diusulkan](#14-routing-protokol-yang-diusulkan)
      - [1.4.1 PDMRP Routing Protocol](#141-pdmrp-routing-protocol)
  - [2. Implementasi](#2-implementasi)
    - [2.1 Deskripsi Sistem](#21-deskripsi-sistem)
    - [2.2 Modifikasi](#22-modifikasi)
  - [3. Testing](#3-testing)
  - [4. Referensi](#4-referensi)

## 1. Konsep
### 1.1 Deskripsi Paper

berikut Paper yang menjadi acuan dalam pengerjaan Final Project ini:

* Judul : **Power and Delay-aware Multi-path Routing Protocol for Ad Hoc Networks**
* Penulis : Salwa Othmen, Aymen Belghith, Faouzi Zarai, Mohammad S. Obaidat, Lotfi Kamoun
* Sumber : https://ieeexplore.ieee.org/document/6878956

### 1.2 Latar Belakang

**MANETs** *(Mobile Ad Hoc Networks)* adalah jaringan yang terdiri dari node-node bergerak yang saling berkomunikasi satu sama lain. Karakteristik jaringan MANET adalah:
  * Topologinya dinamis
  * Terbatasnya energi baterai yang dimiliki oleh node bergerak
 
Habisnya energi baterai suatu node menyebabkan rusaknya rute pada jaringan MANET, sehingga menimbulkan beberapa masalah:
  * Paket hilang
  * Node akan menginisialisasi Route Discovery (pencarian rute) ulang, sehingga menyebabkan banyaknya konsumsi bandwith, meningkatkan delay, dan mengurangi throughput
  
Oleh karena itu, paper ini mengusulkan sebuah routing protocol baru bernama **PDMRP** *(Power and Delay-aware Multi-path Routing Protocol)* yang memperbaiki kekurangan dari **SPR** *(Stable Path Routing Protocol based on Power Awareness)* dan **MAODV** *(Modified Ad Hoc On-Demand Distance Vector Routing Protocol)* dalam segi throughput, end-to-end delay, dan loss rate. 

### 1.3 Dasar Teori
#### 1.3.1 AODV Routing Protocol
* **AODV** *(Ad Hoc On-Demand Distance Vector Routing Protocol)* adalah salah satu routing protocol reaktif yang memiliki 3 jenis paket untuk **route discovery** dan **route maintenance**, yakni:
  * Route Request (RREQ)
    Memiliki format paket sebagai berikut:
  
    ![Paket RREQ](/img/rreq.jpg)

    Keterangan:
      * **Type** : Tipe paket (RREQ = 1)
      * **|J|R|G|D|U|** : Flag yang menunjukkan keadaan paket
      * **Reserved** : Default 0, diabaikan
      * **Hop Count** : Jumlah hops dari node asal ke node yang sedang meng-handle RREQ saat ini
      * **RREQ ID** : Nomor unik untuk mengidentifikasi RREQ tertentu 
      * **Destination IP Address** : Alamat IP tujuan
      * **Destination Sequence Number** : Urutan node tujuan
      * **Originator IP Address** : Alamat IP asal yang menginisialisasi RREQ
      * **Originator Sequence Number** : Urutan node asal

  * Route Reply (RREP)
    Memiliki format paket sebagai berikut:

    ![Paket RREP](/img/rrep.jpg)

  * Route Error (RERR) 
    Memiliki format paket sebagai berikut:

    ![Paket RERR](/img/rerr.jpg)

* Cara kerja AODV :
  1. Ketika node asal ingin berkomunikasi dengan node tujuan yang belum memiliki rute, maka **node asal** akan mem-broadcast RREQ ke jaringan untuk melakukan **route discovery** (pencarian rute).
  2. Ketika **node intermediate** menerima paket RREQ yang belum pernah diterima sebelumnya (cek RREQ ID), maka ia akan membuat **reverse route** ke node asal. 
  3. **Node intermediate** akan mengecek alamat tujuan pada paket RREQ. Jika ia belum punya informasi rute ke node tujuan yang dimaksudkan, maka ia akan menambah hop count pada paket dan meneruskan broadcast RREQ ke jaringan. Namun jika sebaliknya, ia akan mengirimkan **RREP** ke node asal.
  4. Ketika **node asal** menerima RREP, ia akan menyimpan rute tersebut dan memulai transmisi data.
   
#### 1.3.2 SPR Routing Protocol
* **SPR** *(Stable Path Routing Protocol based on Power Awareness)* adalah sebuah on-demand routing protocol yang diusulkan pada paper berikut  https://pdfs.semanticscholar.org/3159/ac48ea17987c3541e636ee431b9450e968aa.pdf 
* Tujuan dari SPR adalah :
  * Mencari rute paling **optimal** dari node asal ke node tujuan pada jaringan MANET dari segi **bandwith**
  * Mencari rute paling **stabil** dari segi **sisa masa hidup baterai**
* SPR memiliki format paket sebagai berikut :
    
  ![Paket RREQ SPR](/img/rreq-spr.png)
  
  Keterangan:
    * **RBW** : Bandwith yang dibutuhkan untuk transmisi data
    * **ML** : Sisa masa hidup (energi baterai) minimum rute
    * **TTL** : Waktu hidup maksimum paket 
    * **Seqnum** : Nomor unik untuk mengidentifikasi RREQ tertentu 
    * **Source Address** : Alamat node asal
    * **Destination Address** : Alamat node tujuan yang diinginkan
    * **Address i ... n** : Alamat node intermediate yang dilewati di dalam rute
* Cara kerja SPR :
  1. Ketika **node intermediate** menerima paket RREQ, ia akan **membandingkan alamat dirinya dengan alamat tujuan** pada paket.
      * Jika ia adalah node tujuan, maka ia akan mengirimkan RREP dan reverse route.
      * Jika ia bukan node tujuan, maka ia akan lanjut mengecek **ketersediaan bandwith** yang dibutuhkan pada paket. 
        * Jika bandwith tidak tersedia, maka paket RREQ di-drop.
        * Jika bandwith tersedia, maka ia akan **mengurangi TTL paket**. 
          * Jika TTL telah mencapai 0, maka paket RREQ di-drop.
  2. Setelah itu, **node intermediate** akan **membandingkan sisa masa hidupnya (sisa energi baterai) dengan nilai ML** pada paket. Jika lebih kecil, maka nilai ML akan diganti dengan sisa masa hidupnya karena ML menyimpan sisa energi baterai minimum node yang dilewati oleh rute.
  3. Ketika **node intermediate** menerima RREQ yang sama dari asal yang berbeda, maka ia akan **membandingkan nilai ML dari kedua paket.** 
      * Jika ML dari paket RREQ yang baru lebih besar, maka ia mem-broadcast ulang paket RREQ yang baru. 
      * Jika sebaliknya, paket RREQ di-drop.
  4. Setelah menerima paket RREQ pertama, **node tujuan** akan menunggu paket RREQ lain dari jalur yang berbeda dengan waktu yang telah ditentukan. Kemudian ia membandingkan **nilai ML pada semua paket RREQ** dan memilih paket dengan ML terbesar, paket lainnya di-drop.
* Kekurangan SPR :
  1. Tidak mempertimbangkan faktor **jumlah hop yang dilewati**. Sehingga SPR memiliki delay yang besar karena lebih memilih rute dengan nilai ML paling besar walaupun memiliki banyak hop, padahal perbedaan nilai ML-nya hanya sedikit dengan rute yang jauh lebih pendek.
  2. Jika ada kerusakan pada rute, maka perlu inisialisasi route discovery lagi, sehingga memakan banyak bandwith.
  
### 1.4 Routing Protokol yang Diusulkan
Untuk memperbaiki kekurangan dari protokol SPR di atas, paper ini mengusulkan sebuah routing protocol baru bernama **Power and Delay-aware Multi-path Routing Protocol (PDMRP)**.

#### 1.4.1 PDMRP Routing Protocol
* Tujuan dari PDMRP adalah :
  * Memilih **jalur paling pendek** (memiliki **jumlah hop minimum**) dan **paling stabil** (memiliki **sisa energi baterai tertinggi**) untuk dijadikan rute utama
  * Memilih **jalur alternatif** yang dapat digunakan sebagai rute sekunder, tersier, dsb (multi-path). Sehingga ketika rute utama sudah tidak dapat digunakan lagi (rusak) maka pengiriman data langsung diarahkan ke rute sekunder tanpa harus melakukan route discovery kembali

* Untuk mencapai tujuan tersebut, maka perlu dihitung Cost (C) untuk setiap jalur dengan rumus berikut :
  
  ```
  C = ML / NH
  ```
  Keterangan:
  * **ML** : Sisa energi baterai minimum node pada rute
  * **NH** : Jumlah hop yang harus dilewati dalam suatu rute
  
* Cara kerja PDMRP :
  1. Ketika **node intermediate** menerima paket RREQ lebih dari satu dari sumber yang sama, maka ia akan menghitung dan membandingkan C pada setiap RREQ. Kemudian ia meneruskan broadcast paket dengan nilai C paling besar, sedangkan paket lain di-drop.
  2. Setelah menerima paket RREQ pertama, **node tujuan** akan menunggu paket RREQ lain dari jalur yang berbeda dengan waktu yang telah ditentukan. Kemudian, node tujuan membalas semua RREQ dengan mengirimkan paket RREP sesuai dengan RREQ-nya ke node asal.
  3. **Node asal** akan menerima paket RREP dari semua jalur dan membandingkan nilai C pada semua RREP. Kemudian ia memilih rute utama dengan nilai C paling besar. Rute selanjutnya dijadikan rute sekunder, tersier, dst. 

## 2. Implementasi
### 2.1 Deskripsi Sistem
Implementasi routing protocol MAODV - PDMRP dilakukan pada sistem dengan
* Sistem Operasi : Linux Mint 18.3 Sylvia
* Aplikasi yang digunakan :
  * NS-2.35 ([Instalasi](/install-ns2.md))
  * Netbeans for C/C++ Development ([Instalasi](https://websiteforstudents.com/how-to-install-netbeans-on-ubuntu-16-04-17-10-18-04/))
  
## 3. Testing
* [Skenario Testing](testing.md)

## 4. Referensi
* [A Tutorial on the Implementation of Ad-hoc On Demand Distance Vector (AODV) Protocol in Network Simulator (NS-2)](https://drive.google.com/file/d/0B6aQ8IUEyp5NekhLZWVwV0lRNU0/edit)
* [Ad hoc On-Demand Distance Vector (AODV) Routing](https://www.ietf.org/rfc/rfc3561.txt)