#ifndef __COMMON_H_
#define __COMMON_H_

#include "wifi_interface.h"
#include "linklist_interface.h"
//#include "network_manager.h"
//#include "checkap.h"
//#include "checksta.h"

typedef struct wifi_notify_msg_s {
	long msgtype;
	char msgtext[256];
} wifi_notify_msg_t;

struct eloop_event_p {
	char ctrl_iface_dir[32];
	void (*func)(int sock, void *eloop_ctx, void *sock_ctx);
};

//extern airkiss_operate_t airkiss_operate_state;
extern int get_client_pid(void *data);
extern char *get_client_name(void *data);
extern void getNameByPid(pid_t pid, char *task_name);
extern int reglist_compare_name(const void *s1, const void *s2);
extern int compare_int_sort(const void *s1, const void *s2);
extern int compare_priority(const void *s1, const void *s2);
extern struct node *find_max_node(List *list,int (*compare)(const void *, const void *));
extern unsigned char convert(struct node *n);
extern void print_list(List *list);
extern char *getipaddr(char *ifname);
extern char *getdefaultgw(char *gw, char *ctrl_if);
extern bool check_conn(char *name);
extern void stop_wifi_operate(void);
extern bool client_is_running(void *data);

/**
 * @brief string format of sta_status, for readable
 */
extern const char *sta_status_str[];
/**
 * @brief string format of event type, for readable
 */




/* wpa_supplicant fixed message prefixes */

/** Interactive request for identity/password/pin */
#define WPA_CTRL_REQ "CTRL-REQ-"

/** Response to identity/password/pin request */
#define WPA_CTRL_RSP "CTRL-RSP-"

/* Event messages with fixed prefix */
/** Authentication completed successfully and data connection enabled */
#define WPA_EVENT_CONNECTED "CTRL-EVENT-CONNECTED "
/** Disconnected, data connection is not available */
#define WPA_EVENT_DISCONNECTED "CTRL-EVENT-DISCONNECTED "
/** Association rejected during connection attempt */
#define WPA_EVENT_ASSOC_REJECT "CTRL-EVENT-ASSOC-REJECT "
/** wpa_supplicant is exiting */
#define WPA_EVENT_TERMINATING "CTRL-EVENT-TERMINATING "
/** Password change was completed successfully */
#define WPA_EVENT_PASSWORD_CHANGED "CTRL-EVENT-PASSWORD-CHANGED "
/** EAP-Request/Notification received */
#define WPA_EVENT_EAP_NOTIFICATION "CTRL-EVENT-EAP-NOTIFICATION "
/** EAP authentication started (EAP-Request/Identity received) */
#define WPA_EVENT_EAP_STARTED "CTRL-EVENT-EAP-STARTED "
/** EAP method proposed by the server */
#define WPA_EVENT_EAP_PROPOSED_METHOD "CTRL-EVENT-EAP-PROPOSED-METHOD "
/** EAP method selected */
#define WPA_EVENT_EAP_METHOD "CTRL-EVENT-EAP-METHOD "
/** EAP peer certificate from TLS */
#define WPA_EVENT_EAP_PEER_CERT "CTRL-EVENT-EAP-PEER-CERT "
/** EAP TLS certificate chain validation error */
#define WPA_EVENT_EAP_TLS_CERT_ERROR "CTRL-EVENT-EAP-TLS-CERT-ERROR "
/** EAP status */
#define WPA_EVENT_EAP_STATUS "CTRL-EVENT-EAP-STATUS "
/** EAP authentication completed successfully */
#define WPA_EVENT_EAP_SUCCESS "CTRL-EVENT-EAP-SUCCESS "
/** EAP authentication failed (EAP-Failure received) */
#define WPA_EVENT_EAP_FAILURE "CTRL-EVENT-EAP-FAILURE "
/** Network block temporarily disabled (e.g., due to authentication failure) */
#define WPA_EVENT_TEMP_DISABLED "CTRL-EVENT-SSID-TEMP-DISABLED "
/** Temporarily disabled network block re-enabled */
#define WPA_EVENT_REENABLED "CTRL-EVENT-SSID-REENABLED "
/** New scan started */
#define WPA_EVENT_SCAN_STARTED "CTRL-EVENT-SCAN-STARTED "
/** New scan results available */
#define WPA_EVENT_SCAN_RESULTS "CTRL-EVENT-SCAN-RESULTS "
/** wpa_supplicant state change */
#define WPA_EVENT_STATE_CHANGE "CTRL-EVENT-STATE-CHANGE "
/** A new BSS entry was added (followed by BSS entry id and BSSID) */
#define WPA_EVENT_BSS_ADDED "CTRL-EVENT-BSS-ADDED "
/** A BSS entry was removed (followed by BSS entry id and BSSID) */
#define WPA_EVENT_BSS_REMOVED "CTRL-EVENT-BSS-REMOVED "
/** Change in the signal level was reported by the driver */
#define WPA_EVENT_SIGNAL_CHANGE "CTRL-EVENT-SIGNAL-CHANGE "
/** Regulatory domain channel */
#define WPA_EVENT_REGDOM_CHANGE "CTRL-EVENT-REGDOM-CHANGE "

