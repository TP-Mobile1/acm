#include <stdio.h>
#include <string.h>

/*#define TEST*/

//revert str in order to make add easier
int revert(char *str, int max_len)
{
	int len = strlen(str);
	char *p1 = NULL;
	char *p2 = NULL;
	int i = 0;

	if(len == 0)
	{
		return -1;
	}

	for(p1=str, p2=str+len-1; p1<p2; p1++, p2--)
	{
		(*p1) ^= (*p2);
		(*p2) ^= (*p1);
		(*p1) ^= (*p2);
	}

	for(p1=str+len; p1<str+max_len; p1++)
	{
		*p1 = '0';
	}
	*p1 = 0;

	return 0;
}

//result will be stored in num1, num1 and num2 should be reverted first
void add(char *num1, char *num2)
{
	int i=0;
	char carry=0; // if a+b>10 then carry=1, char is enough
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int max_len = len1 > len2 ? len1:len2;

	for(i=0; i < max_len; i++)
	{
		if(num1[i] == '\0')
		{
			num1[i] = '0';
		}
		carry = (num1[i]-'0') + (num2[i]-'0') + carry;
		num1[i] = carry % 10 + '0';
		carry /= 10;
	}

	if(carry == 1)
	{
		if(num1[max_len] == '\0')
		{
			num1[max_len] = '0';
		}
		num1[max_len] += carry;
	}
}

int main()
{
	int i = 0;
	char sum[102]={0};
	char num[101]={0};
	int max_len=0;

	sum[0] = '0';
	for (i=0; i<100; i++)
	{
#ifndef TEST
		scanf("%s", num);
		if(!strcmp("0", num))
		{
			break;
		}
		sscanf(num, "%*[^1-9]%s", num);
#endif

#ifdef TEST
		memset(num, '9', sizeof(num));
		num[100]='\0';
		printf("num=%s, strlen(num)=%lu\n", num, strlen(num));
#endif

		revert(num, strlen(sum));
		add(sum, num);
		memset(num, 0, sizeof(num));
#ifdef TEST
		revert(sum, strlen(sum));
		printf("sum=%s, strlen(sum)=%lu", sum, strlen(sum));
		getchar();
		revert(sum, strlen(sum));
		printf("sum=%s, strlen(sum)=%lu\n", sum, strlen(sum));
#endif
	}

	revert(sum, strlen(sum));
	printf("%s\n", sum);
#ifdef TEST
	printf("strlen(sum)=%lu\n", strlen(sum));
#endif
	return 0;
}
