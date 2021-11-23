#pragma once
#include "stdafx.h"

static class Logger{
public:
	template <typename T> static void Print(const T& t);
	template <typename T, typename ... Args> static void Print(const T& t, Args ... args);
};

// TODO ���ڵ���Ϊ��Ա����
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
	Logger::Print(args...);//�ݹ���������ģ���Ƶ����ƣ�ÿ��ȡ����һ�������̲������Ĵ�С��
}
