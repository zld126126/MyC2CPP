#pragma once
#include <iostream>

// 纯虚类:类似interface java/go
class PersonInterface {
public:
	// 纯虚函数
	virtual void desc() = 0;
};

class People :public PersonInterface
{
private:
	int age;
	int sex;

public:
	People();
	People(int age, int sex);
	int getAge();
	int getSex();
	void sing();
	// 虚函数也需要实现
	virtual void sayHello();
	virtual void eat();
	// PersonInterface纯虚函数必须实现
	virtual void desc() {
		printf("People eat\n");
	};
};


