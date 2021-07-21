// lesson12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <stdlib.h>


class Object;
// 类似go中的 type func() 简化方法
typedef void(Object::*SayHi)();
typedef void(Object::*CallaterHandler)();

#define CH(fp) (CallaterHandler)(&fp)

class Object {
public:
	// c++指针
	// void(Object::*SayHi)();
	SayHi sayHi;
};

void threadFunc(Object *target, CallaterHandler handler, int delay) {
	// TODO:延时方法百度一下
	_sleep(3);
	(target->*handler)();
}

// 延时方法
void callater(Object *target, CallaterHandler handler, int delay) {
	std::thread t(threadFunc);
	t.join();
}

class Hello :public Object {
public:
	Hello() {
		// &指向内存地址 (void(Object::*)())是强转
		// sayHi = (void(Object::*)())&Hello::HelloSayHi;
		// sayHi = (SayHi)&Hello::HelloSayHi;
		// 指针执行
		// (this->*sayHi)();

		// 真实示例:延时3秒执行
		//callater(this, (CallaterHandler)(&Hello::HelloSayHi), 3);
		callater(this, CH(Hello::HelloSayHi), 3);
	}

	void HelloSayHi() {
		printf("Hello Cpp\n");
	}
};

int main()
{
	// std::cout << "Hello World!\n";
	Hello *h = new Hello();
	delete h;

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
