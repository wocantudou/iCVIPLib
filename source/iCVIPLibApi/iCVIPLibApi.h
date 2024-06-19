#pragma once
#include "iCVSafeOpenCVReal.hpp"
// Keep the input parameters and return values of the encapsulated function
// consistent with the native OpenCV function
#define iCVimread SafeOpenCVRealInst()->imread
#define iCVimwrite SafeOpenCVRealInst()->imwrite
#define iCVresize SafeOpenCVRealInst()->resize
#define iCVcvtColor SafeOpenCVRealInst()->cvtColor
#define iCVcrop SafeOpenCVRealInst()->crop
#define iCVsub_mean_and_divide_std SafeOpenCVRealInst()->sub_mean_and_divide_std
#define iCVnms SafeOpenCVRealInst()->nms
#define iCVdecode_infer SafeOpenCVRealInst()->decode_infer
