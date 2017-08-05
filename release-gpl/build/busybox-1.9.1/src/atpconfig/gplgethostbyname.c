
#include <features.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <resolv.h>
#include <netdb.h>
#include <ctype.h>
#include <arpa/nameser.h>
#include <sys/utsname.h>
#include <sys/un.h>
#include <time.h>
#include "atpconfig.h"


#define ATP_NAME_RESOLVE_HAS_IPV6

 
#define RECVRTRYTIMES  20     //TCP 接收重试次数
#define REPLY_TIMEOUT 5
#define REPLY_TIMEOUT_SEC 6
#define REPLY_ONE_TIMEOUT_MS 100   /*100ms*/
#define REPLY_ONE_TIMEOUT_USEC 1000   /*1000us*/
#define REPLY_TIMEOUT_USEC 500000
#define MAX_RETRIES 1

#define MAX_ALIASES    5

#define RESULT_OK   0
#define RESULT_NOK  (-1)
/* 1:ip + 1:full + MAX_ALIASES:aliases + 1:NULL */
#define     ALIAS_DIM        (2 + MAX_ALIASES + 1)

#ifndef PACKETSZ
#define PACKETSZ            512
#endif
#ifndef MAXDNAME
#define MAXDNAME            1025
#endif
#ifndef NAMESERVER_PORT
#define NAMESERVER_PORT     53
#endif
#ifndef HFIXEDSZ
#define    HFIXEDSZ            12
#endif
#ifndef RRFIXEDSZ
#define RRFIXEDSZ            10
#endif
#ifndef T_AAAA
#define T_AAAA                28    /* Ip6 Address. */
#endif
#ifndef T_A
#define T_A             1
#endif
#ifndef T_SIG
#define T_SIG           24          /* digital signature (RFC 2535) */
#endif
#ifndef TCPPACKETSZ
#define TCPPACKETSZ            1500 /*mtu*/
#endif

#undef DEBUG
//#define DEBUG
/* #define DEBUG */

#ifdef DEBUG
#define DPRINTF(X,args...) fprintf(stderr, X, ##args)
#else
#define DPRINTF(X,args...)
#endif /* DEBUG */


/* Global stuff (stuff needing to be locked to be thread safe)... */

/* Structs */
struct resolv_header
{
    int id;
    int qr, opcode, aa, tc, rd, ra, rcode;
    int qdcount;
    int ancount;
    int nscount;
    int arcount;
};

struct resolv_question
{
    char* dotted;
    int qtype;
    int qclass;
};

struct resolv_answer
{
    char* dotted;
    int atype;
    int aclass;
    int ttl;
    int rdlength;
    unsigned char* rdata;
    int rdoffset;
    char* buf;
    size_t buflen;
    size_t add_count;
};

/* function prototypes */
static int handy_dns_lookup(const char* name, int type,
                            unsigned char** outpacket, struct resolv_answer* a,
                            char* wanaddr);

static int handy_encode_dotted(const char* dotted, unsigned char* dest, int maxlen);
static int handy_decode_dotted(const unsigned char* message, int offset,
                               char* dest, int maxlen);
static int handy_length_dotted(const unsigned char* message, int offset);
static int handy_encode_header(struct resolv_header* h, unsigned char* dest, int maxlen);
static int handy_decode_header(unsigned char* data, struct resolv_header* h);
static int handy_encode_question(struct resolv_question* q,
                                 unsigned char* dest, int maxlen);
static int handy_decode_answer(unsigned char* message, int offset,
                               struct resolv_answer* a);
static int handy_length_question(unsigned char* message, int offset);

static int handy_encode_header(struct resolv_header* h, unsigned char* dest, int maxlen)
{

    if (maxlen < HFIXEDSZ)
    { return -1; }

    dest[0] = (h->id & 0xff00) >> 8;
    dest[1] = (h->id & 0x00ff) >> 0;
    dest[2] = (h->qr ? 0x80 : 0) |
              ((h->opcode & 0x0f) << 3) |
              (h->aa ? 0x04 : 0) |
              (h->tc ? 0x02 : 0) |
              (h->rd ? 0x01 : 0);
    dest[3] = (h->ra ? 0x80 : 0) | (h->rcode & 0x0f);
    dest[4] = (h->qdcount & 0xff00) >> 8;
    dest[5] = (h->qdcount & 0x00ff) >> 0;
    dest[6] = (h->ancount & 0xff00) >> 8;
    dest[7] = (h->ancount & 0x00ff) >> 0;
    dest[8] = (h->nscount & 0xff00) >> 8;
    dest[9] = (h->nscount & 0x00ff) >> 0;
    dest[10] = (h->arcount & 0xff00) >> 8;
    dest[11] = (h->arcount & 0x00ff) >> 0;

    return HFIXEDSZ;
}

static int handy_decode_header(unsigned char* data, struct resolv_header* h)
{


    h->id = (data[0] << 8) | data[1];
    h->qr = (data[2] & 0x80) ? 1 : 0;
    h->opcode = (data[2] >> 3) & 0x0f;
    h->aa = (data[2] & 0x04) ? 1 : 0;
    h->tc = (data[2] & 0x02) ? 1 : 0;
    h->rd = (data[2] & 0x01) ? 1 : 0;
    h->ra = (data[3] & 0x80) ? 1 : 0;
    h->rcode = data[3] & 0x0f;
    h->qdcount = (data[4] << 8) | data[5];
    h->ancount = (data[6] << 8) | data[7];
    h->nscount = (data[8] << 8) | data[9];
    h->arcount = (data[10] << 8) | data[11];

    return HFIXEDSZ;
}

/* Encode a dotted string into nameserver transport-level encoding.
   This routine is fairly dumb, and doesn't attempt to compress
   the data */

static int handy_encode_dotted(const char* dotted, unsigned char* dest, int maxlen)
{
    int used = 0;
    char* c;
    int l;

    while (dotted && *dotted)
    {
        c = (char*)strchr(dotted, '.');
        l = c ? c - dotted : (int)strlen(dotted);

        if (l >= ((maxlen - used) - 1))
        { return -1; }

        dest[used++] = (unsigned char)l;
        memcpy(dest + used,  dotted, (size_t)l);
        used += l;

        if (c)
        { dotted = c + 1; }
        else
        { break; }
    }

    if (maxlen < 1)
    { return -1; }

    dest[used++] = 0;

    return used;
}

/* Decode a dotted string from nameserver transport-level encoding.
   This routine understands compressed data. */

static int handy_decode_dotted(const unsigned char* data, int offset,
                               char* dest, int maxlen)
{
    int l;
    int measure = 1;
    int total = 0;
    int used = 0;

    if (!data)
    { return -1; }

    while (0 != (l = data[offset++]))
    {
        if (measure)
        { total++; }
        if ((l & 0xc0) == (0xc0))
        {
            if (measure)
            { total++; }
            /* compressed item, redirect */
            offset = ((l & 0x3f) << 8) | data[offset];
            measure = 0;
            continue;
        }

        if ((used + l + 1) >= maxlen)
        { return -1; }

        memcpy(dest + used, data + offset, (size_t)l);
        offset += l;
        used += l;
        if (measure)
        { total += l; }

        if (data[offset] != 0)
        { dest[used++] = '.'; }
        else
        { dest[used++] = '\0'; }
    }

    /* The null byte must be counted too */
    if (measure)
    {
        total++;
    }

    DPRINTF("Total decode len = %d\n", total);

    return total;
}

