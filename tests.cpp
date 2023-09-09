#include "mymap.h"
#include <vector>
#include <map>
#include <string>
#include <random>
#include <stdio.h>
#include "myrandom.h"
#include <gtest/gtest.h>


TEST(mymap, NumberOne) {
    //Default Constructor
    mymap<int, int> map; 
    mymap<int, char> map1;
    mymap<int, string> map2;

    int arr[] = { 10, 7, 8, 9, 4, 5, 3, 12, 13, 11 };
    int arr1[] = { 8, 4, 5, 3, 3, 1 };
    int order[] = { 3, 4, 5, 7, 8, 10, 11, 12, 13 };
    int vals[] = { 9, 1, 2, 3, 5, 6, 7, 7, 7, 8 };
    char vals1[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    string vals2[] = { "Bob", "Jack", "Isaak", "Max", "John", "Tyler" };
    //Put and Size
    for (int i = 0; i < 10; i++) {
        map.put(arr[i], vals[i]);
        map1.put(arr[i], vals1[i]);
    }
    for (int i = 0; i < 6; i++) {
        map2.put(arr1[i], vals2[i]);
    }
    EXPECT_EQ(map.Size(), 10); 
    EXPECT_EQ(map1.Size(), 10);
    EXPECT_EQ(map2.Size(), 5);
    //Contains
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(map.contains(arr[i]));
        EXPECT_TRUE(map1.contains(arr[i]));
    }

    EXPECT_FALSE(map.contains(99));
    EXPECT_FALSE(map1.contains(0));
    EXPECT_FALSE(map2.contains(10));
    //Get
    for (int i = 0; i < 10; i++) { 
        EXPECT_EQ(map.get(arr[i]), vals[i]);
        EXPECT_EQ(map1.get(arr[i]), vals1[i]);
    }
    //Duplicate
    EXPECT_EQ(map2.get(3), vals2[4]); 
    //ToString
    string str = "key: 3 value: 7\nkey: 4 value: 5\nkey: 5 value: 6\nkey: 7 value: 1\nkey: 8 value: 2\nkey: 9 value: 3\nkey: 10 value: 9\nkey: 11 value: 8\nkey: 12 value: 7\nkey: 13 value: 7\n";
    string str1 = "key: 1 value: Tyler\nkey: 3 value: John\nkey: 4 value: Jack\nkey: 5 value: Isaak\nkey: 8 value: Bob\n";
    EXPECT_EQ(str, map.toString());
    EXPECT_EQ(str1, map2.toString());
    //Bracket Operator
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(map[arr[i]], vals[i]);
        EXPECT_EQ(map1[arr[i]], vals1[i]);
    }
    //Duplicate
    EXPECT_EQ(map2[arr1[3]], vals2[4]);
    //ToVector
    vector<pair<int, int>> v1;
    v1.push_back(make_pair(3, 7));
    v1.push_back(make_pair(4, 5));
    v1.push_back(make_pair(5, 6));
    v1.push_back(make_pair(7, 1));
    v1.push_back(make_pair(8, 2));
    v1.push_back(make_pair(9, 3));
    v1.push_back(make_pair(10, 9));
    v1.push_back(make_pair(11, 8));
    v1.push_back(make_pair(12, 7));
    v1.push_back(make_pair(13, 7));

    EXPECT_EQ(v1, map.toVector());

    //Clear
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST(mymap, NumberTwo) {
    // netid: rshah268
    mymap<int, int> m1;
    mymap<int, int> m2;
    //Stress Testing
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int key = randomInteger(0, 100000);
        int val = i;
        m1.put(key, val);
        if (i % 2) {
            m2.put(val, key);
        }
    }
    //Shouldn't Equal because of if(i%2)
    ASSERT_NE(m1.Size(), m2.Size()); 
    m2 = m1;
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());
    mymap<int, int> m3;
    //Equal Operator
    m3 = m2;
    ASSERT_EQ(m3.Size(), m2.Size());
    ASSERT_EQ(m3.toString(), m2.toString());
    //Clear
    m3.clear();
    m1.clear();
    //m2 was not cleared but m1 was
    ASSERT_NE(m1.Size(), m2.Size());
    ASSERT_EQ(m1.Size(), 0);
}

