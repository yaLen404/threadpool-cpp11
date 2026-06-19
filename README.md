# C++11 ThreadPool

This repository contains two versions of a C++11 thread pool project.

## Structure

```text
basic/
  threadpool.h
  threadpool.cpp
  main.cpp

final/
  threadpool.h
  main.cpp
```

## Basic Version

The basic version uses an object-oriented task model:

- `Task` abstract base class
- virtual `Task::run()` for polymorphic task execution
- custom `Any` for arbitrary return values
- custom `Result` for asynchronous result retrieval
- custom `Semaphore` for synchronization between worker threads and callers

## Final Version

The final version improves the task submission API with standard C++11 utilities:

- `std::function<void()>` as the unified task type
- variadic templates for generic `submitTask`
- forwarding references and `std::forward`
- `std::packaged_task` for task wrapping
- `std::future` for asynchronous result retrieval

## Features

- fixed thread pool mode
- cached thread pool mode
- task queue capacity limit
- producer-consumer synchronization with `std::condition_variable`
- dynamic thread creation in cached mode
- idle thread timeout and recycling
- thread-safe counters with `std::atomic`

## Build

Use a compiler with C++14 language support and C++11 threading library support.

Example:

```bash
g++ -std=c++14 basic/main.cpp basic/threadpool.cpp -pthread -o basic_threadpool
g++ -std=c++14 final/main.cpp -pthread -o final_threadpool
```
