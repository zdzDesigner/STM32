#include "scale.h"

#include <stdio.h>


static int factorGen(Scaler* s) {
    return (int)(s->refmax - s->refmin)*1000 / (s->max - s->min);
}

static int conv(Scaler* s, unsigned val) {
    if (s->factor == 0) {
        s->factor = s->factorGen(s);
    }
    int xval = val - s->min;
    // printf("%d\n",xval);
    // printf("%d\n",s->factor);
    if (xval < 0) return 0;
    return (int)(s->factor * xval)/1000;
}

Scaler ScalerInit(unsigned refmin, unsigned refmax, unsigned min, unsigned max) {
    Scaler scaler = {
        .refmin    = refmin,
        .refmax    = refmax,
        .min       = min,
        .max       = max,
        .factorGen = factorGen,
        .conv      = conv,
    };
    return scaler;
}