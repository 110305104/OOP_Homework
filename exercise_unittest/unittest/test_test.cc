#include "gtest/gtest.h"
#include "sphere.h"
#include <cmath>

TEST(SphereTest, ConstructorTest1) {
    Sphere sph(0, 1, 2, 3);
    EXPECT_EQ(sph.getOrigin()[0], 0);
    EXPECT_EQ(sph.getOrigin()[1], 1);
    EXPECT_EQ(sph.getOrigin()[2], 2);
    EXPECT_EQ(sph.getRadius(), 3);
    EXPECT_LT(abs(sph.SurfaceArea()-4 * M_PI * pow(3, 2)),0.001);
    EXPECT_LT(abs(sph.Volume()-(4.0/3) * M_PI * pow(3, 3)),0.001);


}


TEST(SphereTest, ConstructorTest2) {

    Sphere sph1(0, 1, 2, -1);
    EXPECT_EQ(sph1.getRadius(), 0);

    Sphere sph2;
    sph2.setOrigin(0,1,2);
    EXPECT_EQ(sph2.getOrigin()[0], 0);
    EXPECT_EQ(sph2.getOrigin()[1], 1);
    EXPECT_EQ(sph2.getOrigin()[2], 2);
    EXPECT_EQ(sph2.getRadius(), 0);

    sph2.setRadius(2);
    EXPECT_EQ(sph2.getRadius(), 2);

    sph2.setRadius(-1);
    EXPECT_EQ(sph2.getRadius(), 0);


}

TEST(SphereTest, ConstructorTest3) {

    Sphere sph3(0, 0, 0, 2);
    Sphere sph4(0, 0, 1, 2);
    Sphere sph5(10, 10, 10, 2);
    EXPECT_EQ(sph3.intersect(sph4),true);
    EXPECT_EQ(sph3.intersect(sph5),false);

}
