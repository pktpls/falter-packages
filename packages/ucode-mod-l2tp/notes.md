
# ucode-mod-l2tp

## tunneldigger

context_process()

context_process_control_packet()

context_setup_tunnel()
L2TP_CMD_TUNNEL_CREATE {
  L2TP_ATTR_CONN_ID => ctx.tunnel_id
  L2TP_ATTR_PEER_CONN_ID => peer_tunnel_id
  L2TP_ATTR_PROTO_VERSION => 3
  L2TP_ATTR_ENCAP_TYPE => L2TP_ENCAPTYPE_UDP
  L2TP_ATTR_FD => ctx.fd
}
L2TP_CMD_SESSION_CREATE {
  L2TP_ATTR_CONN_ID => ctx.tunnel_id
  L2TP_ATTR_SESSION_ID => 1 or ctx.tunnel_id
  L2TP_ATTR_PEER_SESSION_ID =>  1 or peer_tunnel_id
  L2TP_ATTR_PW_TYPE => L2TP_PWTYPE_ETH
  L2TP_ATTR_IFNAME => ctx.tunnel_iface
}

context_session_set_mtu()
L2TP_CMD_SESSION_MODIFY {
  L2TP_ATTR_CONN_ID => ctx.tunnel_id
  L2TP_ATTR_SESSION_ID => 1
  L2TP_ATTR_MTU => mtu
}

context_delete_tunnel()
L2TP_CMD_SESSION_DELETE {
  L2TP_ATTR_CONN_ID => ctx.tunnel_id
  L2TP_ATTR_SESSION_ID => 1
}
L2TP_CMD_TUNNEL_DELETE {
  L2TP_ATTR_CONN_ID => ctx.tunnel_id
}

packet headers, ctrl types, state machine:
```
// L2TP data header overhead for calculating tunnel MTU; takes
// the following headers into account:
//
//   20 bytes (IP header)
//    8 bytes (UDP header)
//    4 bytes (L2TPv3 Session ID)
//    4 bytes (L2TPv3 Cookie)
//    4 bytes (L2TPv3 Pseudowire CE)
//   14 bytes (Ethernet)
//
#define L2TP_TUN_OVERHEAD 54

enum l2tp_ctrl_type {
  // Unreliable messages (0x00 - 0x7F).
  CONTROL_TYPE_COOKIE    = 0x01,
  CONTROL_TYPE_PREPARE   = 0x02,
  CONTROL_TYPE_ERROR     = 0x03,
  CONTROL_TYPE_TUNNEL    = 0x04,
  CONTROL_TYPE_KEEPALIVE = 0x05,
  CONTROL_TYPE_PMTUD     = 0x06,
  CONTROL_TYPE_PMTUD_ACK = 0x07,
  CONTROL_TYPE_REL_ACK   = 0x08,
  CONTROL_TYPE_PMTU_NTFY = 0x09,
  CONTROL_TYPE_USAGE     = 0x0A,
  // Reliable messages (0x80 - 0xFF).
  CONTROL_TYPE_LIMIT     = 0x80,
};

/* The state machine looks as follows:
   STATE_REINIT (initial state)
   When the FD is successfully initialized:
   -> STATE_RESOLVING
   When DNS resolving succeeds:
   -> STATE_GET_USAGE (sending a usage and a cookie request every 2s)
   when we receive usage information or a cookie
   -> STATE_STANBDY

   Now broker selection is performed; for the selected broker the main loop changes the state so
   that we go on:
   -> STATE_GET_COOKIE (sending a cookie request every 2s)
   when we receive the cookie
   -> STATE_GET_TUNNEL
   when we receive the tunnel information
   -> STATE_KEEPALIVE
   when the connection fails
   -> STATE_FAILED

   In case of an error, we transition to STATE_REINIT (if it happens early) or STATE_FAILED
   (if it happens when we are already >= STATE_GET_COOKIE).  The main loop restarts everything
   once the selected broker enters STATE_FAILED.
   For broken brokers, the main loop sets the state to STATE_FAILED to make sure that
   they do not do anything.
*/
enum l2tp_ctrl_state {
  STATE_REINIT,
  STATE_RESOLVING,
  STATE_GET_USAGE,
  STATE_STANBDY,
  STATE_GET_COOKIE,
  STATE_GET_TUNNEL,
  STATE_KEEPALIVE,
  STATE_FAILED,
};
```
