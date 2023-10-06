
static const uc_l2tp_nested_spec_t l2tp_tunnel_create_msg = {
  .headsize = 0,
  .nattrs = 5,
  .attrs = {
    { L2TP_ATTR_PROTO_VERSION, "proto_version", DT_, 0, NULL },
    { L2TP_ATTR_CONN_ID, "conn_id", DT_, 0, NULL },
    { L2TP_ATTR_PEER_CONN_ID, "peer_conn_id", DT_, 0, NULL },
    { L2TP_ATTR_ENCAP_TYPE, "encap_type", DT_, 0, NULL },
    { L2TP_ATTR_FD, "fd", DT_, 0, NULL },
  }
};

static const uc_l2tp_nested_spec_t l2tp_tunnel_delete_msg = {
  .headsize = 0,
  .nattrs = 2,
  .attrs = {
    { L2TP_ATTR_CONN_ID, "conn_id", DT_, 0, NULL },
    { L2TP_ATTR_SESSION_ID, "session_id", DT_, 0, NULL },
  }
};
static const uc_l2tp_nested_spec_t l2tp_session_create_msg = {
  .headsize = 0,
  .nattrs = 5,
  .attrs = {
    { L2TP_ATTR_CONN_ID, "conn_id", DT_, 0, NULL },
    { L2TP_ATTR_SESSION_ID, "session_id", DT_, 0, NULL },
    { L2TP_ATTR_PEER_SESSION_ID, "peer_session_id", DT_, 0, NULL },
    { L2TP_ATTR_PW_TYPE, "pw_type", DT_, 0, NULL },
    { L2TP_ATTR_IFNAME, "ifname", DT_, 0, NULL },
  }
};
static const uc_l2tp_nested_spec_t l2tp_session_delete_msg = {
  .headsize = 0,
  .nattrs = 1,
  .attrs = {
    { L2TP_ATTR_CONN_ID, "conn_id", DT_, 0, NULL },
  }
};
static const uc_l2tp_nested_spec_t l2tp_session_set_mtu_msg = {
  .headsize = 0,
  .nattrs = 3,
  .attrs = {
    { L2TP_ATTR_CONN_ID, "conn_id", DT_, 0, NULL },
    { L2TP_ATTR_SESSION_ID, "session_id", DT_, 0, NULL },
    { L2TP_ATTR_MTU, "mtu", DT_, 0, NULL },
  }
};