TEST(mymap, NumberThree) {
    mymap<int, int> m1;
    mymap<int, int> m2;
    int arr[] = { 7, 8, 10, 11, 18, 20, 18, 7 };
    int arr1[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    int vals[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    for (int i = 0; i < 8; i++) {
        m1.put(arr[i], vals[i]);
        m2.put(arr1[i], vals[i]);
    }
    EXPECT_EQ(m1.Size(), 6);
    EXPECT_EQ(m2.Size(), 1);
    ASSERT_EQ(m1.get(7), 8);
    EXPECT_TRUE(m1.contains(18));
    EXPECT_FALSE(m2.contains(2));

    EXPECT_EQ(m1.get(0), 0);
    EXPECT_EQ(m2.get(100), 0);
    //Increases size because the values is not in either m1 or m2
    EXPECT_EQ(m1[0], 0);
    EXPECT_EQ(m2[2], 0);

    EXPECT_EQ(m1.Size(), 7);
    EXPECT_EQ(m2.Size(), 2);
    
    mymap<int, int>m3;
    int arr2[] = { 6, 7, 8, 9, 11, 10, 20, 17 };
    for (int i = 0; i < 8; i++) {
        m3.put(arr2[i], vals[i]);
    }
    
    string str = "key: 0 value: 0\nkey: 7 value: 8\nkey: 8 value: 2\nkey: 10 value: 3\nkey: 11 value: 4\nkey: 18 value: 7\nkey: 20 value: 6\n";
    string str1 = "key: 1 value: 8\nkey: 2 value: 0\n";

    EXPECT_EQ(m1.toString(), str);
    EXPECT_EQ(m2.toString(), str1);

    string str2 = "key: 0 nL: 0 nR: 0\nkey: 7 nL: 0 nR: 0\nkey: 8 nL: 0 nR: 0\nkey: 10 nL: 0 nR: 0\nkey: 11 nL: 0 nR: 0\nkey: 18 nL: 0 nR: 0\nkey: 20 nL: 0 nR: 0\n";
    string str3 = "key: 1 nL: 0 nR: 0\nkey: 2 nL: 0 nR: 0\n";
    //Testing CheckBalance
    EXPECT_EQ(m1.checkBalance(), str2);
    EXPECT_EQ(m2.checkBalance(), str3);
    //Testing ToVector
    vector<pair<int, int>>v1;
    v1.push_back(make_pair(0, 0));
    v1.push_back(make_pair(7, 8));
    v1.push_back(make_pair(8, 2));
    v1.push_back(make_pair(10, 3));
    v1.push_back(make_pair(11, 4));
    v1.push_back(make_pair(18, 7));
    v1.push_back(make_pair(20, 6));
    EXPECT_EQ(v1, m1.toVector());
}

TEST(mymap, NumberFour) {
    //Float and Double cases
    mymap<float, float>m1;
    mymap<double, double> m2;
    float arr[] = { 7.34, 4.98, 8.22, 1.23, 10.983, 5.76 };
    double arr1[] = { 8.565, 8.564, 8.567, 9.1766, 3.444, 0.119 };
    float order[] = { 1.23, 4.98, 5.76, 7.34, 8.22, 10.983 };
    double order1[] = { 0.119, 3.444, 8.564, 8.565, 8.567, 9.1766 };
    for (int i = 0; i < 6; i++) {
        m1.put(arr[i], arr[i]);
        m2.put(arr1[i], arr1[i]);
    }

    EXPECT_EQ(m1.Size(), 6);
    EXPECT_EQ(m2.Size(), 6);
    EXPECT_EQ(m1.Size(), m2.Size());

    int i = 0;
    for (auto key : m1) {
        EXPECT_EQ(order[i++], key);
    }
    i = 0;
    for (auto key : m2) {
        EXPECT_EQ(order1[i++], key);
    }

    EXPECT_TRUE(m1.contains(7.34));
    EXPECT_FALSE(m1.contains(7));
    EXPECT_TRUE(m2.contains(8.567));
    EXPECT_FALSE(m2.contains(8));
    //Values not in map
    m1[1];
    EXPECT_EQ(m1.Size(), 7);
    m2[8];
    EXPECT_EQ(m2.Size(), 7);

    string str = "key: 1 value: 0\nkey: 1.23 value: 1.23\nkey: 4.98 value: 4.98\nkey: 5.76 value: 5.76\nkey: 7.34 value: 7.34\nkey: 8.22 value: 8.22\nkey: 10.983 value: 10.983\n";
    string str1 = "key: 0.119 value: 0.119\nkey: 3.444 value: 3.444\nkey: 8 value: 0\nkey: 8.564 value: 8.564\nkey: 8.565 value: 8.565\nkey: 8.567 value: 8.567\nkey: 9.1766 value: 9.1766\n";

    EXPECT_EQ(str, m1.toString());
    EXPECT_EQ(str1, m2.toString());

    string str2 = "key: 1 nL: 0 nR: 0\nkey: 1.23 nL: 0 nR: 0\nkey: 4.98 nL: 0 nR: 0\nkey: 5.76 nL: 0 nR: 0\nkey: 7.34 nL: 0 nR: 0\nkey: 8.22 nL: 0 nR: 0\nkey: 10.983 nL: 0 nR: 0\n";
    string str3 = "key: 0.119 nL: 0 nR: 0\nkey: 3.444 nL: 0 nR: 0\nkey: 8 nL: 0 nR: 0\nkey: 8.564 nL: 0 nR: 0\nkey: 8.565 nL: 0 nR: 0\nkey: 8.567 nL: 0 nR: 0\nkey: 9.1766 nL: 0 nR: 0\n";

    EXPECT_EQ(str2, m1.checkBalance());
    EXPECT_EQ(str3, m2.checkBalance());

    vector<pair<float, float>>v1;
    v1.push_back(make_pair(1, 0));
    v1.push_back(make_pair(1.23, 1.23));
    v1.push_back(make_pair(4.98, 4.98));
    v1.push_back(make_pair(5.76, 5.76));
    v1.push_back(make_pair(7.34, 7.34));
    v1.push_back(make_pair(8.22, 8.22));
    v1.push_back(make_pair(10.983, 10.983));

    EXPECT_EQ(v1, m1.toVector());

}

TEST(mymap, NumberFive) {
    //netid: lsasu2
    mymap<int, string> test;
    map<int, string> omap;
    int n = 10;
    int arr[] = { 40, 25, 60, 18, 35, 80, 30, 38, 50, 70 };

    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap.emplace(arr[i], value);
    }
    for (int i = 0; i < n; i++) {
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    //Value not in map
    for (int i = 0; i < n; i++) {
        ASSERT_EQ(test[i * 1000], "");
        ASSERT_EQ(test.Size(), n + i + 1);
    }

    //Duplicate values
    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(randomInteger(0, 40));
        test.put(arr[i], value);
        omap[arr[i]] = value;
    }
    for (int i = 0; i < n; i++) {
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }
}


TEST(mymap, NumberSix) {
    //tkoope2
    mymap<int, int> m;
    mymap<int, int> m2;

    //Populate 1 and 2
    int key, value, high, low, modOp;
    int arrSize = rand() % 100;

    string mOriginal, m2Original;

    //Populate m
    high = 500;
    low = 1;
    modOp = (high - (low + 1)) + low;
    for (int i = 0; i < arrSize; i++) {
        key = rand() % modOp;
        value = rand() % modOp;
        m.put(key, value);
    }

    //Populate m2
    high = 1000;
    low = 500;
    modOp = (high - (low + 1)) + low;
    for (int i = 0; i < arrSize; i++) {
        key = rand() % modOp;
        value = rand() % modOp;
        m2.put(key, value);
    }

    m = m2;

    EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
    EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
    EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n" << "M:\n" << m.toString() << "\nM2:\n" << m2.toString() << endl;
}

TEST(mymap, NumberSeven) {
    //tkoope2
    mymap<int, int> m;
    map<int, int> correct;
    vector<int> keys;
    int key;
    int val;
    int arrSize = 15;
    int high = 500, low = 0;
    int modOp = (high - (low + 1)) + low;


    //Populate
    for (int i = 0; i < arrSize; i++) {
        key = rand() % modOp;
        val = rand() % modOp;

        keys.push_back(key);

        m.put(key, val);
        correct[key] = val;
    }

    EXPECT_EQ(m.Size(), correct.size()) << "mymap != map\n";

    mymap<int, int> m2 = m;
    EXPECT_EQ(m.toString(), m2.toString()) << "Copy operator formating off\n";
    EXPECT_NE(m2.Size(), correct.size()) << "M2's size does not match correct's\n";

    //Both have the same return value on keys
    int compA;
    int compB;
    for (auto& k : keys) {
        compA = m2[k];
        compB = correct[k];
        EXPECT_EQ(compA, compB) << compA << " != " << compB << "\t Incorrect Copy Constructor\n";
    }
}

// Testing Put with random int key (Testing Size and toString)
TEST(mymap, NumberEight) {
    // netid: msiddi73
    map<int, int> m;
    mymap <int, int> mymap;
    stringstream s;

    int randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;

    for (int i = 0; i < 35; i++) {

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++) {

            randomKey = randomInteger(0, 100);
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m) {
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();

    }

}

// Testing put with random char key (Testing Size and toString)
TEST(mymap, NumberNine) {
    // netid: msiddi73

    map<char, int> m;
    mymap <char, int> mymap;
    stringstream s;

    char randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;


    for (int i = 0; i < 35; i++) {

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++) {

            randomKey = randomInteger(65, 90); // get uppercase characthers
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m) {
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();

    }

}

TEST(mymap, NumberTen) {
    //netID: skowa3
    mymap<int, int> m1;
    mymap<int, int> m2;

    int n = 15;
    stringstream ss;
    int temp;
    for (int i = 0; i < n; i++) {
        m1.put(i, i);
        ss << "key: " << i << " value: " << i << "\n";
    }
    //test size
    EXPECT_EQ(m1.Size(), n);
    //test contains
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(m1.contains(i), true);
    }
    //test get
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(m1.get(i), i);
    }
    //test iterator
    int order[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
    int i = 0;
    for (auto key : m1) {
        EXPECT_EQ(order[i++], key);
    }


    // test toString
    EXPECT_EQ(m1.toString(), ss.str());

    m2 = m1;
    //test size
    EXPECT_EQ(m2.Size(), n);
    //test contains
    for (int i = 0; i < n; i++) {
        int key = randomInteger(0, 14);
        EXPECT_EQ(m2.contains(key), true);
    }
    //test toString
    EXPECT_EQ(m2.toString(), ss.str());

    //test clear
    m1.clear();
    m2.clear();
    EXPECT_EQ(m1.Size(), 0);
    EXPECT_EQ(m2.Size(), 0);

}