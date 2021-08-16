#include <winsock.h>
#include <iostream>
#include <string>
#include <mysql.h>
#include <iomanip>
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
void stu_query(MYSQL sql) {
    char str[40];
    char sqlstr[1024];
    MYSQL_RES* res;
    MYSQL_ROW row;
    cout << "输入你的学号"<<endl;
    cin >> str;
    int len = sprintf_s(sqlstr, "select * from persons where stu_id='%s'", str);
    if (mysql_query(&sql, sqlstr)!=false) {        // 执行指定为一个空结尾的字符串的SQL查询。	
        printf("库中无此学号，请添加 %s\n", str);
        return ;
    }
    res = mysql_store_result(&sql);
    row = mysql_fetch_row(res);
    if (!mysql_num_rows(res)) {
        printf("库中无此学号，请添加 %s\n", str);
        return;
    }
    cout << "学号 : " << row[0] << endl;
    cout << "姓名 : " << row[1] << endl;
    cout << "性别 : " << row[2] << endl;
    cout << "班级 : " << row[3] << endl;
    cout << endl;
    mysql_free_result(res);
    return;
}
void stu_update(MYSQL sql) {
    char sqlstr[1024];
    char id[40];
    char name[40];
    char gender[10];
    int stu_class;
    int command;
    MYSQL_RES* res;
    cout << "输入你的学号       ";
    cin >> id;
    int len1 = sprintf_s(sqlstr, "select * from persons where stu_id=\"%s\"", id);
    if (mysql_query(&sql, sqlstr) != false) {        // 执行指定为一个空结尾的字符串的SQL查询。	
        cout << "库中无此学号，请重试";
        return;
    }
    cout << "此学号存在！\n"<<endl;
    cout << "要修改的内容：1（姓名），2（性别），3（班级），4(退出）:";
    res = mysql_store_result(&sql);
    mysql_free_result(res);
    cin >> command;
    switch (command)
    {
    case 1:
    {
        cout << "请输入新的姓名：";
        cin >> name;
        int len = sprintf_s(sqlstr, sizeof(sqlstr), "update persons set stu_name='%s' where stu_id='%s'", name, id);
        cout << sqlstr << endl;
        if (mysql_query(&sql, sqlstr) != 0 || len < 0) {
            cout << "修改数据失败1\n";
            cout << mysql_error(&sql);
            return;
        }
        else
            cout << "修改数据成功\n";
        break;
    }
    case 2:
    {
        cout << "请输入新的性别：";
        cin >> gender;
        int len = sprintf_s(sqlstr, "update persons set stu_gender='%s' where stu_id='%s'", gender, id);
        if (mysql_query(&sql, sqlstr) != 0 || len < 0) {
            cout << "修改数据失败\n";
            return;
        }
        else
            cout << "修改数据成功\n";
        break;
    }
    case 3:
    {
        cout << "请输入新的班级：";
        cin >> stu_class;
        int len = sprintf_s(sqlstr, "update persons set stu_class=%d where stu_id='%s'", stu_class, id);
        if (mysql_query(&sql, sqlstr) != false|| len < 0) {
            cout << "修改数据失败\n";
            return;
        }
        else
            cout << "修改数据成功\n";
        break;
    }
    case 4:
    {
        return;
    }
    default:
        cout << "请输入正确的指令";
    }

}
void stu_append(MYSQL sql) {
    char sqlstr[1024];
    char id[40];
    char name[40];
    char gender[10];
    int stu_class;
    MYSQL_RES* res;
    while (1) {
        int judge;
        cout << "输入你的学号   ";
        cin >> id;
        cout << "输入你的姓名    ";
        cin >> name;
        cout << "输入你的性别    ";
        cin >> gender;
        cout << "输入你的班级    ";
        cin >> stu_class;
        cout << id << "  " << name << "   " << gender << "  " << stu_class << endl;
        cout << "是否确定？1:确定  2:取消";
        cin >> judge;
        if (judge == 1) {
            break;
        }
        else{
            continue;
        }
    }
    int len = sprintf_s(sqlstr, sizeof(sqlstr),"insert into persons values(\"%s\",\"%s\",\"%s\",%d)", id, name, gender, stu_class);
    if (mysql_query(&sql, sqlstr) != false ||len<0) {        // 执行指定为一个空结尾的字符串的SQL查询。	
        cout << "学生信息添加失败";
        return;
    }
    cout << "学生信息添加成功" << endl;;
    res = mysql_store_result(&sql);
    mysql_free_result(res);
    return;
}
void stu_delete(MYSQL sql) {
    char str[40];
    char sqlstr[1024];
    MYSQL_RES* res;
    cout << "输入要删除的学生学号：";
    cin >> str;
    int len = sprintf_s(sqlstr, "delete from persons where stu_id='%s'", str);
    if (mysql_query(&sql, sqlstr) || len < 0) {
        cout << "删除数据失败\n";
    }
    else
        cout << "删除数据成功\n";
    res = mysql_store_result(&sql);
    mysql_free_result(res);
}


int main() {
    MYSQL mysql;
    mysql = connect_database();
    cout << "****************************************" << endl;
     cout << "************学生学籍管理系统************" << endl;
    cout << "****************************************" << endl;
    int value = NULL;
    while (1) {
        cout << "请选择功能" << endl;
        cout << "1.学籍信息查询" << endl;
        cout << "2.增加学籍信息" << endl;
        cout << "3.修改学籍信息" << endl;
        cout << "4.删除学籍信息" << endl;
        cout << "5.退出 " << endl;
        cin >> value;
        switch (value) {
            case 1:
                stu_query(mysql); break;
            case 2:
                stu_append(mysql); break;
            case 3:
                stu_update(mysql); break;
            case 4:
                stu_delete(mysql); break;
            case 5:
            mysql_close(&mysql);return 0;
            default:
            cout << "输入错误请重新输入" << endl;
        }
        
    }
    return 0;
}