# StudentScoreManageSystem
# 学生成绩管理系统（命令行版）

### 功能菜单界面

		菜单

	1.添加学生信息
	2.查看学生成绩
	3.修改学生成绩
	4.删除学生信息
	5.查看指定班级学生成绩及平均分
	6.查看所有学生成绩及平均分
	7.从文件导入信息
	8.导出信息到文件
	0.退出

### 学生信息存储结构设计
``` 
//学生信息
typedef struct student {
char stuNo[10];			//学号
char stuName[10];		//姓名
int stuClass;			//班级
float stuScore[LEN];	        //成绩+平均分
struct student* next;
}STU;
``` 
### 功能函数
``` 
int menu();				//菜单
void addStu();				//增加学生信息
void showStu();				//显示某个学生信息
void modifyStu();			//修改某个学生信息
void deleteStu();			//删除某个学生信息
int findIndex(char* no);	        //查找某个学生是否已经存在，存在返回索引，否则返回0
STU* findStu(char* no);		        //查找某个学生是否已经存在，存在返回指针，否则返回NULL
int findClass(int class);	        //查找某个班级号是否已经存在，存在返回1，否则返回0
void showByClass();			//显示某个班级所有学生信息及成绩
void showAll();				//显示所有学生信息及成绩
float* getEveryTimeAverage(int class);	//获取某个班所有人每次的平均分，class=0时返回所有人的平均分
void loadFromFile();		        //从文件加载信息
void saveToFile();			//导出信息到文件
``` 