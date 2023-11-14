#include <math.h>
#include "rgb.h"

RGB_t xyBriToRgb(xyBri_t xyBri)
{
    float X, Y, Z, z, r, g, b, maxValue;
    xyBri.x /= 255;
    xyBri.y /= 255;
    // xyBri.x /= 65535;
    // xyBri.y /= 65535;
    printf("x: %f\n", xyBri.x);
    printf("y: %f\n", xyBri.y);
    // Calculate the XYZ values from the xyBri values.
    z = 1.0 - xyBri.x - xyBri.y;
    Y = xyBri.bri / 255.0;
    X = (Y / xyBri.y) * xyBri.x;
    Z = (Y / xyBri.y) * z;

    // Apply gamma correction.
    r = X * 1.612 - Y * 0.203 - Z * 0.302;
    g = -X * 0.509 + Y * 1.412 + Z * 0.066;
    b = X * 0.026 - Y * 0.072 + Z * 0.962;

    // r = X * 3.2406 - Y * 1.5372 - Z * 0.4986;
    // g = -X * 0.9689  + Y * 1.8758 + Z * 0.0415;
    // b = X * 0.0557 - Y * -0.2040 + Z * 1.0570;

    // Clamp the RGB values to the range [0.0, 1.0].
    r = r <= 0.0031308 ? 12.92 * r : (1.0 + 0.055) * pow(r, (1.0 / 2.4)) - 0.055;
    g = g <= 0.0031308 ? 12.92 * g : (1.0 + 0.055) * pow(g, (1.0 / 2.4)) - 0.055;
    b = b <= 0.0031308 ? 12.92 * b : (1.0 + 0.055) * pow(b, (1.0 / 2.4)) - 0.055;

    // Find the maximum RGB value.
    maxValue = fmax(r, fmax(g, b));

    // Normalize the RGB values.
    r /= maxValue;
    g /= maxValue;
    b /= maxValue;

    // Scale the RGB values to the range [0, 255].
    r *= xyBri.bri;
    if (r < 0.0) {
        r = 0.0;
    }
    g *= xyBri.bri;
    if (g < 0.0) {
        g = 0.0;
    }
    b *= xyBri.bri;
    if (b < 0.0) {
        b = 0.0;
    }

    // Return the RGB values.
    RGB_t rgb = {r, g, b};
    return rgb;
}
