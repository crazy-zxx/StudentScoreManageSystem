#define _CRT_SECURE_NO_WARNINGS

//����ɼ�����+1,�����һ�����ƽ����
#define LEN 11

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//ѧ����Ϣ
typedef struct student {
	char stuNo[10];			//ѧ��
	char stuName[10];		//����
	int stuClass;			//�༶
	float stuScore[LEN];	//�ɼ�(10)+ƽ����(1)
	struct student* next;	
}STU;
STU head;	//ͷ���

int menu();					//�˵�
void addStu();				//����ѧ����Ϣ
void showStu();				//��ʾĳ��ѧ����Ϣ
void modifyStu();			//�޸�ĳ��ѧ����Ϣ
void deleteStu();			//ɾ��ĳ��ѧ����Ϣ
int findIndex(char* no);	//����ĳ��ѧ���Ƿ��Ѿ����ڣ����ڷ������������򷵻�0
STU* findStu(char* no);		//����ĳ��ѧ���Ƿ��Ѿ����ڣ����ڷ���ָ�룬���򷵻�NULL
int findClass(int class);	//����ĳ���༶���Ƿ��Ѿ����ڣ����ڷ���1�����򷵻�0
void showByClass();			//��ʾĳ���༶����ѧ����Ϣ���ɼ�
void showAll();				//��ʾ����ѧ����Ϣ���ɼ�
float* getEveryTimeAverage(int class);	//��ȡĳ����������ÿ�ε�ƽ���֣�class=0ʱ���������˵�ƽ����
void loadFromFile();		//���ļ�������Ϣ
void saveToFile();			//������Ϣ���ļ�

int main() {

	head.next = NULL;

	int no = 0;
	
	while (1)
	{
		system("cls");

		no = menu();

		system("cls");

		switch (no)
		{
		case 0:
			exit(0);
		case 1:
			addStu();
			break;
		case 2:
			showStu();
			break;
		case 3:
			modifyStu();
			break;
		case 4:
			deleteStu();
			break;
		case 5:
			showByClass();
			break;
		case 6:
			showAll();
			break;
		case 7:
			loadFromFile();
			break;
		case 8:
			saveToFile();
			break;
		default:
			break;
		}

	}

	return 0;
}

int menu()
{
	int no = 0;

	printf("-------------------------------------------\n\n");
	printf("\t\t�˵�\n\n");
	printf("\t1.���ѧ����Ϣ\n");
	printf("\t2.�鿴ѧ���ɼ�\n");
	printf("\t3.�޸�ѧ���ɼ�\n");
	printf("\t4.ɾ��ѧ����Ϣ\n");
	printf("\t5.�鿴ָ���༶ѧ���ɼ���ƽ����\n");
	printf("\t6.�鿴����ѧ���ɼ���ƽ����\n");
	printf("\t7.���ļ�������Ϣ\n");
	printf("\t8.������Ϣ���ļ�\n");
	printf("\t0.�˳�\n\n");
	printf("-------------------------------------------\n");
	printf("��������Ҫ�Ĳ�����Ӧ����ţ�");

	while (scanf("%d", &no) != 1 || no < 0 || no > 8) {
		//fflush(stdin);	//VS2015��ʼ����֧�֣��Ժ�Ҫ��ʹ�ã�����
		//������̻�����
		char tmp;
		while ((tmp = getchar()) != '\n' && tmp != EOF);
		printf("\n�������!���������룺");
	}

	return no;
}