static int handy_length_dotted(const unsigned char* data, int offset)
{
    int orig_offset = offset;
    int l;

    if (!data)
    { return -1; }

    while (0 != (l = data[offset++]))
    {

        if ((l & 0xc0) == (0xc0))
        {
            offset++;
            break;
        }

        offset += l;
    }

    return offset - orig_offset;
}

static int handy_encode_question(struct resolv_question* q,
                                 unsigned char* dest, int maxlen)
{
    int i;
#ifdef ATP_PCLINT
    q = q;
#endif

    i = handy_encode_dotted(q->dotted, dest, maxlen);
    if (i < 0)
    { return i; }

    dest += i;
    maxlen -= i;

    if (maxlen < 4)
    { return -1; }

    dest[0] = (q->qtype & 0xff00) >> 8;
    dest[1] = (q->qtype & 0x00ff) >> 0;
    dest[2] = (q->qclass & 0xff00) >> 8;
    dest[3] = (q->qclass & 0x00ff) >> 0;

    return i + 4;
}

static int handy_length_question(unsigned char* message, int offset)
{
    int i;
#ifdef ATP_PCLINT
    message = message;
#endif

    i = handy_length_dotted(message, offset);
    if (i < 0)
    { return i; }

    return i + 4;
}

static int handy_decode_answer(unsigned char* message, int offset,
                               struct resolv_answer* a)
{
    char temp[256] = {0};
    int i;

    i = handy_decode_dotted(message, offset, temp, sizeof(temp));
    if (i < 0)
    { return i; }

    message += offset + i;

    a->dotted = strdup(temp);
    a->atype = (message[0] << 8) | message[1];
    message += 2;
    a->aclass = (message[0] << 8) | message[1];
    message += 2;
    a->ttl = (message[0] << 24) |
             (message[1] << 16) | (message[2] << 8) | (message[3] << 0);
    message += 4;
    a->rdlength = (message[0] << 8) | message[1];
    message += 2;
    a->rdata = message;
    a->rdoffset = offset + i + RRFIXEDSZ;

    DPRINTF("i=%d,rdlength=%d\n", i, a->rdlength);

    return i + RRFIXEDSZ + a->rdlength;
}

#define LOOP_ADDR "127.0.0.1"
#define DNS_PACKET_LEN_MAX (512)
#define CHECK_RET(x) {if ((x) < 0){DPRINTF("%s %d fail\r\n", __func__, __LINE__); break;}}

static int BuildQuery(const char* pcName, int ulType, unsigned char* pucPacket, unsigned int* pulLen)
{
    int                     lQueryID = -1;
    int                     lRet = -1;
    struct resolv_header    stHead;
    struct resolv_question  stQuest;
    struct resolv_answer    stAnswer;
    char                    acQueryName[MAXDNAME] = {0};
    unsigned int            ulLen = 0;

    lQueryID = time(NULL) + 1;
    lQueryID &= 0xffff;

    memset(&stHead,  0, sizeof(stHead));
    memset(&stQuest,  0, sizeof(stQuest));
    memset(&stAnswer, 0, sizeof(stAnswer));

    /*构造头部*/
    stHead.id = lQueryID;
    stHead.qdcount = 1;
    stHead.rd = 1;
    lRet = handy_encode_header(&stHead, pucPacket, PACKETSZ);
    if (lRet < 0)
    {
        return -1;
    }
    ulLen += lRet;

    /*构造查询部分*/
    snprintf(acQueryName, sizeof(acQueryName), "%s", pcName);
    stQuest.dotted = (char*)acQueryName;
    stQuest.qtype = ulType;
    stQuest.qclass = 1;

    lRet = handy_encode_question(&stQuest, pucPacket + ulLen, PACKETSZ - ulLen);
    if (lRet < 0)
    {
        return -1;
    }
    ulLen += lRet;

    *pulLen = ulLen;
    return 0;
}

static int RecvReply(int lfd, unsigned char* pucPacket)
{
    fd_set          stfds;
    struct timeval  stTime;

    FD_ZERO(&stfds);
    FD_SET(lfd, &stfds);
    stTime.tv_sec = REPLY_TIMEOUT_SEC;
    stTime.tv_usec = REPLY_TIMEOUT_USEC;
    if (select(lfd + 1, &stfds, NULL, NULL, &stTime) <= 0)
    {
        DPRINTF("%s %d\r\n", __func__, __LINE__);
        return -1;
    }
    if (recv(lfd, pucPacket, DNS_PACKET_LEN_MAX, 0) < HFIXEDSZ)
    {
        DPRINTF("%s %d\r\n", __func__, __LINE__);
        return -1;
    }
    return 0;
}

/*检查Name 和 Type*/
static int GetType(unsigned char* pucPacket, const char* pcName, unsigned short* pusType)
{
    struct resolv_header    stHead;
    unsigned int            ulPos = 0;
    int                     lRet = -1;
    char                    acQueryName[MAXDNAME] = {0};
    unsigned short          usQueryType = 0;

    memset(&stHead,  0, sizeof(stHead));

    handy_decode_header(pucPacket, &stHead);
    if ((stHead.qr != 1) || (stHead.qdcount != 1))
    {
        DPRINTF("\n");
        return -1;
    }

    /*check name*/
    ulPos = HFIXEDSZ;
    handy_decode_dotted(pucPacket, ulPos, acQueryName, sizeof(acQueryName));
    if (0 != strcasecmp(pcName, acQueryName))
    {
        DPRINTF("%s, %s\n", pcName, acQueryName);
        return -1;
    }
    lRet = handy_length_dotted(pucPacket, ulPos);
    if (lRet < 0)
    {
        return -1;
    }
    ulPos += lRet;

    /*check type*/
    usQueryType = ntohs(*((unsigned short*)(pucPacket + ulPos)));
    if ((usQueryType != T_A) && (usQueryType != T_AAAA))
    {
        DPRINTF("%d \n", usQueryType);
        return -1;
    }
    *pusType = usQueryType;
    return 0;
}

