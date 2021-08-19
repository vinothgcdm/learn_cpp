int main(void)
{
    /*  error: static assertion failed: 1 is not equal to 2 */
    static_assert(1 == 2, "1 is not equal to 2");
    return 0;
}
