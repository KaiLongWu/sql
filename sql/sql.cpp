#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libmysql.lib")

const char * user = "root";
const char * key  = "Wkl201114";
const char * db = "student";
unsigned int port = 3306;

MYSQL connect_database() {
    //必备的一个数据结构
    MYSQL mydata;
    //初始化数据库
    if (0 == mysql_library_init(0, NULL, NULL)) {
        cout << "mysql_library_init() succeed" << endl;
    }
    else {
        cout << "mysql_library_init() failed" << endl;
    }

    //初始化数据结构
    if (NULL != mysql_init(&mydata)) {
        cout << "mysql_init() succeed" << endl;
    }
    else {
        cout << "mysql_init() failed" << endl;
    }
    //在连接数据库之前，设置额外的连接选项
    //可以设置的选项很多，这里设置字符集，否则无法处理中文
    if (0 == mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk")) {
        cout << "mysql_options() succeed" << endl;
    }
    else {
        cout << "mysql_options() failed" << endl;
    }
    //连接数据库
    if (NULL!= mysql_real_connect(&mydata, "localhost", user, key, db,port, NULL, 0))
    {
        cout << "mysql_real_connect() succeed" << endl;
        return mydata;
    }
    else {
        cout << "mysql_real_connect() failed" << endl;
    }
}
int main() {
    cout << "****************************************" << endl;
    cout << "************学生学籍管理系统************" << endl;
    cout << "****************************************" << endl;
    MYSQL mysql;
    mysql = connect_database();
    while (1) {
        int value = NULL;
        cout << "请选择功能" << endl;
        cout << "1.学生信息添加" << endl;
        cout << "2.学生信息修改" << endl;
        cout << "3."
    }
    return 0;

   
    
}