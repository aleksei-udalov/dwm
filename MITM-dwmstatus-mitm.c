/* Here is a helper function that warns you if someone tries to sniff your
 * network traffic (i.e. a Man-In-The-Middle attack ran against you thanks
 * to ARP cache poisoning).
 *
 * It checks the dump file of the kernel ARP table (/proc/net/arp) to see
 * if there is more than one IP address associated with the same MAC
 * address.  If so, it shows an alert.  If an error occurs during the
 * check, it returns NULL.
 *
 * Written by vladz (vladz AT devzero.fr).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* The hard maximum number of entries kept in the ARP cache is obtained via
 * "sysctl net.ipv4.neigh.default.gc_thresh3" (see arp(7)).  Default value
 * for Linux is 1024.
 */
#define MAX_ARP_CACHE_ENTRIES  1024


char *detect_arp_spoofing(void) {

  FILE *fp;
  int  i = 1, j;
  char **ptr = NULL;
  char buf[100], *mac[MAX_ARP_CACHE_ENTRIES];

  if (!(fp = fopen("/proc/net/arp", "r"))) {
    return NULL;
  }

  ptr = mac;

  while (fgets(buf, sizeof(buf) - 1, fp)) {

    /* ignore the first line. */
    if (i == 1) { i = 0; continue; }

    if ((*ptr = malloc(18)) == NULL) {
      return NULL;
    }

    sscanf(buf, "%*s %*s %*s %s", *ptr);
    ptr++;
  }

  /* end table with a 0. */
  *ptr = 0;

  fclose(fp);

  for (i = 0; mac[i] != 0; i++)
    for (j = i + 1; mac[j] != 0; j++)
      if ((strcmp("00:00:00:00:00:00", mac[i]) != 0) && 
          (strcmp(mac[i], mac[j]) == 0)) {

	return "** MITM attack detected! Type \"arp -a\". **";
      }

  return "MITM detection: on";
}

int main() {

  printf("%s\n", detect_arp_spoofing());

  return 0;
}
