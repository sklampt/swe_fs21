#include "gtest/gtest.h"
#include "common/exceptions/ZombieException.h"

TEST(Exceptions, Zombie_Exception_Constructor)
{
    std::string test_message = "Test";
    ZombieDiceException exception(test_message);
    ASSER_STREQ(exception.what(),  "Test");
}
