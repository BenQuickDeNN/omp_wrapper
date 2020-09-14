#pragma once
#include <vector>
#include <complex>

namespace omp_wrapper
{
    class Task
    {
    public:
        virtual int priority() const noexcept = 0;
        struct comparator
        {
            bool operator () (const Task & task1, const Task & task2)
            {
                return task1.priority() < task2.priority();
            }
        };
        
    };

    class NUFFTTask : public Task
    {
    public:
        int id;
        int *gray;//该任务的格雷码
        int *task_coord; //该任务的坐标（分区坐标）

        int *gird_starts;//该分区内所有点坐标的最小值
        int *gird_ends;//该分区内所有坐标的最大值
        

        int finished;//1表示任务已经完成
        
        int num_of_samples;//该任务中包含多少个nu点


        std::vector<int> index_nu;//样本点的索引集


        // NUFFTTask();

        // NUFFTTask(int id, int coord_x, int coord_y, int coord_z, int start_x, int start_y, int start_z, int end_x, int end_y, int end_z);

        // void set_samples();//计算该子任务中样本点，即完成index_nu,num_of_samples的值的获取

        int priority() const noexcept override
        {
            return num_of_samples;
        }

        // static void exe_task(NUFFTTask &task, std::complex<float>* nu);//执行任务

    };
}