class LongInteger{
    // Compute (large_number % small_number)
    long long modLargeNumber(const string &a, long long b) {
        long long rem = 0;
        for (char c : a) {
            rem = (rem * 10 + (c - '0')) % b;
        }
        return rem;
    }

    // Euclidean algorithm for GCD
    long long gcdLargeSmall(string a, long long b) {
        if (b == 0) {
            // Convert string to remainder-free integer if it's short enough
            long long result = 0;
            for (char c : a)
                result = (result * 10 + (c - '0')) % 1000000007; // optional mod for display
            return result; // may overflow if a has >18 digits, but only for display
        }
        long long rem = modLargeNumber(a, b);
        return gcdLargeSmall(to_string(b), rem);
    }
}