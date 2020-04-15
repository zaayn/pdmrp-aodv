# MAODV - Power and Delay-aware Multi-path Routing Protocol
```
Moh. Muzayyin Amrullah
05111640000095

Imam Fadhila
05111640000181

Pervasif 2020
```

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
