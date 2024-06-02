# Implementation of a set of stl-compatible algorithms, xrange and zip generator. Test coverage.

### Algorithms

- **all_of** - returns true if all elements of the range satisfy some predicate. Otherwise false
- **any_of** - returns true if at least one of the range elements satisfies some predicate. Otherwise false
- **none_of** - returns true if all elements of the range do not satisfy some predicate. Otherwise false
- **one_of** - returns true if exactly one element of the range satisfies some predicate. Otherwise false
- **is_sorted** - returns true if all elements of the range are in sorted order relative to some criterion
- **is_partitioned** - returns true if there is an element in the range that divides all elements into those that satisfy and those that do not satisfy - some predicate. Otherwise false.
- **find_not** - finds the first element that is not equal to the given one
- **find_backward** - finds the first element equal to the given one from the end
- **is_palindrome** - returns true if the given sequence is a palindrome with respect to some condition. Otherwise false.

### xrange

Python has a very useful function [xrange](https://docs.python.org/2/library/functions.html#xrange). It is required to implement its analogue in O(1) from memory. The function helps to generate a value from a certain range with a certain step

For example:

```cpp
auto x = xrange(1.5, 5.5);
std::vector<int> v{x.begin(), x.end()}; // 1.5 2.5 3.5 4.5
```

```cpp
auto x = xrange(4);
std::vector<int> v{x.begin(), x.end()}; // 0 1 2 3
```

```cpp
// 1 3 5
for(auto i : xrange(1, 6, 2)) {
 std::cout << i << " ";
}
```

Without specifying a step, at each iteration an increment is generated to the previous value, with three parameters it is increased by the specified step

### zip

Python also has a standard [zip function](https://docs.python.org/2/library/functions.html#zip)

Example:
```c++
std::list l = {1, 2, 3, 4, 5};
std::vector v = {'a', 'b', 'c', 'd'};
/*
1 a
2 b
3 s
4 d
*/
for(auto value : zip(l, v)) {
 std::cout << value.first << " " << value.second << std::endl;
}
```
