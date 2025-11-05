#include <gtest/gtest.h>
#include "point.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"
#include "array.h"

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), 4.2);
}

TEST(PointTest, DistanceCalculation) {
    Point<int> p1(0, 0);
    Point<int> p2(3, 4);
    EXPECT_DOUBLE_EQ(p1.distanceTo(p2), 5.0);
}

TEST(RhombusTest, AreaCalculation) {
    Point<double> center(0, 0);
    Rhombus<double> rhombus(center, 4.0, 6.0);
    EXPECT_DOUBLE_EQ(rhombus.area(), 12.0);
}

TEST(RhombusTest, VerticesCount) {
    Point<int> center(0, 0);
    Rhombus<int> rhombus(center, 4, 6);
    auto vertices = rhombus.getVertices();
    EXPECT_EQ(vertices.size(), 4);
}

TEST(PentagonTest, AreaCalculation) {
    Point<double> center(0, 0);
    Pentagon<double> pentagon(center, 5.0);
    EXPECT_GT(pentagon.area(), 0.0);
}

TEST(PentagonTest, VerticesCount) {
    Point<float> center(0, 0);
    Pentagon<float> pentagon(center, 5.0f);
    auto vertices = pentagon.getVertices();
    EXPECT_EQ(vertices.size(), 5);
}

TEST(HexagonTest, AreaCalculation) {
    Point<double> center(0, 0);
    Hexagon<double> hexagon(center, 3.0);
    double expected_area = (3 * std::sqrt(3) * 3 * 3) / 2.0;
    EXPECT_DOUBLE_EQ(hexagon.area(), expected_area);
}

TEST(HexagonTest, VerticesCount) {
    Point<int> center(0, 0);
    Hexagon<int> hexagon(center, 3);
    auto vertices = hexagon.getVertices();
    EXPECT_EQ(vertices.size(), 6);
}

TEST(ArrayTest, DefaultConstructor) {
    Array<std::shared_ptr<Figure<int>>> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, PushBackAndSize) {
    Array<std::shared_ptr<Figure<double>>> arr;
    auto rhombus = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0);
    arr.push_back(rhombus);
    EXPECT_EQ(arr.size(), 1);
}

TEST(ArrayTest, TotalAreaCalculation) {
    Array<std::shared_ptr<Figure<double>>> arr;

    auto rhombus = std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0);
    auto pentagon = std::make_shared<Pentagon<double>>(Point<double>(0, 0), 3.0);

    arr.push_back(rhombus);
    arr.push_back(pentagon);

    double total_area = rhombus->area() + pentagon->area();
    EXPECT_DOUBLE_EQ(arr.totalArea(), total_area);
}

TEST(ArrayTest, EraseElement) {
    Array<std::shared_ptr<Figure<int>>> arr;

    auto fig1 = std::make_shared<Rhombus<int>>(Point<int>(0, 0), 4, 6);
    auto fig2 = std::make_shared<Pentagon<int>>(Point<int>(0, 0), 3);

    arr.push_back(fig1);
    arr.push_back(fig2);

    EXPECT_EQ(arr.size(), 2);
    arr.erase(0);
    EXPECT_EQ(arr.size(), 1);
}

TEST(ArrayTest, CopyConstructor) {
    Array<std::shared_ptr<Figure<double>>> original;
    original.push_back(std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0));

    Array<std::shared_ptr<Figure<double>>> copy = original;
    EXPECT_EQ(original.size(), copy.size());
}

TEST(ConversionTest, DoubleConversion) {
    Point<double> center(0, 0);
    Rhombus<double> rhombus(center, 4.0, 6.0);
    double area = static_cast<double>(rhombus);
    EXPECT_DOUBLE_EQ(area, rhombus.area());
}

TEST(ComparisonTest, FigureEquality) {
    Point<int> center(0, 0);
    Rhombus<int> rhombus1(center, 4, 6);
    Rhombus<int> rhombus2(center, 4, 6); 
    Rhombus<int> rhombus3(center, 4, 8); 

    EXPECT_TRUE(rhombus1 == rhombus2);
    EXPECT_FALSE(rhombus1 == rhombus3); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}