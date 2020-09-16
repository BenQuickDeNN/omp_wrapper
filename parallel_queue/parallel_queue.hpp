#pragma once
#include <queue>
#include <vector>
#include <omp.h>
#include "../task/task.hpp"
namespace omp_wrapper
{
    // Queue for OpenMP parallel operations
    template <typename type>
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
        void push(type &_task) noexcept
        {
            omp_set_lock(&lock);
            _queue.push(_task);
            omp_unset_lock(&lock);
        }
        void pop() noexcept
        {
            omp_set_lock(&lock);
            if (!_queue.empty())
                _queue.pop();
            omp_unset_lock(&lock);
        }
        type * top() noexcept
        {
            type * ret = nullptr;
            omp_set_lock(&lock);
            if (!_queue.empty())
                ret = &(_queue.top());
            omp_unset_lock(&lock);
            return ret;
        }
        size_t size() noexcept
        {
            size_t ret = 0;
            omp_set_lock(&lock);
            ret = _queue.size();
            omp_unset_lock(&lock);
            return ret;
        }
        bool empty() noexcept
        {
            bool ret = true;
            omp_set_lock(&lock);
            ret = _queue.empty();
            omp_unset_lock(&lock);
            return ret;
        }

    private:
        std::priority_queue<type> _queue;
        omp_lock_t lock;
    };

    template <>
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
        void push(NUFFTTask &_task) noexcept
        {
            omp_set_lock(&lock);
            _queue.push(_task);
            omp_unset_lock(&lock);
        }
        void pop() noexcept
        {
            omp_set_lock(&lock);
            if (!_queue.empty())
                _queue.pop();
            omp_unset_lock(&lock);
        }
        NUFFTTask top() noexcept
        {
            NUFFTTask ret;
            omp_set_lock(&lock);
            if (!_queue.empty())
                ret = _queue.top();
            omp_unset_lock(&lock);
            return ret;
        }
        size_t size() noexcept
        {
            size_t ret = 0;
            omp_set_lock(&lock);
            ret = _queue.size();
            omp_unset_lock(&lock);
            return ret;
        }
        bool empty() noexcept
        {
            bool ret = true;
            omp_set_lock(&lock);
            ret = _queue.empty();
            omp_unset_lock(&lock);
            return ret;
        }

    private:
        std::priority_queue<NUFFTTask, std::vector<NUFFTTask>, Task::comparator> _queue;
        omp_lock_t lock;
    };

    template <>
    class OMPQueue<ADJConvTask>
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
        void push(ADJConvTask &_task) noexcept
        {
            omp_set_lock(&lock);
            _queue.push(_task);
            omp_unset_lock(&lock);
        }
        void pop() noexcept
        {
            omp_set_lock(&lock);
            _queue.pop();
            omp_unset_lock(&lock);
        }
        const ADJConvTask &top() const noexcept
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
        std::priority_queue<ADJConvTask, std::vector<ADJConvTask>, Task::comparator> _queue;
        omp_lock_t lock;
    };
} // namespace omp_wrapper