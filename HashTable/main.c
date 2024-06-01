#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "HashMap.h"

int main(void) {
	//1.创建空的哈希表
	HashMap* map = hashmap_create();
	printf("map->size = %d\n", map->size);
	printf("map->capaticy = %d\n\n", map->capacity);

	//2.添加键值对
	hashmap_put(map, "liuqiangdong", "zhangzetian");
	hashmap_put(map, "wangbaoqiang", "marong");
	hashmap_put(map, "wenzhang", "mayili");
	printf("map->size = %d\n", map->size);
	printf("map->capaticy = %d\n\n", map->capacity);

	hashmap_put(map, "jianailiang", "lixiaolu");
	printf("map->size = %d\n", map->size);
	printf("map->capaticy = %d\n\n", map->capacity);

	//3.查找
	V val1 = hashmap_get(map, "liuqiangdong");
	V val2 = hashmap_get(map, "wangbaoqiang");
	V val3 = hashmap_get(map, "peanut");
	printf("%s\n", val1);
	printf("%s\n", val2);
	printf("%s\n\n", val3);

	//4.删除元素
	hashmap_delete(map, "liuqiangdong");

	//删后再查找
	val1 = hashmap_get(map, "liuqiangdong");
	val2 = hashmap_get(map, "wangbaoqiang");
	val3 = hashmap_get(map, "peanut");
	printf("%s\n", val1);
	printf("%s\n", val2);
	printf("%s\n\n", val3);

	//5.销毁
	hashmap_destroy(map);

	return 0;
}
