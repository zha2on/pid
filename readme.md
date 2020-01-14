### PID的简单实现

c 代码的 增量pid的实现.


### 依赖工具

cmake, make


### 使用步骤

测试环节为win10, step1, 在工程文件夹下先执行下面命令, `cmake`检索`MinGW`的环节变量.

```bash
cmake.exe -G "MinGW Makefiles"
```

step2, 执行 `cmake .`.

step3, 执行 `make`.

step4, 执行 `pid_test.exe`.

step5, 修改参数后, 重复 step2 ~ step4 步骤。

### 参数修改参考

1, Kp, Ki, Kd, 先全部设置为0.

2, 调整 Kp的值, Kp的值先设置大, 在设置小。找到曲线变小的零界位置。

3, 在调整Ki的值, 减小系统零差。

4, 在调整Kd的值, 有些系统只有Kp和Ki.
