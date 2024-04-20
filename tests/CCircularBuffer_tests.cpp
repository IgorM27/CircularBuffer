#include <gtest/gtest.h>
#include <sstream>
#include "CCircularBuffer.h"
#include "CCircularBufferExt.h"


TEST(Push_back, int) {
    CCircularBuffer<int, std::allocator<int>> a(2);
    CCircularBufferExt<int, std::allocator<int>> b(2);
    a.push_back(1);
    a.push_back(2);
    b.push_back(1);
    b.push_back(2);
    ASSERT_EQ(1, a[0]);
    ASSERT_EQ(2, a[1]);
    ASSERT_EQ(1, b[0]);
    ASSERT_EQ(2, b[1]);
}

TEST(Push_back, float) {
    CCircularBuffer<float, std::allocator<float>> a(2);
    CCircularBufferExt<float, std::allocator<float>> b(2);
    a.push_back(1.3);
    a.push_back(9.4);
    b.push_back(1.3);
    b.push_back(9.4);
    ASSERT_EQ(static_cast<float>(1.3), a[0]);
    ASSERT_EQ(static_cast<float>(9.4), a[1]);
    ASSERT_EQ(static_cast<float>(1.3), b[0]);
    ASSERT_EQ(static_cast<float>(9.4), b[1]);
}

TEST(Push_back, double) {
    CCircularBuffer<double, std::allocator<double>> a(2);
    CCircularBufferExt<double, std::allocator<double>> b(2);
    a.push_back(1.6767);
    a.push_back(2.15);
    b.push_back(1.6767);
    b.push_back(2.15);
    ASSERT_EQ(1.6767, a[0]);
    ASSERT_EQ(2.15, a[1]);
    ASSERT_EQ(1.6767, b[0]);
    ASSERT_EQ(2.15, b[1]);
}

TEST(Push_back, char) {
    CCircularBuffer<char, std::allocator<char>> a(2);
    CCircularBufferExt<char, std::allocator<char>> b(2);
    a.push_back('a');
    a.push_back('b');
    b.push_back('a');
    b.push_back('b');
    ASSERT_EQ('a', a[0]);
    ASSERT_EQ('b', a[1]);
    ASSERT_EQ('a', b[0]);
    ASSERT_EQ('b', b[1]);
}

TEST(Push_back, string) {
    CCircularBuffer<std::string, std::allocator<std::string>> a(2);
    CCircularBufferExt<std::string, std::allocator<std::string>> b(2);
    a.push_back("Hello world!");
    a.push_back("Saint-Petersburg");
    b.push_back("Hello world!");
    b.push_back("Saint-Petersburg");
    ASSERT_EQ("Hello world!", a[0]);
    ASSERT_EQ("Saint-Petersburg", a[1]);
    ASSERT_EQ("Hello world!", b[0]);
    ASSERT_EQ("Saint-Petersburg", b[1]);
}

TEST(Push_front, int) {
    CCircularBuffer<int, std::allocator<int>> a(2);
    CCircularBufferExt<int, std::allocator<int>> b(2);
    a.push_front(1);
    a.push_front(2);
    b.push_front(1);
    b.push_front(2);
    ASSERT_EQ(2, a[0]);
    ASSERT_EQ(1, a[1]);
    ASSERT_EQ(2, b[0]);
    ASSERT_EQ(1, b[1]);
}

TEST(Push_front, float) {
    CCircularBuffer<float, std::allocator<float>> a(2);
    CCircularBufferExt<float, std::allocator<float>> b(2);
    a.push_front(1.3);
    a.push_front(9.4);
    b.push_front(1.3);
    b.push_front(9.4);
    ASSERT_EQ(static_cast<float>(9.4), a[0]);
    ASSERT_EQ(static_cast<float>(1.3), a[1]);
    ASSERT_EQ(static_cast<float>(9.4), b[0]);
    ASSERT_EQ(static_cast<float>(1.3), b[1]);
}

