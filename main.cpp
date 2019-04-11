#include<iostream>
#include<string>
#include<fstream.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;

class Person
{
  protected:
    string name, id;
    char sex;
    int age;
  public:
    Person(string name, char sex, int age, string id)
    {
      this->name = name;
      this->sex = sex;
      this->age = age;
      this->id = id;    
    }
    Person(){;}
    string getID(){return this->id;} 
    virtual void display() = 0;
    virtual void output(ofstream&) = 0;
};
class UnderGraduate:public Person //本科生 
{
  private:
    float grades;
  public:
    UnderGraduate(string name, char sex, int age, string id, float grades):
      Person(name, sex, age, id)
        {
          this->grades = grades;    
        }
    void display()
    {
      cout << "身份证号码：" << id <<endl;
      cout << "姓名：" << name << endl; 
      cout << "性别：" << (sex == 'm'?"男":"女") << endl;
      cout << "年龄：" << age << endl;
      cout << "高考总分: " << grades << endl << endl;
    }
    void output(ofstream& out)
    {
      out<<"本科生\n"<<name <<' '<<sex<<' '<<age<<' ' <<id
      <<' '<<grades<<endl;          
    }
};
class PureGraduate:public Person //脱产研究生 
{
  private:
    string major;
  public:
    PureGraduate(string name, char sex, int age, string id, string major):
      Person(name, sex, age, id)
        {
          this->major = major;    
        };
    void display()
    {
      cout << "身份证号码：" << id <<endl;
      cout << "姓名：" << name << endl; 
      cout << "性别：" << (sex == '0'?"男":"女") << endl;
      cout << "年龄：" << age << endl;
      cout << "专业: " << major << endl << endl;
    }
    void output(ofstream& out)
    {
      out<<"PureGraduate" << name << " " << sex << " " << age << " " 
      << id << " " << major << endl;
      out<<std::left<<setw(20)<<"PureGraduate"<<std::left<<setw(20)
      <<name<<std::left<<setw(5)<<sex<<std::left<<setw(5)<<age
      <<std::left<<setw(12)<<id<<std::right<<setw(10)<<endl;          
    }
};
class HalfGraduate:public Person //在职研究生 
{
  private:
    string num, major;
    float wage;
  public:
    HalfGraduate(string name, char sex, int age, string id,string num,
     string major, float wage):
      Person(name, sex, age, id)
        {
          this->num = num;
          this->major = major;
          this->wage = wage;    
        }
    void display()
    {
      cout << "身份证号码：" << id <<endl;
      cout << "姓名：" << name << endl; 
      cout << "性别：" << (sex == '0'?"男":"女") << endl;
      cout << "年龄：" << age << endl;
      cout << "学号：" << num << endl;
      cout << "专业：" << major << endl;
      cout << "工资：" << wage << endl << endl;
    }
    void output(ofstream& out)
    {
      out << "HalfGraduate " << name << " " << sex << " " << age << " " 
      << id << " " << num << " " << major << " " << wage << endl;          
    }    
};
class Staff:public Person //职工 
{ 

  private:
    string job;
    float wage;
  public:
    Staff(string name, char sex, int age, string id,float wage,
     string job):
      Person(name, sex, age, id)
        {
          this->job = job;
          this->wage = wage;    
        }
    void display()
    {
      cout << "身份证号码：" << id <<endl;
      cout << "姓名：" << name << endl; 
      cout << "性别：" << (sex == '0'?"男":"女") << endl;
      cout << "年龄：" << age << endl;
      cout << "工资：" << wage << endl;
      cout << "岗位：" << job << endl << endl;
    }
    void output(ofstream& out)
    {
      out << "职工\n" << name << " " << sex << " " << age << " " 
      << id << " " << wage << " " << job << endl;         
    }
};
class Teacher:public Person //教师 
{
  private:
    string major;
    float wage;
  public:
    Teacher(string name, char sex, int age, string id,float wage,
     string major):
      Person(name, sex, age, id)
        {
          this->major = major;
          this->wage = wage;    
        }
    void display()
    {
      cout << "身份证号码：" << id <<endl;
      cout << "姓名：" << name << endl; 
      cout << "性别：" << (sex == '0'?"男":"女") << endl;
      cout << "年龄：" << age << endl;
      cout << "工资：" << wage << endl;
      cout << "专业：" << major << endl << endl;
    } 
    void output(ofstream& out)
    {
      out << "Staff " << name << " " << sex << " " << age << " " 
      << id << " " << wage << " " << major << endl;          
    }     
};

