#include <stdio.h>
#include <stdlib.h>

#define ObjectCreate(Type) malloc(sizeof(Type))

//void(*OnDelete)(struct Object*) void* 无类型指针
#define ObjectField \
	void(*OnDelete)(void*)

#define ObjectDelete(obj) {\
	obj->OnDelete(obj); \
	free(obj);\
};\

typedef struct {
	ObjectField;
} Object;

Object* ObjectAdd() {
	return ObjectCreate(Object);
}

//void ObjectDelete(Object *obj) {
//	obj->OnDelete(obj);
//	free(obj);
//}

void ObjectOnDelete(Object *obj) {
	printf("ObjectOnDel \n");
}

Object* ObjectInit(Object *obj) {
	obj->OnDelete = ObjectOnDelete;
	printf("ObjectInit \n");
	return obj;
}

typedef struct {
	ObjectField;
	int age;
	void(*sayHello)();
}People;

void PeopleSay() {
	printf("PeopleSay:Hello World! \n");
}

//People* Add() {
//	return malloc(sizeof(People));
//}

void PeopleOnDel(People *p) {
	ObjectOnDelete(p);
	printf("PeopleOnDel \n");
}

People* PeopleInit(People *p, int age) {
	ObjectInit((Object*)p);
	p->age = age;
	p->sayHello = PeopleSay;
	p->OnDelete = PeopleOnDel;
	printf("PeopleInit \n");
	return p;
}

int main() {
	// 原始写法
	// People *p = PeopleInit(Add(), 100);
	// 面向对象写法 继承Object类
	People *p = PeopleInit(ObjectCreate(People), 100);
	p->sayHello();
	ObjectDelete(p);
	return 0;
}