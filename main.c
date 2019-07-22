#define _CRT_SECURE_NO_WARNINGS

//定义成绩个数+1,多的那一个存放平均分
#define LEN 11

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//学生信息
typedef struct student {
	char stuNo[10];			//学号
	char stuName[10];		//姓名
	int stuClass;			//班级
	float stuScore[LEN];	//成绩(10)+平均分(1)
	struct student* next;	
}STU;
STU head;	//头结点

int menu();					//菜单
void addStu();				//增加学生信息
void showStu();				//显示某个学生信息
void modifyStu();			//修改某个学生信息
void deleteStu();			//删除某个学生信息
int findIndex(char* no);	//查找某个学生是否已经存在，存在返回索引，否则返回0
STU* findStu(char* no);		//查找某个学生是否已经存在，存在返回指针，否则返回NULL
int findClass(int class);	//查找某个班级号是否已经存在，存在返回1，否则返回0
void showByClass();			//显示某个班级所有学生信息及成绩
void showAll();				//显示所有学生信息及成绩
float* getEveryTimeAverage(int class);	//获取某个班所有人每次的平均分，class=0时返回所有人的平均分
void loadFromFile();		//从文件加载信息
void saveToFile();			//导出信息到文件

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
	printf("\t\t菜单\n\n");
	printf("\t1.添加学生信息\n");
	printf("\t2.查看学生成绩\n");
	printf("\t3.修改学生成绩\n");
	printf("\t4.删除学生信息\n");
	printf("\t5.查看指定班级学生成绩及平均分\n");
	printf("\t6.查看所有学生成绩及平均分\n");
	printf("\t7.从文件导入信息\n");
	printf("\t8.导出信息到文件\n");
	printf("\t0.退出\n\n");
	printf("-------------------------------------------\n");
	printf("请输入需要的操作对应的序号：");

	while (scanf("%d", &no) != 1 || no < 0 || no > 8) {
		//fflush(stdin);	//VS2015开始不再支持，以后不要再使用！！！
		//清除键盘缓冲区
		char tmp;
		while ((tmp = getchar()) != '\n' && tmp != EOF);
		printf("\n输入错误!请重新输入：");
	}

	return no;
}

