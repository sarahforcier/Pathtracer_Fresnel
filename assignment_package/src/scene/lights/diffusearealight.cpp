#include "diffusearealight.h"

Color3f DiffuseAreaLight::Sample_Li(const Intersection &ref, const Point2f &xi,
                                     Vector3f *wi, Float *pdf) const {
    Color3f c(0);

    // Get an Intersection on the surface of its Shape
    Intersection inter = shape->Sample(ref, xi, pdf);

    //Check if the resultant PDF is zero or that the reference Intersection and
    //the resultant Intersection are the same point in space
    if (*pdf == 0.f || inter.point == ref.point) return c;

    //Set ωi to the vector from the reference Intersection's point
    //to the Shape's intersection point.
    // NOT normalized
    *wi = inter.point - ref.point;

    //Return the light emitted along ωi from our intersection point
    return L(ref, *wi);
}

Color3f DiffuseAreaLight::L(const Intersection &isect, const Vector3f &w) const
{
    if (twoSided) return emittedLight;
    return (glm::dot(isect.normalGeometric, glm::normalize(w))>0.f) ? emittedLight : Color3f(0.f);
}

