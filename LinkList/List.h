typedef int E;

typedef struct node {
	E data;
	struct node* next;
} Node;

typedef struct {
	Node* head;
	Node* tail;
	E size;
} List;

//API
List* list_create(void);
void list_destroy(List* list);

//操作
void add_before_head(List* list, E val);   //头插
void add_behind_tail(List* list, E val);   //尾插
void add_node(List* list, int idx, E val); //任意位置插入结点

// 删除第一个值与val相等的结点
void delete_node(List* list, E val);

// 根据索引查找值
Node* find_by_index(List* list, int idx);

// 查找第一个与指定值相等的结点
Node* search_for_value(List* list, E val);