void addStu()
{
	while (1) {
		STU* stu = NULL, * p = &head;
		//ȷ���������½ڵ���䵽�ռ�
		while ((stu = (STU*)malloc(sizeof(STU))) == NULL);
		//�½ڵ����ݳ�ʼ��
		for (int i = 0; i < LEN; i++) {
			stu->stuScore[i] = 0.0f;
		}
		stu->next = NULL;

		//��ӡ��ʾ��Ϣ
		printf("\n\t\t���ѧ����Ϣ\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("������ѧ����Ϣ(��ʽ��ѧ��  ����  �༶,����0-0-0�������˵�)��\n");
				
		//��������У�ˣ���ȡ�������ݣ�ѧ�Ų��ظ����༶�Ŵ���0
		while (scanf("%9s %9s %d", stu->stuNo, stu->stuName, &stu->stuClass) != 3 || findIndex(stu->stuNo) > 0 || stu->stuClass < 0) {
			//������̻�����
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n�������!���������룺");
		}
		//����ȫ0��Ϣ����
		if (!strcmp(stu->stuNo, "0") && !strcmp(stu->stuName, "0") && stu->stuClass == 0) {
			free(stu);
			return 0;
		}

		//׼������½ڵ�
		//�ҵ����һ���ڵ㣬����ǰ�ڵ���������
		while (p->next != NULL) {
			p = p->next;
		}
		//����½ڵ�
		p->next = stu;
	
		printf("\nѧ����Ϣ��ӳɹ���\n");
		system("pause");
		system("cls");
	}

}

void showStu()
{
	while (1) {
		STU* p = NULL;
		char stuNo[10];	//���������ѧ��

		//�����ʾ��Ϣ
		printf("\n\t\t����ѧ����Ϣ\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("������ѧ��ѧ��(����0�������˵�)��\n");

		//��������У�ˣ���ȡһ��С�ڵ���9���ַ����ַ���
		while (scanf("%9s", stuNo) != 1) {
			//������̻�����
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n�������!���������룺");
		}
		//��������Ϊ0ʱ����
		if (!strcmp(stuNo,"0")) {
			return 0;
		}
		
		//���������ѧ�Ŷ�Ӧ�Ľڵ�
		if ((p = findStu(stuNo)) != NULL) {
			//������ҵ���ѧ����Ϣ
			printf("ѧ�ţ�%s��������%s���༶��%d\n�ɼ���", p->stuNo, p->stuName, p->stuClass);
			for (int i = 0; i < LEN; i++) {
				if (i == (LEN - 1)) {
					printf(" ƽ����:");
				}
				printf(" %.1f ", p->stuScore[i]);
			}
			
		}
		else {
			printf("\n��ѧ�������ڣ�");
		}
		
		printf("\n\n");
		system("pause");
		system("cls");
	}

}

void modifyStu()
{
	while (1) {
		STU* p = &head;
		char stuNo[10];		//���������ѧ��

		//�����ʾ��Ϣ
		printf("\n\t\t�޸�ѧ����Ϣ\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("������ѧ��ѧ��(����0�������˵�)��\n");

		//��������У�ˣ�һ��С�ڵ���9���ַ����ַ���
		while (scanf("%9s", stuNo) != 1) {
			//������̻�����
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n�������!���������룺");
		}
		//����Ϊ0ʱ����
		if (!strcmp(stuNo, "0")) {
			return 0;
		}

		//���������ѧ�Ŷ�Ӧ�Ľڵ�
		if ((p = findStu(stuNo)) != NULL) {
			//������ҵ���ѧ����Ϣ
			printf("ѧ�ţ�%s��������%s���༶��%d\n�ɼ���", p->stuNo, p->stuName, p->stuClass);
			for (int i = 0; i < LEN; i++) {
				if (i == (LEN - 1)) {
					printf(" ƽ����:");
				}
				printf(" %.1f ", p->stuScore[i]);
			}

			//�����޸ĵĳɼ�
			printf("\n\n������ѧ����10�γɼ���ÿ�������갴�س���������");
			float s_tmp[LEN-1];
			//��������У�ˣ���ȡʮ���ɼ������ڵ���0��С�ڵ���100
			for (int i = 0; i < LEN-1;) {
				if (scanf("%f", &s_tmp[i]) == 1 && s_tmp[i] >= 0 && s_tmp[i] <= 100) {
					p->stuScore[i] = s_tmp[i];
					//ͳ���ܷ�
					p->stuScore[LEN-1] += s_tmp[i];
					i++;
				}
				else {
					//������̻�����
					char c_tmp;
					while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
					printf("\n�������!���������룺");
				}
			}
			//����ÿ��ѧ����ƽ���֣����ڳɼ���������Ԫ��
			p->stuScore[LEN - 1] /= (LEN - 1);
			printf("\n�ɼ��޸���ɣ�\n");
		}
		else {
			printf("\n��ѧ�������ڣ�\n");
		}
				
		system("pause");
		system("cls");
	}

}

void deleteStu()
{
	while (1) {
		STU* p = &head, * q = NULL;
		char stuNo[10];			//���������ѧ��

		printf("\n\t\tɾ��ѧ����Ϣ\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("������ѧ��ѧ��(����0�������˵�)��\n");

		///��������У�ˣ�һ��С�ڵ���9���ַ����ַ���
		while (scanf("%9s", stuNo) != 1) {
			//������̻�����
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n�������!���������룺");
		}
		//����Ϊ0ʱ����
		if (!strcmp(stuNo, "0")) {
			return 0;
		}

		//ȷ��Ҫɾ���������Ƿ����
		int index = 0;
		if ((index = findIndex(stuNo)) > 0) {
			//ѭ����pָ��Ҫɾ���ڵ��ǰһ���ڵ�
			for (int i = 0; i < index - 1; i++) {
				p = p->next;
			}
			//qָ��Ҫɾ���ڵ㣬p��nextָ��Ҫɾ���ڵ����һ���ڵ�
			q = p->next;

			//���Ҫɾ����ѧ����Ϣ
			printf("ѧ�ţ�%s��������%s���༶��%d\n�ɼ���", q->stuNo, q->stuName, q->stuClass);
			for (int i = 0; i < LEN; i++) {
				if (i == (LEN - 1)) {
					printf(" ƽ����:");
				}
				printf(" %.1f ", q->stuScore[i]);
			}

			//ɾ��ȷ��
			printf("\n\nȷ��ɾ����������yɾ������������ȡ����");
			//������̻�����
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			//��������У�ˣ���ȡһ���ַ���y��n
			char ch;
			if (scanf("%c", &ch) == 1 && ch == 'y') {
				//ɾ���ڵ�
				p->next = q->next;
				free(q);
				printf("\n��ѧ����Ϣ��ɾ����\n");
			}
			else {
				printf("\nɾ��������ȡ����\n");
			}

		}
		else {
			printf("\n��ѧ�������ڣ�\n");
		}

		system("pause");
		system("cls");
	}

}

int findIndex(char* no)
{
	STU* p = &head;
	int count = 0;
	while (p->next != NULL) {
		p = p->next;
		count++;
		//�Ƚ�ѧ���Ƿ���ͬ
		if (!strcmp(no, p->stuNo)) {
			return count;
		}	
	}

	return 0;
}

STU* findStu(char* no)
{
	STU* p = &head;
	
	while (p->next != NULL) {
		p = p->next;
		//�Ƚ�ѧ���Ƿ���ͬ
		if (!strcmp(no, p->stuNo)) {
			return p;
		}
	}

	return NULL;
}

int findClass(int class)
{
	STU* p = &head;
	int count = 0;
	while (p->next != NULL) {
		p = p->next;
		count++;
		//�Ƚϰ༶���Ƿ���ͬ
		if (p->stuClass == class) {
			return 1;
		}
	}

	return 0;
}

void showByClass()
{
	while (1) {
		STU* p = &head;
		int stuClass = 0;		//��������İ༶��

		printf("\n\t\t�鿴ָ���༶ѧ���ɼ�\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("������༶��(����0�������˵�)��");

		//��������У�ˣ���ȡһ���������ݣ�����0
		while (scanf("%d", &stuClass) != 1 || stuClass < 0) {
			//������̻�����
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n�������!���������룺");
		}
		//����Ϊ0����
		if (stuClass == 0) {
			return 0;
		}

		//ȷ������İ༶ѧ����Ϣ��Ϊ��
		if (findClass(stuClass)) {
		
			printf("\tѧ��\t����\t�༶\t�ɼ�1\t�ɼ�2\t�ɼ�3\t�ɼ�4\t�ɼ�5\t�ɼ�6\t�ɼ�7\t�ɼ�8\t�ɼ�9\t�ɼ�10\t10��ƽ����\n");
			while (p->next != NULL) {
				p = p->next;
				//ɸѡ���ָ���༶��ѧ����Ϣ
				if (p->stuClass == stuClass) {
					printf("%11s%11s%6d", p->stuNo, p->stuName, p->stuClass);
					for (int i = 0; i < LEN; i++) {
						printf("%8.1f", p->stuScore[i]);
					}
					printf("\n");
				}
			}
			//���ÿ����ҵ��ƽ����
			printf("����ƽ����\t\t    ");
			float* avr = getEveryTimeAverage(stuClass);
			for (int i = 0; i < LEN; i++) {
				printf("%8.1f", avr[i]);
			}		
		}
		else {
			printf("\nû�иð༶��ѧ����Ϣ��");
		}

		printf("\n\n");
		system("pause");
		system("cls");
	}

}

void showAll()
{
	STU* p = &head;
	
	//ȷ������Ϊ��
	if (p->next != NULL) {
		
		printf("\tѧ��\t����\t�༶\t�ɼ�1\t�ɼ�2\t�ɼ�3\t�ɼ�4\t�ɼ�5\t�ɼ�6\t�ɼ�7\t�ɼ�8\t�ɼ�9\t�ɼ�10\t10��ƽ����\n");
		while (p->next != NULL) {
			p = p->next;
			printf("%11s%11s%6d", p->stuNo, p->stuName, p->stuClass);
			for (int i = 0; i < LEN; i++) {
				printf("%8.1f", p->stuScore[i]);
			}
			printf("\n");
		}
		//���ÿ����ҵ��ƽ����
		printf("����ƽ����\t\t    ");
		float* avr = getEveryTimeAverage(0);
		for (int i = 0; i < LEN; i++) {
			printf("%8.1f", *(avr+i));
		}
	}
	else {
		printf("\nû��ѧ����Ϣ��");
	}

	printf("\n\n");
	system("pause");

}

float* getEveryTimeAverage(int class)
{
	STU* p = &head;
	//C ��֧���ں����ⷵ�ؾֲ������ĵ�ַ�����Ƕ���ֲ�����Ϊ static ������
	static float average[LEN];		//����ÿ����ҵ��ƽ����
	//ÿ�μ���ǰ��0
	for (int i = 0; i < LEN; i++) {
		average[i] = 0.0f;
	}

	//����ÿ����ҵ��ƽ���֣�count��������
	int count = 0;
	for (int i = 0; i < LEN; i++) {
		p = &head;
		count = 0;
		while (p->next != NULL) {
			p = p->next;
			//����&&��·���ã�ɸѡ����ѧ����Ϣ����ָ���༶ѧ����Ϣ
			if (class == 0 || p->stuClass == class) {
				count++;
				average[i] += p->stuScore[i];
			}
		}
		average[i] /= count;
	}

	return average;
}

void loadFromFile()
{
	char filename[100];		//�ļ���
	FILE* file = NULL;
	STU* stu = NULL, * p = &head;

	printf("\n\t\t���ļ�����ѧ����Ϣ\n\n");
	printf("-----------------------------------------------------------------------------------\n");
	printf("\t�ļ����ݸ�ʽҪ������,ÿ�ж�Ӧһ��ѧ����Ϣ��\n");
	printf("ѧ��  ����  �༶  �ɼ�1 �ɼ�2 �ɼ�3 �ɼ�4 �ɼ�5 �ɼ�6 �ɼ�7 �ɼ�8 �ɼ�9 �ɼ�10\n");
	printf("-----------------------------------------------------------------------------------\n\n");

	printf("���������·�����ļ�����(��ʽ�磺D:\\\\PersonData\\\\C_Source\\\\testload.txt ,����0�˳�)��\n");
	//����У��
	while (scanf("%s", filename) != 1 || (file = fopen(filename, "r")) == NULL) {
		char temp[100] = "";
		if (!strcmp("0", strcat(temp, filename))) {
			return 0;
		}
		//������̻�����
		char c_tmp;
		while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
		printf("\n������Ч!���������룺");
	}
		
	//�ҵ����һ���ڵ㣬����ǰ�ڵ���������
	while (p->next != NULL) {
		p = p->next;
	}

	//���ļ�һ���еĶ�ȡ��Ϣ���浽�����У�count������ӵĸ���
	int count = 0;
	//�ж��Ƿ��ļ�ĩβ
	while (!feof(file)) {
		
		//�½��ڵ㣬����ռ䣬���ݳ�ʼ��
		while ((stu = (STU*)malloc(sizeof(STU))) == NULL);
		for (int i = 0; i < LEN; i++) {
			stu->stuScore[i] = 0.0f;
		}
		stu->next = NULL;

		////�����á�������ӡ���ļ���ȡ������
		//fscanf(file, "%9s%9s%d%f%f%f%f%f%f%f%f%f%f%[^\n]%*c",
		//	&stu->stuNo, &stu->stuName, &stu->stuClass, &stu->stuScore[0], &stu->stuScore[1],
		//	&stu->stuScore[2], &stu->stuScore[3], &stu->stuScore[4], &stu->stuScore[5],
		//	&stu->stuScore[6], &stu->stuScore[7], &stu->stuScore[8], &stu->stuScore[9]);
		//printf("%-11s%-11s%6d%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f\n",
		//	stu->stuNo, stu->stuName, stu->stuClass, stu->stuScore[0], stu->stuScore[1],
		//	stu->stuScore[2], stu->stuScore[3], stu->stuScore[4], stu->stuScore[5],
		//	stu->stuScore[6], stu->stuScore[7], stu->stuScore[8], stu->stuScore[9]);


		//����У��:������������(������Ϣ���붼Ҫ��)��ѧ��Ψһ���༶�Ŵ���0���������ڵ���0��С�ڵ���100
		//���ȶ�ȡ����Ϣ�����ȡ10�ɼ�
		if (fscanf(file, "%9s%9s%d", &stu->stuNo, &stu->stuName, &stu->stuClass) == 3 && !findIndex(stu->stuNo) && stu->stuClass > 0) {
			int i = 0;
			for (; i < LEN - 1; ) {
				if (fscanf(file,"%f", &stu->stuScore[i]) == 1 && stu->stuScore[i] >= 0 && stu->stuScore[i] <= 100) {
					//�����ܷ�
					stu->stuScore[LEN - 1] += stu->stuScore[i];
					i++;
				}
				else {
					//��ǰ��Ϊ��Ч���ݣ�ֹͣ��ȡ
					break;
				}
			}
			//���ļ���ȡ��������������ӽڵ�
			if (i == (LEN - 1)) {
				//����ƽ����
				stu->stuScore[LEN - 1] /= (LEN - 1);
				//��ӽڵ�
				p->next = stu;
				p = p->next;
				count++;
			}
		}
		//������ǰ��δ����Ķ�������
		//%*s:����֮����ַ���
		//%[^\n]��ʾ��ȡ'\n'֮��������ַ���֮���%*c��ʾ���Զ�ȡ��'\n'������˵��ȡ'\n'�������档
		fscanf(file, "%[^\n]%*c");

		//�ڱ��취
		//if (fscanf(file,"%9s%9s%d%f%f%f%f%f%f%f%f%f%f%[^\n]%*c",
		//	&stu->stuNo, &stu->stuName, &stu->stuClass, &stu->stuScore[0], &stu->stuScore[1],
		//	&stu->stuScore[2], &stu->stuScore[3], &stu->stuScore[4], &stu->stuScore[5],
		//	&stu->stuScore[6], &stu->stuScore[7], &stu->stuScore[8], &stu->stuScore[9]) >= 13
		//	&& !findIndex(stu->stuNo) && stu->stuClass > 0
		//	&& stu->stuScore[0] >= 0 && stu->stuScore[0] <= 100
		//	&& stu->stuScore[1] >= 0 && stu->stuScore[1] <= 100
		//	&& stu->stuScore[2] >= 0 && stu->stuScore[2] <= 100
		//	&& stu->stuScore[3] >= 0 && stu->stuScore[3] <= 100
		//	&& stu->stuScore[4] >= 0 && stu->stuScore[4] <= 100
		//	&& stu->stuScore[5] >= 0 && stu->stuScore[5] <= 100
		//	&& stu->stuScore[6] >= 0 && stu->stuScore[6] <= 100
		//	&& stu->stuScore[7] >= 0 && stu->stuScore[7] <= 100
		//	&& stu->stuScore[8] >= 0 && stu->stuScore[8] <= 100
		//	&& stu->stuScore[9] >= 0 && stu->stuScore[9] <= 100) {
		//	
		//	//����ƽ����
		//	for (int i = 0; i < LEN - 1; i++) {
		//		stu->stuScore[LEN - 1] += stu->stuScore[i];
		//	}
		//	stu->stuScore[LEN - 1] /= (LEN - 1);
		//	//��ӽڵ�
		//	p->next = stu;
		//	p = p->next;
		//	count++;
		//}

	}
	fclose(file);

	if (count > 0) {
		printf("\n�ɹ����%d��ѧ����Ϣ��", count);
	}
	else {
		printf("\n�ļ�����Ч��ʽ��ѧ����Ϣ��");
	}

	printf("\n\n");
	system("pause");
	system("cls");

}

void saveToFile()
{
	STU* p = &head;
	FILE* file = NULL;
	char filename[100];


	printf("\n\t\t����ѧ����Ϣ���ļ�\n\n");
	printf("-----------------------------------------------------------------------------------\n\n");
	
	printf("���������·�����ļ�����(��ʽ�磺D:\\\\C_Source\\\\testload.txt�����ֻ�����ļ�����������Դ����Ŀ¼�� ,����0�����˵�)��\n");
	char temp[100] = "";
	int result = 0;
	//����У��
	while (scanf("%s", filename) != 1 || !(result = strcmp("0", strcat(temp, filename))) || (file = fopen(filename, "w")) == NULL) {
		if (!result) {
			return 0;
		}
		//������̻�����
		char c_tmp;
		while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
		printf("\n������Ч!���������룺");
	}
		
	int count = 0;
	fprintf(file,"    ѧ��    ����    �༶  �ɼ�1  �ɼ�2  �ɼ�3  �ɼ�4  �ɼ�5  �ɼ�6  �ɼ�7  �ɼ�8  �ɼ�9  �ɼ�10  10��ƽ����\n");
	while (p->next != NULL) {
		p = p->next;

		//�����������Ϣ����ѭ������ɼ���ƽ����
		if (fprintf(file, "%11s%11s%6d", p->stuNo, p->stuName, p->stuClass) == (11+11+6)) {
			int i = 0;
			for (; i < LEN ; i++ ) {
				if (fprintf(file, "%8.1f", p->stuScore[i]) != 8) {
					fclose(file);
					return;
				}
			}
			if (i == LEN) {
				fprintf(file, "\n");
				count++;
			}
		}
		else {
			fclose(file);
			return;
		}

		//�ڱ��취
		////fprintf����д���"�ַ�����"
		//if (fprintf(file, "%-11s%-11s%6d%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f\n", p->stuNo, p->stuName, p->stuClass, p->stuScore[0], p->stuScore[1],
		//	p->stuScore[2], p->stuScore[3], p->stuScore[4], p->stuScore[5],
		//	p->stuScore[6], p->stuScore[7], p->stuScore[8], p->stuScore[9],p->stuScore[10]) == (11+11+6+8*11+1)) {
		//	count++;
		//}
	}
	//��ÿ�γɼ���ƽ����д���ļ�
	fprintf(file,"����ƽ����\t ");
	float* avr = getEveryTimeAverage(0);
	for (int i = 0; i < LEN; i++) {
		fprintf(file,"%8.1f", avr[i]);
	}
	fclose(file);

	if (count > 0) {
		printf("\n�ɹ�����%d��ѧ����Ϣ���ļ���", count);
	}
	else {
		printf("\n��ѧ����Ϣ���浽�ļ���");
	}

	printf("\n\n");
	system("pause");
	system("cls");

}
