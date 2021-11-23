#pragma once
#include "stdafx.h"

static class Logger{
public:
	template <typename T> static void Print(const T& t);
	template <typename T, typename ... Args> static void Print(const T& t, Args ... args);
};

// TODO 后期调整为成员变量
#define LOGTYPEINFO "[info]:"
#define LOGTYPEWARN "[warn]:"
#define LOGTYPEDEBUG "[debug]:"
#define LOGTYPEERROR "[error]:"

template <typename T>
void Logger::Print(const T& t){
	cout << t << '\n';
}

template <typename T, typename ... Args>
void Logger::Print(const T& t, Args ... args){
	cout << t << " ";
	Logger::Print(args...);//递归解决，利用模板推导机制，每次取出第一个，缩短参数包的大小。
}
