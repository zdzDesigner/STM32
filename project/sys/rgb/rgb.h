#include <stdint.h>

typedef struct xyBri {
  float x;
  float y;
  uint8_t bri;
} xyBri_t;

typedef struct RGB {
  uint8_t R;
  uint8_t G;
  uint8_t B;
} RGB_t;

RGB_t xyBriToRgb(xyBri_t xyBri);

