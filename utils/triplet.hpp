#pragma once

namespace omp_wrapper
{
    /**
     * 三元组
     * @deprecated
     */
    struct Triplet
    {
        int x;
        int y;
        int z;
        void operator=(int arr[3])
        {
            x = arr[0];
            y = arr[1];
            z = arr[2];
        }
        void set(const int & x, const int & y, const int & z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };
    struct Coordinate3D : Triplet
    {
    };
} // namespace omp_wrapper