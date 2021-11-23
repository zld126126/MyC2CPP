#pragma once
#include <string>

const char LOGTYPEINFO[] = "[info]:";
const char LOGTYPEWARN[] = "[warn]:";
const char LOGTYPEDEBUG[] = "[debug]:";
const char LOGTYPEERROR[] = "[error]:";

using namespace std;

template <typename T> void Logger(const T& t);
template <typename T, typename ... Args> void Logger(const T& t, Args ... args);

template <typename T>
void Logger(const T& t){
	cout << t << '\n';
}

template <typename T, typename ... Args>
void Logger(const T& t, Args ... args){
	cout << t << " ";
	Logger(args...);//递归解决，利用模板推导机制，每次取出第一个，缩短参数包的大小。
}