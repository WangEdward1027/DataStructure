// HashMap.h
#include <stdint.h>	//别名unit32_t的头文件 

typedef char* K;
typedef char* V;

//拉链法的哈希桶是链表，链表结点定义如下：
typedef struct node {
	K key;
	V val;
	struct node* next;
} Node;

typedef struct {
	Node** table;
	int size;     //实际大小
	int capacity; //最大容量
	uint32_t hashseed;
} HashMap;

HashMap* hashmap_create();
void hashmap_destroy(HashMap* map);
V hashmap_put(HashMap* map, K key, V val);
V hashmap_get(HashMap* map, K key);
void hashmap_delete(HashMap* map, K key);
static uint32_t hash(const void* key, int len, uint32_t seed);
