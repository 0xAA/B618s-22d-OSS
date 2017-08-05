/*
 * chap.h - Challenge Handshake Authentication Protocol definitions.
 *
 * Copyright (c) 1995 Eric Rosenquist, Strata Software Limited.
 * http://www.strataware.com/
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Eric Rosenquist.  The name of the author may not be used to
 * endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __CHAPMS_INCLUDE__

#define MD4_SIGNATURE_SIZE	16	/* 16 bytes in a MD4 message digest */
#define MAX_NT_PASSWORD	256	/* Maximum number of (Unicode) chars in an NT password */

#ifdef SUPPORT_ATP_PPTP_VPN
#define MS_CHAP_RESPONSE_LEN	49	/* Response length for MS-CHAP */
#define MS_CHAP2_RESPONSE_LEN	49	/* Response length for MS-CHAPv2 */
#define MS_AUTH_RESPONSE_LENGTH	40	/* MS-CHAPv2 authenticator response, */
					/* as ASCII */

/* E=eeeeeeeeee error codes for MS-CHAP failure messages. */
#define MS_CHAP_ERROR_RESTRICTED_LOGON_HOURS	646
#define MS_CHAP_ERROR_ACCT_DISABLED		647
#define MS_CHAP_ERROR_PASSWD_EXPIRED		648
#define MS_CHAP_ERROR_NO_DIALIN_PERMISSION	649
#define MS_CHAP_ERROR_AUTHENTICATION_FAILURE	691
#define MS_CHAP_ERROR_CHANGING_PASSWORD		709

/*
 * Offsets within the response field for MS-CHAP
 */
#define MS_CHAP_LANMANRESP	0
#define MS_CHAP_LANMANRESP_LEN	24
#define MS_CHAP_NTRESP		24
#define MS_CHAP_NTRESP_LEN	24
#define MS_CHAP_USENT		48

/*
 * Offsets within the response field for MS-CHAP2
 */
#define MS_CHAP2_PEER_CHALLENGE	0
#define MS_CHAP2_PEER_CHAL_LEN	16
#define MS_CHAP2_RESERVED_LEN	8
#define MS_CHAP2_NTRESP		24
#define MS_CHAP2_NTRESP_LEN	24
#define MS_CHAP2_FLAGS		48

#ifdef MPPE
#include "mppe.h"	/* MPPE_MAX_KEY_LEN */
extern u_char mppe_send_key[MPPE_MAX_KEY_LEN];
extern u_char mppe_recv_key[MPPE_MAX_KEY_LEN];
extern int mppe_keys_set;

/* These values are the RADIUS attribute values--see RFC 2548. */
#define MPPE_ENC_POL_ENC_ALLOWED 1
#define MPPE_ENC_POL_ENC_REQUIRED 2
#define MPPE_ENC_TYPES_RC4_40 2
#define MPPE_ENC_TYPES_RC4_128 4

/* used by plugins (using above values) */
extern void set_mppe_enc_types(int, int);
#endif

/* Are we the authenticator or authenticatee?  For MS-CHAPv2 key derivation. */
#define MS_CHAP2_AUTHENTICATEE 0
#define MS_CHAP2_AUTHENTICATOR 1

void ChapMS __P((u_char *, char *, int, u_char *));
void ChapMS2 __P((u_char *, u_char *, char *, char *, int,
		  u_char *, u_char[MS_AUTH_RESPONSE_LENGTH+1], int));
#ifdef MPPE
void mppe_set_keys __P((u_char *, u_char[MD4_SIGNATURE_SIZE]));
void mppe_set_keys2(u_char PasswordHashHash[MD4_SIGNATURE_SIZE],
		    u_char NTResponse[24], int IsServer);
#endif

void	ChallengeHash __P((u_char[16], u_char *, char *, u_char[8]));

void GenerateAuthenticatorResponse(u_char PasswordHashHash[MD4_SIGNATURE_SIZE],
			u_char NTResponse[24], u_char PeerChallenge[16],
			u_char *rchallenge, char *username,
			u_char authResponse[MS_AUTH_RESPONSE_LENGTH+1]);

void chapms_init(void);

#else
void ChapMS __P((chap_state *, char *, int, char *, int));
#endif

#define __CHAPMS_INCLUDE__
#endif /* __CHAPMS_INCLUDE__ */
