//头文件:类型的定义、API的声明

typedef int E;

typedef struct{
	E* elements;    //指向堆空间的数组
	int capacity;   //元素的容量
	int size;       //元素的实际个数
} Vector;

//构造函数
Vector* vector_create(void);

//析构函数
void vector_destroy(Vector* v);

//请实现push_back方法
void push_back(Vector* v, E val);
