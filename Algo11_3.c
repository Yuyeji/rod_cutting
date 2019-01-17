#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int cut_rod(int **p, int l);
int MAX(int a, int b);
int buttom_up_cut_rod(int **p, int l);

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	int **p; 
	int length, price; //length, price
	int l; //�־��� ���� ����

	f = fopen("rod_cutting.txt", "rt"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	if (feof(f) == 0) { //������ ù��° ���� �о�´�
		fscanf(f, "%d", &l);
	}

	/*����,���� ���� l, 2��ŭ�� ũ�⸦ ���� 2���� �迭 ����*/
	p = (int**)malloc(sizeof(int*)*(l+1));
	for (int i = 0; i <= l; i++) {
		p[i] = (int*)malloc(sizeof(int) * (2));
	}

	/*���� �о�ͼ�*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d", &length, &price);
		p[0][i] = length;
		p[1][i] = price;
	}

	startTime = clock();

	printf("cut_rod result : %d\n", cut_rod(p, l));
	printf("buttom_up_cut_rod result : %d\n", buttom_up_cut_rod(p, l));
	
	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

/*�ִ밪�� ���Ѵ� �Լ�*/
int MAX(int a, int b) {
	return (a > b) ? a : b;
}

/*��� ���*/
int cut_rod(int **p, int l) {
	int i, q;

	if (l == 0) //���̰� 0�ΰ��
		return 0;

	q = -9999999999; //-���Ѵ� ������ �ʱ�ȭ

	for (i = 1; i <= l;i++) {
		//��������� subproblem�� ������ Ǯ�����.
		q = MAX(q, p[1][i] + cut_rod(p, l - i));
	}

	return q; //q�� ��ȯ
}

int buttom_up_cut_rod(int **p, int l) {
	int *r;
	r = (int*)malloc(sizeof(int)*(l+1));
	int i, j;
	int q;

	r[0] = 0;

	for (j= 1; j <= l; j++) {
		q = -9999999999; //-���Ѵ� ������ �ʱ�ȭ
		for (i = 1; i <= j; i++) {
			//subproblem���κ��� ������ ���� ã��
			q = MAX(q, p[1][i] + r[j - i]);
		}
		r[j] = q;
	}

	return r[l];
}