static int ResolvReply(unsigned char* pucPacket, unsigned int ulPacketLen, unsigned short usType, struct resolv_answer* pstResolv)
{
    unsigned int            ulPos = 0;
    unsigned int            j = 0;
    struct resolv_header    stHead;
    int                     lRet = -1;
    unsigned int            ulFirstAnswer = 1;
    struct resolv_answer    stAnswer;

    memset(&stHead,  0, sizeof(stHead));
    memset(&stAnswer,  0, sizeof(stAnswer));

    handy_decode_header(pucPacket, &stHead);

    if ((stHead.rcode > 0) || (stHead.ancount < 1))
    {
        /* negative result, not present */
        return -1;
    }

    ulPos = HFIXEDSZ;

    lRet = handy_length_question(pucPacket, ulPos);
    if (lRet < 0)
    {
        return -1;
    }
    ulPos += lRet;
    DPRINTF("Decoding answer at pos %d\n", ulPos);

    for (j = 0; j < (unsigned int)stHead.ancount; j++, ulPos += (unsigned int)lRet)
    {
        if (ulPos >= ulPacketLen)
        {
            DPRINTF("invalid pos [%u]\n", ulPos);
            if (NULL != stAnswer.dotted)
            {
                free(stAnswer.dotted);
                stAnswer.dotted = NULL;
            }
            return -1;
        }
        memset(&stAnswer,  0, sizeof(stAnswer));
        lRet = handy_decode_answer(pucPacket, ulPos, &stAnswer);

        if (lRet < 0)
        {
            DPRINTF("failed decode\n");
            if (NULL != stAnswer.dotted)
            {
                free(stAnswer.dotted);
                stAnswer.dotted = NULL;
            }
            return -1;
        }

        if (ulFirstAnswer)
        {
            stAnswer.buf = pstResolv->buf;
            stAnswer.buflen = pstResolv->buflen;
            stAnswer.add_count = pstResolv->add_count;
            memcpy(pstResolv,  &stAnswer, sizeof(stAnswer));
            if ((pstResolv->atype != T_SIG) && (0 == pstResolv->buf))
            {
                break;
            }
            if (pstResolv->atype != (int)usType)
            {
                if (NULL != pstResolv->dotted)
                {
                    free(pstResolv->dotted);
                    pstResolv->dotted = NULL;
                }
                continue;
            }
            pstResolv->add_count = (size_t)((stHead.ancount - j) - 1);
            if (((size_t)pstResolv->rdlength + sizeof(struct in_addr*)) *pstResolv->add_count > pstResolv->buflen)
            {
                break;
            }
            pstResolv->add_count = 0;
            ulFirstAnswer = 0;
        }
        else
        {
            if (NULL != stAnswer.dotted)
            {
                free(stAnswer.dotted);
                stAnswer.dotted = NULL;
            }

            if (stAnswer.atype != (int)usType)
            {
                continue;
            }
            if (pstResolv->rdlength != stAnswer.rdlength)
            {
                if (NULL != pstResolv->dotted)
                {
                    free(pstResolv->dotted);
                    pstResolv->dotted = NULL;
                }
                DPRINTF("Answer address len(%u) differs from original(%u)\n",
                        stAnswer.rdlength, pstResolv->rdlength);
                return -1;
            }
            /*目标地址的buffer大小不易计算，先用stAnswer.rdlength作为buffer大小，解决coverity*/
            memcpy(pstResolv->buf + (pstResolv->add_count * ((size_t)stAnswer.rdlength)),
                stAnswer.rdata, (size_t)stAnswer.rdlength);
            ++pstResolv->add_count;

            if (pstResolv->add_count >= 7)
            {
                DPRINTF("8 records at most.\n");
                break;
            }
        }
    }
    return 0;
}

//lint -save -e826
static int resolv_v4(unsigned char* pucPacket,
                     unsigned int ulPacketLen,
                     const char* name,
                     struct hostent* result_buf,
                     char* buf,
                     size_t buflen,
                     struct hostent** result,
                     struct resolv_answer* pA)
{
    struct in_addr* in;
    struct in_addr** addr_list;
    char** alias;

    int i;

    *result = NULL;
    if (!name)
    { return EINVAL; }

    if (buflen < sizeof(*in))
    { return ERANGE; }
    in = (struct in_addr*)buf;
    buf += sizeof(*in);
    buflen -= sizeof(*in);

    if (buflen < sizeof(*addr_list) * 2)
    { return ERANGE; }
    addr_list = (struct in_addr**)buf;
    buf += sizeof(*addr_list) * 2;
    buflen -= sizeof(*addr_list) * 2;

    addr_list[0] = in;
    addr_list[1] = 0;

    if (buflen < sizeof(char*) * (ALIAS_DIM))
    { return ERANGE; }
    alias = (char**)buf;
    buf += sizeof(char**) * (ALIAS_DIM);
    buflen -= sizeof(char**) * (ALIAS_DIM);

    if (buflen < 256)
    {
        return ERANGE;
    }
    snprintf(buf,  buflen, "%s", name);

    alias[0] = buf;
    alias[1] = NULL;

    /* First check if this is already an address */
    if (inet_aton(name, in))
    {
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        result_buf->h_aliases = alias;
        *result = result_buf;
        return NETDB_SUCCESS;
    }

    pA->buf = buf;
    pA->buflen = buflen;
    pA->add_count = 0;

    i = ResolvReply(pucPacket, ulPacketLen, T_A, pA);
    if (i < 0)
    {
        DPRINTF("handy_dns_lookup\n");
        return TRY_AGAIN;
    }

    if (((size_t)pA->rdlength + sizeof(struct in_addr*)) * pA->add_count + 256 > buflen)
    {
        free(pA->dotted);
        pA->dotted = NULL;
        DPRINTF("buffer too small for all addresses\n");
        return ERANGE;
    }
    else if (pA->add_count > 0)
    {
        memmove(buf - sizeof(struct in_addr*) * 2,  buf, pA->add_count * ((size_t)pA->rdlength));
        addr_list = (struct in_addr**)(buf + pA->add_count * ((size_t)pA->rdlength));
        addr_list[0] = in;
        for (i = (int)pA->add_count - 1; i >= 0; --i)
        { addr_list[i + 1] = (struct in_addr*)((buf - sizeof(struct in_addr*) * 2) + pA->rdlength * i); }
        addr_list[pA->add_count + 1] = 0;
        buflen -= (size_t)(((char*) & (addr_list[pA->add_count + 2])) - buf);
        buf = (char*)&addr_list[pA->add_count + 2];
    }
    if (NULL != pA->dotted)
    {
        snprintf(buf,  buflen, "%s", pA->dotted);
        free(pA->dotted);
        pA->dotted = NULL;
    }


    if (pA->atype == 1)   /* ADDRESS T_A=1 */
    {
        memcpy(in,  pA->rdata, sizeof(*in));
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        result_buf->h_aliases = alias; /* TODO: generate the full list */
        *result = result_buf;
        return NETDB_SUCCESS;
    }
    return TRY_AGAIN;
}

static int resolv_v6(unsigned char* pucPacket,
                     unsigned int ulPacketLen,
                     const char* name,
                     struct hostent* result_buf,
                     char* buf, size_t buflen,
                     struct hostent** result,
                     struct resolv_answer* pA)
{
    struct in6_addr* in;
    struct in6_addr** addr_list;
    int i;
    struct in6_addr stAddr;

    memset(&stAddr,  0, sizeof(struct in6_addr));

    *result = NULL;

    if (!name)
    { return EINVAL; }

    if (buflen < sizeof(*in))
    { return ERANGE; }
    in = (struct in6_addr*)buf;
    buf += sizeof(*in);
    buflen -= sizeof(*in);

