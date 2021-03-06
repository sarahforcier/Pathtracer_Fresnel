#include "directlightingintegrator.h"

Color3f DirectLightingIntegrator::Li(const Ray &ray, const Scene &scene, std::shared_ptr<Sampler> sampler, int depth) const
{
    Intersection isect;
    Color3f Le;
    Color3f color;
    if (scene.Intersect(ray, &isect)) {
        Vector3f woW = - ray.direction;
        Le = isect.Le(woW);
        if (depth < 1 || !isect.objectHit->GetMaterial()) {
            color = Le;
        } else {
            // choose a random light
            int num= scene.lights.length();
            if (num == 0) return color;
            int index = std::min((int)(sampler->Get1D() * num), num - 1);

            // sample light source
            float pdf;
            Vector3f wiW;
            Point2f l_samp = sampler->Get2D(); // for lighting sample
            Color3f li = scene.lights[index]->Sample_Li(isect, l_samp, &wiW, &pdf);
            pdf /= num;

            // sample BSDF
            isect.ProduceBSDF();
            Color3f f = isect.bsdf->f(woW, wiW);

            // is Shadowed?
            Intersection shad_Feel;
            if (scene.Intersect(isect.SpawnRay(wiW), &shad_Feel)) {
                if (shad_Feel.t < 0.9) {
                    return Le;
                }
            }
            wiW = glm::normalize(wiW);

            if (pdf == 0.f) color = Le;
            else color =  Le + f * li * AbsDot(wiW, isect.normalGeometric)/pdf;
        }
    }
    return color;
}
