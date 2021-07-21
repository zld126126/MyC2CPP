#pragma once
#include "People.h"
#include <iostream>

// 继承
class Man:public People
{
public:
	Man(int age);
	void sing();

	virtual void sayHello();

	virtual void eat() {
		printf("man eat\n");
	};
	// PersonInterface纯虚函数必须实现
	virtual void desc() {
		printf("man eat\n");
	};
};

