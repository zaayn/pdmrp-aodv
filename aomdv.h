/*
 * Copyright (c) 2008, Marcello Caleffi, <marcello.caleffi@unina.it>,
 * http://wpage.unina.it/marcello.caleffi
 *
 * The AOMDV code has been developed at DIET, Department of Electronic
 * and Telecommunication Engineering, University of Naples "Federico II"
 *
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 * The copyright of this module includes the following
 * linking-with-specific-other-licenses addition:
 *
 * In addition, as a special exception, the copyright holders of
 * this module give you permission to combine (via static or
															  * dynamic linking) this module with free software programs or
 * libraries that are released under the GNU LGPL and with code
 * included in the standard release of ns-2 under the Apache 2.0
 * license or under otherwise-compatible licenses with advertising
 * requirements (or modified versions of such code, with unchanged
					  * license).  You may copy and distribute such a system following the
 * terms of the GNU GPL for this module and the licenses of the
 * other code concerned, provided that you include the source code of
 * that other code when and as the GNU GPL requires distribution of
 * source code.
 *
 * Note that people who make modified versions of this module
 * are not obligated to grant this special exception for their
 * modified versions; it is their choice whether to do so.  The GNU
 * General Public License gives permission to release a modified
 * version without this exception; this exception also makes it
 * possible to release a modified version which carries forward this
 * exception.
 *
 */



/*
Copyright (c) 1997, 1998 Carnegie Mellon University.  All Rights
Reserved. 

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The AODV code developed by the CMU/MONARCH group was optimized and tuned by Samir Das and Mahesh Marina, University of Cincinnati. The work was partially done in Sun Microsystems.

*/



#ifndef __aomdv_h__
#define __aomdv_h__

//#include <agent.h>
//#include <packet.h>
//#include <sys/types.h>
//#include <cmu/list.h>
//#include <scheduler.h>

#include <cmu-trace.h>
#include <priqueue.h>
#include <aomdv/aomdv_rtable.h>
#include <aomdv/aomdv_rqueue.h>
// AODV ns-2.31 code
#include <classifier/classifier-port.h>

// Modifikasi - menambah header untuk manet dan energi
#include <mobilenode.h> 

// AOMDV code
#define AOMDV_PACKET_SALVAGING
#define AOMDV_MAX_SALVAGE_COUNT  10
#define AOMDV_EXPANDING_RING_SEARCH

// MODIFIKASI B - mengaktifkan Link Disjoint Path
// AOMDV code
#define AOMDV_LINK_DISJOINT_PATHS
// #define AOMDV_NODE_DISJOINT_PATHS

/*
  Allows local repair of routes 
*/
// AOMDV code - could it be uncomment?
#define AOMDV_LOCAL_REPAIR

/*
  Allows AODV to use link-layer (802.11) feedback in determining when
  links are up/down.
*/
//#define AOMDV_LINK_LAYER_DETECTION

/*
  Causes AODV to apply a "smoothing" function to the link layer feedback
  that is generated by 802.11.  In essence, it requires that RT_MAX_ERROR
  errors occurs within a window of RT_MAX_ERROR_TIME before the link
  is considered bad.
*/
#define AOMDV_USE_LL_METRIC

/*
  Only applies if AODV_USE_LL_METRIC is defined.
  Causes AODV to apply omniscient knowledge to the feedback received
  from 802.11.  This may be flawed, because it does not account for
  congestion.
*/
//#define AOMDV_USE_GOD_FEEDBACK


class AOMDV;

#define MY_ROUTE_TIMEOUT  10           // 100 seconds
#define ACTIVE_ROUTE_TIMEOUT    10    // 50 seconds
#define REV_ROUTE_LIFE    6      // 5  seconds
// AODV ns-2.31 code
#define BCAST_ID_SAVE     6      // 3 seconds


// No. of times to do network-wide search before timing out for 
// MAX_RREQ_TIMEOUT sec. 
#define RREQ_RETRIES      3  
// timeout after doing network-wide search RREQ_RETRIES times
#define MAX_RREQ_TIMEOUT   1.0 //sec

/* Various constants used for the expanding ring search */
// AOMDV code
#ifdef AOMDV_EXPANDING_RING_SEARCH
#define TTL_START     		5		// 5
#define TTL_INCREMENT 		2 		// 2
#else // NO EXPANDING RING SEARCH
#define TTL_START     		30
#define TTL_INCREMENT 		30
#endif // NO EXPANDING RING SEARCH
#define TTL_THRESHOLD     7

// Should be set by the user using best guess (conservative) 
#define NETWORK_DIAMETER  30       // 30 hops

// Must be larger than the time difference between a node propagates a route 
// request and gets the route reply back.

//#define RREP_WAIT_TIME     (3 * NODE_TRAVERSAL_TIME * NETWORK_DIAMETER) // ms
//#define RREP_WAIT_TIME     (2 * REV_ROUTE_LIFE)  // seconds
#define RREP_WAIT_TIME   1.0  // sec

#define ID_NOT_FOUND    0x00
#define ID_FOUND  0x01
//#define INFINITY  0xff