void addStu()
{
	while (1) {
		STU* stu = NULL, * p = &head;
		//确保创建的新节点分配到空间
		while ((stu = (STU*)malloc(sizeof(STU))) == NULL);
		//新节点数据初始化
		for (int i = 0; i < LEN; i++) {
			stu->stuScore[i] = 0.0f;
		}
		stu->next = NULL;

		//打印提示信息
		printf("\n\t\t添加学生信息\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("请输入学生信息(格式：学号  姓名  班级,输入0-0-0返回主菜单)：\n");
				
		//输入数据校核：读取三个数据，学号不重复，班级号大于0
		while (scanf("%9s %9s %d", stu->stuNo, stu->stuName, &stu->stuClass) != 3 || findIndex(stu->stuNo) > 0 || stu->stuClass < 0) {
			//清除键盘缓冲区
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n输入错误!请重新输入：");
		}
		//输入全0信息返回
		if (!strcmp(stu->stuNo, "0") && !strcmp(stu->stuName, "0") && stu->stuClass == 0) {
			free(stu);
			return 0;
		}

		//准备添加新节点
		//找到最后一个节点，将当前节点添加在其后
		while (p->next != NULL) {
			p = p->next;
		}
		//添加新节点
		p->next = stu;
	
		printf("\n学生信息添加成功！\n");
		system("pause");
		system("cls");
	}

}

void showStu()
{
	while (1) {
		STU* p = NULL;
		char stuNo[10];	//接受输入的学号

		//输出提示信息
		printf("\n\t\t查找学生信息\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("请输入学生学号(输入0返回主菜单)：\n");

		//输入数据校核：读取一个小于等于9个字符的字符串
		while (scanf("%9s", stuNo) != 1) {
			//清除键盘缓冲区
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n输入错误!请重新输入：");
		}
		//输入数据为0时返回
		if (!strcmp(stuNo,"0")) {
			return 0;
		}
		
		//查找输入的学号对应的节点
		if ((p = findStu(stuNo)) != NULL) {
			//输出查找到的学生信息
			printf("学号：%s，姓名：%s，班级：%d\n成绩：", p->stuNo, p->stuName, p->stuClass);
			for (int i = 0; i < LEN; i++) {
				if (i == (LEN - 1)) {
					printf(" 平均分:");
				}
				printf(" %.1f ", p->stuScore[i]);
			}
			
		}
		else {
			printf("\n该学生不存在！");
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
		char stuNo[10];		//接受输入的学号

		//输出提示信息
		printf("\n\t\t修改学生信息\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("请输入学生学号(输入0返回主菜单)：\n");

		//输入数据校核：一个小于等于9个字符的字符串
		while (scanf("%9s", stuNo) != 1) {
			//清除键盘缓冲区
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n输入错误!请重新输入：");
		}
		//输入为0时返回
		if (!strcmp(stuNo, "0")) {
			return 0;
		}

		//查找输入的学号对应的节点
		if ((p = findStu(stuNo)) != NULL) {
			//输出查找到的学生信息
			printf("学号：%s，姓名：%s，班级：%d\n成绩：", p->stuNo, p->stuName, p->stuClass);
			for (int i = 0; i < LEN; i++) {
				if (i == (LEN - 1)) {
					printf(" 平均分:");
				}
				printf(" %.1f ", p->stuScore[i]);
			}

			//输入修改的成绩
			printf("\n\n请输入学生的10次成绩（每次输入完按回车结束）：");
			float s_tmp[LEN-1];
			//输入数据校核：读取十个成绩，大于等于0，小于等于100
			for (int i = 0; i < LEN-1;) {
				if (scanf("%f", &s_tmp[i]) == 1 && s_tmp[i] >= 0 && s_tmp[i] <= 100) {
					p->stuScore[i] = s_tmp[i];
					//统计总分
					p->stuScore[LEN-1] += s_tmp[i];
					i++;
				}
				else {
					//清除键盘缓冲区
					char c_tmp;
					while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
					printf("\n输入错误!请重新输入：");
				}
			}
			//计算每个学生的平均分，放在成绩数组的最后元素
			p->stuScore[LEN - 1] /= (LEN - 1);
			printf("\n成绩修改完成！\n");
		}
		else {
			printf("\n该学生不存在！\n");
		}
				
		system("pause");
		system("cls");
	}

}

void deleteStu()
{
	while (1) {
		STU* p = &head, * q = NULL;
		char stuNo[10];			//接受输入的学号

		printf("\n\t\t删除学生信息\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("请输入学生学号(输入0返回主菜单)：\n");

		///输入数据校核：一个小于等于9个字符的字符串
		while (scanf("%9s", stuNo) != 1) {
			//清除键盘缓冲区
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n输入错误!请重新输入：");
		}
		//输入为0时返回
		if (!strcmp(stuNo, "0")) {
			return 0;
		}

		//确认要删除的数据是否存在
		int index = 0;
		if ((index = findIndex(stuNo)) > 0) {
			//循环，p指向要删除节点的前一个节点
			for (int i = 0; i < index - 1; i++) {
				p = p->next;
			}
			//q指向要删除节点，p的next指向将要删除节点的下一个节点
			q = p->next;

			//输出要删除的学生信息
			printf("学号：%s，姓名：%s，班级：%d\n成绩：", q->stuNo, q->stuName, q->stuClass);
			for (int i = 0; i < LEN; i++) {
				if (i == (LEN - 1)) {
					printf(" 平均分:");
				}
				printf(" %.1f ", q->stuScore[i]);
			}

			//删除确认
			printf("\n\n确认删除？（输入y删除，输入其他取消）");
			//清除键盘缓冲区
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			//输入数据校核：读取一个字符：y或n
			char ch;
			if (scanf("%c", &ch) == 1 && ch == 'y') {
				//删除节点
				p->next = q->next;
				free(q);
				printf("\n该学生信息已删除！\n");
			}
			else {
				printf("\n删除操作已取消！\n");
			}

		}
		else {
			printf("\n该学生不存在！\n");
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
		//比较学号是否相同
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
		//比较学号是否相同
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
		//比较班级号是否相同
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
		int stuClass = 0;		//接受输入的班级号

		printf("\n\t\t查看指定班级学生成绩\n\n");
		printf("-----------------------------------------------------------------------------------\n\n");
		printf("请输入班级号(输入0返回主菜单)：");

		//输入数据校核：读取一个整形数据，大于0
		while (scanf("%d", &stuClass) != 1 || stuClass < 0) {
			//清除键盘缓冲区
			char c_tmp;
			while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
			printf("\n输入错误!请重新输入：");
		}
		//输入为0返回
		if (stuClass == 0) {
			return 0;
		}

		//确保输入的班级学生信息不为空
		if (findClass(stuClass)) {
		
			printf("\t学号\t姓名\t班级\t成绩1\t成绩2\t成绩3\t成绩4\t成绩5\t成绩6\t成绩7\t成绩8\t成绩9\t成绩10\t10次平均分\n");
			while (p->next != NULL) {
				p = p->next;
				//筛选输出指定班级的学生信息
				if (p->stuClass == stuClass) {
					printf("%11s%11s%6d", p->stuNo, p->stuName, p->stuClass);
					for (int i = 0; i < LEN; i++) {
						printf("%8.1f", p->stuScore[i]);
					}
					printf("\n");
				}
			}
			//输出每次作业的平均分
			printf("单次平均分\t\t    ");
			float* avr = getEveryTimeAverage(stuClass);
			for (int i = 0; i < LEN; i++) {
				printf("%8.1f", avr[i]);
			}		
		}
		else {
			printf("\n没有该班级的学生信息！");
		}

		printf("\n\n");
		system("pause");
		system("cls");
	}

}

void showAll()
{
	STU* p = &head;
	
	//确保链表不为空
	if (p->next != NULL) {
		
		printf("\t学号\t姓名\t班级\t成绩1\t成绩2\t成绩3\t成绩4\t成绩5\t成绩6\t成绩7\t成绩8\t成绩9\t成绩10\t10次平均分\n");
		while (p->next != NULL) {
			p = p->next;
			printf("%11s%11s%6d", p->stuNo, p->stuName, p->stuClass);
			for (int i = 0; i < LEN; i++) {
				printf("%8.1f", p->stuScore[i]);
			}
			printf("\n");
		}
		//输出每次作业的平均分
		printf("单次平均分\t\t    ");
		float* avr = getEveryTimeAverage(0);
		for (int i = 0; i < LEN; i++) {
			printf("%8.1f", *(avr+i));
		}
	}
	else {
		printf("\n没有学生信息！");
	}

	printf("\n\n");
	system("pause");

}

float* getEveryTimeAverage(int class)
{
	STU* p = &head;
	//C 不支持在函数外返回局部变量的地址，除非定义局部变量为 static 变量。
	static float average[LEN];		//保存每次作业的平均分
	//每次计算前置0
	for (int i = 0; i < LEN; i++) {
		average[i] = 0.0f;
	}

	//计算每次作业的平均分，count计算人数
	int count = 0;
	for (int i = 0; i < LEN; i++) {
		p = &head;
		count = 0;
		while (p->next != NULL) {
			p = p->next;
			//利用&&短路作用，筛选所有学生信息或者指定班级学生信息
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
	char filename[100];		//文件名
	FILE* file = NULL;
	STU* stu = NULL, * p = &head;

	printf("\n\t\t由文件加载学生信息\n\n");
	printf("-----------------------------------------------------------------------------------\n");
	printf("\t文件内容格式要求如下,每行对应一条学生信息！\n");
	printf("学号  姓名  班级  成绩1 成绩2 成绩3 成绩4 成绩5 成绩6 成绩7 成绩8 成绩9 成绩10\n");
	printf("-----------------------------------------------------------------------------------\n\n");

	printf("请输入包含路径的文件名称(格式如：D:\\\\PersonData\\\\C_Source\\\\testload.txt ,输入0退出)：\n");
	//数据校核
	while (scanf("%s", filename) != 1 || (file = fopen(filename, "r")) == NULL) {
		char temp[100] = "";
		if (!strcmp("0", strcat(temp, filename))) {
			return 0;
		}
		//清除键盘缓冲区
		char c_tmp;
		while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
		printf("\n输入无效!请重新输入：");
	}
		
	//找到最后一个节点，将当前节点添加在其后
	while (p->next != NULL) {
		p = p->next;
	}

	//从文件一行行的读取信息保存到链表中，count计算添加的个数
	int count = 0;
	//判断是否到文件末尾
	while (!feof(file)) {
		
		//新建节点，分配空间，数据初始化
		while ((stu = (STU*)malloc(sizeof(STU))) == NULL);
		for (int i = 0; i < LEN; i++) {
			stu->stuScore[i] = 0.0f;
		}
		stu->next = NULL;

		////测试用。。。打印从文件读取的数据
		//fscanf(file, "%9s%9s%d%f%f%f%f%f%f%f%f%f%f%[^\n]%*c",
		//	&stu->stuNo, &stu->stuName, &stu->stuClass, &stu->stuScore[0], &stu->stuScore[1],
		//	&stu->stuScore[2], &stu->stuScore[3], &stu->stuScore[4], &stu->stuScore[5],
		//	&stu->stuScore[6], &stu->stuScore[7], &stu->stuScore[8], &stu->stuScore[9]);
		//printf("%-11s%-11s%6d%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f\n",
		//	stu->stuNo, stu->stuName, stu->stuClass, stu->stuScore[0], stu->stuScore[1],
		//	stu->stuScore[2], stu->stuScore[3], stu->stuScore[4], stu->stuScore[5],
		//	stu->stuScore[6], stu->stuScore[7], stu->stuScore[8], stu->stuScore[9]);


		//数据校验:读入数据完整(所有信息必须都要有)，学号唯一，班级号大于0，分数大于等于0，小于等于100
		//①先读取三信息，后读取10成绩
		if (fscanf(file, "%9s%9s%d", &stu->stuNo, &stu->stuName, &stu->stuClass) == 3 && !findIndex(stu->stuNo) && stu->stuClass > 0) {
			int i = 0;
			for (; i < LEN - 1; ) {
				if (fscanf(file,"%f", &stu->stuScore[i]) == 1 && stu->stuScore[i] >= 0 && stu->stuScore[i] <= 100) {
					//计算总分
					stu->stuScore[LEN - 1] += stu->stuScore[i];
					i++;
				}
				else {
					//当前行为无效数据，停止读取
					break;
				}
			}
			//从文件读取的数据完整，添加节点
			if (i == (LEN - 1)) {
				//计算平均分
				stu->stuScore[LEN - 1] /= (LEN - 1);
				//添加节点
				p->next = stu;
				p = p->next;
				count++;
			}
		}
		//跳过当前行未读完的多余数据
		//%*s:忽略之后的字符串
		//%[^\n]表示读取'\n'之外的所有字符；之后的%*c表示忽略读取的'\n'，就是说读取'\n'但不保存。
		fscanf(file, "%[^\n]%*c");

		//②笨办法
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
		//	//计算平均分
		//	for (int i = 0; i < LEN - 1; i++) {
		//		stu->stuScore[LEN - 1] += stu->stuScore[i];
		//	}
		//	stu->stuScore[LEN - 1] /= (LEN - 1);
		//	//添加节点
		//	p->next = stu;
		//	p = p->next;
		//	count++;
		//}

	}
	fclose(file);

	if (count > 0) {
		printf("\n成功添加%d条学生信息！", count);
	}
	else {
		printf("\n文件无有效格式的学生信息！");
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


	printf("\n\t\t保存学生信息到文件\n\n");
	printf("-----------------------------------------------------------------------------------\n\n");
	
	printf("请输入包含路径的文件名称(格式如：D:\\\\C_Source\\\\testload.txt，如果只输入文件名将保存在源代码目录中 ,输入0回主菜单)：\n");
	char temp[100] = "";
	int result = 0;
	//数据校核
	while (scanf("%s", filename) != 1 || !(result = strcmp("0", strcat(temp, filename))) || (file = fopen(filename, "w")) == NULL) {
		if (!result) {
			return 0;
		}
		//清除键盘缓冲区
		char c_tmp;
		while ((c_tmp = getchar()) != '\n' && c_tmp != EOF);
		printf("\n输入无效!请重新输入：");
	}
		
	int count = 0;
	fprintf(file,"    学号    姓名    班级  成绩1  成绩2  成绩3  成绩4  成绩5  成绩6  成绩7  成绩8  成绩9  成绩10  10次平均分\n");
	while (p->next != NULL) {
		p = p->next;

		//①先输出三信息，后循环输出成绩及平均分
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

		//②笨办法
		////fprintf返回写入的"字符总数"
		//if (fprintf(file, "%-11s%-11s%6d%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f%8.1f\n", p->stuNo, p->stuName, p->stuClass, p->stuScore[0], p->stuScore[1],
		//	p->stuScore[2], p->stuScore[3], p->stuScore[4], p->stuScore[5],
		//	p->stuScore[6], p->stuScore[7], p->stuScore[8], p->stuScore[9],p->stuScore[10]) == (11+11+6+8*11+1)) {
		//	count++;
		//}
	}
	//将每次成绩的平均分写入文件
	fprintf(file,"单次平均分\t ");
	float* avr = getEveryTimeAverage(0);
	for (int i = 0; i < LEN; i++) {
		fprintf(file,"%8.1f", avr[i]);
	}
	fclose(file);

	if (count > 0) {
		printf("\n成功保存%d条学生信息到文件！", count);
	}
	else {
		printf("\n无学生信息保存到文件！");
	}

	printf("\n\n");
	system("pause");
	system("cls");

}
