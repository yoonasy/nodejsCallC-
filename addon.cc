#include <iostream>
#include <algorithm>
#include <vector>
#include <napi.h>
#include <openssl/md5.h>

using namespace Napi;
using namespace std;

void openssl_md5(const char *data, int size, unsigned char *buf){
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c,data,size);
	MD5_Final(buf,&c);
}

String GetMD5(const CallbackInfo& info) {
  Env env = info.Env();
  std::string password = info[0].As<String>().Utf8Value();
  //printf("md5 in str:%s %ld\n",password.c_str(),password.size());
  unsigned char hash[16];
  memset(hash,0,16);
  openssl_md5(password.c_str(),password.size(),hash);
  char tmp[3];
  char md5str[33]={};
  int i;
	for (i = 0; i < 16; i++){
	  sprintf(tmp,"%02x",hash[i]);
	  strcat(md5str,tmp);
	}
  return String::New(env, md5str,32);
}

class Person {
public:
    Person(string name, int age) {
        this->m_Name = name;
        this->m_Age = age;
    }

    string m_Name;
    int m_Age;
};

void printPerson(Person p) {
    cout << "name:" << p.m_Name << " age:" << p.m_Age << endl;
}

void PrintVector(const CallbackInfo& info) {
    vector<Person> v;
    Person p1("’≈∑…", 30);
    Person p2("¡ı±∏", 35);
    Person p3("πÿ”", 33);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    for_each(v.begin(), v.end(), printPerson);
    cout << endl;
}

String Hello(const CallbackInfo& info) {
    cout << "this is C++ cout" << endl;
  return String::New(info.Env(), "world");
}

Napi::Object  Init(Env env, Object exports) {
  exports.Set("hello", Function::New(env, Hello));
  exports.Set("md5", Function::New(env, GetMD5));
  exports.Set("printVector", Function::New(env, PrintVector));
  return exports;
}

NODE_API_MODULE(addon, Init)