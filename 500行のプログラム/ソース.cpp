#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include<string>
#include<windows.h>



int main()
{
	int chr, x=0, y=0,cnt=0;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	FILE* fp;
	char cmp[100], str[100],str2[100],cursor[100],pg[100],pg2[100],search[100],word[100];
	
	printf("開きたいテキストを入力\n");
	scanf("%s", pg);
	printf("実行したいモードを選択\nw:入力\nr:閲覧\ncmd:コマンドモード\nclear:画面クリア\nexit:終了\nremove:テキストの最初の行から書き込み\nrename:ファイル名の変更\n");
	scanf("%s", cmp);
	while ((strcmp(cmp, "exit") != 0))
	{
		if (strcmp(cmp, "w") == 0)
		{
			fp = fopen(pg, "a+");
			if (fp == NULL) 
			{
				printf("%s file not open!\n", pg);
				return -1;
			}
			else {
				printf("文字を入力\n");
				scanf("%s", str);
				fputs(str, fp);
				fputc('\n', fp);
			}
			fclose(fp); // ファイルを閉じる
		}
		else if (strcmp(cmp, "r") == 0)
		{
			fp = fopen(pg, "r");
			if (fp == NULL) 
			{
				printf("%s file not open!\n", pg);
				return -1;
			}
			else {

				while ((chr = fgetc(fp)) != EOF)
				{
					putchar(chr);
				}
				fclose(fp); // ファイルを閉じる
			}
		}
		else if (strcmp(cmp, "cmd") == 0)
		{
			fp = fopen(pg, "r+b");
			if (fp == NULL)
			{
				printf("%s file not open!\n",pg);
				return -1;
			}
			else {
				printf("カーソル移動\nテキストの先頭:p\n左:a\n右:d\n上:w\n下:s\n終了:z\n");
				scanf("%s", cursor);
				
				while ((strcmp(cursor, "z") != 0))
				{
					fgets(str, 100, fp);
					if (strcmp(cursor, "a") == 0)
					{
						x = x -1;
						coord.X = x;
						str[x] = str[x -1];
						cnt++;
					}
					else if (strcmp(cursor, "d") == 0)
					{
						x = x +1;
						coord.X=x;
						str[x] = str[x + 1];
						cnt--;
					}
					else if (strcmp(cursor, "w") == 0)
					{
						y = y-1;
						coord.Y = y;
						while (strcmp(str, "\n") == 0)
						{
							str[x] = str[x -1];
						}
						if (str == "\n")
						{
							str[x] = str[x - 1];

						}


					}
					else if (strcmp(cursor, "s") == 0)
					{
						y = y +1;
						coord.Y=y;
						while (strcmp(str,"\n")==0)
						{
							str[x] = str[x + 1];
						}
						if (str == "\n")
						{
							str[x] = str[x + 1];

						}

					}
					else if (strcmp(cursor,"p")==0)
					{
						system("cls");
						while ((chr = fgetc(fp)) != EOF) 
						{
							putchar(chr);
						}
						fseek(fp, 1, SEEK_SET);
						coord.X = 0;
						coord.Y = 0;
					}
					SetConsoleCursorPosition(
						GetStdHandle(STD_OUTPUT_HANDLE),
						coord);
					scanf("%s", cursor);
				}
				fseek(fp, 0, SEEK_CUR);
				//scanf("%s", str);
				scanf("%s", str2);
				strcpy(str, str2);//Xは書き込む位置

				fputs(str, fp);
			}
			fclose(fp); // ファイルを閉じる
		}
		
		else if (strcmp(cmp, "clear") == 0)
		{
			system("cls");
		}
		else if (strcmp(cmp,"remove")==0)
		{
			fp = fopen(pg, "w");
			if (fp == NULL) 
			{
				printf("%s file not open!\n", pg);
				return -1;
			}
			else 
			{
				printf("文字を入力\n");
				scanf("%s", str);
				fputs(str, fp);
				fputc('\n', fp);
			}
			fclose(fp); // ファイルを閉じる
		}
		else if (strcmp(cmp, "del") == 0)
				{
					printf("\n削除するファイル名を入力してください\n");
					scanf("%s", pg);
					fp = fopen(pg, "a"); // ファイルを開く
				if (remove(pg) == 0)
				{

					printf("ファイルの削除に成功");
				}
		else
				{
				printf("ファイルの削除に失敗");
			}
				fclose(fp); // ファイルを閉じる
				}
		else if (strcmp(cmp, "rename") == 0)
		{
			printf("\n名前を変更するファイル名を入力してください\n");
			scanf("%s", pg);
			fp = fopen(pg, "a"); // ファイルを開く
			if (rename(pg,pg2) == 0)
			printf("%sを%sに変更しました。\n", pg, pg2);
			else
			printf("%sを%sに変更できませんでした。\n", pg, pg2);
			fclose(fp); // ファイルを閉じる
		}	
		else if (strcmp(cmp, "firstpg") == 0)
		{
			fp = fopen(pg, "a+");
			fseek(fp, 0, SEEK_SET);
			printf("先頭に入れたい文字を入力");
			scanf("%s", str);
			fputs(str, fp);
			printf("書き込み済み");
		}
		else if (strcmp(cmp, "endpg") == 0)
		{
			fp = fopen(pg, "a+");
			fseek(fp, 0, SEEK_END);
			printf("最後に入れたい文字を入力");
			scanf("%s", str);
			fputs(str, fp);
			printf("書き込み済み");
		}
		else if (strcmp(cmp,"search")==0)
		{
		fp = fopen(pg, "r");
		printf("探したい文字を入力");
		scanf("%s", search);
		while ((chr = fgetc(fp)) != EOF)
		{
			if (strcmp(str,search)==0)
			{
				printf("検索にマッチしました!!");
			}
			else
			{
				printf("ワードが見つかりませんでした");
			}
		}
		}
		else if (strcmp(cmp,"deleteword")==0)
		{
		printf("削除したい文字を入力");
		scanf("%s",word);
		for (int i = 0; i < 100; i++)
		{
			str[i] = str[i + 1];
			if (strcmp(str,word)==0)
			{
				strcpy(&str[i], '\0');
			}
		}
		}
		else if (strcmp(cmp, "alarm") == 0)
		{
		printf("警告受信完了直ちにデータを消去します!!");
		Sleep(1000);
		system("cls");
		printf("\a");
		}
		else if (strcmp(cmp, "back") == 0)
		{
			printf("もしかしてエンターキー押しあちゃった？\n一文字後ろに戻ろう");
			printf("\b");
			printf("これでひと安心つけるね");
		}
		else if (strcmp(cmp, "fprs") == 0)
		{
			printf("検索したいテキストを入力");
			scanf("%s", pg);
			printf("見たいテキストを変換したよ!");
		}
		else if (strcmp(cmp, "hack") == 0)
		{
			printf("ハッキングモード");
			system("cls");
			printf("esdfghjuytrewqdsgfhjm,kjluiyutyrtegsrfdsvfbgnmutdyrst");
			Sleep(1000);
			printf("wxcfvgbj,lpl0976hhggfddxssfgtrdxcvbjuytdcvbnytrcy6ytr");
			Sleep(100);
			printf("23458987645642356787654345787654323959784393945859495");
			printf("ハッキング完了");
		}
		else if (strcmp(cmp, "angou") == 0)
		{
			while ((chr = fgetc(fp)) != EOF)
			{
				printf("%d",chr);
			}
		}
		else if (strcmp(cmp, "background") == 0)
		{
			printf("¥033[33m");
		}
		printf("\n実行したいモードを選択\nw:入力\nr:閲覧\ncmd:コマンドモード\nclear:画面クリア\nexit:終了\n");
		scanf("%s", cmp);
	}
	return 0;
}
BOOL WINAPI SetConsoleCursorPosition(
	HANDLE hConsoleOutput,
	COORD  dwCursorPosition
);