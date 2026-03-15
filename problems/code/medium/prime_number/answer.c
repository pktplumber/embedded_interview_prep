#include <stdbool.h>

// A prime number has no divisors
// Idea here is to check if the number is two, then check if all
// odd number up to the square root of 'num' is a factor
bool is_prime(int num)
{
  // Numbers less than or equal to 1 are not prime by definition
  if (num < 2)
  {
    return false;
  }

  // Two is the only even prime number
  if (num == 2)
  {
    return true;
  }

  // All even numbers after 2 are not prime. 
  // Note: could do modulo, but checking if the first bit is 0
  // is more efficient
  if ((num & 1) == 0)
  {
    return false;
  }

  // Check if 'num' is divisible by any odd number up to its square root
  for (int i = 3; i*i <= num; i += 2)
  {
    if (num % i == 0)
    {
      // Divisor found, not prime
      return false;
    }
  }

  // No divisor found, prime
  return true;
}