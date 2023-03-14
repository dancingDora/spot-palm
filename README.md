# Spot-Palm 游乐园

  $\color{#BA55D3}{一个给大家偷偷玩 spot palm 的地方}$ 

# 🫓大饼
## 文件结构


```
project spot-palm
│
└───README.md
│  
└───src
│   │    
│   └───cmake-build-debug
│   │   CMakeLists.txt
│   │   
│   └───main.cpp 
│   │   spot.h
│   │   status.h
│   │   tools.h
│   │   user.h

```
## `user.h`

### 父类成员
```cpp
class USER {
  
private:
    Char<16> password;
protected:
    const Char<16> uid;
public:
    Char<32> userName;
    const int privilege;  //privilege  :  visitor-0 ; user-1  ; contributor-3 ; leader-7.
    int gender;           //gender     :  male-1   ; female-2; others-0.
}
  ```
现支持默认构造和拷贝构造函数

### 子类成员
暂时只支持默认构造函数 -- 用来赋予用户应有的权限


## tools.h文件

--------
### class Char
```c
template<int n = 64>
class Char {};
```
char数组，方便以后进行文件读写
用法
* **声明 :** `Char<int>`类中参数为数组大小，默认64
* **[] :** 同`string`的`[]`用法
* **`c_str()` :** 返回char*
* **`str()` :** 返回string
* **`empty()` :** 判断Char是否为空
* 支持`>, <, ==`等比较，调用`strcmp()`函数
* 支持`=`赋值
* 支持`>>`,`<<`输入输出流
------
### class TokenScanner
用于指令读取
* `TokenScanner`类参数为`size_t pos`记录字符串位置，`Buffer`目标字符串
* 用法
  * 声明：`TokenScanner token(t)`(t表示目标字符串)
  * 使用：`string tmp = token.NextToken()` 获取行中的下一个字符串，函数参数为`char`,默认为空格，故不填写参数即可表示读取下一个参数

  