// The followings are used for the forward() function. Controls pacing.
#define AOMDV_DELAY 1.0     // random delay
#define NO_AOMDV_DELAY -1.0       // no delay 

// think it should be 30 ms
#define ARP_DELAY 0.01      // fixed delay to keep arp happy


#define HELLO_INTERVAL    1         // 1000 ms
#define ALLOWED_HELLO_LOSS      3         // packets
#define BAD_LINK_LIFETIME       3         // 3000 ms
#define MaxHelloInterval  (1.25 * HELLO_INTERVAL)
#define MinHelloInterval  (0.75 * HELLO_INTERVAL)

// AOMDV code - Could it be removev?
// This should be somewhat related to arp timeout
#define NODE_TRAVERSAL_TIME     0.03       // 30 ms
#define LOCAL_REPAIR_WAIT_TIME  0.15 //sec



/*
  Timers (Broadcast ID, Hello, Neighbor Cache, Route Cache)
*/
class AOMDVBroadcastTimer : public Handler {
public:
  AOMDVBroadcastTimer(AOMDV* a) : agent(a) {}
  void   handle(Event*);
private:
  AOMDV   *agent;
  Event   intr;
};

class AOMDVHelloTimer : public Handler {
public:
  AOMDVHelloTimer(AOMDV* a) : agent(a) {}
  void   handle(Event*);
private:
  AOMDV   *agent;
  Event   intr;
};

class AOMDVNeighborTimer : public Handler {
public:
  AOMDVNeighborTimer(AOMDV* a) : agent(a) {}
  void   handle(Event*);
private:
  AOMDV   *agent;
  Event   intr;
};

class AOMDVRouteCacheTimer : public Handler {
public:
  AOMDVRouteCacheTimer(AOMDV* a) : agent(a) {}
  void   handle(Event*);
private:
  AOMDV  *agent;
  Event  intr;
};

class AOMDVLocalRepairTimer : public Handler {
public:
  AOMDVLocalRepairTimer(AOMDV* a) : agent(a) {}
  void   handle(Event*);
private:
  AOMDV   *agent;
  Event   intr;
};

// AOMDV code
/*
  Route List
*/
class AOMDV_Route {
  friend class AOMDVBroadcastID;
 public:
  AOMDV_Route(nsaddr_t nexthop, nsaddr_t lasthop=0) {
				nh_addr = nexthop;
				lh_addr = lasthop;
		  }
	protected:
	LIST_ENTRY(AOMDV_Route) route_link;
  nsaddr_t  nh_addr;
  nsaddr_t  lh_addr;
};

LIST_HEAD(aomdv_routes, AOMDV_Route);

/*
  Broadcast ID Cache
*/
class AOMDVBroadcastID {
  friend class AOMDV;

public:  
  // MODIFIKASI C4 -- menambahkan parameter cost pada broadcast ID cache
  AOMDVBroadcastID(nsaddr_t i, u_int32_t b, double c) { 
    src = i; 
    id = b;
    cost = c;
    // AOMDV code
    count=0;  
    LIST_INIT(&reverse_path_list);
    LIST_INIT(&forward_path_list);
  }

protected:
  LIST_ENTRY(AOMDVBroadcastID)  link;
  nsaddr_t                      src;
  u_int32_t                     id;
  // MODIFIKASI C4 -- menambahkan parameter cost pada broadcast ID cache
  double                        cost; //modif
  double                        expire;   // now + BCAST_ID_SAVE s
  
  // AOMDV code
  int					  count;
  aomdv_routes  reverse_path_list;     // List of reverse paths used for forwarding replies
  aomdv_routes  forward_path_list;     // List of forward paths advertised already

  inline AOMDV_Route* reverse_path_insert(nsaddr_t nexthop, nsaddr_t lasthop=0) {
    AOMDV_Route* route = new AOMDV_Route(nexthop, lasthop);
    assert(route);
    LIST_INSERT_HEAD(&reverse_path_list, route, route_link);
    return route;
  }

  inline AOMDV_Route* reverse_path_lookup(nsaddr_t nexthop, nsaddr_t lasthop=0) {
    AOMDV_Route *route = reverse_path_list.lh_first;

    // Search the list for a match of id
    for( ; route; route = route->route_link.le_next) {
      if ( (route->nh_addr == nexthop) && (route->lh_addr == lasthop) )
        return route;     
      }
    return NULL;
    }
  
  inline AOMDV_Route* forward_path_insert(nsaddr_t nexthop, nsaddr_t lasthop=0) {
    AOMDV_Route* route = new AOMDV_Route(nexthop, lasthop);
    assert(route);
    LIST_INSERT_HEAD(&forward_path_list, route, route_link);
    return route;
  }

  inline AOMDV_Route* forward_path_lookup(nsaddr_t nexthop, nsaddr_t lasthop=0) {
    AOMDV_Route *route = forward_path_list.lh_first;

    // Search the list for a match of id
    for( ; route; route = route->route_link.le_next) {
      if ( (route->nh_addr == nexthop) &&	(route->lh_addr == lasthop) ) 
        return route;     
    }
    return NULL;
  }
};

