#pragma once
#include <vector>
#include <complex>
#include <unordered_map>
#include <cmath>
#include "../utils/triplet.hpp"

namespace omp_wrapper
{
    class Task
    {
    public:
        ~Task() {}
        virtual int priority() const noexcept = 0;
        virtual void execute() noexcept = 0;
        struct comparator
        {
            bool operator()(const Task &task1, const Task &task2)
            {
                return task1.priority() < task2.priority();
            }
        };
    };

    class NUFFTTask : public Task
    {
    public:
        int id;
        int num_of_samples; //该任务中包含多少个nu点

        int priority() const noexcept override
        {
            return num_of_samples;
        }

        void execute() noexcept override
        {
        }
    };

    class ADJConvTask : public Task
    {
    public:
        struct Coord_map_p
        {
            float data;
            int p;
            static bool comparator(const Coord_map_p &a, const Coord_map_p &b)
            {
                return a.data < b.data;
            }
        };

        int id;
        int gray_code;      //该任务的格雷码
        int num_of_samples; //该任务中包含多少个nu点

        Coordinate3D task_coord;  //该任务的坐标（分区坐标）
        Coordinate3D gird_starts; //该分区内所有点坐标的最小值
        Coordinate3D gird_ends;   //该分区内所有坐标的最大值

        bool finished = false; //true表示任务已经完成

        std::vector<int> index_nu; //样本点的索引集

        void set(const int &id,
                 const int &coord_x, const int &coord_y, const int &coord_z,
                 const int &start_x, const int &start_y, const int &start_z,
                 const int &end_x, const int &end_y, const int &end_z,
                 const int **hist,
                 const std::vector<Coord_map_p> &x_map_p,
                 const float *ky, const float *kz) noexcept
        {
            this->id = id;
            task_coord.set(coord_x, coord_y, coord_z);
            gird_starts.set(start_x, start_y, start_z);
            gird_ends.set(end_x, end_y, end_z);

            setGrayCode(task_coord);

            setSamples(hist, x_map_p, ky, kz);
        }

        int priority() const noexcept override
        {
            return num_of_samples;
        }

        void execute() noexcept override
        {
        }

        /**
         * @param kernel adj卷积函数
         */
        void execute(void (*kernel)()) noexcept
        {
            (*kernel)();
        }

    private:
        void setGrayCode(const Coordinate3D &coord) noexcept
        {
            const int mask = 1;
            gray_code = (coord.x & mask) << 2 + (coord.y & mask) << 1 + (coord.z & mask);
        }
        void setSamples(const int **hist,
                        const std::vector<Coord_map_p> &x_map_p,
                        const float *ky, const float *kz) noexcept
        {
            const int &startX = hist[0][gird_starts.x];
            const int &endX = hist[0][gird_ends.x];
            for (int i = startX; i < endX; ++i)
            {
                const int &p = x_map_p[i].p;
                if (ky[p] >= gird_starts.y && ky[p] < gird_ends.y)
                    if (kz[p] >= gird_starts.z && kz[p] < gird_ends.z)
                        index_nu.emplace_back(p);
            }
            num_of_samples = index_nu.size();
        }
    };
} // namespace omp_wrapper