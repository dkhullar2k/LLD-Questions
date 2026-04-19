# Payment System - Low Level Design

A comprehensive payment processing system demonstrating key design patterns and best practices in C++. This system handles payment processing, refunds, idempotency, retry logic, and integration with multiple payment gateways.

## Table of Contents

- [Overview](#overview)
- [Architecture](#architecture)
- [Class Diagram](#class-diagram)
- [Design Patterns](#design-patterns)
- [File Structure](#file-structure)
- [Getting Started](#getting-started)
- [Usage Example](#usage-example)

## Overview

The Payment System is designed to handle complex payment operations with the following capabilities:

✅ **Multiple Payment Methods** - Support for different payment types (Card, UPI, etc.)  
✅ **Multiple Gateways** - Integration with various payment providers (Razorpay, Stripe, etc.)  
✅ **Idempotency** - Prevents duplicate payment processing  
✅ **Retry Logic** - Automatic retries for failed external gateway calls  
✅ **Refund Handling** - Complete refund workflow management  
✅ **Flexible Architecture** - Easy to extend with new payment methods and gateways  

## Architecture

### System Layers

The system is organized into 5 distinct layers:

```
┌─────────────────────────────────────────────┐
│      LAYER 5: FACTORY PATTERN               │
│(PaymentMethodFactory, PaymentGatewayFactory)│
└─────────────────────────────────────────────┘
                      ↓
┌─────────────────────────────────────────────┐
│   LAYER 4: PRIMARY SERVICES                 │
│  (PaymentService, RefundService)            │
│  - Orchestrates complete workflows          │
│  - Contains internal services               │
└─────────────────────────────────────────────┘
                      ↓
┌─────────────────────────────────────────────┐
│   LAYER 3: SUPPORTING SERVICES              │
│  (PaymentProcessor, IdempotencyService,     │
│   RetryHandler)                             │
│  - Provides specific functionality          │
└─────────────────────────────────────────────┘
                      ↓
┌─────────────────────────────────────────────┐
│   LAYER 2: STRATEGY IMPLEMENTATIONS         │
│  (CardPayment, UPIPayment,                  │
│   RazorpayGateway, StripeGateway)           │
│  - Concrete implementations                 │
└─────────────────────────────────────────────┘
                      ↓
┌─────────────────────────────────────────────┐
│   LAYER 1: DOMAIN MODEL                     │
│  (Payment, PaymentStatus)                   │
│  - Core data structures                     │
└─────────────────────────────────────────────┘
```

## Class Diagram

![Payment System Architecture] (image.png)

### Relationship Legend

- **◁ (Inheritance)** - Child class implements/inherits from parent interface/class
- **◆ (Composition)** - Parent class contains and owns the child class
- **→ (Dependency)** - Class uses another class for specific functionality

## Design Patterns

### 1. **Strategy Pattern**
- **Payment Methods**: `PaymentMethod` interface with `CardPayment`, `UPIPayment` implementations
- **Payment Gateways**: `PaymentGateway` interface with `RazorpayGateway`, `StripeGateway` implementations
- **Benefit**: Switch between different implementations at runtime without changing client code

### 2. **Factory Pattern**
- **PaymentMethodFactory**: Creates appropriate `PaymentMethod` based on type string
- **PaymentGatewayFactory**: Creates appropriate `PaymentGateway` based on type string
- **Benefit**: Centralized object creation, easy to add new types

### 3. **Template Method Pattern**
- **RetryHandler**: Uses template method with lambda functions for flexible execution
- **Benefit**: Reusable retry logic for any callable function

### 4. **Dependency Injection**
- Services receive dependencies through constructors
- `PaymentService` receives `PaymentGateway` as dependency
- **Benefit**: Loose coupling, easy testing and maintenance

### 5. **Composition Over Inheritance**
- `PaymentService` contains `PaymentProcessor`, `IdempotencyService`, `RetryHandler`
- **Benefit**: Flexible component reuse, cleaner architecture

## File Structure

```
Design Payment System/
├── Payment.h                 # Core payment data model and status enum
├── PaymentMethod.h          # Strategy interface & implementations (Card, UPI)
├── PaymentGateway.h         # Gateway interface & implementations (Razorpay, Stripe)
├── PaymentProcessor.h       # Payment validation and processing logic
├── IdempotencyService.h     # Duplicate request detection
├── RetryHandler.h           # Retry logic with templates
├── PaymentService.h         # Main payment orchestration service
├── RefundService.h          # Refund processing service
├── Factory.h                # Factory implementations
├── main.cpp                 # Example usage
├── image.png                # Architecture diagram
└── README.md               # This file
```

## Getting Started

### Prerequisites
- C++11 or later
- Standard C++ library

### Compilation

```bash
g++ -std=c++11 main.cpp -o payment_system
```

### Running

```bash
./payment_system
```

## Usage Example

### Basic Payment Processing

```cpp
#include "PaymentService.h"
#include "Factory.h"

int main(){
    // Create payment
    Payment payment("p1", "u1", "INR", 5000);
    
    // Create payment method using factory
    PaymentMethod* method = PaymentMethodFactory::create("UPI");
    
    // Create gateway using factory
    PaymentGateway* gateway = PaymentGatewayFactory::create("RAZORPAY");
    
    // Create payment service
    PaymentService paymentService(gateway);
    
    // Process payment with idempotency key
    bool result = paymentService.makePayment(payment, method, "unique_key_123");
    
    // Check payment status
    cout << "Payment Status: " << (int)payment.status << endl;
    
    return 0;
}
```

### Refund Processing

```cpp
// Create refund service with same gateway
RefundService refundService(gateway);

// Process refund (only works if payment was successful)
bool refundResult = refundService.refund(payment);

if(refundResult) {
    cout << "Refund successful!" << endl;
}
```

## Payment Status Flow

```
INITIATED → PENDING → SUCCESS  → (can be refunded to REFUNDED)
                   ↓
                 FAILED (no refund possible)
```

## Key Features Explained

### 1. **Idempotency Service**
Prevents duplicate payments when the same request is retried.
```cpp
// Multiple calls with same key won't reprocess
paymentService.makePayment(payment, method, "key_123"); // Processes
paymentService.makePayment(payment2, method, "key_123"); // Skipped - duplicate
```

### 2. **Retry Handler**
Automatically retries failed external gateway calls (default: 3 retries).
```cpp
// Built into PaymentService.makePayment()
// Transparently retries gateway.charge() if it fails
```

### 3. **Payment Processor**
- Validates payment method
- Executes payment method processing
- Sets payment status

### 4. **Refund Service**
- Only refunds successful payments
- Marks payment as REFUNDED
- Integrates with payment gateway

## Extending the System

### Adding a New Payment Method

1. Create new class inheriting from `PaymentMethod`:
```cpp
class WalletPayment: public PaymentMethod {
    bool validate(Payment& payment) override { /* ... */ }
    bool process(Payment& payment) override { /* ... */ }
};
```

2. Update `PaymentMethodFactory::create()`:
```cpp
if(type=="WALLET") {
    return new WalletPayment();
}
```

### Adding a New Gateway

1. Create new class inheriting from `PaymentGateway`:
```cpp
class SquareGateway: public PaymentGateway {
    bool charge(Payment& payment) override { /* ... */ }
    bool refund(Payment& payment) override { /* ... */ }
};
```

2. Update `PaymentGatewayFactory::create()`:
```cpp
if(type=="SQUARE") {
    return new SquareGateway();
}
```

## Best Practices Demonstrated

✅ Separation of Concerns - Each class has single responsibility  
✅ Open/Closed Principle - Open for extension, closed for modification  
✅ Liskov Substitution - Derived classes can replace base classes  
✅ Interface Segregation - Focused, minimal interfaces  
✅ Dependency Inversion - Depend on abstractions, not concretions  
✅ DRY (Don't Repeat Yourself) - Reusable components  
✅ SOLID Principles - Well-designed architecture  

## Error Handling

The system handles failures at multiple levels:
- **Payment Method Validation**: Validates payment details
- **Gateway Failures**: Automatic retry with exponential backoff concept
- **Refund Constraints**: Only refunds successful payments
- **Idempotency**: Prevents duplicate processing of same request

## Thread Safety

Note: Current implementation is not thread-safe. For multi-threaded environments, consider:
- Using thread-safe containers for `IdempotencyService`
- Adding locks around critical sections
- Using atomic operations for payment status