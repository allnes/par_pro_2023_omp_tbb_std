// Copyright 2023 Bataev Ivan
#ifndef MODULES_TASK_3_BATAEV_I_RDX_SRT_DBL_ODD_EVN_RDX_SRT_DBL_ODD_EVN_H_
#define MODULES_TASK_3_BATAEV_I_RDX_SRT_DBL_ODD_EVN_RDX_SRT_DBL_ODD_EVN_H_

#include <vector>
#include <string>

void printVector(const std::vector<double>& v, const std::string& prefix = "");
std::vector<double> getRandomVector(int size, double left, double right);
void parRdxSrt(std::vector<double>* buf, const int size, int numParts = -1);
void oddEvnMerge(std::vector<double>* buf, std::vector<double>* tmpBuf, const int numParts, const int sizePart);

#endif  // MODULES_TASK_3_BATAEV_I_RDX_SRT_DBL_ODD_EVN_RDX_SRT_DBL_ODD_EVN_H_
