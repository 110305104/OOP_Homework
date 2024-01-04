#include <iostream>

class Sphere {
   public:
    Sphere();
    Sphere(float ox, float oy, float oz, float rad);
    float SurfaceArea();
    float Volume();
    void setOrigin(float ox, float oy, float oz);
    void setRadius(float rad);
    float* getOrigin();
    float getRadius();
    bool intersect(Sphere&);
    friend std::ostream& operator<<(std::ostream&, const Sphere&);

   private:
    float orig_x, orig_y, orig_z;
    float radius;
};