TEST(Push_front, double) {
    CCircularBuffer<double, std::allocator<double>> a(2);
    CCircularBufferExt<double, std::allocator<double>> b(2);
    a.push_front(1.6767);
    a.push_front(2.15);
    b.push_front(1.6767);
    b.push_front(2.15);
    ASSERT_EQ(2.15, a[0]);
    ASSERT_EQ(1.6767, a[1]);
    ASSERT_EQ(2.15, b[0]);
    ASSERT_EQ(1.6767, b[1]);
}

TEST(Push_front, char) {
    CCircularBuffer<char, std::allocator<char>> a(2);
    CCircularBufferExt<char, std::allocator<char>> b(2);
    a.push_front('a');
    a.push_front('b');
    b.push_front('a');
    b.push_front('b');
    ASSERT_EQ('b', a[0]);
    ASSERT_EQ('a', a[1]);
    ASSERT_EQ('b', b[0]);
    ASSERT_EQ('a', b[1]);
}

TEST(Push_front, string) {
    CCircularBuffer<std::string, std::allocator<std::string>> a(2);
    CCircularBufferExt<std::string, std::allocator<std::string>> b(2);
    a.push_front("Hello world!");
    a.push_front("Saint-Petersburg");
    b.push_front("Hello world!");
    b.push_front("Saint-Petersburg");
    ASSERT_EQ("Saint-Petersburg", a[0]);
    ASSERT_EQ("Hello world!", a[1]);
    ASSERT_EQ("Saint-Petersburg", b[0]);
    ASSERT_EQ("Hello world!", b[1]);
}

TEST(Equality, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(3);
    CCircularBuffer<int, std::allocator<int>> b(3);
    a.push_back(2);
    a.push_back(12);
    b.push_back(2);
    b.push_back(12);
    ASSERT_TRUE(a == b);
    b.push_back(5);
    ASSERT_FALSE(a == b);
}

TEST(Equality, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(3);
    CCircularBufferExt<int, std::allocator<int>> b(3);
    a.push_back(55);
    a.push_back(84);
    b.push_back(55);
    b.push_back(84);
    ASSERT_TRUE(a == b);
    b.push_back(10);
    ASSERT_FALSE(a == b);
}

TEST(NotEquality, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(3);
    CCircularBuffer<int, std::allocator<int>> b(3);
    a.push_back(4);
    a.push_back(125);
    b.push_back(4);
    b.push_back(125);
    ASSERT_FALSE(a != b);
    b.push_back(27);
    ASSERT_TRUE(a != b);
}

TEST(NotEquality, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(3);
    CCircularBufferExt<int, std::allocator<int>> b(3);
    a.push_back(718181818);
    a.push_back(46);
    b.push_back(718181818);
    b.push_back(46);
    ASSERT_FALSE(a != b);
    b.push_back(111);
    ASSERT_TRUE(a != b);
}

TEST(MoveConstructor, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(3);
    a.push_front(23);
    a.push_back(12);
    a.push_back(57);
    CCircularBuffer<int, std::allocator<int>> b(a);
    ASSERT_EQ(23, b[0]);
    ASSERT_EQ(12, b[1]);
    ASSERT_EQ(57, b[2]);
}

TEST(MoveConstructor, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(3);
    a.push_front(768);
    a.push_back(3);
    a.push_back(450);
    CCircularBufferExt<int, std::allocator<int>> b(a);
    ASSERT_EQ(768, b[0]);
    ASSERT_EQ(3, b[1]);
    ASSERT_EQ(450, b[2]);
}

TEST(Pop_front, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(2);
    a.push_front(123);
    a.push_back(56);
    a.pop_front();
    ASSERT_EQ(56, a[0]);
    ASSERT_EQ(a.size(), 1);
}

TEST(Pop_front, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(2);
    a.push_front(545);
    a.push_back(72);
    a.pop_front();
    ASSERT_EQ(72, a[0]);
    ASSERT_EQ(a.size(), 1);
}

