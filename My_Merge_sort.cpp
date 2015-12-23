#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

//連結リスト構造体
typedef struct node{
	int data;
	struct node *next;
}LISTEL;

//プロトタイプ宣言
void construct_list();
void print_list();
LISTEL *merge_sort(LISTEL *top);
LISTEL *do_sort(LISTEL *a, LISTEL *b);

/* 【グローバル変数】*/
//ノードのはじめ
LISTEL *root;

int main()
{
	//変数
	int data[MAX], num=0;
	
	//root初期化
	root = NULL;
	
	//入力
	construct_list();
	printf("Input Data>");
	print_list();

	//ソート実行
	root = merge_sort(root);
	
	//表示
	printf("Output Data>");
	print_list();
	
	return 0;
}

//マージソート【昇順】
LISTEL *merge_sort(LISTEL *top)
{
	//変数
	LISTEL *a, *b;

	//最初の呼び出しで要素数が1の時の回避
	if( top==NULL || top->next==NULL ) return top;

	//ポインタ初期化
	//aは先頭
	a = top;
	//bは2つ先
	b = top->next->next;
	
	//真ん中計算
	while( b != NULL )
	{
		//aは1回
		a = a->next;
		//bは2回
		b = b->next;
		if( b != NULL ) b = b->next;
		else break;
	}
	
	//リスト分割
	b = a->next;
	a->next = NULL;

	//分割したリストを繋げたのを返す
	//微妙に再起(?)
	return do_sort( merge_sort(top), merge_sort(b) );
}

//ソート連結部分
LISTEL *do_sort(LISTEL *a, LISTEL *b)
{
	/* 【ソート】 */
	//変数宣言
	LISTEL *p;
	//仮先頭ノード
	LISTEL top;
	
	//回し変数pを初期化
	p = &top;

	/* 【ソート実施】 */
	while (a != NULL && b != NULL)
	{
		//前半分割リストが小さい時
		if (a->data <= b->data)
		{
			//topに繋げる
			p->next = a;
			p = a;
			//使ったデータの次に移動
			a = a->next;
		}
		//後半分割リストが小さい時
		else
		{
			//topに繋げる
			p->next = b;
			p = b;
			//使ったデータの次に移動
			b = b->next;
		}
	}
	//余り連結
	if (a == NULL) p->next = b;
	else p->next = a;

	//仮先頭ノードの次のノードからソート後のリストになる
	//ここのreturnはmain()まで帰る(rootに上書き)
	return top.next;
}

//連結リスト構築
void construct_list()
{
	//変数
	LISTEL *p;
	int num, no_index[50], i = 0, k = 0;
	char buf[100];

	printf("Input Data>");

	while (1)
	{
		fgets(buf, sizeof(buf), stdin);

		//何も入力されてない時
		if (buf[0] == '\n') return;

		//更新
		i = 0, k = 0;

		//最初の文字が' 'でない時
		if (buf[i] != ' ') no_index[k++] = i;

		//2文字目以降がスペースでない時
		while (buf[i] != '\0')
		{
			i++;
			if (buf[i - 1] == ' ' && buf[i] != ' ' && buf[i] != '\n') no_index[k++] = i;
		}

		//文字列オーバー処理
		if (buf[i - 1] != '\n')
		{
			printf("Error:Too long input data!\n");
			exit(1);
		}

		//格納
		for (i = 0; i < k; i++)
		{
			//エラー 
			if (sscanf(&buf[no_index[i]], "%d", &num) != 1)
			{
				printf("Error:no number input data!\n");
				continue;
			}

			//保存
			p = (LISTEL *)malloc(sizeof(LISTEL));
			p->data = num;
			p->next = root;
			root = p;
		}
	}
}

//リスト出力
void print_list()
{
	//変数と初期化
	LISTEL *p;
	p = (LISTEL *)malloc( sizeof(LISTEL) );
	p = root;

	//エラー
	if(p == NULL)
	{
		printf("There is no data!\n");
		return;
	}
	
	//表示
	while(p != NULL)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}