# Data Lab 实验解答

## 实验简介

Data Lab 是 CSAPP 课程中的第一个实验，主要目的是通过实现一系列位操作函数，深入理解计算机如何表示和处理数据。

## 实验要求

- 只使用位操作符（如 &, |, ^, ~, >>, <<）实现指定功能
- 不允许使用条件语句、循环、函数调用等高级结构
- 每个函数都有操作符数量的限制
- 实现的函数需要通过自动测试

## 实验文件

- `bits.c`: 需要完成的源代码文件
- `bits.h`: 头文件，包含函数原型
- `btest.c`: 测试程序
- `dlc`: 代码风格检查工具
- `Makefile`: 构建脚本

## 环境配置

1. 下载 Data Lab 实验包
```bash
wget http://csapp.cs.cmu.edu/3e/datalab-handout.tar
```

2. 解压并进入目录
```bash
tar -xvf datalab-handout.tar
cd datalab-handout
```

3. 编译
```bash
make clean
make
```

## 函数实现及思路

### 1. bitXor

```c
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    /* 使用德摩根定律: x^y = (~x&y)|(x&~y) = ~(~(~x&y)&~(x&~y)) */
    return ~(~(~x & y) & ~(x & ~y));
}
```

**思路分析**：
- 异或运算的本质是：当两个位不同时结果为1，否则为0
- 可以使用德摩根定律将异或表达为与和非的组合

### 2. tmin

```c
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /* 最小的二进制补码是 0x80000000，即 1 左移 31 位 */
    return 1 << 31;
}
```

**思路分析**：
- 在二进制补码表示中，最小值是最高位为1，其余位为0
- 32位整数的最小值是 0x80000000，即 1 左移 31 位

### 3. isTmax

```c
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /* Tmax + 1 = Tmin，即 0x7FFFFFFF + 1 = 0x80000000 */
    /* 检查 x+1 的反码是否等于 x */
    int i = x + 1; /* 如果 x 是 Tmax，则 i 是 Tmin */
    
    /* 排除 x = -1 的情况，因为 -1 + 1 = 0，~0 = -1，也符合 ~(x+1) = x */
    int not_neg_one = !!(x + 1);
    
    return !(~x ^ i) & not_neg_one;
}
```

**思路分析**：
- 最大的二进制补码是 0x7FFFFFFF
- Tmax + 1 = Tmin，即 0x7FFFFFFF + 1 = 0x80000000
- Tmin 的反码恰好是 Tmax
- 需要注意排除 x = -1 的特殊情况

### 4. allOddBits

```c
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
    /* 创建一个掩码，奇数位全为1 */
    int mask = 0xAA;  /* 10101010 */
    mask = (mask << 8) + mask;  /* 16位全奇数位为1 */
    mask = (mask << 16) + mask;  /* 32位全奇数位为1 */
    
    /* 检查 x 的奇数位是否全为1 */
    return !((x & mask) ^ mask);
}
```

**思路分析**：
- 奇数位全为1的掩码是 0xAAAAAAAA
- 先构建这个掩码，然后检查 x 的奇数位是否都为1

### 5. negate

```c
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    /* 二进制补码的相反数：取反加1 */
    return ~x + 1;
}
```

**思路分析**：
- 二进制补码的一个重要性质是：一个数的相反数等于它的按位取反加1

## 完整解答

完整的 `bits.c` 文件包含所有函数的实现，可在仓库中查看。

## 实验技巧

1. **使用位操作的常见模式**：
   - 获取最低位：`x & 1`
   - 获取最高位：`(x >> 31) & 1`
   - 判断 x 是否为 0：`!x`
   - 判断 x 是否为 1：`!(x ^ 1)`
   - 将 x 的第 n 位设为 1：`x | (1 << n)`
   - 将 x 的第 n 位设为 0：`x & ~(1 << n)`

2. **测试方法**：
   - 使用 `./btest` 测试函数正确性
   - 使用 `./dlc bits.c` 检查是否符合操作符数量限制
   - 使用 `./btest -f <function_name>` 测试单个函数

3. **调试技巧**：
   - 使用纸笔跟踪位操作的结果
   - 对复杂函数，先使用更多操作符实现，然后再优化
   - 考虑边界情况：0、-1、最大值、最小值等

## 参考资源

- [CSAPP 官方网站](http://csapp.cs.cmu.edu/)
- [位操作技巧总结](https://graphics.stanford.edu/~seander/bithacks.html)
- [C语言位操作符详解](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)

## 实验收获

完成 Data Lab 后，你将深入理解：
- 整数和浮点数在计算机中的表示方式
- 位操作的优势和应用场景
- 二进制补码的性质和运算规则
- 如何用基本位操作构建复杂的功能
