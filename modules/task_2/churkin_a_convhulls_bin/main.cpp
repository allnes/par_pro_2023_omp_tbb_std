// Copyright 2023 Churkin Aleksandr
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include "./convhulls_bin.h"

void CheckImages(int* imageOrig, int* imagePar, int* imageSeq, int M, int N,
    bool compareWithOriginal) {
    std::map<int, int> bijectionMap;
    bijectionMap[0] = 0;

    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            int pOrig = imageOrig[y * N + x];
            int p1 = imagePar[y * N + x];
            int p2 = imageSeq[y * N + x];

            // checks that both processed images keep only original pixels
            if (compareWithOriginal) {
                EXPECT_FALSE((p1 == 0 && pOrig != 0) || (p1 != 0 && pOrig == 0));
            }

            // checking bijection
            if (bijectionMap.find(p1) == bijectionMap.end()) {
                bijectionMap[p1] = p2;
            } else {
                EXPECT_EQ(p2, bijectionMap[p1]);
            }
        }
    }
}

void RunRandomImageTest(int M, int N) {
    std::vector<int> imageOrig = GetRandomBinImage(M, N);
    std::vector<int> imagePar(imageOrig);
    std::vector<int> imageSeq(imageOrig);

    double t1Par, t2Par, t1Seq, t2Seq, tParTotal, tSeqTotal;

    /* std::cout << "Original image:\n";
    PrintImage(&imageOrig[0], M, N); */

    t1Par = omp_get_wtime();
    auto componentsPar = MarkComponentsParallel(&imagePar[0], M, N);
    t2Par = omp_get_wtime();

    t1Seq = omp_get_wtime();
    auto componentsSeq = MarkComponents(&imageSeq[0], M, N);
    t2Seq = omp_get_wtime();

    tParTotal = (t2Par - t1Par);
    tSeqTotal = (t2Seq - t1Seq);

    RedrawImageFromComponents(&imagePar[0], componentsPar, M, N);
    RedrawImageFromComponents(&imageSeq[0], componentsSeq, M, N);

    // Check 1: checking that after labelling components original pixels saved
    // and we have bijection between components of both processed images
    CheckImages(&imageOrig[0], &imagePar[0], &imageSeq[0], M, N, true);

    t1Par = omp_get_wtime();
    componentsPar = LeaveOnlyHulls(&componentsPar, M, N);
    t2Par = omp_get_wtime();

    t1Seq = omp_get_wtime();
    componentsSeq = LeaveOnlyHulls(&componentsSeq, M, N);
    t2Seq = omp_get_wtime();

    tParTotal += (t2Par - t1Par);
    tSeqTotal += (t2Seq - t1Seq);

    RedrawImageFromComponents(&imagePar[0], componentsPar, M, N);
    RedrawImageFromComponents(&imageSeq[0], componentsSeq, M, N);

    // Check 2: checking that after Graham convex hulls search
    // we have bijection between components of both processed images
    CheckImages(&imageOrig[0], &imagePar[0], &imageSeq[0], M, N, false);

    /* std::cout << "Parallel processed result:\n";
    PrintImage(&imagePar[0], M, N);

    std::cout << "Sequential processed result:\n";
    PrintImage(&imageSeq[0], M, N); */

    /* std::cout << "Duration parallel: " << tParTotal << "\n";
    std::cout << "Duration sequential: " << tSeqTotal << "\n"; */
}

TEST(ConvHullsBin_OpenMP, Test_1_Can_Get_Hulls_10X10) {
    const int M = 10, N = 10;
    std::vector<int> image({
    0, 1, 0, 0, 0, 1, 1, 1, 0, 0,
    1, 1, 0, 0, 1, 1, 1, 1, 0, 0,
    1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
    1, 1, 0, 1, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 1, 1, 0, 1,
    1, 1, 0, 0, 0, 0, 1, 1, 0, 0,
    1, 1, 0, 0, 0, 0, 1, 1, 0, 0,
    });

    auto components = MarkComponentsParallel(&image[0], M, N);
    components = LeaveOnlyHulls(&components, M, N);
    RedrawImageFromComponents(&image[0], components, M, N);

    std::vector<int> rightResult({
    0, 2, 0, 0, 0, 3, 0, 3, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 2, 0, 0, 0, 0, 3, 3, 0, 0,
    });

    CheckImages(&image[0], &image[0], &rightResult[0], M, N, false);
}

TEST(ConvHullsBin_OpenMP, Test_2_EmptyImage_10X10) {
    const int M = 10, N = 10;
    std::vector<int> image({
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    });

    auto components = MarkComponentsParallel(&image[0], M, N);
    components = LeaveOnlyHulls(&components, M, N);

    EXPECT_EQ(components.size(), 0);
}

TEST(ConvHullsBin_OpenMP, Test_3_RandomImage_10X10) {
    RunRandomImageTest(10, 10);
}

TEST(ConvHullsBin_OpenMP, Test_4_RandomImage_20X10) {
    RunRandomImageTest(20, 10);
}

TEST(ConvHullsBin_OpenMP, Test_5_RandomImage_40X40) {
    RunRandomImageTest(40, 40);
}

/* TEST(ConvHullsBin_OpenMP, Test_6_RandomImage_1500X1500) {
    // Note that recreating images from info about connected components
    // also takes time,
    // and this time was not counted in tests
    RunRandomImageTest(1500, 1500);
} */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
