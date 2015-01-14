/*#include <stdio.h>
#include <string.h>
main()
{

  char * temp ="lol some get onboag fsdfdsfs";
  char * find = "onboarding";


    if (strstr(temp,find) != NULL){

printf("Hello, world found!\n");

    }

	char str[] ="name='ssid' \n \n Zakukashi \n ------WebKitFormBoundarybKJgzIXaneJgAL4D\nContent-Disposition: form-data; name='pass'\n\n7946137410\n------WebKitFormBoundarybKJgzIXaneJgAL4D--";
	findit(str," ");
return 0;

}
char findit(char str[], char find){

	char * pch;

	char *token;
	char *state;
	for (token = strtok_r(*str, find, &state);
	 token != NULL;
	 token = strtok_r(NULL, find, &state))
	{
	printf("%s\n", state);
	}

}*/