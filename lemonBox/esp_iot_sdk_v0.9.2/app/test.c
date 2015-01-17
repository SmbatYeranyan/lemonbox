#include <stdio.h>
#include <string.h>
main()
{


   	char data[] = "\n+IPD,0,572:POST /odfsfnboard HTTP/1.1\n[00]Host: 192.168.1.2\n[00]Connection: keep-alive\n[00]Content-Length: 27\n[00]Pragma: no-cache\nCache-Control: no-cache\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=\nOrigin: http://192.168.1.2\nUser-Agent: Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36\nContent-Type: application/x-www-form-urlencoded\nReferer: http://192.168.1.2/onboarding\nAccept-Encoding: gzip, deflate\nAccept-Language: en-US,en;q=0.8,de-DE;q=0.6,de;q=0.4 printf(data,\nssid21=Zadasdasd[00]password=eqweqdasd\n";
	printf("%s\n", data);
	char * tok = data;
	int i;
	for (i = 0; i < 13; ++i)
	{
	    strtok(tok, "\n");
	    tok =NULL;
	}

    char * pass = strtok(tok, "\n");
    pass = strtok(pass, "=");
    pass= NULL;
    pass = strtok(pass, "=");
    printf("%s\n", pass);
	return 0;
}
