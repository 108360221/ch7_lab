#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct clientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
};

int main(void){
	FILE* pRead, * pWrite;
	FILE* cfPtr;
	int cnt = 0;
	struct clientData client = { 0,"","",0.0 };

	pRead = fopen("C://credit.txt", "r");
	if (pRead == NULL)
		return 0;

	pWrite = fopen("C://credit_bin.txt", "wb");
	if (pWrite == NULL){
		fclose(pRead);
		return 0;
	}

	while (!feof(pRead)){
		fscanf(pRead, "%d%s%s%lf", &client.acctNum,
			client.lastName, client.firstName, &client.balance);

		fwrite(&client, sizeof(struct clientData), 1, pWrite);

		printf("%-6d%-16s%-11s%10.2f\n", client.acctNum,
			client.lastName, client.firstName, client.balance);
	}

	fclose(pRead);
	fclose(pWrite);
	printf("已讀取文字檔的ACSII資料，並轉存成二進位資料檔案\n\n");
	system("pause");

	printf("\n讀取二進位資料檔案，並格式化輸出如下:\n");
	if ((cfPtr = fopen("C://credit_bin.txt", "rb")) == NULL)
		printf("File could not be opened.\n");
	else{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

		cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);

		while (cnt > 0){
			printf("%-6d%-16s%-11s%10.2f\n", client.acctNum,
				client.lastName, client.firstName, client.balance);

			cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);
		}
		fclose(cfPtr);
	}
	system("pause");
	return 0;
}