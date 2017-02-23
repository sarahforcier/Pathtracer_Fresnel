#include "fresnel.h"

Color3f FresnelDielectric::Evaluate(float cosThetaI) const
{
    //TODO
    Color3f color(1.f);
    bool in_out = cosThetaI > 0.f;
    float nI = in_out ? etaI : etaT;
    float nT = in_out ? etaT : etaI;
    float cosI = in_out ? cosThetaI : std::abs(cosThetaI);
    float sinI = std::sqrt(std::max(0.f, 1 - cosI * cosI));
    float sinT = nI / nT * sinI;
    if (sinT >= 1.f) {
        return color;
    }
    float cosT = std::sqrt(std::max(0.f, 1 - sinT * sinT));
    float rPara = (nT * cosI - nI * cosT) / (nT * cosI + nI * cosT);
    float rPerp = (nI * cosI - nT * cosT) / (nI * cosI + nT * cosT);
    return Color3f((rPara * rPara + rPerp * rPerp) / 2.f);
}
