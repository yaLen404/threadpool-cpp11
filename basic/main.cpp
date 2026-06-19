#include <chrono>
#include <iostream>
#include <thread>

#include "threadpool.h"

using namespace std;
using uLong = unsigned long long;

class MyTask : public Task
{
public:
	MyTask(int begin, int end)
		: begin_(begin)
		, end_(end)
	{}

	Any run()
	{
		std::cout << "tid:" << std::this_thread::get_id()
			<< " begin!" << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(3));

		uLong sum = 0;
		for (uLong i = begin_; i <= end_; i++)
			sum += i;

		std::cout << "tid:" << std::this_thread::get_id()
			<< " end!" << std::endl;

		return sum;
	}

private:
	int begin_;
	int end_;
};

int main()
{
	{
		ThreadPool pool;
		pool.setMode(PoolMode::MODE_CACHED);
		pool.start(2);

		Result res1 = pool.submitTask(std::make_shared<MyTask>(1, 100000000));
		Result res2 = pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
		pool.submitTask(std::make_shared<MyTask>(100000001, 200000000));
	}

	cout << "main over!" << endl;
	getchar();
}