TEST(Pop_back, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(2);
    a.push_front(34);
    a.push_back(2);
    a.pop_back();
    ASSERT_EQ(a.size(), 1);
    ASSERT_EQ(34, a[0]);
}

TEST(Pop_back, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(2);
    a.push_front(22);
    a.push_back(1);
    a.pop_back();
    ASSERT_EQ(a.size(), 1);
    ASSERT_EQ(22, a[0]);
}

TEST(Front, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(4);
    a.push_back(14);
    a.push_front(26);
    a.push_back(889);
    a.push_front(17);
    ASSERT_EQ(17, a.front());
}

TEST(Front, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(4);
    a.push_back(45);
    a.push_front(22);
    a.push_back(581);
    a.push_front(80);
    ASSERT_EQ(80, a.front());
}

TEST(Back, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(4);
    a.push_back(35);
    a.push_front(256);
    a.push_back(1000);
    a.push_front(15);
    ASSERT_EQ(1000, a.back());
}

TEST(Back, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(4);
    a.push_back(33);
    a.push_front(129);
    a.push_back(341);
    a.push_front(512);
    ASSERT_EQ(341, a.back());
}

TEST(Capacity, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(65);
    ASSERT_EQ(65, a.capacity());
}

TEST(Capacity, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(239);
    ASSERT_EQ(239, a.capacity());
    CCircularBufferExt<char, std::allocator<char>> b(2);
    b.push_back('a');
    b.push_back('b');
    b.push_back('c');
    ASSERT_EQ('a', b[0]);
    ASSERT_EQ('b', b[1]);
    ASSERT_EQ('c', b[2]);
    ASSERT_EQ(4, b.capacity());
}

TEST(Size, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(20);
    for (int i = 0; i < 12; ++i) {
        a.push_back(1);
    }
    ASSERT_EQ(12, a.size());
}

TEST(Size, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(45);
    for (int i = 0; i < 34; ++i) {
        a.push_back(1);
    }
    ASSERT_EQ(34, a.size());
    CCircularBufferExt<char, std::allocator<char>> b(2);
    b.push_back('a');
    b.push_back('b');
    b.push_back('c');
    ASSERT_EQ(3, b.size());
}

TEST(Empty, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(70);
    ASSERT_TRUE(a.empty());
    a.push_back(1);
    ASSERT_FALSE(a.empty());
}

TEST(Empty, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(32);
    ASSERT_TRUE(a.empty());
    a.push_back(333);
    ASSERT_FALSE(a.empty());
}

TEST(Iterator, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(3);
    a.push_back(23);
    a.push_back(14);
    a.push_front(1);
    ASSERT_EQ(1, *a.begin());
    ASSERT_EQ(14, *(a.begin() + 2));
    ASSERT_EQ(1, *(a.begin() + 3));
    ASSERT_EQ(2, (a.begin() + 2) - a.begin());
    ASSERT_EQ(23, (a.begin()[1]));
//    ASSERT_EQ(14,*(a.begin()-1));
    int sum = 0;
    for (auto i = a.begin(); i != a.end(); ++i) {
        sum += *(i);
    }
    ASSERT_EQ(38, sum);
    *a.begin() = 5;
    ASSERT_EQ(5, *a.begin());
}

TEST(Iterator, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(3);
    a.push_back(129);
    a.push_back(2);
    a.push_front(715);
    ASSERT_EQ(715, *a.begin());
    ASSERT_EQ(2, *(a.begin() + 2));
    ASSERT_EQ(715, *(a.begin() + 3));
    ASSERT_EQ(7, (a.begin() + 7) - a.begin());
    ASSERT_EQ(129, (a.begin()[1]));
    ASSERT_EQ(2, *(a.begin() - 1));
    int sum = 0;
    for (auto i = a.begin(); i != a.end(); ++i) {
        sum += *(i);
    }
    ASSERT_EQ(846, sum);
    *a.begin() = 10;
    ASSERT_EQ(10, *a.begin());
}


