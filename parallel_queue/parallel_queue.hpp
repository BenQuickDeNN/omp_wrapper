#pragma once
#include <queue>
#include <vector>
#include <omp.h>
#include "../task/task.hpp"
namespace omp_wrapper
{
    // Queue for OpenMP parallel operations
    template<typename type>
    class OMPQueue
    {
    public:
        OMPQueue()
        {
            omp_init_lock(&lock);
        }
        ~OMPQueue()
        {
            omp_destroy_lock(&lock);
        }
        // thread safe
        void push(type & _task) noexcept
        {
            omp_set_lock(&lock);
            _queue.push(_task);
            omp_unset_lock(&lock);
        }
        void pop() noexcept
        {
            _queue.pop();
        }
        const type & top() const noexcept
        {
            return _queue.top();
        }
        size_t size() const noexcept
        {
            return _queue.size();
        }
        bool empty() const noexcept
        {
            return _queue.empty();
        }
    private:
        std::priority_queue<type> _queue;
        omp_lock_t lock;
    };

    template<>
    class OMPQueue<NUFFTTask>
    {
    public:
        OMPQueue()
        {
            omp_init_lock(&lock);
        }
        ~OMPQueue()
        {
            omp_destroy_lock(&lock);
        }
        // thread safe
        void push(NUFFTTask & _task) noexcept
        {
            omp_set_lock(&lock);
            _queue.push(_task);
            omp_unset_lock(&lock);
        }
        void pop() noexcept
        {
            _queue.pop();
        }
        const NUFFTTask & top() const noexcept
        {
            return _queue.top();
        }
        size_t size() const noexcept
        {
            return _queue.size();
        }
        bool empty() const noexcept
        {
            return _queue.empty();
        }
    private:
        std::priority_queue<NUFFTTask, std::vector<NUFFTTask>, Task::comparator> _queue;
        omp_lock_t lock;
    };
}