/** RSN IBSS 4-way handshakes completed with specified peer */
#define IBSS_RSN_COMPLETED "IBSS-RSN-COMPLETED "

/** Notification of frequency conflict due to a concurrent operation.
 *
 * The indicated network is disabled and needs to be re-enabled before it can
 * be used again.
 */
#define WPA_EVENT_FREQ_CONFLICT "CTRL-EVENT-FREQ-CONFLICT "
/** Frequency ranges that the driver recommends to avoid */
#define WPA_EVENT_AVOID_FREQ "CTRL-EVENT-AVOID-FREQ "
/** WPS overlap detected in PBC mode */
#define WPS_EVENT_OVERLAP "WPS-OVERLAP-DETECTED "
/** Available WPS AP with active PBC found in scan results */
#define WPS_EVENT_AP_AVAILABLE_PBC "WPS-AP-AVAILABLE-PBC "
/** Available WPS AP with our address as authorized in scan results */
#define WPS_EVENT_AP_AVAILABLE_AUTH "WPS-AP-AVAILABLE-AUTH "
/** Available WPS AP with recently selected PIN registrar found in scan results
 */
#define WPS_EVENT_AP_AVAILABLE_PIN "WPS-AP-AVAILABLE-PIN "
/** Available WPS AP found in scan results */
#define WPS_EVENT_AP_AVAILABLE "WPS-AP-AVAILABLE "
/** A new credential received */
#define WPS_EVENT_CRED_RECEIVED "WPS-CRED-RECEIVED "
/** M2D received */
#define WPS_EVENT_M2D "WPS-M2D "
/** WPS registration failed after M2/M2D */
#define WPS_EVENT_FAIL "WPS-FAIL "
/** WPS registration completed successfully */
#define WPS_EVENT_SUCCESS "WPS-SUCCESS "
/** WPS enrollment attempt timed out and was terminated */
#define WPS_EVENT_TIMEOUT "WPS-TIMEOUT "
/* PBC mode was activated */
#define WPS_EVENT_ACTIVE "WPS-PBC-ACTIVE "
/* PBC mode was disabled */
#define WPS_EVENT_DISABLE "WPS-PBC-DISABLE "

#define WPS_EVENT_ENROLLEE_SEEN "WPS-ENROLLEE-SEEN "

#define WPS_EVENT_OPEN_NETWORK "WPS-OPEN-NETWORK "

/* WPS ER events */
#define WPS_EVENT_ER_AP_ADD "WPS-ER-AP-ADD "
#define WPS_EVENT_ER_AP_REMOVE "WPS-ER-AP-REMOVE "
#define WPS_EVENT_ER_ENROLLEE_ADD "WPS-ER-ENROLLEE-ADD "
#define WPS_EVENT_ER_ENROLLEE_REMOVE "WPS-ER-ENROLLEE-REMOVE "
#define WPS_EVENT_ER_AP_SETTINGS "WPS-ER-AP-SETTINGS "
#define WPS_EVENT_ER_SET_SEL_REG "WPS-ER-AP-SET-SEL-REG "

#endif