TEST(ConstIterator, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(3);
    a.push_back(210);
    a.push_back(6);
    a.push_front(47);
    ASSERT_EQ(47, *a.cbegin());
    ASSERT_EQ(6, *(a.cbegin() + 2));
    ASSERT_EQ(47, *(a.cbegin() + 3));
    ASSERT_EQ(4, (a.cbegin() + 4) - a.cbegin());
    ASSERT_EQ(210, (a.cbegin()[1]));
    ASSERT_EQ(6, *(a.cbegin() - 1));
    int sum = 0;
    for (auto i = a.cbegin(); i != a.cend(); ++i) {
        sum += *(i);
    }
    ASSERT_EQ(263, sum);
}

TEST(ConstIterator, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(3);
    a.push_back(224);
    a.push_back(801);
    a.push_front(12);
    ASSERT_EQ(12, *a.cbegin());
    ASSERT_EQ(801, *(a.cbegin() + 2));
    ASSERT_EQ(12, *(a.cbegin() + 3));
    ASSERT_EQ(26, (a.cbegin() + 26) - a.cbegin());
    ASSERT_EQ(224, (a.cbegin()[1]));
    ASSERT_EQ(801, *(a.cbegin() - 1));
    int sum = 0;
    for (auto i = a.cbegin(); i != a.cend(); ++i) {
        sum += *(i);
    }
    ASSERT_EQ(1037, sum);
}

TEST(Insert, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> tmp1(4);
    tmp1.push_back(1);
    tmp1.push_back(2);
    tmp1.push_back(3);
    tmp1.push_back(4);
    auto ans1 = tmp1.insert(tmp1.begin() + 2, 9);
    ASSERT_EQ(2, *(ans1 - 1));
    ASSERT_EQ(9, *(ans1));
    ASSERT_EQ(3, *(ans1 + 1));
    CCircularBuffer<int, std::allocator<int>> tmp2(4);
    tmp2.push_back(1);
    tmp2.push_back(2);
    tmp2.push_back(3);
    tmp2.push_back(4);
    auto ans2 = tmp2.insert(tmp2.begin() + 2, 3, 9);
    ASSERT_EQ(2, *(ans2 - 1));
    for (int i = 0; i < 3; ++i, ans2++) {
        ASSERT_EQ(9, *ans2);
    }
    CCircularBuffer<int, std::allocator<int>> tmp3(4);
    tmp3.push_back(1);
    tmp3.push_back(2);
    tmp3.push_back(3);
    tmp3.push_back(4);
    auto ans3 = tmp3.insert(tmp3.begin() + 1, {3, 9});
    ASSERT_EQ(1, *(ans3 - 1));
    ASSERT_EQ(3, *ans3);
    ASSERT_EQ(9, *(ans3 + 1));
}


TEST(Insert, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> tmp1(4);
    tmp1.push_back(1);
    tmp1.push_back(2);
    tmp1.push_back(3);
    tmp1.push_back(4);
    auto ans1 = tmp1.insert(tmp1.begin() + 2, 7);
    ASSERT_EQ(2, *(ans1 - 1));
    ASSERT_EQ(7, *(ans1));
    ASSERT_EQ(3, *(ans1 + 1));
    CCircularBufferExt<int, std::allocator<int>> tmp2(4);
    tmp2.push_back(1);
    tmp2.push_back(2);
    tmp2.push_back(3);
    tmp2.push_back(4);
    auto ans2 = tmp2.insert(tmp2.begin() + 2, 77, 7);
    ASSERT_EQ(2, *(ans2 - 1));
    for (int i = 0; i < 77; ++i, ans2++) {
        ASSERT_EQ(7, *ans2);
    }
    CCircularBufferExt<int, std::allocator<int>> tmp3(4);
    tmp3.push_back(1);
    tmp3.push_back(2);
    tmp3.push_back(3);
    tmp3.push_back(4);
    auto ans3 = tmp3.insert(tmp3.begin() + 1, {2, 8});
    ASSERT_EQ(1, *(ans3 - 1));
    ASSERT_EQ(2, *ans3);
    ASSERT_EQ(8, *(ans3 + 1));
}


