#include "People.h"
#include <iostream>

// 默认构造方法
People::People()
{
	this->age = 10;
	this->sex = 2;
}

// 有参构造方法
People::People(int age, int sex)
{
	this->age = age;
	this->sex = sex;
}

int People::getAge()
{
	return this->age;
}

int People::getSex()
{
	return this->sex;
}

void People::sayHello() {
	printf("People Hello Cpp\n");
}
