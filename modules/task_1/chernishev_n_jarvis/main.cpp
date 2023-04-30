// Copyright 2023 Chernishev Nikita

#include <gtest/gtest.h>

#include "./chernishev_n_jarvis_seq.h"

TEST(OMP, Test_SEQ_Jarvis_30) {
    std::vector<dot> vec{
        dot(-5, 38),   dot(-57, 80),  dot(73, 9),    dot(-85, -83),
        dot(74, 12),   dot(-32, -55), dot(32, 43),   dot(-10, 33),
        dot(-6, -46),  dot(38, 79),   dot(-61, -52), dot(-44, 40),
        dot(-37, 64),  dot(-61, -13), dot(14, 79),   dot(7, 88),
        dot(-8, 59),   dot(-68, 10),  dot(54, 4),    dot(48, -15),
        dot(-94, -40), dot(65, 88),   dot(-70, 58),  dot(8, -81),
        dot(-70, -21), dot(33, -44),  dot(-31, 67),  dot(-20, -88),
        dot(-62, 0),   dot(77, 70),
    };
    std::vector<dot> res{
        dot(-20, -88), dot(-85, -83), dot(-94, -40), dot(-70, 58),
        dot(-57, 80),  dot(7, 88),    dot(65, 88),   dot(77, 70),
        dot(74, 12),   dot(73, 9),    dot(8, -81),
    };
    std::vector<dot> seqRes = JarvisSeq(vec);
    EXPECT_TRUE(isEqual(seqRes, res));
}

TEST(OMP, Test_SEQ_Jarvis_10) {
    std::vector<dot> vec{
        dot(87, -83), dot(28, -32),  dot(50, -66), dot(6, 19),   dot(-35, -90),
        dot(-46, 61), dot(-75, -29), dot(6, 0),    dot(-6, -88), dot(37, -69),
        dot(-52, 20), dot(10, -64),  dot(-66, 22), dot(-16, 74), dot(-78, 14)};

    std::vector<dot> res{dot(-35, -90), dot(-75, -29), dot(-78, 14),
                         dot(-46, 61),  dot(-16, 74),  dot(87, -83)};

    std::vector<dot> seqRes = JarvisSeq(vec);
    EXPECT_TRUE(isEqual(seqRes, res));
}

TEST(OMP, Test_SEQ_Jarvis_15) {
    std::vector<dot> vec{
        dot(87, -83), dot(28, -32),  dot(50, -66), dot(6, 19),   dot(-35, -90),
        dot(-46, 61), dot(-75, -29), dot(6, 0),    dot(-6, -88), dot(37, -69),
        dot(-52, 20), dot(10, -64),  dot(-66, 22), dot(-16, 74), dot(-78, 14),
        dot(-5, -53), dot(18, -85),  dot(54, 2),   dot(79, 70),  dot(-51, 26),
        dot(87, 94),  dot(-10, -85), dot(84, 5),   dot(62, 41),  dot(-53, -58),
        dot(27, 38),  dot(46, -63),  dot(37, -77), dot(71, -60), dot(63, 73)};

    std::vector<dot> res{dot(-35, -90), dot(-75, -29), dot(-78, 14),
                         dot(-46, 61),  dot(-16, 74),  dot(87, 94),
                         dot(87, -83)};

    std::vector<dot> seqRes = JarvisSeq(vec);
    EXPECT_TRUE(isEqual(seqRes, res));
}

TEST(OMP, Test_SEQ_Jarvis_20) {
    std::vector<dot> vec{
        dot(87, -83), dot(28, -32),  dot(50, -66), dot(6, 19),   dot(-35, -90),
        dot(-46, 61), dot(-75, -29), dot(6, 0),    dot(-6, -88), dot(37, -69),
        dot(-52, 20), dot(10, -64),  dot(-66, 22), dot(-16, 74), dot(-78, 14),
        dot(-5, -53), dot(18, -85),  dot(54, 2),   dot(79, 70),  dot(-51, 26),
        dot(87, 94),  dot(-10, -85), dot(84, 5),   dot(62, 41),  dot(-53, -58),
        dot(27, 38),  dot(46, -63),  dot(37, -77), dot(71, -60), dot(63, 73),
        dot(20, -23), dot(22, -64),  dot(67, 32),  dot(79, 24),  dot(44, 28),
        dot(55, -30), dot(94, -93),  dot(33, -63), dot(86, -20), dot(-20, 90),
        dot(66, 71),  dot(78, -62),  dot(97, 58),  dot(-4, 38),  dot(-94, 59),
        dot(50, -32), dot(-11, -7),  dot(-55, -8), dot(10, -32), dot(29, 4)};

    std::vector<dot> res{dot(94, -93), dot(-35, -90), dot(-75, -29),
                         dot(-94, 59), dot(-20, 90),  dot(87, 94),
                         dot(97, 58)};

    std::vector<dot> seqRes = JarvisSeq(vec);
    EXPECT_TRUE(isEqual(seqRes, res));
}

TEST(OMP, Test_SEQ_Jarvis_25) {
    std::vector<dot> vec{
        dot(87, -83),  dot(28, -32),  dot(50, -66),  dot(6, 19),
        dot(-35, -90), dot(-46, 61),  dot(-75, -29), dot(6, 0),
        dot(-6, -88),  dot(37, -69),  dot(-52, 20),  dot(10, -64),
        dot(-66, 22),  dot(-16, 74),  dot(-78, 14),  dot(-5, -53),
        dot(18, -85),  dot(54, 2),    dot(79, 70),   dot(-51, 26),
        dot(87, 94),   dot(-10, -85), dot(84, 5),    dot(62, 41),
        dot(-53, -58), dot(27, 38),   dot(46, -63),  dot(37, -77),
        dot(71, -60),  dot(63, 73),   dot(20, -23),  dot(22, -64),
        dot(67, 32),   dot(79, 24),   dot(44, 28),   dot(55, -30),
        dot(94, -93),  dot(33, -63),  dot(86, -20),  dot(-20, 90),
        dot(66, 71),   dot(78, -62),  dot(97, 58),   dot(-4, 38),
        dot(-94, 59),  dot(50, -32),  dot(-11, -7),  dot(-55, -8),
        dot(10, -32),  dot(29, 4),    dot(-88, 94),  dot(48, 28),
        dot(93, 34),   dot(-42, -43), dot(-51, -2),  dot(-66, 73),
        dot(1, -33),   dot(-57, -4),  dot(38, 73),   dot(-3, 15),
        dot(-16, -23), dot(85, -69),  dot(-21, 98),  dot(-70, 7),
        dot(-32, -73), dot(-38, -30), dot(61, 76),   dot(-9, 0),
        dot(-28, -1),  dot(96, -36),  dot(83, 3),    dot(-33, -91),
        dot(-37, 21),  dot(-26, -28), dot(-65, 53)};

    std::vector<dot> res{dot(94, -93),  dot(-33, -91), dot(-35, -90),
                         dot(-75, -29), dot(-94, 59),  dot(-88, 94),
                         dot(-21, 98),  dot(87, 94),   dot(97, 58),
                         dot(96, -36)};

    std::vector<dot> seqRes = JarvisSeq(vec);
    EXPECT_TRUE(isEqual(seqRes, res));
}