    if (buflen < sizeof(*addr_list) * 2)
    { return ERANGE; }
    addr_list = (struct in6_addr**)buf;
    buf += sizeof(*addr_list) * 2;
    buflen -= sizeof(*addr_list) * 2;

    addr_list[0] = in;
    addr_list[1] = 0;

    if (buflen < 256)
    {
        return ERANGE;
    }
    snprintf(buf,  buflen, "%s", name);

    /* First check if this is already an address */
    if (inet_pton(AF_INET6, name, in))
    {
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET6;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        *result = result_buf;
        return NETDB_SUCCESS;
    }


    pA->buf = buf;
    pA->buflen = buflen;

    i = ResolvReply(pucPacket, ulPacketLen, T_AAAA, pA);
    if (i < 0)
    {
        DPRINTF("handy_dns_lookup\n");
        return TRY_AGAIN;
    }

    if (((size_t)pA->rdlength + sizeof(struct in6_addr*)) * pA->add_count + 256 > buflen)
    {
        free(pA->dotted);
        pA->dotted = NULL;
        DPRINTF("buffer too small for all addresses\n");
        return ERANGE;
    }
    else if (pA->add_count > 0)
    {
        memmove(buf - sizeof(struct in6_addr*) * 2, 
            buf, pA->add_count * ((size_t)pA->rdlength));
        addr_list = (struct in6_addr**)(buf + pA->add_count * (size_t)pA->rdlength);
        addr_list[0] = in;
        for (i = (int)pA->add_count - 1; i >= 0; --i)
        { addr_list[i + 1] = (struct in6_addr*)((buf - sizeof(struct in6_addr*) * 2) + pA->rdlength * i); }
        addr_list[pA->add_count + 1] = 0;
        buflen -= (size_t)(((char*) & (addr_list[pA->add_count + 2])) - buf);
        buf = (char*)&addr_list[pA->add_count + 2];
    }

    if (NULL != pA->dotted)
    {
        snprintf(buf, buflen, "%s", pA->dotted);
        free(pA->dotted);
        pA->dotted = NULL;
    }


    if (pA->atype == T_AAAA)      /* ADDRESS */
    {
        memcpy(in, pA->rdata, sizeof(*in));
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET6;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        DPRINTF("%p\n", result_buf);
        *result = result_buf;
        return NETDB_SUCCESS;
    }
    return TRY_AGAIN;
}
//lint -restore



/***********************************************************
  Function:     tcp_client_close
  Description:  关闭TCP连接
  Input:        fd  socket句柄
                
  Output:       无
  Return:       void
************************************************************/
static void tcp_client_close(int fd)
{ 
    if(-1 != fd)
    {
        (void)close(fd);
    }
    return; 
}


