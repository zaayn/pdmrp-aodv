## Testing AODV

1. Generate the positions of nodes and their moving speed and moving directions using **Setdest tool**. 
    * Move to the directory of setdest tool :
        ```bash
        cd ~/ns-allinone-2.35/ns-2.35/indep-utils/cmu-scen-gen/setdest
        ```
    
    * Check the syntax of setdest using `./setdest`
        ```bash
        usage:

        <original 1999 CMU version (version 1)>
        ./setdest -v <1> -n <nodes> -p <pause time> -M <max speed> -t <simulation time> -x <max X> -y <max Y>

        OR
        <modified 2003 U.Michigan version (version 2)>
        ./setdest -v <2> -n <nodes> -s <speed type> -m <min speed> -M <max speed> -t <simulation time> -P <pause type> -p <pause time> -x <max X> -y <max Y>
        ```
        Example:

        ```bash  
        ./setdest -v 2 -n 8-s 1 -m 10 -M 50 -t 30 -P 1 -p 1 -x 500 -y 500 > setdest10.tcl
        ```

        Output file: **setdest10.tcl** (change the filename as you want)

    * Add two static nodes as source node and destination node as you want and its position. 
        Example for 10 node :
        ```tcl
        ...

        # set node source and destination
        # node source: node 8
        $node_(8) set X_ 500.000000000000
        $node_(8) set Y_ 0.000000000000
        $node_(8) set Z_ 0.000000000000
        
        # destination: node 9
        $node_(9) set X_ 0.000000000000
        $node_(9) set Y_ 500.000000000000
        $node_(9) set Z_ 0.000000000000
        ```
2. Generate CBR packet using **cbrgen**.
    * Move to directory of cbrgen:
        ```bash
        cd ~/ns-allinone-2.35/ns-2.35/indep-utils/cmu-scen-gen 
        ```
    * Check the syntax of cbrgen using `ns cbrgen.tcl`
        
        ```bash
        usage: cbrgen.tcl [-type cbr|tcp] [-nn nodes] [-seed seed] [-mc connections] [-rate rate]
        ```
        Example:

        ```bash  
        ns cbrgen.tcl -type cbr -nn 10 -seed 1 -mc 1 -rate 5.0 > cbr10.tcl
        ```

        Output file: **cbr10.tcl** (change the filename as you want)
    * Add node 8 and 9 as source and destination agent. The source agent send UDP packet.
        Example for 10 node:
        ```tcl
        set udp_(0) [new Agent/UDP]
        $ns_ attach-agent $node_(8) $udp_(0)
        set null_(0) [new Agent/Null]
        $ns_ attach-agent $node_(9) $null_(0)
        ```

3. Move the two output files above into one folder
4. Move TCL script for set the scenario called **scen.tcl** into that folder.
    * Snippet:

        ```tcl
        set val(chan)       		  Channel/WirelessChannel		  ;# channel type
        set val(prop)       		  Propagation/TwoRayGround	  ;# radio-propagation model
        set val(netif)      		  Phy/WirelessPhy   			    ;# network interface type
        set val(mac)        		  Mac/802_11		          	  ;# MAC type
        set val(ifq)        		  Queue/DropTail/PriQueue		  ;# interface queue type
        set val(ll)         		  LL			             	      ;# link layer type
        set val(ant)        		  Antenna/OmniAntenna		      ;# antenna model
        set opt(x)              	530                         ;# X dimension of the topography
        set opt(y)              	530                         ;# Y dimension of the topography
        set val(ifqlen)         	50				                  ;# max packet in ifq
        set val(nn)             	5				                    ;# how many nodes are simulated
        set val(seed)				      1.0				                  ;# seed cbr
        set val(adhocRouting)   	AODV				                ;# routing protocol
        set val(stop)           	200				                  ;# simulation time
        set val(cp)					      "cbr10.tcl"			        ;#<-- traffic file
        set val(sc)               "setdest10.tcl"		      ;
        
        ...
        ```
        Adjust the **val(cp)** and **val(sc)** file name according to yours.

5. Run the secnario
    ```bash
    ns scen.tcl
    ```

    Output: **result.tr** and **result.nam**
6. Move AWK script (AWK is a programming language designed for text processing and typically used as a data extraction and reporting tool.) called **pdr.awk** for reading the **result.tr**.
    1. Install AWK `sudo apt-get install gawk`
    2. Run the AWK script `awk -f pdr.awk result.tr`. The output will be more readable.


