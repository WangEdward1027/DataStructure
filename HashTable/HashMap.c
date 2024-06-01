#include "HashMap.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 8
#define LOAD_FACTOR 0.75

//1.创建：创建空的哈希表
HashMap* hashmap_create(void) {
	HashMap* map = malloc(sizeof(HashMap));

	map->table = calloc(DEFAULT_CAPACITY, sizeof(Node*));
	map->size = 0;
	map->capacity = DEFAULT_CAPACITY;
	map->hashseed = time(NULL);

	return map;
}

//2.销毁
void hashmap_destroy(HashMap* map) {
	//1.释放所有的结点(遍历哈希表)
	for (int i = 0; i < map->capacity; i++) {
		Node* curr = map->table[i];         
		while (curr != NULL) {
			Node* next = curr->next;
			free(curr);
			curr = next;
		} 
	}
	//2.释放动态数组
	free(map->table);
	//3.释放HashMap结构体
	free(map);
}

/* murmurhash2 */
// key: 关键字的地址，len: 关键字的字节长度，seed: 哈希种子，避免攻击
static uint32_t hash(const void* key, int len, uint32_t seed) {
	const uint32_t m = 0x5bd1e995;
	const int r = 24;
	uint32_t h = seed ^ len;
	const unsigned char* data = (const unsigned char*)key;
	while (len >= 4) {
		uint32_t k = *(uint32_t*)data;
		k *= m;
		k ^= k >> r;
		k *= m;
		h *= m;
		h ^= k;
		data += 4;
		len -= 4;
	}
	switch (len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
		h *= m;
	};
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;
	return h;
}

//6.扩容
void grow_capacity(HashMap* map) {
	int new_capacity = 2 * map->capacity; 

	Node** new_table = calloc(new_capacity, sizeof(Node*));  
	if (!new_table) {
		printf("calloc failed of new_arr in grow_capacity\n");
		exit(1);
	}

	//重新映射(rehash)：扩容后，哈希表的容量改变了，每个键的哈希值和相应的索引位置也需要重新计算。
	map->hashseed = time(NULL)-10086;

	for (int i = 0; i < map->capacity; i++) {
		Node* curr = map->table[i];      
		while (curr) {
			Node* next = curr->next;
			//使用新的容量重新计算哈希值并找到新的索引
			int new_idx = hash(curr->key, strlen(curr->key), map->hashseed) % new_capacity;
			//将旧哈希表当前节点插入到新表的相应位置：头插法
			curr->next = new_table[new_idx];	//curr下一个指向新位置
			new_table[new_idx] = curr;			//新位置首元素就是curr结点，完成头插
			curr = next;
		}
	}

	//释放旧的表
	free(map->table);
	//更新结构体信息
	map->capacity = new_capacity;
	map->table = new_table;
	return;
}

//3.添加 put：返回旧值,若是新结点则返回NULL
//(1)如果key不存在，则添加(key, val), 返回NULL
//(2)如果key存在，更新key关联的值，并返回原来关联的值。
V hashmap_put(HashMap* map, K key, V val) {
	//对key进行哈希，判断key在哪个哈希桶中(哪一条链表中)
	int idx = hash(key, strlen(key), map->hashseed) % map->capacity;

	//遍历链表
	Node* curr = map->table[idx];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			//b.更新key关联的值，并返回原来的值
			V oldval = curr->val;
			curr->val = val;
			return oldval;
		}
		curr = curr->next;
	}
	//a.添加一个结点保存键值对 key-val，并返回NULL
	//判断扩容:如果达到负载因子，则扩容
	if( ((float)map->size+1)/map->capacity > LOAD_FACTOR){
		grow_capacity(map);
		idx = hash(key, strlen(key), map->hashseed) % map->capacity; //重新计算索引
	}

	//创建结点
	Node* new_node = malloc(sizeof(Node));
	new_node->key = key;
	new_node->val = val;
	//头插法
	new_node->next = map->table[idx];
	map->table[idx] = new_node;
	map->size++;

	return NULL;
}

//4.查找：根据key，返回对应的value
V hashmap_get(HashMap* map, K key) {
	//对key进行哈希，判断key在哪个哈希桶中
	int idx = hash(key, strlen(key), map->hashseed) % map->capacity;
	//遍历链表
	Node* curr = map->table[idx];
	while (curr != NULL) {
		if (strcmp(curr->key, key) == 0) {
			return curr->val;
		}
		curr = curr->next;
	}
	return NULL;
}

//5.删除：删除键值对，如果key不存在，则什么也不做
void hashmap_delete(HashMap* map, K key) {
	//对key进行哈希，判断key在哪个哈希桶中
	int idx = hash(key, strlen(key), map->hashseed) % map->capacity;
	//遍历链表
	Node* prev = NULL;
	Node* curr = map->table[idx];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			//删除curr结点
			if (prev == NULL) {
				map->table[idx] = curr->next;
			}else{
				prev->next = curr->next;
			}
			free(curr);
			map->size--;
			return;
		}
		prev = curr;
		curr = curr->next;
	} // curr == NULL
}
