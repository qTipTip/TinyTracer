#include "vec3.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>

// Simple testing framework
#define TEST(name) void test_##name()
#define ASSERT_EQ(expected, actual) \
    do { \
        if (!((expected) == (actual))) { \
            std::cerr << "ASSERTION FAILED: " << #expected << " == " << #actual \
                      << " (expected: " << (expected) << ", actual: " << (actual) << ")" \
                      << " at line " << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while(0)

#define ASSERT_FLOAT_EQ(expected, actual, tolerance) \
    do { \
        if (std::abs((expected) - (actual)) > (tolerance)) { \
            std::cerr << "FLOAT ASSERTION FAILED: " << #expected << " ≈ " << #actual \
                      << " (expected: " << (expected) << ", actual: " << (actual) \
                      << ", diff: " << std::abs((expected) - (actual)) << ")" \
                      << " at line " << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while(0)

#define RUN_TEST(name) \
    do { \
        std::cout << "Running " << #name << "... "; \
        test_##name(); \
        std::cout << "PASSED" << std::endl; \
    } while(0)

// Helper function to compare Vec3 with tolerance
bool vec3_equals(const Vec3& a, const Vec3& b, float tolerance = 1e-6f) {
    return std::abs(a.x() - b.x()) < tolerance &&
           std::abs(a.y() - b.y()) < tolerance &&
           std::abs(a.z() - b.z()) < tolerance;
}

// Constructor Tests
TEST(default_constructor) {
    Vec3 v;
    ASSERT_EQ(0.0f, v.x());
    ASSERT_EQ(0.0f, v.y());
    ASSERT_EQ(0.0f, v.z());
}

TEST(parameterized_constructor) {
    Vec3 v(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(1.0f, v.x());
    ASSERT_EQ(2.0f, v.y());
    ASSERT_EQ(3.0f, v.z());
}

// Access Tests
TEST(component_access) {
    Vec3 v(1.5f, 2.5f, 3.5f);
    ASSERT_EQ(1.5f, v.x());
    ASSERT_EQ(2.5f, v.y());
    ASSERT_EQ(3.5f, v.z());
}

TEST(subscript_operator_read) {
    Vec3 v(10.0f, 20.0f, 30.0f);
    ASSERT_EQ(10.0f, v[0]);
    ASSERT_EQ(20.0f, v[1]);
    ASSERT_EQ(30.0f, v[2]);
}

TEST(subscript_operator_write) {
    Vec3 v(1.0f, 2.0f, 3.0f);
    v[0] = 5.0f;
    v[1] = 6.0f;
    v[2] = 7.0f;
    ASSERT_EQ(5.0f, v[0]);
    ASSERT_EQ(6.0f, v[1]);
    ASSERT_EQ(7.0f, v[2]);
}

TEST(const_subscript_operator) {
    const Vec3 v(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(1.0f, v[0]);
    ASSERT_EQ(2.0f, v[1]);
    ASSERT_EQ(3.0f, v[2]);
    // Note: v[0] = 5.0f; would be a compiler error here (good!)
}

// Arithmetic Tests
TEST(negation_operator) {
    Vec3 v(1.0f, -2.0f, 3.0f);
    Vec3 neg = -v;
    ASSERT_EQ(-1.0f, neg.x());
    ASSERT_EQ(2.0f, neg.y());
    ASSERT_EQ(-3.0f, neg.z());
}

TEST(addition_assignment) {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    a += b;
    ASSERT_EQ(5.0f, a.x());
    ASSERT_EQ(7.0f, a.y());
    ASSERT_EQ(9.0f, a.z());
}

TEST(scalar_multiplication_assignment) {
    Vec3 v(2.0f, 3.0f, 4.0f);
    v *= 2.5f;
    ASSERT_EQ(5.0f, v.x());
    ASSERT_EQ(7.5f, v.y());
    ASSERT_EQ(10.0f, v.z());
}

TEST(scalar_division_assignment) {
    Vec3 v(10.0f, 20.0f, 30.0f);
    v /= 2.0f;
    ASSERT_EQ(5.0f, v.x());
    ASSERT_EQ(10.0f, v.y());
    ASSERT_EQ(15.0f, v.z());
}

// Binary Operations Tests
TEST(vector_addition) {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    Vec3 c = a + b;
    ASSERT_EQ(5.0f, c.x());
    ASSERT_EQ(7.0f, c.y());
    ASSERT_EQ(9.0f, c.z());
}

TEST(vector_subtraction) {
    Vec3 a(5.0f, 7.0f, 9.0f);
    Vec3 b(1.0f, 2.0f, 3.0f);
    Vec3 c = a - b;
    ASSERT_EQ(4.0f, c.x());
    ASSERT_EQ(5.0f, c.y());
    ASSERT_EQ(6.0f, c.z());
}

TEST(vector_multiplication) {
    Vec3 a(2.0f, 3.0f, 4.0f);
    Vec3 b(5.0f, 6.0f, 7.0f);
    Vec3 c = a * b;
    ASSERT_EQ(10.0f, c.x());
    ASSERT_EQ(18.0f, c.y());
    ASSERT_EQ(28.0f, c.z());
}

TEST(scalar_multiplication_left) {
    Vec3 v(2.0f, 3.0f, 4.0f);
    Vec3 result = 3.0f * v;
    ASSERT_EQ(6.0f, result.x());
    ASSERT_EQ(9.0f, result.y());
    ASSERT_EQ(12.0f, result.z());
}

TEST(scalar_multiplication_right) {
    Vec3 v(2.0f, 3.0f, 4.0f);
    Vec3 result = v * 3.0f;
    ASSERT_EQ(6.0f, result.x());
    ASSERT_EQ(9.0f, result.y());
    ASSERT_EQ(12.0f, result.z());
}

TEST(scalar_division) {
    Vec3 v(6.0f, 9.0f, 12.0f);
    Vec3 result = v / 3.0f;
    ASSERT_EQ(2.0f, result.x());
    ASSERT_EQ(3.0f, result.y());
    ASSERT_EQ(4.0f, result.z());
}

// Property Tests
TEST(length_squared) {
    Vec3 v(3.0f, 4.0f, 0.0f);  // 3-4-5 triangle
    ASSERT_EQ(25.0f, v.length_squared());
}

TEST(length) {
    Vec3 v(3.0f, 4.0f, 0.0f);  // 3-4-5 triangle
    ASSERT_FLOAT_EQ(5.0f, v.length(), 1e-6f);
}

TEST(unit_vector_member) {
    Vec3 v(3.0f, 4.0f, 0.0f);
    Vec3 unit = v.unit_vector();
    ASSERT_FLOAT_EQ(1.0f, unit.length(), 1e-6f);
    ASSERT_FLOAT_EQ(0.6f, unit.x(), 1e-6f);  // 3/5
    ASSERT_FLOAT_EQ(0.8f, unit.y(), 1e-6f);  // 4/5
    ASSERT_FLOAT_EQ(0.0f, unit.z(), 1e-6f);
}

TEST(unit_vector_free_function) {
    Vec3 v(3.0f, 4.0f, 0.0f);
    Vec3 unit = unit_vector(v);
    ASSERT_FLOAT_EQ(1.0f, unit.length(), 1e-6f);
    ASSERT_FLOAT_EQ(0.6f, unit.x(), 1e-6f);
    ASSERT_FLOAT_EQ(0.8f, unit.y(), 1e-6f);
    ASSERT_FLOAT_EQ(0.0f, unit.z(), 1e-6f);
}

// Utility Function Tests
TEST(dot_product) {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    float result = dot(a, b);
    ASSERT_EQ(32.0f, result);  // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
}

TEST(dot_product_orthogonal) {
    Vec3 a(1.0f, 0.0f, 0.0f);
    Vec3 b(0.0f, 1.0f, 0.0f);
    float result = dot(a, b);
    ASSERT_EQ(0.0f, result);  // Orthogonal vectors
}

TEST(cross_product) {
    Vec3 a(1.0f, 0.0f, 0.0f);
    Vec3 b(0.0f, 1.0f, 0.0f);
    Vec3 c = cross(a, b);
    ASSERT_EQ(0.0f, c.x());
    ASSERT_EQ(0.0f, c.y());
    ASSERT_EQ(1.0f, c.z());
}

TEST(cross_product_anticommutative) {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    Vec3 cross_ab = cross(a, b);
    Vec3 cross_ba = cross(b, a);
    Vec3 neg_cross_ba = -cross_ba;

    ASSERT_FLOAT_EQ(cross_ab.x(), neg_cross_ba.x(), 1e-6f);
    ASSERT_FLOAT_EQ(cross_ab.y(), neg_cross_ba.y(), 1e-6f);
    ASSERT_FLOAT_EQ(cross_ab.z(), neg_cross_ba.z(), 1e-6f);
}

// Type Alias Tests
TEST(point3_alias) {
    Point3 p(1.0f, 2.0f, 3.0f);
    ASSERT_EQ(1.0f, p.x());
    ASSERT_EQ(2.0f, p.y());
    ASSERT_EQ(3.0f, p.z());
}

TEST(color_alias) {
    Color c(0.5f, 0.7f, 1.0f);
    ASSERT_EQ(0.5f, c.x());  // Red component
    ASSERT_EQ(0.7f, c.y());  // Green component
    ASSERT_EQ(1.0f, c.z());  // Blue component
}

// Stream Output Test
TEST(stream_output) {
    Vec3 v(1.5f, 2.5f, 3.5f);
    std::stringstream ss;
    ss << v;
    ASSERT_EQ("(1.5,2.5,3.5)", ss.str());
}

// Edge Cases
TEST(zero_vector_length) {
    Vec3 zero;
    ASSERT_EQ(0.0f, zero.length_squared());
    ASSERT_EQ(0.0f, zero.length());
}

TEST(large_numbers) {
    Vec3 v(1e6f, 2e6f, 3e6f);
    ASSERT_FLOAT_EQ(14e12f, v.length_squared(), 1e6f);  // 1e12 + 4e12 + 9e12
}

// Constexpr Tests (compile-time evaluation)
TEST(constexpr_operations) {
    // These should be computable at compile time
    constexpr Vec3 a(1.0f, 2.0f, 3.0f);
    constexpr Vec3 b(4.0f, 5.0f, 6.0f);
    constexpr Vec3 c = a + b;
    constexpr float d = dot(a, b);

    ASSERT_EQ(5.0f, c.x());
    ASSERT_EQ(32.0f, d);
}

int main() {
    std::cout << "Running Vec3 Test Suite\n";
    std::cout << "======================\n";

    // Constructor tests
    RUN_TEST(default_constructor);
    RUN_TEST(parameterized_constructor);

    // Access tests
    RUN_TEST(component_access);
    RUN_TEST(subscript_operator_read);
    RUN_TEST(subscript_operator_write);
    RUN_TEST(const_subscript_operator);

    // Arithmetic tests
    RUN_TEST(negation_operator);
    RUN_TEST(addition_assignment);
    RUN_TEST(scalar_multiplication_assignment);
    RUN_TEST(scalar_division_assignment);

    // Binary operation tests
    RUN_TEST(vector_addition);
    RUN_TEST(vector_subtraction);
    RUN_TEST(vector_multiplication);
    RUN_TEST(scalar_multiplication_left);
    RUN_TEST(scalar_multiplication_right);
    RUN_TEST(scalar_division);

    // Property tests
    RUN_TEST(length_squared);
    RUN_TEST(length);
    RUN_TEST(unit_vector_member);
    RUN_TEST(unit_vector_free_function);

    // Utility function tests
    RUN_TEST(dot_product);
    RUN_TEST(dot_product_orthogonal);
    RUN_TEST(cross_product);
    RUN_TEST(cross_product_anticommutative);

    // Type alias tests
    RUN_TEST(point3_alias);
    RUN_TEST(color_alias);

    // Stream output test
    RUN_TEST(stream_output);

    // Edge cases
    RUN_TEST(zero_vector_length);
    RUN_TEST(large_numbers);

    // Constexpr tests
    RUN_TEST(constexpr_operations);


    return 0;
}