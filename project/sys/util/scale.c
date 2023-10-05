#include "scale.h"

static int factor_get(Scaler *s)
{
    return (int)(s->refmax - s->refmin) * 1000 / (int)(s->max - s->min);
}

static int conv(Scaler *s, int val)
{
    if (s->factor == 0) {
        s->factor = s->factor_get(s);
    }

    int refmin = s->refmin;
    int refmax = s->refmax;

    int nval = val - s->min; // 以真实最小值为基准, 得到当前值
    // nval = nval < 0 ? 0 : nval;

    nval = (int)(s->factor * nval) / 1000; // 乘以比例因子
    nval = nval + refmin;

    // printf("%d,refmin:%d,:%d\n", nval, refmin, nval < refmin);
    if (nval <= refmin) return refmin; // 最小值
    if (nval >= refmax) return refmax; // 最大值
    return nval;

    // int nval = val - s->min; // 以真实最小值为基准, 得到当前值
    // if (nval < 0) return 0;  // 最小值
    //
    // nval = (int)(s->factor * nval) / 1000;  // 乘以比例因子
    // if (nval > s->refmax) return s->refmax; // 最大值
    // return nval;
}

Scaler ScalerInit(unsigned refmin, unsigned refmax, unsigned min, unsigned max)
{
    Scaler scaler = {
        .refmin     = refmin,
        .refmax     = refmax,
        .min        = min,
        .max        = max,
        .factor_get = factor_get,
        .conv       = conv,
    };
    return scaler;
}
