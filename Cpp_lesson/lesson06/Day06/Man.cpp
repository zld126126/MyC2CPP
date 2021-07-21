#include "Man.h"
#include <iostream>
// 执行父类的构造方法
Man::Man(int age):People(age,1)
{
	
}

void Man::sayHello()
{
	// 执行父类方法
	People::sayHello();
	printf("man say hello cpp\n");
}
