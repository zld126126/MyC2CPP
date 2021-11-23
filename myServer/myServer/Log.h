#pragma once
#include <string>

using namespace std;
static class Logger{
public:
	template <typename T> static void Print(const T& t);
	template <typename T, typename ... Args> static void Print(const T& t, Args ... args);
	static string LOGTYPEINFO;
	static string LOGTYPEWARN;
	static string LOGTYPEDEBUG;
	static string LOGTYPEERROR;
};

string Logger::LOGTYPEINFO = "[info]:";
string Logger::LOGTYPEWARN = "[warn]:";
string Logger::LOGTYPEDEBUG = "[debug]:";
string Logger::LOGTYPEERROR = "[error]:";

template <typename T>
void Logger::Print(const T& t){
	cout << t << '\n';
}

template <typename T, typename ... Args>
void Logger::Print(const T& t, Args ... args){
	cout << t << " ";
	Logger::Print(args...);//递归解决，利用模板推导机制，每次取出第一个，缩短参数包的大小。
}