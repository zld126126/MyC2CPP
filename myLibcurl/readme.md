
- [1.安装 && 下载](#1安装--下载)
- [2.编译lib](#2编译lib)
- [3.新建一个空的解决方案-vc-A](#3新建一个空的解决方案-vc-a)
- [4.准备lib库](#4准备lib库)
- [5.核心代码](#5核心代码)
- [6.各种出错解决方案:](#6各种出错解决方案)
  - [6.1 LNK2005错误 :error LNK2005: 已经在 libcmtd.lib(dbgheap.obj) 中定义](#61-lnk2005错误-error-lnk2005-已经在-libcmtdlibdbgheapobj-中定义)
  - [6.2 error LNK2001: 无法解析的外部符号 __imp__curl_easy_cleanup](#62-error-lnk2001-无法解析的外部符号-__imp__curl_easy_cleanup)
- [7.参考文章](#7参考文章)

## 1.安装 && 下载
    https://curl.se/libcurl/

## 2.编译lib
    按需要:curl-7.56.1\projects\Windows 选择VC版本直接编译.lib文件

## 3.新建一个空的解决方案-vc-A
    C/C++ -->> 预处理器定义 -->> WIN32;_DEBUG;_CONSOLE;_LIB;%(PreprocessorDefinitions);WIN32_LEAN_AND_MEAN;BUILDING_LIBCURL;
    C/C++ -->> 附加包含目录 -->> ../;

    链接器 -->> 附加依赖项 -->> libcurld.lib;wldap32.lib;ws2_32.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)
    链接器 -->> 忽略特定默认库 -->> libcmtd.lib
    链接器 -->> 附加库目录 -->> ../lib;

## 4.准备lib库
    拷贝curl的include/curl文件夹到A
    拷贝curl的.lib文件到A/lib

## 5.核心代码
```
    #include <iostream>
#include <curl/curl.h>
#include <string>
using namespace std;

/**
// curl_test.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
#include <curl/curl.h>

using namespace std;

/**
* 一旦curl接收到数据，就会调用此回调函数
* buffer:数据缓冲区指针
* size:调试阶段总是发现为1
* nmemb:(memory block)代表此次接受的内存块的长度
// curl_test.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
#include <curl/curl.h>

using namespace std;

/**
* 一旦curl接收到数据，就会调用此回调函数
* buffer:数据缓冲区指针
* size:调试阶段总是发现为1
* nmemb:(memory block)代表此次接受的内存块的长度
* userp:用户自定义的一个参数
*/
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	static int current_index = 0;

	cout << "current:" << current_index++;
	cout << (char*)buffer;
	cout << "---------------" << endl;

	int temp = *(int*)userp;    // 这里获取用户自定义参数
	return nmemb;
}

int main(int argc, char* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL); // 首先全局初始化CURL
	CURL* curl = curl_easy_init(); // 初始化CURL句柄

	if (NULL == curl)
	{
		return 0;
	}

	int my_param = 1;    // 自定义一个用户参数

	// 设置目标URL
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
	// 设置接收到HTTP服务器的数据时调用的回调函数
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	// 设置自定义参数(回调函数的第四个参数)
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_param);
	// 执行一次URL请求
	CURLcode res = curl_easy_perform(curl);
	// 清理干净
	curl_easy_cleanup(curl);

	system("pause");
	return 0;
}
```

## 6.各种出错解决方案:
   
### 6.1 LNK2005错误 :error LNK2005: 已经在 libcmtd.lib(dbgheap.obj) 中定义
    https://blog.csdn.net/stoneboy100200/article/details/8216257
    项目属性-配置属性-链接器-输入-忽略特定的库：libcmtd.lib

### 6.2 error LNK2001: 无法解析的外部符号 __imp__curl_easy_cleanup
    https://blog.csdn.net/yangchuangbao/article/details/80829966
    
    1、给工程添加依赖的库：项目->属性->链接器->输入->附加依赖项，把libcurl.lib ws2_32.lib winmm.lib wldap32.lib添加进去
        注意，debug配置用libcurld.lib
    2、加入预编译选项：项目->属性->c/c++ ->预处理器->预处理器，把  ;BUILDING_LIBCURL;HTTP_ONLY复制进去（注意不要丢了";"）

## 7.参考文章
    https://blog.csdn.net/arbboter/article/details/43448189    