// Copyright 2023 Terentiev Alexander
#include "../../../modules/task_1/terentiev_a_trapez_integral/trapez_integral.h"

double Func1(double x, double y, double z) { return x * y * z; }

double Func2(double x, double y, double z) { return 1 / (x * y * z); }

bool Testing(double fromX, double fromY, double fromZ, double toX, double toY,
             double toZ, double (*integrateFunc)(double, double, double),
             double trueRes) {
    double trapezRes = TrapezIntegral3D(fromX, fromY, fromZ, toX, toY, toZ,
                                        Steps, integrateFunc);
    std::cout << trapezRes << " " << trueRes;
    return Compare(trapezRes, trueRes);
}

bool Compare(double a, double b) { return abs(a - b) < MaxError; }

double TrapezIntegral3D(double fromX, double fromY, double fromZ, double toX,
                        double toY, double toZ, int steps,
                        double (*func)(double, double, double)) {
    double lx = toX - fromX;
    double ly = toY - fromY;
    double lz = toZ - fromZ;

    double dx = lx / steps;
    double dy = ly / steps;
    double dz = lz / steps;

    double result = 0;

    for (int stepX = 0; stepX < steps; stepX++)
        for (int stepY = 0; stepY < steps; stepY++)
            for (int stepZ = 0; stepZ < steps; stepZ++) {
                double xPrev = fromX + dx * stepX;
                double yPrev = fromY + dy * stepY;
                double zPrev = fromZ + dz * stepZ;

                double xNext = fromX + dx * (stepX + 1);
                double yNext = fromY + dy * (stepY + 1);
                double zNext = fromZ + dz * (stepZ + 1);

                result +=
                    dx * dy * dz *
                    (func(xPrev, yPrev, zPrev) + func(xNext, yNext, zNext)) / 2;
            }

    return result;
}
