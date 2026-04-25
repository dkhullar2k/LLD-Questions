# Design Rate Limiter

A simple implementation of a rate limiter using the Token Bucket algorithm in C++.

## Description

This project demonstrates a thread-safe rate limiter that controls the rate of requests per user using a token bucket approach. Each user has their own bucket with a defined capacity and refill rate, allowing for burst requests while maintaining an overall rate limit.

## Features

- **Per-user rate limiting**: Each user gets their own token bucket.
- **Thread-safe operations**: Uses mutexes to handle concurrent requests safely.
- **Configurable parameters**: Bucket capacity and refill rate can be adjusted.
- **Token bucket algorithm**: Supports burst requests with gradual token replenishment.

## Build Instructions

Compile the source files using g++ (requires C++11 or later):

```bash
g++ main.cpp RateLimiter.cpp Bucket.cpp -o main
```

## Run Instructions

Execute the compiled program:

```bash
./main
```

This will run a demonstration that sends 10 rapid requests, waits 2 seconds, then sends 5 more requests, showing how the rate limiter blocks excess requests.

## Usage

The `RateLimiter` class provides an `isAllowed(user)` method that returns `true` if the request is allowed, `false` otherwise.

### Example Code

```cpp
#include "RateLimiter.cpp"
#include "Bucket.cpp"

RateLimiter limiter;
std::string user = "user1";

if (limiter.isAllowed(user)) {
    // Process the request
    std::cout << "Request allowed" << std::endl;
} else {
    // Block the request
    std::cout << "Request blocked" << std::endl;
}
```

### Configuration

In `RateLimiter.cpp`, modify the bucket creation:

```cpp
Bucket* newBucket = new Bucket(capacity, refillRate);
```

- `capacity`: Maximum number of tokens (allows burst requests)
- `refillRate`: Tokens added per millisecond

## Architecture

- **`Bucket.cpp`**: Implements the token bucket logic. Manages token count, refills tokens based on time elapsed, and checks if requests can be allowed.
- **`RateLimiter.cpp`**: Manages a map of user buckets, creates new buckets on demand, and ensures thread safety.
- **`main.cpp`**: Provides a test harness to demonstrate the rate limiter's behavior.

## Algorithm Details

The token bucket algorithm works as follows:

1. Each bucket starts with a full capacity of tokens.
2. When a request arrives, tokens are refilled based on elapsed time since the last refill.
3. If there are sufficient tokens (> 0), the request is allowed and one token is consumed.
4. Tokens are replenished at a constant rate over time.

This allows for burst traffic while maintaining an average rate limit.

## Dependencies

- C++ compiler with C++11 support (e.g., g++ 4.8+)
- Standard library headers: `<iostream>`, `<chrono>`, `<thread>`, `<unordered_map>`, `<mutex>`