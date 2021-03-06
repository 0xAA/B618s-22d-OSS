/* Shared library add-on to iptables to add masquerade support. */
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <iptables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <net/netfilter/nf_nat.h>
#include <linux/netfilter_ipv4/ip_conenat.h>


/* Function which prints out usage message. */
static void MASQUERADE_help(void)
{
	printf(
    "CONE_NAT v%s options:\n"
    " --to-ports <port>[-<port>]\n"
    "				Port (range) to map to.\n"
    " --random\n"
    "				Randomize source port.\n"
    " --type\n"
    "               cone nat type 0: full cone 1 addr cone 2 port cone"
    "\n"
    ,
    IPTABLES_VERSION);
}

static const struct xt_option_entry MASQUERADE_opts[] = {
	{.name = "to-ports", .id = 1, .type = XTTYPE_STRING},
	{.name = "random", .id = 2, .type = XTTYPE_NONE},
	{.name = "type", .id = 3, .type = XTTYPE_UINT8},
	XTOPT_TABLEEND,
};

/* Initialize the target. */
static void MASQUERADE_init(struct xt_entry_target *t)
{
    struct ip_cone_nat_data *p = (struct ip_cone_nat_data *)t->data;
	struct ip_nat_multi_range *mr = (struct ip_nat_multi_range *)&p->data;

    p->cone_nat_type = 0;
	/* Actually, it's 0, but it's ignored at the moment. */
	mr->rangesize = 1;

}

/* Parses ports */
static void
parse_ports(const char *arg, struct ip_nat_multi_range *mr)
{
	const char *dash;
	int port;

	mr->range[0].flags |= IP_NAT_RANGE_PROTO_SPECIFIED;

	port = atoi(arg);
	if (port <= 0 || port > 65535)
		xtables_error(PARAMETER_PROBLEM, "Port `%s' not valid\n", arg);

	dash = strchr(arg, '-');
	if (!dash) {
		mr->range[0].min.tcp.port
			= mr->range[0].max.tcp.port
			= htons(port);
	} else {
		int maxport;

		maxport = atoi(dash + 1);
		if (maxport == 0 || maxport > 65535)
			xtables_error(PARAMETER_PROBLEM,
				   "Port `%s' not valid\n", dash+1);
		if (maxport < port)
			/* People are stupid.  Present reader excepted. */
			xtables_error(PARAMETER_PROBLEM,
				   "Port range `%s' funky\n", arg);
		mr->range[0].min.tcp.port = htons(port);
		mr->range[0].max.tcp.port = htons(maxport);
	}
}

static void MASQUERADE_parse_nattype(const char *arg, struct ip_cone_nat_data *p)
{
    int type = 0;
    type = atoi(arg);
    if ((type != FULL_CONE_TYPE) && (type != ADDR_CONE_TYPE) && (type != PORT_CONE_TYPE))
    {
        xtables_error(PARAMETER_PROBLEM,
               "cone nat type error\n", arg);
    }
    p->cone_nat_type = type;
}


/* Function which parses command options; returns true if it
   ate an option */
static void MASQUERADE_parse(struct xt_option_call *cb)
{
    struct ip_cone_nat_data *p = cb->data;
	const struct ipt_entry *entry = cb->xt_entry;
	int portok;
	struct ip_nat_multi_range *mr = (void *)(*cb->target)->data;


	if (entry->ip.proto == IPPROTO_TCP
	    || entry->ip.proto == IPPROTO_UDP
	    || entry->ip.proto == IPPROTO_ICMP)
		portok = 1;
	else
		portok = 0;

	xtables_option_parse(cb);
	switch (cb->entry->id) {
	case 1:
		if (!portok)
			xtables_error(PARAMETER_PROBLEM,
				   "Need TCP or UDP with port specification");

		if (xtables_check_inverse(optarg,  &cb->invert, NULL, 0, 0))
			xtables_error(PARAMETER_PROBLEM,
				   "Unexpected `!' after --to-ports");

		parse_ports(optarg, mr);
		return 1;

	case 2:
		mr->range[0].flags |=  IP_NAT_RANGE_PROTO_RANDOM;
		return 1;
    case 3:
        MASQUERADE_parse_nattype(optarg, p);
        return 1;

	default:
		return 0;
	}
}

/* Prints out the targinfo. */
static void
MASQUERADE_print(const void *ip, const struct xt_entry_target *target,
                 int numeric)
{    
    struct ip_cone_nat_data *p = (struct ip_cone_nat_data *)target->data;
	struct ip_nat_multi_range *mr
		= (struct ip_nat_multi_range *)&p->data;
	struct ip_nat_range *r = &mr->range[0];

	if (r->flags & IP_NAT_RANGE_PROTO_SPECIFIED) {
		printf("conenat ports: ");
		printf("%hu", ntohs(r->min.tcp.port));
		if (r->max.tcp.port != r->min.tcp.port)
			printf("-%hu", ntohs(r->max.tcp.port));
		printf(" ");
	}

	if (r->flags & IP_NAT_RANGE_PROTO_RANDOM)
		printf("random ");

    printf("type: %d ", p->cone_nat_type);
}

/* Saves the union ipt_targinfo in parsable form to stdout. */
static void
MASQUERADE_save(const void *ip, const struct xt_entry_target *target)
{
    struct ip_cone_nat_data *p = (struct ip_cone_nat_data *)target->data;
	struct ip_nat_multi_range *mr
		= (struct ip_nat_multi_range *)&p->data;
	struct ip_nat_range *r = &mr->range[0];

	if (r->flags & IP_NAT_RANGE_PROTO_SPECIFIED) {
		printf("--to-ports %hu", ntohs(r->min.tcp.port));
		if (r->max.tcp.port != r->min.tcp.port)
			printf("-%hu", ntohs(r->max.tcp.port));
		printf(" ");
	}

	if (r->flags & IP_NAT_RANGE_PROTO_RANDOM)
		printf("--random ");

    printf("type: %d ", p->cone_nat_type);
}

static struct xtables_target conenat_target = {
	.name		= "ALLCONE_NAT",
	.version	= XTABLES_VERSION,
	.size		= XT_ALIGN(sizeof(struct ip_cone_nat_data)),
	.userspacesize	= XT_ALIGN(sizeof(struct ip_cone_nat_data)),
	.help		= MASQUERADE_help,
	.init		= MASQUERADE_init,
	.x6_parse	= MASQUERADE_parse,
	.print		= MASQUERADE_print,
	.save		= MASQUERADE_save,
	.x6_options	= MASQUERADE_opts,
};

void _init(void)
{
	xtables_register_target(&conenat_target);
}
