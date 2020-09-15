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
    };
    struct Coordinate3D : Triplet
    {
    };
} // namespace omp_wrapper