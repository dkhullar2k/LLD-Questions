# Mutex & Lock Summary

## 1. What is a mutex?

A mutex (**Mutual Exclusion**) is a synchronization object that protects a shared resource.

Think of it as a door to a room containing shared data:

- **Mutex** = the door
- **`lock()`** = lock the door and enter
- **`unlock()`** = leave the room and unlock the door
- **Critical section** = the code inside the room that accesses shared data

## 2. Why do we need a mutex?

Without a mutex, two threads can modify the same shared data simultaneously, causing race conditions.

Only one thread should execute a critical section at a time.

## 3. Why not one global mutex?

A single global mutex is correct, but it is not scalable:

```text
Global mutex
    🔒
     |
Entire allowRequests()
```

If User 1 is updating their bucket, User 2 and User 3 must wait—even though they are working with different buckets.

## 4. Why separate mutexes?

There are two distinct shared resources:

1. The `unordered_map`, which stores the User → Bucket mapping.
2. Each `Bucket`, which stores that user's tokens and timestamp.

Each shared resource gets its own mutex:

```text
                RateLimiter

           unordered_map
                🚪
            mapMutex

        /        |        \
    Bucket1   Bucket2   Bucket3
       🚪         🚪         🚪
 bucketMutex1 bucketMutex2 bucketMutex3
```

This allows:

- Requests for different users to execute concurrently.
- Requests for the same user to be serialized by that user's bucket mutex.

## 5. Where should the locks be?

```cpp
Bucket* bucket;

// Protect the map.
{
    lock(mapMutex);

    if (bucket doesn't exist)
        create bucket;

    bucket = mp[userId];

    unlock(mapMutex);
}

// Protect this user's bucket.
{
    lock(bucket->bucketMutex);

    refill tokens;

    if (enough tokens)
        consume tokens;

    update lastAccessedTime;

    unlock(bucket->bucketMutex);
}
```

In real C++, prefer `std::lock_guard<std::mutex>` instead of manual `lock()`/`unlock()`. The mutex is then released automatically if the function returns early or throws an exception.
