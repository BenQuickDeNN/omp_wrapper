#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "task.hpp"
using namespace std;
using namespace omp_wrapper;
const size_t numTasks = 16;
int main()
{
    priority_queue<NUFFTTask, vector<NUFFTTask>, Task::comparator> _queue;
    vector<NUFFTTask> _array(numTasks);
    // 初始化任务数组
    for (auto & task : _array)
        task.num_of_samples = rand();
    // 插入任务队列
    for (auto & task : _array)
        _queue.push(task);
    // 输出任务的优先级
    while (!_queue.empty())
    {
        cout << _queue.top().priority() << ' ';
        _queue.pop();
    }
    cout << endl;
    return 0;
}