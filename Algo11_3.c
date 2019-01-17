#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

int cut_rod(int **p, int l);
int MAX(int a, int b);
int buttom_up_cut_rod(int **p, int l);

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	int **p; 
	int length, price; //length, price
	int l; //주어진 막대 길이

	f = fopen("rod_cutting.txt", "rt"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	if (feof(f) == 0) { //파일의 첫번째 값만 읽어온다
		fscanf(f, "%d", &l);
	}

	/*가로,세로 각각 l, 2만큼의 크기를 가진 2차원 배열 생성*/
	p = (int**)malloc(sizeof(int*)*(l+1));
	for (int i = 0; i <= l; i++) {
		p[i] = (int*)malloc(sizeof(int) * (2));
	}

	/*파일 읽어와서*/
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

	printf("측정 시간 : %f\n", gap);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

/*최대값을 구한는 함수*/
int MAX(int a, int b) {
	return (a > b) ? a : b;
}

/*재귀 사용*/
int cut_rod(int **p, int l) {
	int i, q;

	if (l == 0) //길이가 0인경우
		return 0;

	q = -9999999999; //-무한대 값으로 초기화

	for (i = 1; i <= l;i++) {
		//재귀적으로 subproblem의 문제를 풀어나간다.
		q = MAX(q, p[1][i] + cut_rod(p, l - i));
	}

	return q; //q값 반환
}

int buttom_up_cut_rod(int **p, int l) {
	int *r;
	r = (int*)malloc(sizeof(int)*(l+1));
	int i, j;
	int q;

	r[0] = 0;

	for (j= 1; j <= l; j++) {
		q = -9999999999; //-무한대 값으로 초기화
		for (i = 1; i <= j; i++) {
			//subproblem으로부터 최적의 수입 찾기
			q = MAX(q, p[1][i] + r[j - i]);
		}
		r[j] = q;
	}

	return r[l];
}
