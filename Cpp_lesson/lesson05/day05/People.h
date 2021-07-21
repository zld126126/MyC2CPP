#pragma once
class People
{
private:
	int age;
	int sex;

public:
	People();
	People(int age, int sex);
	int getAge();
	int getSex();
	void sayHello();
};