/***********************************************************
  Function:     tcp_v4client_init
  Description:  建立IPv4 TCP连接
  Input:        pIP 需要连接的IP地址
                port 端口号
                fd  socket句柄
  Output:       无
  Return:       RESULT_OK成功 RESULT_NOK失败
  Others:
************************************************************/
static int tcp_v4client_init(const char *pIP, const int port, int *fd)
{
    struct sockaddr_in cli;

    memset(&cli,  0, sizeof(struct sockaddr_in));
    if ((NULL == pIP) || (NULL == fd))
    {
        return RESULT_NOK;
    }

    cli.sin_family = AF_INET;
    cli.sin_port = htons(port);
    cli.sin_addr.s_addr = inet_addr(pIP);
   
    *fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(*fd < 0)
    {
        DPRINTF("v4 socket() failure,errornum = %d.\n", errno);
        return RESULT_NOK; 
    }

    if(connect(*fd, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        tcp_client_close(*fd);
        DPRINTF("v4 connect() failure,errornum = %d.\n", errno);
        return RESULT_NOK;
    }

    return RESULT_OK;
}

/***********************************************************
  Function:     tcp_v6client_init
  Description:  建立IPv6 TCP连接
  Input:        pIP 需要连接的IP地址
                port 端口号
                fd  socket句柄
  Output:       无
  Return:       RESULT_OK成功 RESULT_NOK失败
************************************************************/
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
static int tcp_v6client_init(const char *pIP, const int port, int *fd)
{
    struct sockaddr_in6 cli;

    if ((NULL == pIP) || (NULL == fd))
    {
        return RESULT_NOK;
    }

    memset(&cli, 0, sizeof(struct sockaddr_in6));
    cli.sin6_family = AF_INET6;
    cli.sin6_port = htons(port);
    (void)inet_pton(AF_INET6, pIP, &cli.sin6_addr);/*need check return value?*/
    
    *fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if(*fd < 0)
    {
        DPRINTF("v6 socket() failure,errornum = %d.\n", errno);
        return RESULT_NOK; 
    }
    
    if(connect(*fd, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        tcp_client_close(*fd);
        DPRINTF("v6 connect() failure,errornum = %d.\n", errno);
        return RESULT_NOK;
    }

    return RESULT_OK;
}
#endif
/***********************************************************
  Function:     tcp_client_send
  Description:  TCP发送数据
  Input:        buf 需要发送的数据
                len 发送数据的长度
                fd  socket句柄
  Output:       无
  Return:       RESULT_OK成功 RESULT_NOK失败
************************************************************/
static int tcp_client_send(unsigned char *buf, unsigned int len, int fd)
{
    int sendLen = 0;
    unsigned int sendbuflen = 0;
    int tmperrno = 0;

    if (NULL == buf)
    {
        return RESULT_NOK;
    }
    while (sendbuflen < len)
    {
        sendLen = send(fd, buf + sendbuflen, len - sendbuflen, 0);
        tmperrno = errno;
        if (0 < sendLen)
        {
            sendbuflen += sendLen;
        }
        else if(0 == sendLen)
        {
            return RESULT_NOK;
        }
        else
        {
            /*Wsocket 异常处理*/
            if ((EINTR == tmperrno) 
                || (EAGAIN == tmperrno)
                || (EWOULDBLOCK == tmperrno))
            {
                DPRINTF("\n %s continue write err:%s \n", __FUNCTION__, strerror(tmperrno));
                continue;
            }
            
            DPRINTF("%s write nok err:%s \n", __FUNCTION__, strerror(tmperrno));
            return RESULT_NOK;
        }
    }

    return RESULT_OK;
}

/***********************************************************
  Function:     tcp_client_recv
  Description:  TCP接收数据
  Input:        buf 接收数据的缓存
                len 接收数据缓存大小
                fd  socket句柄
  Output:       无
  Return:       RESULT_OK成功 RESULT_NOK失败
************************************************************/
static int tcp_client_recv(unsigned char *buf, int len, int fd)
{
    int lReadLen = 0;
    int retry_times = RECVRTRYTIMES;
    int tmperrno = 0;
    
    if (NULL == buf)
    {
        return RESULT_NOK;
    }
    
    while (1)
    {
        lReadLen = recv(fd, buf, len, 0);
        tmperrno = errno;

        if (0 == lReadLen)
        {
            /*超时*/
            DPRINTF( "read Rdsocket timeout" );
            return RESULT_NOK;
        }
        else if (0 > lReadLen)
        {
            /*Rdsocket 异常处理*/
            if ((EINTR == tmperrno) 
                || (EAGAIN == tmperrno)
                || (EWOULDBLOCK == tmperrno))
            {
                DPRINTF( "read Rdsocket err:%s", strerror(tmperrno));
                if (0 == retry_times)
                {
                    DPRINTF("recv over after 20 times.\n");
                    return RESULT_NOK;
                }
                else
                {
                    retry_times--;
                    continue;
                }
            }

            DPRINTF( "read Rdsocket err:%s", strerror(tmperrno));
            return RESULT_NOK;
        }
        else
        {
            break;//数据接收成功
        }
    }

    return RESULT_OK;
}


/***********************************************************
  Function:     dns_tcp_lookup
  Description:  建立TCP连接进行DNS域名解析请求
  Input:        package DNS请求报文
                buflen package的缓存大小
                
                pkglen package的缓存大小的实际请求报文长度
                addr DNS服务器地址
                supportV6 标识是否支持IPV6
  Output:       package DNS回复报文
  Return:       RESULT_NOK 请求DNS解析失败
                RESULT_OK  请求DNS解析成功
************************************************************/
static int dns_tcp_lookup(unsigned char *package, int buflen, unsigned int pkglen, const char *addr, int supportV6)
{
    int ret = RESULT_NOK;
    int i = 0;
    struct timeval tv;
    fd_set fds;
    int tcpclientsk = -1;

    memset(&tv,  0, sizeof(struct timeval));
    
    if ((NULL == package) || (NULL == addr))
    {
        DPRINTF("tcp dns: package or addr is NULL.\n");
        return ret;
    }

    /*建立TCP连接*/
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
    if (supportV6) 
    {
        ret = tcp_v6client_init(addr, NAMESERVER_PORT, &tcpclientsk);
        if (RESULT_NOK == ret)
        {
            DPRINTF("tcp dns: v6 socket init failed\n");
            return ret;
        }
    } 
    else 
    {
#endif
        ret = tcp_v4client_init(addr, NAMESERVER_PORT, &tcpclientsk);
        if (RESULT_NOK == ret)
        {
            DPRINTF("tcp dns: v4 socket init failed\n");
            return ret;
        }

#ifdef ATP_NAME_RESOLVE_HAS_IPV6
    }
#endif



    /*发动DNS报文*/
    ret = tcp_client_send(package, pkglen, tcpclientsk);
    if (RESULT_NOK == ret)
    {
        DPRINTF("tcp dns: tcp send dns package failed\n");
        tcp_client_close(tcpclientsk);
        return ret;
    }

    /*监测socket句柄状态，如果状态为可写，则开始接收报文*/
    for ( i = 0; i < REPLY_TIMEOUT * REPLY_ONE_TIMEOUT_USEC; i += REPLY_ONE_TIMEOUT_MS )
    {
        FD_ZERO(&fds);
        FD_SET(tcpclientsk, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = REPLY_ONE_TIMEOUT_MS * REPLY_ONE_TIMEOUT_USEC;

        ret = select(tcpclientsk + 1, &fds, NULL, NULL, &tv);         
        if ( ret > 0 )
        {
            break;
        }            
    }

    if (ret <= 0)
    {
        DPRINTF("tcp dns: select failed, no response from server.\n");
        ret = RESULT_NOK;
    }
    else
    {
        /*接收dns respose报文*/
        ret = tcp_client_recv(package, buflen, tcpclientsk);
        if (RESULT_OK == ret)
        {
            DPRINTF("tcp dns: recv success.\n");
        }
        else
        {
            DPRINTF("tcp dns: recv failed.\n");
        }
    }

    tcp_client_close(tcpclientsk);
    return ret;
}
//lint -save -e801
//lint -save -e593
static int handy_dns_lookup(const char* name, int type,
                            unsigned char** outpacket, struct resolv_answer* a,
                            char* wanaddr)
{
    int i, j, len, fd, pos, rc;
    struct timeval tv;
    fd_set fds;
    struct resolv_header h;
    struct resolv_question q;
    struct resolv_answer ma;
    struct sockaddr_in  bindAddr;
    struct in_addr inaddr;
    int first_answer = 1;
    int retries = 0;
    unsigned char* packet = malloc(PACKETSZ);
    unsigned char *udppacket_copy = malloc(PACKETSZ);
    unsigned char *tmp_udppacket = NULL;
    unsigned char *tcppacket = NULL;
    unsigned char *tmptcppacket = NULL;
    unsigned char *tmp_resultpacket = NULL;
    unsigned short *tmppacket = 0;
    unsigned int dns_len = 0;
    int ret = -1;
    char* dns, *lookup = malloc(MAXDNAME);
    int local_id = -1;
    struct sockaddr_in sa;
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
    int v6;
    struct sockaddr_in6 sa6;
    struct sockaddr_in6  bindAddr6;
    int record_flag = 0;
#endif


    fd = -1;
    memset(&sa,  0, sizeof(sa));
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
    memset(&sa6,  0, sizeof(sa6));
#endif

    if (!packet || !lookup)
    { goto fail; }

    DPRINTF("Looking up type %d answer for '%s'\n", type, name);
    local_id = time(NULL);

    ++local_id;
    local_id &= 0xffff;

    while (retries < MAX_RETRIES)
    {
        tmp_udppacket = NULL;
        memset(packet,  0, PACKETSZ);
        memset(&h,  0, sizeof(h));

        h.id = local_id;
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
        if (NULL == wanaddr)
        {

            if (T_AAAA == type)
            {
                if (!record_flag)
                {
                    dns = "::1";
                }
                else
                {
                    dns = "127.0.0.1";
                }
            }
            else
            {
                if (!record_flag)
                {
                    dns = "127.0.0.1";
                }
                else
                {
                    dns = "::1";
                }
            }
        }
        else if (inet_pton(AF_INET6, wanaddr, &sa6.sin6_addr) > 0)
        {
            dns = "::1";
        }
        else
        {
            dns = "127.0.0.1";
        }
#else
        dns = "127.0.0.1";
#endif
        DPRINTF("got server %s\n", dns);


        h.qdcount = 1;
        h.rd = 1;

        DPRINTF("encoding header %d\n", h.rd);

        i = handy_encode_header(&h, packet, PACKETSZ);
        if (i < 0)
        {
            goto fail;
        }

        snprintf(lookup,  MAXDNAME, "%s", name);
        DPRINTF("lookup name: %s\n", lookup);
        q.dotted = (char*)lookup;
        q.qtype = type;
        q.qclass = 1; /* CLASS_IN C_IN*/

        j = handy_encode_question(&q, packet + i, PACKETSZ - i);
        if (j < 0)
        { goto fail; }

        len = i + j;
        dns_len= len;
        if (NULL != udppacket_copy)
        {
            memset(udppacket_copy,  0, PACKETSZ);
            memcpy(udppacket_copy, packet, PACKETSZ);
        }
        DPRINTF("On try %d, sending query to port %d of machine %s\n",
                retries + 1, NAMESERVER_PORT, dns);

#ifdef ATP_NAME_RESOLVE_HAS_IPV6
        v6 = inet_pton(AF_INET6, dns, &sa6.sin6_addr) > 0;
        fd = socket(v6 ? AF_INET6 : AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else
        fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
        if (fd < 0)
        {
            goto again;
        }

        /* Connect to the UDP socket so that asyncronous errors are returned */
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
        if (v6)
        {
            memset((void*)(&bindAddr6),  0, sizeof(bindAddr6));
            bindAddr6.sin6_family = AF_INET6;
            if ((NULL == wanaddr) || (inet_pton(AF_INET6, wanaddr, &bindAddr6.sin6_addr) <= 0))
            {
                DPRINTF("Bind any addr!\n");
            }
            if (bind(fd, (struct sockaddr*)(&bindAddr6), sizeof(bindAddr6)) < 0)
            {
                DPRINTF("Bind addr %s failed!\n", wanaddr);
                goto fail;
            }
            sa6.sin6_family = AF_INET6;
            //lint -save -e572
            sa6.sin6_port = htons(NAMESERVER_PORT);
            /* sa6.sin6_addr is already here */
            rc = connect(fd, (struct sockaddr*) &sa6, sizeof(sa6));
        }
        else
        {
#endif
            sa.sin_family = AF_INET;
            //lint -save -e572
            sa.sin_port = htons(NAMESERVER_PORT);

            // TODO: Doing binding
            memset((void*)(&bindAddr),  0, sizeof(bindAddr));
            bindAddr.sin_family = AF_INET;
            if ((NULL == wanaddr) || (inet_pton(AF_INET, wanaddr, &bindAddr.sin_addr) <= 0))
            {
                bindAddr.sin_addr.s_addr = 0;
            }
            if (bind(fd, (struct sockaddr*)(&bindAddr), sizeof(bindAddr)) < 0)
            {
                DPRINTF("Bind addr %s failed!\n", inet_ntoa(bindAddr.sin_addr));
                goto fail;
            }

            if (0 == inet_aton(dns, &inaddr))
            {
                DPRINTF("inet_aton failed!\n");
                goto fail;
            }
            sa.sin_addr.s_addr = inaddr.s_addr;

            rc = connect(fd, (struct sockaddr*) &sa, sizeof(sa));
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
        }
#endif
        if (rc < 0)
        {
            if (errno == ENETUNREACH)
            {
                /* routing error, presume not transient */
                retries++;
            }
            else
            {
                /* retry */
                retries++;
            }

#ifdef ATP_NAME_RESOLVE_HAS_IPV6
            if ((retries >= MAX_RETRIES) && (!record_flag))
            {
                retries = 0;
                record_flag = 1;
            }
#endif
            if (fd >= 0)
            {
                close(fd);
                fd = -1;
            }
            continue;
        }

        DPRINTF("Transmitting packet of length %d, id=%d, qr=%d\n",
                len, h.id, h.qr);

        (void)send(fd, packet, (unsigned int)len, 0);

        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = REPLY_TIMEOUT;
        tv.tv_usec = 0;
        if (select(fd + 1, &fds, NULL, NULL, &tv) <= 0)
        {
            DPRINTF("Timeout\n");

            /* timed out, so retry send and receive,
             * to next nameserver on queue */
            goto fail;
        }
        memset(packet,  0, PACKETSZ);

        len = recv(fd, packet, 512, 0);
        if (len < HFIXEDSZ)
        {
            /* too short ! */
            goto again;
        }

        handy_decode_header(packet, &h);

        /*1表示数据包截断，采用tcp方式重新请求*/
        if (1 == h.tc)
        {
            tcppacket = malloc(TCPPACKETSZ);
            if (NULL == tcppacket)
            {
                goto again;
            }

            /*组装DNS报文，TCP发送DNS报文时需要在原UDP包前加2个字节标明DNS报文长度*/
            memset(tcppacket,0, TCPPACKETSZ);
            tmppacket = (unsigned short *)tcppacket;
            tmppacket[0] = htons(dns_len);
            tmptcppacket = tcppacket + 2;/*跳过表示DNS报文长度的2个字节*/

            /*拷贝原UDP DNS报文到TCP报文的发送缓存*/
            if (NULL != udppacket_copy)
            {
                /*表示DNS报文长度的2个字节*/
                memcpy(tmptcppacket, udppacket_copy, PACKETSZ);
            }
            else
            {
                DPRINTF("tcp dns:get dns packet failed\n");
                goto again;
            }

            /*建立TCP连接获取DNS回复报文*/
#ifdef ATP_NAME_RESOLVE_HAS_IPV6
            ret = dns_tcp_lookup(tcppacket, TCPPACKETSZ, dns_len + 2, dns, v6);/*表示DNS报文长度的2个字节*/
#else
            /*ipv4的方式获取DNS回复报文*/
            ret = dns_tcp_lookup(tcppacket, TCPPACKETSZ, dns_len + 2, dns, 0);/*表示DNS报文长度的2个字节*/
#endif

            if (RESULT_NOK == ret)
            {
                DPRINTF("tcp dns: DNS lookup failed.\n");
                goto again;
            }

            len = ret;
            tmp_udppacket = packet; 
            packet = tcppacket + 2;/*表示DNS报文长度的2个字节*/

            (void)handy_decode_header(packet, &h);
        }
        DPRINTF("id = %d, qr = %d\n", h.id, h.qr);

        if ((h.id != local_id) || (!h.qr))
        {
            /* unsolicited */
            goto again;
        }


        DPRINTF("Got response %s\n", "(i think)!");
        DPRINTF("qrcount=%d,ancount=%d,nscount=%d,arcount=%d\n",
                h.qdcount, h.ancount, h.nscount, h.arcount);
        DPRINTF("opcode=%d,aa=%d,tc=%d,rd=%d,ra=%d,rcode=%d\n",
                h.opcode, h.aa, h.tc, h.rd, h.ra, h.rcode);

        if ((h.rcode) || (h.ancount < 1))
        {
            /* negative result, not present */
            goto fail;
        }

        pos = HFIXEDSZ;

        for (j = 0; j < h.qdcount; j++)
        {
            DPRINTF("Skipping question %d at %d\n", j, pos);
            i = handy_length_question(packet, pos);
            DPRINTF("Length of question %d is %d\n", j, i);
            if (i < 0)
            { goto again; }
            pos += i;
        }
        DPRINTF("Decoding answer at pos %d\n", pos);

        first_answer = 1;
        for (j = 0; j < h.ancount; j++, pos += i)
        {
            i = handy_decode_answer(packet, pos, &ma);

            if (i < 0)
            {
                DPRINTF("failed decode %d\n", i);
                goto again;
            }

            if ( first_answer )
            {
                ma.buf = a->buf;
                ma.buflen = a->buflen;
                ma.add_count = a->add_count;
                memcpy(a,  &ma, sizeof(ma));
                //if (a->atype != T_SIG && (0 == a->buf || (type != T_A && type != T_AAAA)))
                if (a->atype != 24 && (0 == a->buf || (type != 1 && type != 28)))
                {
                    break;
                }
                if (a->atype != type)
                {
                    free(a->dotted);
                    a->dotted = NULL;
                    continue;
                }
                a->add_count = (size_t)((h.ancount - j) - 1);
                if (((size_t)a->rdlength + sizeof(struct in_addr*)) * a->add_count > a->buflen)
                {
                    break;
                }
                a->add_count = 0;
                first_answer = 0;
				//if (T_AAAA == type && CNAME == ma.atype && rrs == 1)
				if ((28 == type) &&(5 == ma.atype) && (1 == h.ancount))
				{
				    DPRINTF("Answer only CNAME V6\n");
				    goto fail;
				}                    
            }
            else
            {
                free(ma.dotted);
                ma.dotted = NULL;
                if (ma.atype != type)
                {
                    continue;
                }
                if (a->rdlength != ma.rdlength)
                {
                    free(a->dotted);
                    a->dotted = NULL;
                    DPRINTF("Answer address len(%u) differs from original(%u)\n",
                            ma.rdlength, a->rdlength);
                    goto again;
                }
                /*目标地址的buffer大小不易计算，先用stAnswer.rdlength作为buffer大小，解决coverity*/
                memcpy(a->buf + (a->add_count * ((size_t)ma.rdlength)),
                    ma.rdata, (size_t)ma.rdlength);
                ++a->add_count;

                if (a->add_count >= 7)
                {
                    DPRINTF("8 records at most.\n");
                    break;
                }
            }
        }

        DPRINTF("Answer name = |%s|\n", a->dotted);
        DPRINTF("Answer type = |%d|\n", a->atype);

        close(fd);
        fd = -1;

        if (outpacket)
        {
            if (NULL != tmp_udppacket)
            {
                tmp_resultpacket = malloc(TCPPACKETSZ - 2);
                if (NULL == tmp_resultpacket)
                {
                    goto again;    
                }

                memset(tmp_resultpacket,  0, TCPPACKETSZ - 2);
                memcpy(tmp_resultpacket,  packet, TCPPACKETSZ - 2);
                packet = tmp_resultpacket;
                if (NULL != tcppacket)
                {
                    free(tcppacket);
                    tcppacket = NULL;
                }
            }
            *outpacket = packet;
        }
        else
        {
            if (NULL != tmp_udppacket)
            {
                if (NULL != tcppacket)
                {
                    free(tcppacket);
                    tcppacket = NULL;
                }
            }
            else
            {
                //lint -save -e673
                if (NULL != packet)
                {
                    free(packet);
                    packet = NULL;
                }
                //lint -restore
            }
            
        }
        if (NULL != tmp_udppacket)
        {
            free(tmp_udppacket);
            tmp_udppacket = NULL;
        }

        if (NULL != lookup)
        {
            free(lookup);
            lookup = NULL;
        }

        if (NULL != udppacket_copy)
        {
            free(udppacket_copy);
            udppacket_copy = NULL;
        }

        return (len);                /* success! */

    again:
        retries++;

#ifdef ATP_NAME_RESOLVE_HAS_IPV6
        if ((retries >= MAX_RETRIES) && (!record_flag))
        {
            retries = 0;
            record_flag = 1;
        }
#endif
        if (fd >= 0)
        {
            close(fd);
            fd = -1;
        }
        if (NULL != tmp_udppacket)
        {
            packet = tmp_udppacket;
        }
        if (NULL != tcppacket)
        {
            free(tcppacket);
            tcppacket = NULL;
        }
    }

fail:
    if (fd != -1)
    { close(fd); }
    //lint -save -e644
    if (NULL != lookup)
    {
        free(lookup);
        lookup = NULL;
    }

    if (NULL != tmp_udppacket)
    {
        free(tmp_udppacket);
        tmp_udppacket = NULL;
    }
    else
    {
        //lint -save -e673
        if (NULL != packet)
        {
            free(packet);
            packet = NULL;
        }
        //lint -restore
    }
    if (NULL != tcppacket)
    {
        free(tcppacket);
        tcppacket = NULL;
    }

    if (NULL != udppacket_copy)
    {
        free(udppacket_copy);
        udppacket_copy = NULL;
    }

    //lint -restore
    return -1;
}
//lint -restore
//lint -restore

//lint -save -e826
static int gethostbyname_handy_r(const char* name,
                                 struct hostent* result_buf,
                                 char* buf, size_t buflen,
                                 struct hostent** result,
                                 char* wanaddr,
                                 const char* pcCheckFile)
{
    struct in_addr* in;
    struct in_addr** addr_list;
    char** alias;
    unsigned char* packet;
    struct resolv_answer a;
    int i;
#ifdef ATP_PCLINT
    pcCheckFile = pcCheckFile;
#endif
    *result = NULL;
    if (!name)
    { return EINVAL; }

    if (buflen < sizeof(*in))
    { return ERANGE; }
    in = (struct in_addr*)buf;
    buf += sizeof(*in);
    buflen -= sizeof(*in);

    if (buflen < sizeof(*addr_list) * 2)
    { return ERANGE; }
    addr_list = (struct in_addr**)buf;
    buf += sizeof(*addr_list) * 2;
    buflen -= sizeof(*addr_list) * 2;

    addr_list[0] = in;
    addr_list[1] = 0;

    if (buflen < sizeof(char*) * (ALIAS_DIM))
    { return ERANGE; }
    alias = (char**)buf;
    buf += sizeof(char**) * (ALIAS_DIM);
    buflen -= sizeof(char**) * (ALIAS_DIM);

    if (buflen < 256)
    {
        return ERANGE;
    }
    snprintf(buf,  buflen, "%s", name);

    alias[0] = buf;
    alias[1] = NULL;

    /* First check if this is already an address */
    if (inet_aton(name, in))
    {
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        result_buf->h_aliases = alias;
        *result = result_buf;
        return NETDB_SUCCESS;
    }

    for (;;)
    {
        a.buf = buf;
        a.buflen = buflen;
        a.add_count = 0;

        i = handy_dns_lookup(name, 1, &packet, &a, wanaddr);

        if (i < 0)
        {
            DPRINTF("handy_dns_lookup\n");
            return TRY_AGAIN;
        }

        if (((size_t)a.rdlength + sizeof(struct in_addr*)) * a.add_count + 256 > buflen)
        {
            free(a.dotted);
            a.dotted = NULL;
            free(packet);
            packet = NULL;
            DPRINTF("buffer too small for all addresses\n");
            return ERANGE;
        }
        else if (a.add_count > 0)
        {
            memmove(buf - sizeof(struct in_addr*) * 2, 
                buf, a.add_count * ((size_t)a.rdlength));
            addr_list = (struct in_addr**)(buf + a.add_count * ((size_t)a.rdlength));
            addr_list[0] = in;
            for (i = (int)a.add_count - 1; i >= 0; --i)
            { addr_list[i + 1] = (struct in_addr*)((buf - sizeof(struct in_addr*) * 2) + a.rdlength * i); }
            addr_list[a.add_count + 1] = 0;
            buflen -= (size_t)(((char*) & (addr_list[a.add_count + 2])) - buf);
            buf = (char*)&addr_list[a.add_count + 2];
        }
        if (NULL != a.dotted)
        {
            snprintf(buf,  buflen, "%s", a.dotted);
            free(a.dotted);
            a.dotted = NULL;
        }


        if (a.atype == 1)   /* ADDRESS T_A=1 */
        {
            memcpy(in,  a.rdata, sizeof(*in));
            result_buf->h_name = buf;
            result_buf->h_addrtype = AF_INET;
            result_buf->h_length = sizeof(*in);
            result_buf->h_addr_list = (char**) addr_list;
#ifdef __UCLIBC_MJN3_ONLY__
#warning TODO -- generate the full list
#endif
            result_buf->h_aliases = alias; /* TODO: generate the full list */
            free(packet);
            packet = NULL;
            break;
        }
        else
        {
            free(packet);
            packet = NULL;
            return TRY_AGAIN;
        }
    }

    *result = result_buf;
    return NETDB_SUCCESS;
}

struct hostent *atp_gethostbyname(const char *name, unsigned int localAddr);

struct hostent *atp_gethostbyname(const char *name, unsigned int localAddr)
{
    int ret;
    static struct hostent h;
    static char buf[TCPPACKETSZ];

    struct hostent* hp;
    struct in_addr wanin;

    wanin.s_addr = localAddr;

    ret = gethostbyname_handy_r(name, &h, buf, sizeof(buf), &hp, inet_ntoa(wanin), NULL);
    if (NETDB_SUCCESS != ret)
    {
        return NULL;
    }

    return hp;
}

int handy_gethostbyname2_r(const char* name, int family,
                           struct hostent* result_buf,
                           char* buf, size_t buflen,
                           struct hostent** result,
                           char* bindaddr)
{
    struct in6_addr* in;
    struct in6_addr** addr_list;
    unsigned char* packet;
    struct resolv_answer a;
    int i;
    int lRet = 1;
    char cmd[32] = {0};
    FILE* fp;
    struct in6_addr stAddr;
    struct in_addr stAddrIpv4;


    memset(&stAddr, 0, sizeof(struct in6_addr));
    memset(&stAddrIpv4, 0, sizeof(struct in_addr));

    if (family == AF_INET)
    {
        if (inet_pton(AF_INET6, name, &stAddr))
        {
            return EINVAL;
        }
        return gethostbyname_handy_r(name, result_buf, buf, buflen, result, bindaddr, "/var/dns/ipv4");
    }

    *result = NULL;
    if (family != AF_INET6)
    { return EINVAL; }

    if (!name)
    { return EINVAL; }

    /* 未开启IPV6功能直接返回 */
    fp = fopen("/proc/sys/net/ipv6/conf/all/enable", "r");
    if (fp != NULL)
    {
        fgets(cmd, 32, fp);
        lRet = atoi(cmd);
        fclose(fp);
    }
    if (lRet != 1)
    {
        return EINVAL;
    }

    if (buflen < sizeof(*in))
    { return ERANGE; }
    in = (struct in6_addr*)buf;
    buf += sizeof(*in);
    buflen -= sizeof(*in);

    if (buflen < sizeof(*addr_list) * 2)
    { return ERANGE; }
    addr_list = (struct in6_addr**)buf;
    buf += sizeof(*addr_list) * 2;
    buflen -= sizeof(*addr_list) * 2;

    addr_list[0] = in;
    addr_list[1] = 0;

    if (buflen < 256)
    {
        return ERANGE;
    }
    snprintf(buf,  buflen, "%s", name);

    /* First check if this is already an address */
    if (inet_pton(AF_INET6, name, in))
    {
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET6;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        *result = result_buf;
        return NETDB_SUCCESS;
    }

    if (inet_aton(name, &stAddrIpv4))
    {
        return EINVAL;
    }

    fp = fopen("/var/dns/ipv6", "r");
    if (fp != NULL)
    {
        fgets(cmd, 32, fp);
        lRet = atoi(cmd);
        fclose(fp);
    }
    if (lRet != 1)
    {
        return EINVAL;
    }

    memset((char*) &a,  '\0', sizeof(a));
    a.buf = buf;
    a.buflen = buflen;

    i = handy_dns_lookup(buf, T_AAAA, &packet, &a, bindaddr);

    if (i < 0)
    {
        return TRY_AGAIN;
    }

    if (((size_t)a.rdlength + sizeof(struct in6_addr*)) * a.add_count + 256 > buflen)
    {
        free(a.dotted);
        a.dotted = NULL;
        free(packet);
        packet = NULL;
        DPRINTF("buffer too small for all addresses\n");
        return ERANGE;
    }
    else if (a.add_count > 0)
    {
        memmove(buf - sizeof(struct in6_addr*) * 2,
            buf, a.add_count * ((size_t)a.rdlength));
        addr_list = (struct in6_addr**)(buf + a.add_count * (size_t)a.rdlength);
        addr_list[0] = in;
        for (i = (int)a.add_count - 1; i >= 0; --i)
        { addr_list[i + 1] = (struct in6_addr*)((buf - sizeof(struct in6_addr*) * 2) + a.rdlength * i); }
        addr_list[a.add_count + 1] = 0;
        buflen -= (size_t)(((char*) & (addr_list[a.add_count + 2])) - buf);
        buf = (char*)&addr_list[a.add_count + 2];
    }

    if (NULL != a.dotted)
    {
        snprintf(buf, buflen,  "%s", a.dotted);
        free(a.dotted);
        a.dotted = NULL;
    }

    if (a.atype == T_AAAA)
    {
        /* ADDRESS */
        memcpy(in,  a.rdata, sizeof(*in));
        result_buf->h_name = buf;
        result_buf->h_addrtype = AF_INET6;
        result_buf->h_length = sizeof(*in);
        result_buf->h_addr_list = (char**) addr_list;
        free(packet);
        packet = NULL;
        *result = result_buf;
        return NETDB_SUCCESS;
    }
    else
    {
        free(packet);
        packet = NULL;
        return TRY_AGAIN;
    }
}
//lint -restore
struct hostent *ATP_GPL_Gethostbyname(const char *name, int family, char* bindaddr);
struct hostent* ATP_GPL_Gethostbyname(const char* name, int family, char* bindaddr)
{
    int ret;
    static struct hostent h;
    static char buf[TCPPACKETSZ];
    struct hostent* hp;

    if ((strlen(name) == 0) || name[0] == '.')//不对根域名发起查询
    {
        printf("Don't query <Root>\n");
        return NULL;
    }

    ret = handy_gethostbyname2_r(name, family, &h, buf, sizeof(buf), &hp, bindaddr);
    if (NETDB_SUCCESS != ret)
    {
        return NULL;
    }

    return hp;
}