LIST_HEAD(aomdv_bcache, AOMDVBroadcastID);


/*
  The Routing Agent
*/
class AOMDV: public Agent {

  /*
   * make some friends first 
   */

  friend class aomdv_rt_entry;
  friend class AOMDVBroadcastTimer;
  friend class AOMDVHelloTimer;
  friend class AOMDVNeighborTimer;
  friend class AOMDVRouteCacheTimer;
  friend class AOMDVLocalRepairTimer;

public:
  AOMDV(nsaddr_t id);
  void recv(Packet *p, Handler *);

protected:
  int command(int, const char *const *);
  int initialized() { return 1 && target_; }

  /*
   * Route Table Management
   */
  void rt_resolve(Packet *p);
  void rt_down(aomdv_rt_entry *rt);
  void local_rt_repair(aomdv_rt_entry *rt, Packet *p);

public:
  void rt_ll_failed(Packet *p);
  // AOMDV code
  // void rt_update(aodv_rt_entry *rt, u_int32_t seqnum, u_int16_t metric, nsaddr_t nexthop, double expire_time);
  // void handle_link_failure(nsaddr_t id);
  void handle_link_failure(nsaddr_t id);

protected:
  void rt_purge(void);

  void enque(aomdv_rt_entry *rt, Packet *p);
  Packet* deque(aomdv_rt_entry *rt);

  /*
   * Neighbor Management
   */
  void nb_insert(nsaddr_t id);
  AOMDV_Neighbor* nb_lookup(nsaddr_t id);
  void nb_delete(nsaddr_t id);
  void nb_purge(void);

  /*
   * Broadcast ID Management
   */

  // AODV ns-2.31 code
  // MODIFIKASI C4 -- menambahkan parameter cost pada broadcast cache
  void id_insert(nsaddr_t id, u_int32_t bid, double cost);
  bool id_lookup(nsaddr_t id, u_int32_t bid);
  AOMDVBroadcastID* id_get(nsaddr_t id, u_int32_t bid, double cost, bool check_cost);
  void id_purge(void);
  void id_delete(nsaddr_t id, u_int32_t bid, double cost);


  /*
   * Packet TX Routines
   */
  void forward(aomdv_rt_entry *rt, Packet *p, double delay);
  // AOMDV code - should it be removed?
  void forwardReply(aomdv_rt_entry *rt, Packet *p, double delay);
  void sendHello(void);
  void sendRequest(nsaddr_t dst);

  // AOMDV code
  // void      sendReply(nsaddr_t ipdst, u_int32_t hop_count, nsaddr_t rpdst, u_int32_t rpseq, u_int32_t lifetime, double timestamp);
  // MODIFIKASI D1 -- menambahkan parameter cost pada send RREP
  void sendReply(nsaddr_t ipdst, u_int32_t hop_count, nsaddr_t rpdst, u_int32_t rpseq, double lifetime, double timestamp, nsaddr_t nexthop, u_int32_t bcast_id, nsaddr_t rp_first_hop, double cost);
  void sendError(Packet *p, bool jitter = true);
            
  /*
   * Packet RX Routines
   */
  void recvAOMDV(Packet *p);
  void recvHello(Packet *p);
  void recvRequest(Packet *p);
  void recvReply(Packet *p);
  void recvError(Packet *p);

   /*
    * History management
    */
   
  double  PerHopTime(aomdv_rt_entry *rt);


  nsaddr_t  index;      // IP Address of this node
  u_int32_t seqno;      // Sequence Number
  int       bid;        // Broadcast ID

  aomdv_rtable   rthead;     // routing table
  aomdv_ncache   nbhead;     // Neighbor Cache
  aomdv_bcache   bihead;     // Broadcast ID Cache

  /*
   * Timers
   */
  AOMDVBroadcastTimer  btimer;
  AOMDVHelloTimer      htimer;
  AOMDVNeighborTimer   ntimer;
  AOMDVRouteCacheTimer rtimer;
  AOMDVLocalRepairTimer lrtimer;

  /*
   * Routing Table
   */
  aomdv_rtable    rtable;
  /*
   *  A "drop-front" queue used by the routing layer to buffer
   *  packets to which it does not have a route.
   */
  aomdv_rqueue   rqueue;

  /*
   * A mechanism for logging the contents of the routing
   * table.
   */
  Trace     *logtarget;

  /*
   * A pointer to the network interface queue that sits
   * between the "classifier" and the "link layer".
   */
  PriQueue  *AOMDVifqueue;

  /*
   * Logging stuff
   */
  void log_link_del(nsaddr_t dst);
  void log_link_broke(Packet *p);
  void log_link_kept(nsaddr_t dst);

  /* Manet*/
public: 
  double      xpos; 
  double      ypos; 
  double      zpos; 
  double      iEnergy; 
  MobileNode   *iNode;

  // AOMDV code
  int aomdv_max_paths_;
  int aomdv_prim_alt_path_len_diff_;
  // AODV ns-2.31 code
  /*	for passing packets up to agents */
  PortClassifier *dmux_;
};

#endif /* __aomdv_h__ */
