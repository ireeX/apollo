# 如何记录doxygen的源代码

不熟悉doxygen的开发者可以从[官方网站](http://www.stack.nl/~dimitri/doxygen/)获取更多信息。
我们用 [time.h](https://github.com/ApolloAuto/apollo/blob/master/modules/common/time/time.h)作为示例来展示怎样成功的记录代码
### 文件
```
/**
 * @file
 *
 * @brief This library provides the utilities to deal with timestamps.
 * currently our assumption is that every timestamp will be of a
 * precision at 1 us.
 */
```

### 命名空间
```
/**
 * @namespace apollo::common::time
 * @brief apollo::common::time
 */
namespace apollo {
namespace common {
namespace time {
```

### 类
```
/**
 * @class Clock
 * @brief a singleton clock that can be used to get the current current
 * timestamp. The source can be either system clock or a mock clock.
 * Mock clock is for testing purpose mainly. The mock clock related
 * methods are not thread-safe.
 */
class Clock {
 public:
 ...
```

### 函数
```
/**
  * @brief Set the behavior of the \class Clock.
  * @param is_system_clock if provided with value TRUE, further call
  * to Now() will return timestamp based on the system clock. If
  * provided with FALSE, it will use the mock clock instead.
  */
 static void UseSystemClock(bool is_system_clock) {
   Clock::instance()->is_system_clock_ = is_system_clock;
 }
```

### Public / protected 类成员变量
```
/// Stores the currently set timestamp, which serves mock clock
/// queries.
Timestamp mock_now_;
```
