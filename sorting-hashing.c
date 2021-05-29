/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("[-------[황슬비] [2018032027] ------");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) //더블포인터
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; //array가 NULL이 아닌 경우 temp가 배열 가리키도록 함

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) //a가 NULL이 아닌 경우
		free(a); //array에 할당된 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { //a가 NULL일 때, 빈 배열일 때 경고문구 출력
		printf("nothing to print.\n");
		return;
	}
	//빈 배열이 아닌 경우
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //인덱스번호 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열값 출력
		printf("%5d ", a[i]);
	printf("\n");
}



/*선택정렬
 	 주어진 리스트 중 최소값 찾아 맨 앞에 위치한 값과 교체
 	 맨 앞 값 제외하고 반복*/
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //기존배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //첫번째 인덱스부터
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //두번째인덱스~마지막인덱스 중 최솟값 찾기
		{
			if (min > a[j]) //최솟값 찾아 min에 할당하고 인덱스 번호 저장
			{
				min = a[j];
				minindex = j;
			}
		}
		//Switch a[min]<->a[i]
		a[minindex] = a[i]; //최솟값인덱스에 첫번째 인덱스 값 넣기
		a[i] = min; //첫번째 인덱스에 최솟값 넣기
	} //MAX_ARRAY_SIZE-1 까지 반복

	printf("----------------------------------------------------------------\n");
	printArray(a); //선택정렬 후 배열 출력
	return 0;
}

/*삽입정렬
 	 정렬되어있는 부분집합에 새로운 원소의 위치 찾아 삽입
 	 i와 i-1비교
 	 */
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //기존배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) //s={a[0]}로 시작
	{
		t = a[i];  //인덱스값 저장
		j = i; //인덱스번호 저장
		while (a[j-1] > t && j > 0) //바로 앞 인덱스와 비교연산, a[i-1]>a[i]인 경우 반복
		{
			a[j] = a[j-1]; //a[j]에 a[j-1] 넣고 j한칸 앞으로(i=1인 경우 j=1이므로 반복문 탈출)
			j--;
		}
		a[j] = t; //a[j]에 기존값 저장(Switch)
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //삽입정렬 후 배열 출력

	return 0;
}

/* 버블정렬
	인접한 배열의 요소 비교, 교환
	최댓값을 맨 뒤로 보내며 반복
 * */
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //인접한 두 원소 비교, 앞 원소가 더 큰 경우
			{
				t = a[j-1]; //작은 수가 앞으로 오도록 값 교환
				a[j-1] = a[j];
				a[j] = t;
			}
		}//가장 큰 수 맨 뒤로 옴
	} //모두 정렬될 때까지 반복하며 큰 수 뒤로 보냄

	printf("----------------------------------------------------------------\n");
	printArray(a); //버블정렬된 배열 출력

	return 0;
}

/*셸 정렬
 * Insertion Sort의 문제점 보완 (인접요소만 비교)
 * 간격h 이용 (h=n/2) h=1될 때까지 반복
 * */

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //h=n/2 (n=원소의 개수), h의 값을 반으로 감소시키면서 h가 1이 될 때까지 반복
	{
		for (i = 0; i < h; i++) //h=n/2하여 두 개 원소 비교하므로 배열의 반절만 반복하면 됨
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j한칸씩 이동하여 배열의 반이 되는 부분까지 감
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v) //a[j]와 a[j-h]비교
				{
					a[k] = a[k-h]; //a[j]=a[j-h], 큰 값을 a[j]로
					k -= h; //큰 값이 있던 자리를 k로 하여 그 앞에 값이 있으면 비교반복
				}
				a[k] = v; //비교한 두 배열 교환
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //셸정렬된 배열 출력

	return 0;
}


/*퀵 정렬
 * 	가운데를 pivot으로 설정하여 부분집합 정렬
 * 	이 함수에서는 마지막 원소를 pivot으로 설정함*/
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)//배열의 크기가 1개 이상인 경우에만 작동
	{
		v = a[n-1]; //pivot을 마지막인덱스로 설정
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v); //a[0]부터 왼쪽->오른쪽 이동
			while(a[--j] > v); //a[n-2]부터오른쪽->왼쪽 이동

			if (i >= j) break; //i와j만나면 끝냄,
			t = a[i]; // while문에 부합하지 않는 경우, a[i]>v이거나 a[j]<v인 경우
			a[i] = a[j];//i와 j 교환
			a[j] = t;
		}
		t = a[i]; //j와 i가 만난 경우 i와 pivot교환
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // 왼쪽(pivot보다 작은 부분집합)
		quickSort(a+i+1, n-i-1); //오른쪽 부분집합(pivot보다 큰 부분집합)으로 나누어 퀵정렬 반복
	}


	return 0;
}


/*해싱*/
int hashCode(int key) { //division함수 사용
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //hash table -1로 채우기
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]); //hash테이블 내용 출력
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key); //배열의 값 이용하여 hashfunction(hashCode)으로 hashcode얻음
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //해당 버켓이 비어있는 경우
		{
			hashtable[hashcode] = key; //버켓에 데이터 넣음
		} else 	{ //collision&overflow발생

			index = hashcode; //hashcode를 index로 할당하여 방 다시 찾기

			while(hashtable[index] != -1) // 빈 슬롯 찾기
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //linear probing사용하여 빈 슬롯 있는지 조사
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //해당 버켓에 데이터 넣음
		}
	}

	return 0;
}

int search(int *ht, int key) //해싱 사용하여 인덱스 찾기
{
	int index = hashCode(key); //key의 해시코드를 index에 할당

	if(ht[index] == key) //해시테이블의 해당 index에 key값이 있는지 확인하여 있으면 index리턴
		return index;

	while(ht[++index] != key) //해시테이블 해당 index의 값이 key가 아닌 경우 collision&overflow발생했을 때 빈 슬롯 새로 찾은 공식으로 버켓 옮겨가면서 확인
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index; //찾으면 해당 index값 리턴
}



