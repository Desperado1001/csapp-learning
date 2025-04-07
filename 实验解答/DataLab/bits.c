/* 
 * CS:APP Data Lab 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int foo(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */

#endif
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

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /* 检查是否在 ASCII 数字范围内 (0x30-0x39) */
    int lower_bound = 0x30;
    int upper_bound = 0x3A;
    
    /* 检查 x >= 0x30 (即 x - 0x30 >= 0) */
    int check_lower = ((x + (~lower_bound + 1)) >> 31) & 1;
    
    /* 检查 x < 0x3A (即 0x3A - x > 0) */
    int check_upper = ((upper_bound + (~x + 1)) >> 31) & 1;
    
    /* 如果 x 是 ASCII 数字，则上下界检查都为 0 */
    return !(check_lower | check_upper);
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    /* 将 x 转换为全 0 或全 1 的掩码 */
    int mask = (!x) + ~0;
    
    /* 如果 x 非零，mask = 0xFFFFFFFF (全1)，否则 mask = 0x00000000 (全0) */
    /* 使用掩码选择 y 或 z: (mask & y) | (~mask & z) */
    return (mask & y) | (~mask & z);
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /* 获取 x 和 y 的符号位 */
    int sign_x = (x >> 31) & 1;
    int sign_y = (y >> 31) & 1;
    
    /* 检查符号是否不同: 1为不同，0为相同 */
    int diff_sign = sign_x ^ sign_y;
    
    /* 如果符号不同，且 x 为负数，则 x <= y */
    int case_diff_sign = diff_sign & sign_x;
    
    /* 如果符号相同，检查 y - x >= 0 */
    int diff = y + (~x + 1);
    int case_same_sign = !diff_sign & !((diff >> 31) & 1);
    
    /* x <= y 当且仅当: 符号不同且x为负数，或符号相同且y-x>=0 */
    return case_diff_sign | case_same_sign;
}

/*
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
    /* 如果 x 是 0，则 -x 也是 0 */
    /* 利用了 0 是唯一一个符号位与其相反数的符号位相同的数 */
    
    /* 取 x 的相反数 */
    int neg_x = ~x + 1;
    
    /* 获取 x 和 -x 的符号位 */
    int sign_x = (x >> 31) & 1;
    int sign_neg_x = (neg_x >> 31) & 1;
    
    /* 将符号位进行或运算，取反后加1 */
    /* 若 x = 0，则结果为 1；若 x != 0，则结果为 0 */
    return ((sign_x | sign_neg_x) ^ 1) & 1;
}

/* 
 * howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    int sign, bit16, bit8, bit4, bit2, bit1, bit0;
    
    /* 如果 x 为负数，则将其按位取反 */
    /* 这样可以将问题统一为：找到最高的1的位置 */
    sign = x >> 31;
    x = (sign & ~x) | (~sign & x);
    
    /* 二分查找最高位的1 */
    /* 先看高16位是否有1 */
    bit16 = !!(x >> 16) << 4;
    x = x >> bit16; /* 如果高16位有1，则右移16位 */
    
    /* 再看剩余高8位是否有1 */
    bit8 = !!(x >> 8) << 3;
    x = x >> bit8;
    
    /* 再看剩余高4位是否有1 */
    bit4 = !!(x >> 4) << 2;
    x = x >> bit4;
    
    /* 再看剩余高2位是否有1 */
    bit2 = !!(x >> 2) << 1;
    x = x >> bit2;
    
    /* 再看剩余高1位是否有1 */
    bit1 = !!(x >> 1);
    x = x >> bit1;
    
    /* 最后一位是否为1 */
    bit0 = x;
    
    /* 计算总位数并加上符号位 */
    return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    /* 浮点数分为三部分：符号位(31)、指数(30-23)、尾数(22-0) */
    unsigned sign = uf & 0x80000000;  /* 提取符号位 */
    unsigned exp = (uf & 0x7F800000) >> 23;  /* 提取指数位 */
    unsigned frac = uf & 0x007FFFFF;  /* 提取尾数位 */
    
    /* 特殊情况：NaN 或 无穷大 */
    if (exp == 0xFF)
        return uf;
    
    /* 特殊情况：非规格化数（指数为0） */
    if (exp == 0) {
        /* 尾数左移一位，溢出部分进入指数 */
        frac = frac << 1;
        if (frac & 0x00800000) {  /* 检查溢出到指数位 */
            exp = 1;
            frac = frac & 0x007FFFFF;  /* 清除溢出位 */
        }
    }
    /* 普通情况：规格化数 */
    else {
        exp = exp + 1;
        /* 检查指数是否溢出 */
        if (exp == 0xFF) {
            frac = 0;  /* 变为无穷大 */
        }
    }
    
    /* 组合三部分，返回结果 */
    return sign | (exp << 23) | frac;
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned exp = 0;
    unsigned frac = 0;
    unsigned E = 0;
    unsigned tmp = 0;
    unsigned round = 0;
    
    /* 特殊情况：0 */
    if (x == 0)
        return 0;
    
    /* 提取符号位 */
    sign = (x < 0) ? 0x80000000 : 0;
    
    /* 对负数取绝对值 */
    if (x < 0) {
        /* 避免溢出，特殊处理 Tmin */
        if (x == 0x80000000) {
            return 0xCF000000;  /* Tmin 的浮点表示 */
        }
        x = -x;
    }
    
    /* 计算 E (规格化后的指数) */
    tmp = x;
    while (tmp > 1) {
        tmp = tmp >> 1;
        E++;
    }
    
    /* 计算指数部分 */
    exp = E + 127;
    
    /* 计算尾数部分 */
    if (E < 23) {
        /* 尾数不会溢出 */
        frac = (x << (23 - E)) & 0x007FFFFF;
    } else if (E > 23) {
        /* 需要舍入 */
        int shift = E - 23;
        int mask = (1 << shift) - 1;
        round = x & mask;
        frac = (x >> shift) & 0x007FFFFF;
        
        /* 四舍五入处理 */
        if (round > (1 << (shift - 1)) ||
            (round == (1 << (shift - 1)) && (frac & 1))) {
            frac = frac + 1;
            /* 检查是否需要进位到指数 */
            if (frac == 0x00800000) {
                exp = exp + 1;
                frac = 0;
            }
        }
    } else {
        /* E == 23，直接取尾数 */
        frac = x & 0x007FFFFF;
    }
    
    /* 组合三部分，返回结果 */
    return sign | (exp << 23) | frac;
}

/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
    /* 提取浮点数各部分 */
    unsigned sign = (uf >> 31) & 1;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x007FFFFF;
    int E = exp - 127;  /* 真实指数 */
    int result = 0;
    
    /* 特殊情况：NaN、无穷大或超出 int 范围 */
    if (exp == 0xFF || E >= 31)
        return 0x80000000u;
    
    /* 指数太小，结果为 0 */
    if (E < 0)
        return 0;
    
    /* 计算整数结果 */
    /* 规格化数的尾数隐含了前导1 */
    result = (frac | 0x00800000) >> (23 - E);
    
    /* 处理符号 */
    if (sign)
        result = -result;
    
    return result;
}