template<class T> class List; //链表存储系统 
template<class T>
class Node
{
  friend class List<T>;
  private:
    T *data;  
    Node<T>* next;
  public:
    Node(T *data):data(data),next(NULL){};
}; 
template<class T>
class List
{
  public:
    List():length(0),head(NULL),tail(NULL){};//this->是不是不能存在于初始化列表？ 
    void Insert(T* newNode);
    void DeleteNode(string);
    void Query(string);
    void Print();
    void Output(ofstream&); 
  private:
    int length;
    Node<T> *head;
    Node<T> *tail;    
};
template<class T>
void List<T>::Insert(T* newNode) //为什么能用List的T来给Node中的T赋值？因为是指针？ 
{
  cout << "...插入一个新成员" << endl; 
  Node<T> *tmp = new Node<T>(newNode);
  if(!head)
  {
    head = tail = tmp;
    length++;    
  }
  else
  {
    tail->next = tmp;
    tail = tmp;
    length++;    
  }
  printf("插入成功，当前共 %d 人！\n\n",length);   
}
template<class T>
void List<T>::DeleteNode(string id)
{
  cout << "...执行删除id: " << id << " 成员中" << endl;
  if(!head) 
  {
    cout << "数据库中没有人！\n" << endl;
    return ;
  }
  else
  {
    Node<T> *tmp1 = head, *tmp2 = tmp1->next;  
    if(head->data->getID() == id)
      {
        delete head->data;
        delete head;
        head = tmp2;
        length--;
        return ;    
      }
    while(tmp2 != NULL )
    {
      if(tmp2->data->getID() == id)
      {
        //Node<T> *p = tmp2->data;
        tmp1->next = tmp2->next;
        delete tmp2->data;
        delete tmp2;
        length--;
        printf("id: %s 删除成功！\n\n",id.c_str());
        break;    
      }
      else 
      {
        tmp1 = tmp1->next;
        tmp2 = tmp1->next;
      }
    }
  }       
}
template<class T>
void List<T>::Query(string id)
{
  cout << "...查询id为: "<< id.c_str() <<" 的成员" <<endl;
  if(!head) cout << "数据库中没有人！" << endl;
  else
  {
    Node<T> *tmp = head;
    while(tmp != NULL)
    {
      if(tmp->data->getID() == id) 
      {
        tmp->data->display();
        break;
      }    
      else tmp = tmp->next;    
    }
    if(tmp != NULL) 
      printf("id: %s 查找成功!其信息打印如上\n\n",id.c_str());
    else
      cout << "查找失败!" <<endl;
  }      
} 
template<class T>
void List<T>::Print()
{
  cout << "...开始打印数据库成员" <<endl; 
  if(!head) cout << "数据库中没有人！" << endl;
  else
  {
    Node<T> *tmp = head;
    while(tmp != NULL)
    {
      tmp->data->display();
      tmp = tmp->next;
    }    
  }
  cout << "打印成功，共 " << length << " 人！\n" <<endl;    
}; 
template<class T>
void List<T>::Output(ofstream& out)
{
  cout << "...开始输出数据库成员到文本文件" <<endl; 
  if(!head) cout << "数据库中没有人！" << endl;
  else
  {
    Node<T>* tmp = head;
    while(tmp != NULL)
    {
      tmp->data->output(out);
      tmp = tmp->next;    
    }    
  }
  cout << "输出完成！" << endl << endl;     
}
int main()
{
//  UnderGraduate a("xiaoming",'m',23,"28837694",600.5);
//  Staff b("xiaoli",'f',43,"237694",1000,"清理教室");
//  UnderGraduate a("小明",'m',23,"288376",600.5);
//  Staff b("小丽",'f',43,"237694",1000,"清理教室");
//  List<Person> zju;
//  zju.Insert(&a);
//  zju.Insert(&b);
//  
//  ofstream out;
//  out.open("zju.txt");
//  zju.Output(out);
//  out.close();


  
  ifstream in;
  in.open("zju.txt");
  char cl[10],line[10];
//  while(!in.eof())
//    {
//    in >> cl;
//    cout << cl << endl;
//    }
  while(in.getline(line,80))
  {
    string str(line);
    string first = str.substr(0,2);
    if(first == "本")
    {
      cout<<"...读取数据库文本"<<endl;
      string name;
      char sex;
      int age;
      string id;
      float grades;
      in >> name >> sex >> age >> id >> grades;
      
      UnderGraduate tmp(name,sex,age,id,grades);
      Person* p;
      p = &tmp;
      p->display();
      cout << "发现一个本科生，已将其加入数据库！\n" <<endl;    
    }
    if(first == "职")
    {
      cout<<"...读取数据库文本"<<endl;
      string name;
      char sex;
      int age;
      string id;
      float grades;
      float wage;
      string job;
      in >> name >> sex >> age >> id >> wage >> job;
      
      Staff tmp(name,sex,age,id,wage,job);
      Person* p;
      p = &tmp;
      p->display();
      cout << "发现一个职工，已将其加入数据库！\n" <<endl;    
    }
  }  
  in.close();
   
  
//  zju.Insert(&b);
//  zju.Print();
//  zju.Query("237694");
//  zju.DeleteNode("237694");
//  zju.Print();
////  Person* current;
////  current = &xiaoming;
////  current->display();
  
  
    
  system("pause");
  return 0;     
}
