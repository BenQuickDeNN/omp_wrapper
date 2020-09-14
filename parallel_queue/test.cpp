#include <omp.h>
#include <cstdlib>
#include <iostream>
#include "parallel_queue.hpp"
using namespace std;
using namespace omp_wrapper;
const size_t numTasks = 16;
int main()
{
    OMPQueue<NUFFTTask> q;
    vector<NUFFTTask> _array(numTasks);

    // 初始化任务数组
    for (auto & task : _array)
        task.num_of_samples = rand();

    // 并行插入任务队列
    #pragma omp parallel for num_threads(4)
    for (size_t i = 0; i < numTasks; ++i)
        q.push(_array[i]);
    
    // 打印任务的优先级
    while (!q.empty())
    {
        cout << q.top().priority() << ' ';
        q.pop();
    }
    cout << endl;

    return 0;
}