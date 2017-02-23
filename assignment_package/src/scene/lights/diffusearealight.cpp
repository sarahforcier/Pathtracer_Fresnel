#include "diffusearealight.h"

Color3f DiffuseAreaLight::Sample_Li(const Intersection &ref, const Point2f &xi,
                                     Vector3f *wi, Float *pdf) const {
    Color3f c(0);
    return c;
}

Color3f DiffuseAreaLight::L(const Intersection &isect, const Vector3f &w) const
{
    if (twoSided) return emittedLight;
    return (glm::dot(isect.normalGeometric, w)>0.f) ? emittedLight : Color3f(0.f);
}

