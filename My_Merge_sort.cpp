#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

//�A�����X�g�\����
typedef struct node{
	int data;
	struct node *next;
}LISTEL;

//�v���g�^�C�v�錾
void construct_list();
void print_list();
LISTEL *merge_sort(LISTEL *top);
LISTEL *do_sort(LISTEL *a, LISTEL *b);

/* �y�O���[�o���ϐ��z*/
//�m�[�h�̂͂���
LISTEL *root;

int main()
{
	//�ϐ�
	int data[MAX], num=0;
	
	//root������
	root = NULL;
	
	//����
	construct_list();
	printf("Input Data>");
	print_list();

	//�\�[�g���s
	root = merge_sort(root);
	
	//�\��
	printf("Output Data>");
	print_list();
	
	return 0;
}

//�}�[�W�\�[�g�y�����z
LISTEL *merge_sort(LISTEL *top)
{
	//�ϐ�
	LISTEL *a, *b;

	//�ŏ��̌Ăяo���ŗv�f����1�̎��̉��
	if( top==NULL || top->next==NULL ) return top;

	//�|�C���^������
	//a�͐擪
	a = top;
	//b��2��
	b = top->next->next;
	
	//�^�񒆌v�Z
	while( b != NULL )
	{
		//a��1��
		a = a->next;
		//b��2��
		b = b->next;
		if( b != NULL ) b = b->next;
		else break;
	}
	
	//���X�g����
	b = a->next;
	a->next = NULL;

	//�����������X�g���q�����̂�Ԃ�
	//�����ɍċN(?)
	return do_sort( merge_sort(top), merge_sort(b) );
}

//�\�[�g�A������
LISTEL *do_sort(LISTEL *a, LISTEL *b)
{
	/* �y�\�[�g�z */
	//�ϐ��錾
	LISTEL *p;
	//���擪�m�[�h
	LISTEL top;
	
	//�񂵕ϐ�p��������
	p = &top;

	/* �y�\�[�g���{�z */
	while (a != NULL && b != NULL)
	{
		//�O���������X�g����������
		if (a->data <= b->data)
		{
			//top�Ɍq����
			p->next = a;
			p = a;
			//�g�����f�[�^�̎��Ɉړ�
			a = a->next;
		}
		//�㔼�������X�g����������
		else
		{
			//top�Ɍq����
			p->next = b;
			p = b;
			//�g�����f�[�^�̎��Ɉړ�
			b = b->next;
		}
	}
	//�]��A��
	if (a == NULL) p->next = b;
	else p->next = a;

	//���擪�m�[�h�̎��̃m�[�h����\�[�g��̃��X�g�ɂȂ�
	//������return��main()�܂ŋA��(root�ɏ㏑��)
	return top.next;
}

//�A�����X�g�\�z
void construct_list()
{
	//�ϐ�
	LISTEL *p;
	int num, no_index[50], i = 0, k = 0;
	char buf[100];

	printf("Input Data>");

	while (1)
	{
		fgets(buf, sizeof(buf), stdin);

		//�������͂���ĂȂ���
		if (buf[0] == '\n') return;

		//�X�V
		i = 0, k = 0;

		//�ŏ��̕�����' '�łȂ���
		if (buf[i] != ' ') no_index[k++] = i;

		//2�����ڈȍ~���X�y�[�X�łȂ���
		while (buf[i] != '\0')
		{
			i++;
			if (buf[i - 1] == ' ' && buf[i] != ' ' && buf[i] != '\n') no_index[k++] = i;
		}

		//������I�[�o�[����
		if (buf[i - 1] != '\n')
		{
			printf("Error:Too long input data!\n");
			exit(1);
		}

		//�i�[
		for (i = 0; i < k; i++)
		{
			//�G���[ 
			if (sscanf(&buf[no_index[i]], "%d", &num) != 1)
			{
				printf("Error:no number input data!\n");
				continue;
			}

			//�ۑ�
			p = (LISTEL *)malloc(sizeof(LISTEL));
			p->data = num;
			p->next = root;
			root = p;
		}
	}
}

//���X�g�o��
void print_list()
{
	//�ϐ��Ə�����
	LISTEL *p;
	p = (LISTEL *)malloc( sizeof(LISTEL) );
	p = root;

	//�G���[
	if(p == NULL)
	{
		printf("There is no data!\n");
		return;
	}
	
	//�\��
	while(p != NULL)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}