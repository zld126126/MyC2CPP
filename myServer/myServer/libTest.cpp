#include "stdafx.h"

void LibTest::testMysql(){
	cout << "testMysql" << endl;

	const char user[] = "root";
	const char pswd[] = "root";
	const char host[] = "localhost";
	const char table[] = "dongbao";
	unsigned int port = 3306;
	MYSQL myCont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	int res;
	mysql_init(&myCont);
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES 'utf8'"); //���ñ����ʽ
		res = mysql_query(&myCont, "select * from users");//��ѯ
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					cout << "ID:" << sql_row[1] << endl;
					cout << "NAME:" << sql_row[2] << endl;
				}
			}
		}
		else
		{
			cout << "query sql failed!" << endl;
		}
	}
	else
	{
		cout << "connect failed!" << endl;
	}
	if (result != NULL)
		mysql_free_result(result);
	mysql_close(&myCont);
}

void LibTest::testLua(){
	cout << "testLua" << endl;

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	luaopen_socket_core(lua);
	luaL_dofile(lua, "2lua.lua");
	lua_close(lua);
}

void LibTest::testCurl(){
	cout << "testCurl" << endl;

	curl_global_init(CURL_GLOBAL_ALL); // ����ȫ�ֳ�ʼ��CURL
	CURL* curl = curl_easy_init(); // ��ʼ��CURL���

	if (curl != NULL)
	{
		int my_param = 1;    // �Զ���һ���û�����

		// ����Ŀ��URL
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
		// ���ý��յ�HTTP������������ʱ���õĻص�����
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		// �����Զ������(�ص������ĵ��ĸ�����)
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_param);
		// ִ��һ��URL����
		CURLcode res = curl_easy_perform(curl);
		// ����ɾ�
		curl_easy_cleanup(curl);
	}
}

/**
* һ��curl���յ����ݣ��ͻ���ô˻ص�����
* buffer:���ݻ�����ָ��
* size:���Խ׶����Ƿ���Ϊ1
* nmemb:(memory block)����˴ν��ܵ��ڴ��ĳ���
* userp:�û��Զ����һ������
*/
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
	static int current_index = 0;

	cout << "current:" << current_index++;
	cout << (char*)buffer;
	cout << "---------------" << endl;

	int temp = *(int*)userp;    // �����ȡ�û��Զ������
	return nmemb;
}


static const char MESSAGE[] = "Hello, World!\n";

static const int PORT = 8080;

static void conn_writecb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0)
	{
		printf("flushed answer\n");
		bufferevent_free(bev);
	}
}

static void conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF)
	{
		printf("Connection closed.\n");
	}
	else if (events & BEV_EVENT_ERROR)
	{
		printf("Got an error on the connection: %s\n",
			errno);/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	* timeouts */
	bufferevent_free(bev);
}

static void signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}

static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct bufferevent *bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev)
	{
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	bufferevent_setcb(bev, NULL, conn_writecb, conn_eventcb, NULL);
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_disable(bev, EV_READ);

	bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

void LibTest::testLibevent(){
	cout <<"myLibevent" << endl;

	struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;

	struct sockaddr_in sin;

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new();
	if (!base)
	{
		fprintf(stderr, "Could not initialize libevent!\n");
		return;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (!listener)
	{
		fprintf(stderr, "Could not create a listener!\n");
		return;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0)
	{
		fprintf(stderr, "Could not create/add a signal event!\n");
		return;
	}

	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	free(base);

	cout << "done\n" << endl;
}