TEST(Erase, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(4);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.erase(a.begin());
    size_t counter1 = 2;
    for (auto i = a.begin(); i != a.end(); ++i, ++counter1) {
        ASSERT_EQ(*i, counter1);
    }

    CCircularBuffer<int, std::allocator<int>> b(6);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);
    b.erase(a.begin(), a.begin() + 2);
    size_t counter2 = 3;
    for (auto i = b.begin(); i != b.end(); ++i, ++counter2) {
        ASSERT_EQ(*i, counter2);
    }
}

TEST(Erase, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(1);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.erase(a.begin());
    size_t counter1 = 2;
    for (auto i = a.begin(); i != a.end(); ++i, ++counter1) {
        ASSERT_EQ(*i, counter1);
    }

    CCircularBufferExt<int, std::allocator<int>> b(1);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);
    b.erase(a.begin(), a.begin() + 2);
    size_t counter2 = 3;
    for (auto i = b.begin(); i != b.end(); ++i, ++counter2) {
        ASSERT_EQ(*i, counter2);
    }
}

TEST(Swap, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(4);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    CCircularBuffer<int, std::allocator<int>> b(4);
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    CCircularBuffer<int, std::allocator<int>> ans1(a);
    CCircularBuffer<int, std::allocator<int>> ans2(b);
    a.swap(b);
    ASSERT_TRUE(a == ans2);
    ASSERT_TRUE(b == ans1);
}

TEST(Swap, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(4);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    CCircularBufferExt<int, std::allocator<int>> b(4);
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);
    a.push_back(1);
    CCircularBufferExt<int, std::allocator<int>> ans1(a);
    CCircularBufferExt<int, std::allocator<int>> ans2(b);
    a.swap(b);
    ASSERT_TRUE(a == ans2);
    ASSERT_TRUE(b == ans1);
}

TEST(Assign, CCircularBuffer) {
    CCircularBuffer<int, std::allocator<int>> a(4);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.asign(2, 1);
    for (auto i = a.begin(); i != a.end(); ++i) {
        ASSERT_EQ(1, *i);
    }
    CCircularBuffer<int, std::allocator<int>> b(4);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    CCircularBuffer<int, std::allocator<int>> c(2);
    c.push_back(9);
    c.push_back(9);
    b.asign(c.begin(), c.end());
    ASSERT_TRUE(b == c);
    CCircularBuffer<int, std::allocator<int>> d(4);
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    d.asign({1, 5, 9});
    ASSERT_EQ(1, *d.begin());
    ASSERT_EQ(5, *(d.begin() + 1));
    ASSERT_EQ(9, *(d.begin() + 2));
}


TEST(Assign, CCircularBufferExt) {
    CCircularBufferExt<int, std::allocator<int>> a(4);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.asign(2, 1);
    for (auto i = a.begin(); i != a.end(); ++i) {
        ASSERT_EQ(1, *i);
    }
    CCircularBufferExt<int, std::allocator<int>> b(4);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    CCircularBufferExt<int, std::allocator<int>> c(2);
    c.push_back(9);
    c.push_back(9);
    b.asign(c.begin(), c.end());
    ASSERT_TRUE(b == c);
    CCircularBufferExt<int, std::allocator<int>> d(4);
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    d.asign({1, 5, 9});
    ASSERT_EQ(1, *d.begin());
    ASSERT_EQ(5, *(d.begin() + 1));
    ASSERT_EQ(9, *(d.begin() + 2));
}


TEST(Test, CCircularBuffer) {
    CCircularBuffer<int> a(12);
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    a.push_back(10);
    a.push_back(11);
    a.push_back(12);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    std::sort(a.begin(),a.end());
    for(auto i:a){
        std::cout<<i<<' ';
    }
}