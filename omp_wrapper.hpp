#pragma once

namespace omp_wrapper
{
    class OMPWrapper
    {
    public:
        void execute() noexcept;
        void execute(const int & num_threads) noexcept;
    };
}