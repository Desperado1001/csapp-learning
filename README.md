# 深入理解计算机系统（CSAPP）学习

本仓库包含《深入理解计算机系统》（CSAPP，Computer Systems: A Programmer's Perspective）的学习记录、学习路线以及实验解答。

## 📚 目录结构

```
csapp-learning/
├── 学习路线/
│   └── roadmap.md              # CSAPP 整体学习路线
├── 章节笔记/
│   ├── 第01章_计算机系统漫游/
│   ├── 第02章_信息的表示和处理/
│   ├── 第03章_程序的机器级表示/
│   └── ...
├── 实验解答/
│   ├── DataLab/
│   ├── BombLab/
│   ├── AttackLab/
│   └── ...
└── 资源/
    └── diagrams/              # 包含 Excalidraw 图表
```

## 🗺️ 学习路线

请查看 [学习路线](./学习路线/roadmap.md) 文件，获取完整的学习建议和路线图。

## 📖 章节笔记

每个章节目录下包含：
- 知识点总结
- 重要概念解释
- 示例代码（C语言，采用 snake_case 风格）
- 课后习题解答

## 🧪 实验解答

包含 CSAPP 所有实验的详细解答：
- Data Lab：位操作与整数运算
- Bomb Lab：二进制炸弹拆解
- Attack Lab：缓冲区溢出攻击
- Buffer Lab：缓冲区漏洞利用
- Architecture Lab：Y86-64 处理器架构
- Cache Lab：高速缓存模拟
- Performance Lab：性能优化
- Shell Lab：Unix Shell 实现
- Malloc Lab：动态内存分配器实现
- Proxy Lab：Web 代理服务器实现

## 📊 框架图

查看 [Excalidraw 图表](./资源/diagrams/csapp_framework.svg) 了解本书和实验的整体框架。

## 🔗 参考资源

- [CSAPP 官方网站](http://csapp.cs.cmu.edu/)
- [CMU 15-213 课程](https://www.cs.cmu.edu/~213/)
- [实验资源下载](http://csapp.cs.cmu.edu/3e/labs.html)

## 📝 使用说明

1. 克隆本仓库：
```bash
git clone https://github.com/Desperado1001/csapp-learning.git
```

2. 使用 cnpm 安装依赖（如果需要）：
```bash
cnpm install
```

3. 查看相关章节或实验的内容，按照学习路线进行学习。

## 🤝 贡献

欢迎提交 Pull Request 或 Issue 来完善本仓库内容！

## 📄 许可

MIT License
