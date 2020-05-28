#include <iostream>
#include <exception>
using namespace std;
 
struct command_error : public exception
{
  const char * what () const throw ()
  {
    return "command execute error";
  }
};

struct file_not_exist : public exception
{
    const char * what () const throw ()
    {
        return "the file doesn't exist";
    }
};

//测试代码 
// int main()
// {
//   try
//   {
//     throw MyException();
//   }
//   catch(MyException& e)
//   {
//     std::cout << "MyException caught" << std::endl;
//     std::cout << e.what() << std::endl;
//   }
//   catch(std::exception& e)
//   {
//     //其他的错误
//   }
// }
