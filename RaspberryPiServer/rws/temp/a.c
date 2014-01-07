#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

#define logh(x) printf(#x": 0x%08x\n",x)

main(){
	//char *host = "arbeit.iptime.org";
	char *host = "www.naver.com";
	//char *host = NULL;
	struct hostent *he = gethostbyname(host);
	int i;
	puts(host);
	for (i=0; he->h_addr_list[i]; i++) {
		printf("\t%s\n", inet_ntoa(*(struct in_addr *)he->h_addr_list[i]));
	}

	puts(host);
	logh(*he->h_addr_list);
	logh(he->h_addr_list[0]);
	
	while (*he->h_addr_list) {
		printf("\t%s\n", inet_ntoa(*(struct in_addr *)(*he->h_addr_list));
		printf("\t%s\n", inet_ntoa(*(struct in_addr *)(*he->h_addr_list));
		he->h_addr_list++;
	}
}
